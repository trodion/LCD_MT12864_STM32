#ifndef TIME_CONTROL
#define TIME_CONTROL

#include <stdint.h>

struct time_config {
    /* Кол-во ходов, которое должен сделать игрок за время time */
    short count_move; 
    /* Отведенное игроку время */
    uint8_t time_h, time_m;
    /* Добавление времени (для контроля Фишера) */
    uint32_t adding_time;
    /* Контроль времени "Песочные часы" */
    char sandglass;
};

extern struct time_config mode01;
extern struct time_config mode02;
extern struct time_config mode03;

#endif