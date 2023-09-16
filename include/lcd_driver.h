#ifndef LCD_DRIVER
#define LCD_DRIVER

#include <stdint.h>

/* Инициализация и включение дисплея */
void lcd_init();

/* Отправка команды в дисплей */
void lcd_cmd(uint8_t byte);

/* Отправка данных в дисплей 
    Данные - 1 байт 
    Биты - вкл/выкл пиксели в заранее выбранном столбце
*/
void lcd_data(uint8_t byte);

/* Очистка экрана */
void lcd_clr();

/* Нарисовать изображение, определенное в массиве */
void draw_image(uint8_t* p, uint16_t size);

/* Выставить новую страницу и нулевой столбец */
void next_page(uint8_t page);

/* Выбор "страницы" (блок 8p*128p) */
void set_page(uint8_t page);

/* Выбор столбца XY */
void set_col(uint8_t x, uint8_t y);

/* Нарисовать линию */
void draw_line(uint8_t page, uint8_t X, uint8_t Y);

/* Задержка на ms микросекунд */
void ms_delay(uint32_t ms);

#endif