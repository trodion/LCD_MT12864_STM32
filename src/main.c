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
	
	ms_delay(2000);
	
	start(); /* Запуск и первоначальная отрисовка */

	while(1){};
	return 0;
}

void init_rcc() {
	/* Включение тактирования портаов А, C, TIM6 */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN; 
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
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
    /* Разрешены прерывания от нулевой ноги */
    EXTI->IMR |= EXTI_IMR_IM0;
    /* По нарастающему фронту */
    EXTI->RTSR |= EXTI_RTSR_RT0;
    
    NVIC_SetPriority(EXTI0_IRQn, 0);
    NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_SetPriority(EXTI0_IRQn, 1);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
}
