#include "stm32f100xb.h"
#include "IRQHandlers.h"
#include "lcd_driver.h"
#include "graphics.h"

#define H(cnt) ((cnt) / 360000)
#define M(cnt) ((cnt) / 6000)
#define S(cnt) ((cnt) / 100)
#define KEY_A (GPIOA->IDR & GPIO_IDR_IDR0)
#define KEY_B (GPIOB->IDR & GPIO_IDR_IDR15) 

struct time {
	uint32_t h, m, s;
	char status;
} t = {.status = 'w'};

void TIM6_DAC_IRQHandler(void){
	static uint32_t cnt_white = 0; // Кол-во миллисекунд, прошедшее для "Белого"
	static uint32_t cnt_black = 0; // Кол-во миллисекунд, прошедшее для "Черного"
		
	// Сбросить событие обновления
	TIM6->SR &= ~TIM_SR_UIF;
	
	if (KEY_A) t.status = 'w';
	else if (!KEY_B) t.status = 'b';
	
	if (t.status == 'w') {
		cnt_white += 1;
		t.s = 59 - (S(cnt_white) % 60);
		t.m = 59 - (M(cnt_white) % 60);
		t.h = 2 - (H(cnt_white) % 60);
	} else if (t.status == 'b') {
		cnt_black += 1;
		t.s = 59 - (S(cnt_black) % 60);
		t.m = 59 - (M(cnt_black) % 60);
		t.h = 2 - (H(cnt_black) % 60);
	}
	// Закончилось время у одного из игроков
	if (cnt_white == 1079999 || cnt_black == 1079999) TIM6->CR1 &= ~TIM_CR1_CEN;
}

void TIM7_IRQHandler(void) {
	if (t.status == 'w'){
		draw_number(t.s, 49, 55); // Вывод секунд
		draw_number(t.m, 34, 40); // Вывод минут
		draw_number(t.h, 19, 25); // Вывод часов
	} else if (t.status == 'b') {
		draw_number(t.s, 99, 105);
		draw_number(t.m, 84, 90);
		draw_number(t.h, 69, 75);
	}

	// Сбросить событие обновления
	TIM7->SR &= ~TIM_SR_UIF;
}
