#include "lcd_driver.h"
#include "stm32f1xx.h"

#define Set_CS  (GPIOA->ODR |= GPIO_ODR_ODR1)
#define Res_CS  (GPIOA->ODR &= ~GPIO_ODR_ODR1)
#define Set_RES (GPIOA->ODR |= GPIO_ODR_ODR2)
#define Clr_RES (GPIOA->ODR &= ~GPIO_ODR_ODR2)
#define Set_A0  (GPIOA->ODR |= GPIO_ODR_ODR3)
#define Res_A0  (GPIOA->ODR &= ~GPIO_ODR_ODR3)
#define SCK_1   (GPIOA->ODR |= GPIO_ODR_ODR5)
#define SCK_0   (GPIOA->ODR &= ~GPIO_ODR_ODR5)
#define SI_1    (GPIOA->ODR |= GPIO_ODR_ODR7)
#define SI_0    (GPIOA->ODR &= ~GPIO_ODR_ODR7)


void lcd_init() {
    Clr_RES;
    Set_CS;
    SCK_1;
    ms_delay(50);

    Set_RES;
    ms_delay(50);

    /* Команды инициализации */
    lcd_cmd(0x2F);
	lcd_cmd(0x27);
	lcd_cmd(0x81);
	lcd_cmd(0x30);
	lcd_cmd(0xA6);
	lcd_cmd(0xC8);
	lcd_cmd(0xA0);	
    lcd_cmd(0x7F);
    
    status = 0xFF;
    DisplayOn;
    /* Очистка дисплея */
    lcd_clr();
}


void lcd_cmd(uint8_t byte) {
    Res_A0;
    Res_CS;

    for(uint8_t i = 0; i < 8; ++i) {
		if(byte & 0x80) SI_1;
		else SI_0;
		SCK_0;
		byte <<= 1;
		SCK_1;
	}
    Set_CS;
}

void lcd_data(uint8_t byte) {
    Set_A0;
    Res_CS;

    for (uint8_t i = 0; i < 8; ++i){
        if (byte & 0x01) SI_1;
        else SI_0;
        SCK_0;
        byte >>= 1;
        SCK_1;
    }
    Set_CS;
}

void lcd_clr() {
    for(uint8_t page = 0; page < 8; ++page) {
        set_page(page);
        set_col(0 , 0);
        for(uint8_t i = 0; i < 128; ++i) lcd_data(0xFF);
    }    
}

void draw_image(uint8_t* p, uint16_t size){
    for (uint16_t i = 0; i < size; ++i){
        if (i % 5 == 0 && i != 0) {
            for (uint8_t i = 0; i < 9; ++i) lcd_data(0xFF);
        }
        lcd_data(*p);
        ++p;
    }
}

void set_page(uint8_t page) {
    lcd_cmd(0xB0 + page);
}

void set_col(uint8_t x, uint8_t y){
    lcd_cmd(0x10 + x); /* Старший полубайт столбца */
    lcd_cmd(0x00 + y); /* Младший полубайт столбца */
}

void draw_line(uint8_t page, uint8_t X, uint8_t Y) {
    set_page(page);
    set_col(X, Y);
    lcd_data(0x00);
}

void ms_delay(uint32_t ms) {
    while(ms-- > 0) {
      volatile uint16_t x = 500;
      while (x-- > 0) __asm("nop");
   }
}