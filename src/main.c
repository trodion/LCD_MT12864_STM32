#include "stm32f1xx.h"
#include "lcd_driver.h"
#include "font.h"

#define START (TIM6->CR1 |= TIM_CR1_CEN)

void pin_init(); /* Настройка выводов */
void init_rcc(); /* Настройка системы тактирования */
void init_NVIC(); /* Настройка контроллера прерываний */
void init_TIM6(); /* Настройка таймера */

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
    static uint8_t* ptr = &num; /* Изображение хранится ввиде байтов в массиве, указатель на массив */
	static uint8_t count = 5; /*  */
	if (count == 50){
		ptr = &num;
		count = 5;
	} 
    
	set_page(1);
	set_col(0x3, 0xE);
	
	draw_image(ptr, 5);
	ptr += 5;
	count += 5;
	
	// Сбросить событие обновления
    TIM6->SR &= ~TIM_SR_UIF;
}

int main() {
	init_rcc();
	pin_init();
	
	lcd_init();
	init_NVIC();

	init_TIM6();
	
	ms_delay(2000);
	START;

	while(1){};
	return 0;
}

void init_rcc() {
	/* Включение тактирования порта А, интерфейса SPI1 */
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
}

void init_TIM6() {
	// Предделитель
    TIM6->PSC = 8000 - 1;
    // Максимальное значение ва CNT
    TIM6->ARR = 1000;
    // Разрешение генерации прерывания по событию сброса счетчика
    TIM6->DIER |= TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM6_DAC_IRQn);  
}