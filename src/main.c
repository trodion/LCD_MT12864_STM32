#include "stm32f1xx.h"
#include "lcd_driver.h"
#include "font.h"

void pin_init(); /* Настройка выводов */
void init_rcc(); /* Настройка системы тактирования */


int main() {
	init_rcc();
	pin_init();
	
	lcd_init();

	set_page(1);
	set_col(0, 0x5);
	draw_image(*num, 45);
	
	while(1){};
	return 0;
}

void init_rcc() {
	/* Включение тактирования порта А, интерфейса SPI1 */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 
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
}
