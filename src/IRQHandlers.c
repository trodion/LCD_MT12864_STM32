#include "stm32f100xb.h"
#include "IRQHandlers.h"
#include "graphics.h"


#define H(cnt) ((cnt) / 360000)
#define M(cnt) ((cnt) / 6000)
#define S(cnt) ((cnt) / 100)
#define KEY_A (GPIOA->IDR & GPIO_IDR_IDR0)
#define KEY_B (GPIOB->IDR & GPIO_IDR_IDR15) 


struct time {
	uint32_t h, m, s; 
	/* Кол-во миллисекунд, прошедшее для "Белого" и для "Черного"*/
	uint32_t cnt_white, cnt_black; 
	/* Кол-во митнут, часов, с которых начинается отсчёт */
	uint8_t m_max, h_max;
	uint32_t stop;
	char status;
} t;


void TIM6_DAC_IRQHandler(void) {
	static uint32_t cnt_white = 5900; // Кол-во миллисекунд, прошедшее для "Белого"
	static uint32_t cnt_black = 5900; // Кол-во миллисекунд, прошедшее для "Черного"
	
	// Сбросить событие обновления
	TIM6->SR &= ~TIM_SR_UIF;
	
	if (KEY_A) t.status = 'w';
	else if (!KEY_B) t.status = 'b';
	
	if (t.status == 'w') {
		cnt_white += 1;
		t.s = 59 - (S(cnt_white) % 60);
		t.m = t.m_max - (M(cnt_white) % 60);
		t.h = t.h_max - (H(cnt_white) % 60);
	} else if (t.status == 'b') {
		cnt_black += 1;
		t.s = 59 - (S(cnt_black) % 60);
		t.m = t.m_max - (M(cnt_black) % 60);
		t.h = t.h_max - (H(cnt_black) % 60);
	}
	// Закончилось время у одного из игроков
	if (cnt_white == t.stop || cnt_black == t.stop) TIM6->CR1 &= ~TIM_CR1_CEN;
}

void TIM7_IRQHandler(void) {
	if (t.status == 'w'){
		draw_number(t.s, w_s, w_s + 6); // Вывод секунд
		draw_number(t.m, w_m, w_m + 6); // Вывод минут
		draw_number(t.h, w_h, w_h + 6); // Вывод часов
	} else if (t.status == 'b') {
		draw_number(t.s, b_s, b_s + 6);
		draw_number(t.m, b_m, b_m + 6);
		draw_number(t.h, b_h, b_h + 6);
	}

	// Сбросить событие обновления
	TIM7->SR &= ~TIM_SR_UIF;
}

void init_time() {
	t.h_max = mode02.time_h;
	t.m_max = mode02.time_m;
	t.stop = (t.m_max + (t.h_max * 60) + 1) * 6000 - 100;
	t.status = 'w';
}