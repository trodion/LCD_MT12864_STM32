#include "stm32f100xb.h"
#include "IRQHandlers.h"
#include "lcd_driver.h"
#include "graphics.h"


void EXTI0_IRQHandler(void) {
	/* Обработчик прерывания от линии EXTI0, 
	   Подлкюченной к кнопке PA0 */
	// if (status) DisplayOFF;
	// else DisplayOn;	
	// ChangeStatus; // Поменять статус дисплея 
	TIM6->CR1 ^= TIM_CR1_CEN;
	TIM7->CR1 ^= TIM_CR1_CEN;
	EXTI->PR &= 0x01; // Произошла генерация запроса на прерывания, нужно сбросить
	ms_delay(1000);
}

void TIM6_DAC_IRQHandler(void){
	static uint8_t count = 0;
	
	draw_sec_white();
	if (++count == 60) {
		draw_min_white();
		count = 0;
	} 
	// Сбросить событие обновления
	TIM6->SR &= ~TIM_SR_UIF;
}

void TIM7_IRQHandler(void) {
	static uint8_t count = 0;
	
	draw_sec_black();
	if (++count == 60) {
		draw_min_black();
		count = 0;
	} 
	// Сбросить событие обновления
	TIM7->SR &= ~TIM_SR_UIF;
}
