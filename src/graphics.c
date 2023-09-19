#include "graphics.h"
#include "font.h"
#include "lcd_driver.h"

void draw_sec() {
	static uint8_t* ptr = &num; /* Изображение хранится ввиде байтов в массиве, указатель на массив */
	static uint8_t count = 0; /* Узнать, достигнут ли конец масива */
	static uint8_t i = 0; /* Для вывода двузначных чисел, первое число */

	if (count == 10){
		/* Младшая цифра должна обнулится, не может быть 10 */
		ptr = &num;
		count = 0;
		if (++i == 6) i = 0; /* Обновляем стату разряда десятков */
	} 
	if (count == 0){
		/* Обновляет старшую цифру, если младшая становится 0 */
		set_page(1);
		set_col(0x3, 0xE);
		draw_image((ptr + i * 5), 5);
	}

	set_col(0x4, 0x4);
	draw_image(ptr, 5);
	
	ptr += 5;
	count += 1;
}

void draw_min() {
	static uint8_t* ptr = &num; /* Изображение хранится ввиде байтов в массиве, указатель на массив */
	static uint8_t count = 0; /* Узнать, достигнут ли конец масива */
	static uint8_t i = 0; /* Для вывода двузначных чисел, первое число */

	if (count == 10){
		/* Младшая цифра должна обнулится, не может быть 10 */
		ptr = &num;
		count = 0;
		if (++i == 6) i = 0; /* Обновляем стату разряда десятков */
	} 
	if (count == 0){
		/* Обновляет старшую цифру, если младшая становится 0 */
		set_page(1);
		set_col(0x3, 0x0);
		draw_image((ptr + i * 5), 5);
	}

	set_col(0x3, 0x6);
	draw_image(ptr, 5);
	
	ptr += 5;
	count += 1;
}
