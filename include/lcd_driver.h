#ifndef LCD_DRIVER
#define LCD_DRIVER

#include <stdint.h>

#define DisplayOn  (lcd_cmd(0xAF))
#define DisplayOFF (lcd_cmd(0xAE))
#define ChangeStatus (status = ~status)

/* Статус дисплея вкл/выкл */
uint8_t status;

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

/* Нарисовать байт (столбец) */
void draw_byte(uint8_t page, uint8_t col, uint8_t byte);

/* Нарисовать изображение, определенное в массиве */
void draw_image(uint8_t* p, uint16_t size);

/* Выбор "страницы" (блок 8p*128p) */
void set_page(uint8_t page);

/* Выбор столбца XY */
void set_col(uint8_t x, uint8_t y);

/* Выбрать место куда запишем байт */
void set_position(uint8_t page, uint8_t col);

/* Задержка на ms микросекунд */
void ms_delay(uint32_t ms);

#endif