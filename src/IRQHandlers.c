#include "stm32f100xb.h"
#include "IRQHandlers.h"
#include "lcd_driver.h"
#include "graphics.h"


void EXTI0_IRQHandler(void) {
	/* Обработчик прерывания от линии EXTI0, 
	   Подлкюченной к кнопке PA0 */
	if (status) DisplayOFF;
	else DisplayOn;
	
	ChangeStatus; // Поменять статус дисплея 
	EXTI->PR &= 0x01; // Произошла генерация запроса на прерывания, нужно сбросить
	ms_delay(1000);
}

void TIM6_DAC_IRQHandler(void){
	static uint8_t count = 0;
	
	draw_sec();
	if (++count == 60) {
		draw_min();
		count = 0;
	} 

	// Сбросить событие обновления
	TIM6->SR &= ~TIM_SR_UIF;
}
