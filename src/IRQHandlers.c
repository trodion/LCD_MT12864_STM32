#include "stm32f100xb.h"
#include "IRQHandlers.h"
#include "graphics.h"


#define H(cnt) ((cnt) / 360000)
#define M(cnt) ((cnt) / 6000)
#define S(cnt) ((cnt) / 100)
#define KEY_A (GPIOA->IDR & GPIO_IDR_IDR0)
#define KEY_B (GPIOB->IDR & GPIO_IDR_IDR15)

#define update_watch(cnt) t.s = S(cnt) % 60;\
						  t.m = M(cnt) % 60;\
					 	  t.h = H(cnt);\

#define update_screen_w draw_number(t.s, w_s, w_s + 6);\
						draw_number(t.m, w_m, w_m + 6);\
						draw_number(t.h, w_h, w_h + 6);\

#define update_screen_b draw_number(t.s, b_s, b_s + 6);\
						draw_number(t.m, b_m, b_m + 6);\
						draw_number(t.h, b_h, b_h + 6);\


struct time {
	uint32_t h, m, s; 
	/* Время, с которого начинается отсчет */
	uint32_t cnt_white, cnt_black; 
	char status;
} t;


void TIM6_DAC_IRQHandler(void) {	
	// Сбросить событие обновления
	TIM6->SR &= ~TIM_SR_UIF;

	if (t.status == 'w') {
		t.cnt_white -= 1;
		update_watch(t.cnt_white);
	} else if (t.status == 'b') {
		t.cnt_black -= 1;
		update_watch(t.cnt_black);
	}
	
	if (KEY_A && t.status == 'b'){
		t.cnt_black += conf.adding_time;
		update_watch(t.cnt_black);
		update_screen_b;
		t.status = 'w';
	} 
	else if (!KEY_B && t.status == 'w'){
		t.cnt_white += conf.adding_time;
		update_watch(t.cnt_white);
		update_screen_w
		t.status = 'b';
	} 
	
	// Закончилось время у одного из игроков
	if (t.cnt_white < 100 || t.cnt_black < 100) TIM6->CR1 &= ~TIM_CR1_CEN;
}

void TIM7_IRQHandler(void) {
	if (t.status == 'w'){
		update_screen_w
	} else if (t.status == 'b') {
		update_screen_b
	}

	// Сбросить событие обновления
	TIM7->SR &= ~TIM_SR_UIF;
}

void init_time() {
	t.cnt_white = conf.time_ms;
	t.cnt_black = conf.time_ms;
	t.status = 'w';
}
