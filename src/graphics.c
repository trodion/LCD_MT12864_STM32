#include "graphics.h"

void start() {
	/* Надпись "Белые" */
	set_page(2);
	set_col(0x1, 0xD);
	draw_image(white, 25);

	/* Надпись "Черные" */
	set_col(0x4, 0x6);
	draw_image(black, 30);

	/* Вертикальная линия */
	draw_byte(2, 0x4, 0x00, 0x00);
	draw_byte(3, 0x4, 0x00, 0x00);
	draw_byte(4, 0x4, 0x00, 0x00);
	
	/* Время за "Белые" */
	draw_min_white(); 
	set_page(4); set_col(0x2, 0x0); lcd_data(0x99);
	
	/* Время за "Черные" */
	draw_min_black();
	set_col(0x5, 0xC); lcd_data(0x99);
	draw_sec_black();
	
	(TIM6->CR1 |= TIM_CR1_CEN);
}

void draw_number(uint32_t number, uint8_t coord_high, uint8_t coord_low) {
	set_page(1);
	set_col((coord_high >> 4) & 0xF, coord_high & 0xF);
	draw_image((uint8_t*)num + (number / 10) * 5, 5);
	
	set_col((coord_low >> 4) & 0xF, coord_low & 0xF);
	draw_image((uint8_t*)num + (number % 10) * 5, 5);
}

void draw_sec_white() {
	static uint8_t* ptr = &num; /* Изображение хранится ввиде байтов в массиве, указатель на массив */
	static uint8_t count = 0; /* Узнать, достигнут ли конец масива */
	static uint8_t i = 4; /* Для вывода двузначных чисел, первое число */

	if (count == 10 /*|| count == 0*/ ){
		// if (count == 0) {
		// 	set_col(0x2, 0xA);
		// 	draw_image(((uint8_t*)num + 9 * 5), 5);
		// 	set_col(0x3, 0x0);
		// 	draw_image(((uint8_t*)num + 9 * 5), 5);
		// 	i = 3;
		// 	ms_delay(1000);
		// }
		/* Младшая цифра должна обнулится, не может быть 10 */
		ptr = &num;
		count = 0;
		if (++i == 10) i = 4;  /* Обновляем разряд десятков */
	}
	
	set_page(4);
	set_col(0x2, 0x2);
	draw_image(((uint8_t*)num + i * 5), 5);

	set_col(0x2, 0x8);
	draw_image(ptr, 5);
	
	ptr += 5;
	count += 1;
}

void draw_min_white() {
	static uint8_t* ptr = &num; /* Изображение хранится ввиде байтов в массиве, указатель на массив */
	static uint8_t count = 0; /* Узнать, достигнут ли конец масива */
	static uint8_t i = 4; /* Для вывода двузначных чисел, первое число */

	if (count == 10){
		/* Младшая цифра должна обнулится, не может быть 10 */
		ptr = &num;
		count = 0;
		if (++i == 10) i = 4; /* Обновляем разряд десятков */
	}
	
	set_page(4);
	set_col(0x1, 0x4);
	draw_image(((uint8_t*)num + i * 5), 5);

	set_col(0x1, 0xA);
	draw_image(ptr, 5);
	
	ptr += 5;
	count += 1;
}

void draw_hour_white() {

}

void draw_sec_black() {
	static uint8_t* ptr = num; /* Изображение хранится ввиде байтов в массиве, указатель на массив */
	static uint8_t count = 0; /* Узнать, достигнут ли конец масива */
	static uint8_t i = 4; /* Для вывода двузначных чисел, первое число */

	if (count == 10){
		/* Младшая цифра должна обнулится, не может быть 10 */
		ptr = &num;
		count = 0;
		if (++i == 10) i = 4; /* Обновляем разряд десятков */
	}

	set_page(4);
	set_col(0x5, 0xE);
	draw_image(((uint8_t*)num + i * 5), 5);
	
	set_col(0x6, 0x4);
	draw_image(ptr, 5);
	
	ptr += 5;
	count += 1;
}

void draw_min_black() {
	static uint8_t* ptr = &num; /* Изображение хранится ввиде байтов в массиве, указатель на массив */
	static uint8_t count = 0; /* Узнать, достигнут ли конец масива */
	static uint8_t i = 4; /* Для вывода двузначных чисел, первое число */

	if (count == 10){
		/* Младшая цифра должна обнулится, не может быть 10 */
		ptr = &num;
		count = 0;
		if (++i == 10) i = 4; /* Обновляем разряд десятков */
	} 

	set_page(4);
	set_col(0x5, 0x0);
	draw_image(((uint8_t*)num + i * 5), 5);

	set_col(0x5, 0x6);
	draw_image(ptr, 5);
	
	ptr += 5;
	count += 1;
}