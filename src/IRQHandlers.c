#include "stm32f100xb.h"
#include "IRQHandlers.h"
#include "lcd_driver.h"
#include "graphics.h"

#define H(cnt) ((cnt) / 360000)
#define M(cnt) ((cnt) / 6000)
#define S(cnt) ((cnt) / 100)
#define KEY_A (GPIOA->IDR & GPIO_IDR_IDR0)
#define KEY_B (GPIOB->IDR & GPIO_IDR_IDR15) 


void EXTI0_IRQHandler(void) {
	/* Обработчик прерывания от линии EXTI0, 
	   Подлкюченной к кнопке PA0 */
	TIM6->CR1 ^= TIM_CR1_CEN;
	TIM7->CR1 ^= TIM_CR1_CEN;
	EXTI->PR &= 0x01; // Произошла генерация запроса на прерывания, нужно сбросить
	ms_delay(1000);
}

void TIM6_DAC_IRQHandler(void){
	static uint32_t cnt_white = 0; // Кол-во миллисекунд, прошедшее для "Белого"
	static uint32_t cnt_black = 0; // Кол-во миллисекунд, прошедшее для "Черного"
	static char status = 'w';

	if (KEY_A) status = 'w';
	else if (!KEY_B) status = 'b';
	
	if (status == 'w') {
		cnt_white += 1;
		draw_number(59 - (S(cnt_white) % 60), 49, 55); // Вывод секунд
		draw_number(59 - (M(cnt_white) % 60), 34, 40); // Вывод минут
		draw_number(2 - (H(cnt_white) % 60), 19, 25); // Вывод часов
	} else if (status == 'b') {
		cnt_black += 1;
		draw_number(59 - (S(cnt_black) % 60), 99, 105);
		draw_number(59 - (M(cnt_black) % 60), 84, 90);
		draw_number(2 - (H(cnt_black) % 60), 69, 75);
	}
	
	// Сбросить событие обновления
	TIM6->SR &= ~TIM_SR_UIF;
}

void TIM7_IRQHandler(void) {

	// Сбросить событие обновления
	TIM7->SR &= ~TIM_SR_UIF;
}
