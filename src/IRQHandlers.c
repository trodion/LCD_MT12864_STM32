#include "stm32f100xb.h"
#include "IRQHandlers.h"
#include "lcd_driver.h"
#include "graphics.h"


void EXTI0_IRQHandler(void) {
	/* Обработчик прерывания от линии EXTI0, 
	   Подлкюченной к кнопке PA0 */
	TIM6->CR1 ^= TIM_CR1_CEN;
	TIM7->CR1 ^= TIM_CR1_CEN;
	EXTI->PR &= 0x01; // Произошла генерация запроса на прерывания, нужно сбросить
	ms_delay(1000);
}

void TIM6_DAC_IRQHandler(void){
	/* В обработчик заходит каждые 10 миллисекунд */
	static uint32_t cnt = 0; // Кол-во миллисекунд
	
	cnt += 1;
	uint32_t h = cnt / 360000; // Получили кол-во целых часов
	uint32_t m = cnt / 6000; // Получили кол-во целых минут
	uint32_t s = cnt / 100; // Кол-во целых сек
	
	draw_number(59 - (s % 60), 30, 36); // Вывод секунд
	draw_number(59 - (m % 60), 16, 22); // Вывод минут
	draw_number(2 - (h % 60), 2, 8); // Вывод часов
	// Сбросить событие обновления
	TIM6->SR &= ~TIM_SR_UIF;
}

void TIM7_IRQHandler(void) {
	static uint8_t count = 1;
	
	draw_sec_black();
	if (count++ == 60) {
		draw_min_black();
		count = 1;
	} 
	// Сбросить событие обновления
	TIM7->SR &= ~TIM_SR_UIF;
}
