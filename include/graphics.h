#ifndef GRAPHICS
#define GRAPHICS

#include <stdint.h>
#include "stm32f100xb.h"
#include "font.h"
#include "lcd_driver.h"
#include "timers.h"
#include "time_control.h"

#define w_s 50
#define w_m 34
#define w_h 18
#define b_s 101
#define b_m 85
#define b_h 69

void start(); /* Начальна отрисовка и запуск таймера */
/* Прорисовка числа, coord_high - координаты ст.разряда, coord_low - мл.разряда */
void draw_number(uint32_t number, uint8_t coord_high, uint8_t coord_low);

#endif