#include "stm32f100xb.h"
#include "lcd_driver.h"
#include "font.h"
#include "graphics.h"
#include "IRQHandlers.h"
#include "timers.h"


void pin_init(); /* Настройка выводов */
void init_rcc(); /* Настройка системы тактирования */
void init_NVIC(); /* Настройка контроллера прерываний */


int main() {
	init_rcc();
	pin_init();
	
	lcd_init(); /* Инициализировать дисплей */
	init_NVIC();
	init_TIM6(); /* Настроить таймер для отсчета времени */
	init_TIM7();

	//ms_delay(2000);
	init_conf();
	init_time();
	start(); /* Запуск и первоначальная отрисовка */
	
	while(1){};
	return 0;
}

void init_rcc() {
	RCC->CR |= RCC_CR_HSEON; /* Включение HSE (внеш. источник тактирования) */
	while (!(RCC->CR & RCC_CR_HSERDY)); /* Ожидание готовности */
	RCC->CFGR |= RCC_CFGR_SW_HSE; /*  */
	RCC->CR &= ~RCC_CR_HSION;
	/* Включение тактирования портаов А, C, TIM6 */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPBEN; 
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN | RCC_APB1ENR_TIM7EN;
}

void pin_init() {
	/* PA1 - /CS1 (general purpose push-pull) */
	GPIOA->CRL &= ~GPIO_CRL_CNF1_1 & ~GPIO_CRL_CNF1_0;
	GPIOA->CRL |= GPIO_CRL_MODE1_1 | GPIO_CRL_MODE1_0;

	/* PA2 - /RES (general purpose push-pull) */
	GPIOA->CRL &= ~GPIO_CRL_CNF2_1 & ~GPIO_CRL_CNF2_0;
	GPIOA->CRL |= GPIO_CRL_MODE2_1 | GPIO_CRL_MODE2_0;

	/* PA3 - A0 (general purpose push-pull) */
	GPIOA->CRL &= ~GPIO_CRL_CNF3_1 & ~GPIO_CRL_CNF3_0;
	GPIOA->CRL |= GPIO_CRL_MODE3_1 | GPIO_CRL_MODE3_0;

	/* PA5 - SCL (general purpose push-pull) */
	GPIOA->CRL |= GPIO_CRL_MODE5_1 | GPIO_CRL_MODE5_0;
	GPIOA->CRL &= ~GPIO_CRL_CNF5_0 & ~GPIO_CRL_CNF5_1;

	/* PA7 - SI (general purpose push-pull) */
	GPIOA->CRL |= GPIO_CRL_MODE7_1 | GPIO_CRL_MODE7_0;
	GPIOA->CRL &= ~GPIO_CRL_CNF7_0 & ~GPIO_CRL_CNF7_1;

	GPIOC->CRH &= ~GPIO_CRH_CNF8_0 & ~GPIO_CRH_CNF8_1 ;
	GPIOC->CRH |= GPIO_CRH_MODE8_0 | GPIO_CRH_MODE8_1;
}

void init_NVIC() {
	NVIC_EnableIRQ(TIM7_IRQn);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	NVIC_SetPriority(TIM6_DAC_IRQn, 1);
	NVIC_SetPriority(TIM7_IRQn, 2);
}
