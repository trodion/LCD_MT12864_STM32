#ifndef GRAPHICS
#define GRAPHICS

#include <stdint.h>
#include "stm32f100xb.h"
#include "font.h"
#include "lcd_driver.h"
#include "timers.h"

void start(); /* Начальна отрисовка и запуск таймера */
void draw_sec_white();
void draw_min_white();
void draw_sec_black();
void draw_min_black();

#endif