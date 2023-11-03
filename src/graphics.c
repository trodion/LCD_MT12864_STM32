#include "graphics.h"

void start() {
	/* Надпись "Белые" */
	set_position(2, 29);
	draw_image(white, 25);

	/* Надпись "Черные" */
	set_position(2, 70);
	draw_image(black, 30);
	
	/* Вертикальная линия */
	draw_byte(2, 64, 0x00); draw_byte(3, 64, 0x00); draw_byte(4, 64, 0x00);
	/* Двоеточия межды h:m:s */
	draw_byte(4, 31, 0x99); draw_byte(4, 47, 0x99);
	draw_byte(4, 82, 0x99); draw_byte(4, 98, 0x99);
	
	/* Предварительная прорисовка времени */
	draw_number((conf[0].time_ms / 100) % 60, w_s, w_s + 6); // Вывод секунд
	draw_number((conf[0].time_ms / 6000) % 60, w_m, w_m + 6); // Вывод минут
	draw_number((conf[0].time_ms / 360000), w_h, w_h + 6); // Вывод часов

	draw_number((conf[0].time_ms / 100) % 60, b_s, b_s + 6);
	draw_number((conf[0].time_ms / 6000) % 60, b_m, b_m + 6);
	draw_number((conf[0].time_ms / 360000), b_h, b_h + 6);
	
	TIM6->CR1 |= TIM_CR1_CEN;
	TIM7->CR1 |= TIM_CR1_CEN;
}

void draw_number(uint32_t number, uint8_t coord_high, uint8_t coord_low) {
	set_page(4);
	set_col((coord_high >> 4) & 0xF, coord_high & 0xF);
	draw_image((uint8_t*)num + (number / 10) * 5, 5);
	
	set_col((coord_low >> 4) & 0xF, coord_low & 0xF);
	draw_image((uint8_t*)num + (number % 10) * 5, 5);
}
