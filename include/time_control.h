#ifndef TIME_CONTROL
#define TIME_CONTROL

#include <stdint.h>

struct time_config {
    /* Кол-во ходов, которое должен сделать игрок за время time */
    short count_move; 
    /* Отведенное игроку время */
    uint32_t time_ms;
    /* Добавление времени (для контроля Фишера) */
    uint32_t adding_time;
    /* Контроль времени "Песочные часы" */
    char sandglass;
};

extern struct time_config mode01;
extern struct time_config mode02;
extern struct time_config mode03;
extern struct time_config mode04;
extern struct time_config mode05;

#endif