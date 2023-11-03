#include "time_control.h"

/* 1 режим(blitz) - 10 минут на партию, без подсчета ходов */
extern struct time_config mode01 = {.count_move=-1, .time_ms=60050, .adding_time=0, .sandglass=-1};

/* 2 режим(rapid) - 30 минут на партию, без подсчета ходов */
extern struct time_config mode02 = {.count_move=-1, .time_ms=180050, .adding_time=0, .sandglass=-1};

/* 3 режим(Classic) - 1 час на партию, без подсчета ходов */
extern struct time_config mode03 = {.count_move=-1, .time_ms=360050, .adding_time=0, .sandglass=-1};

/* 4 режим(Classic) - 1:30 минут на партию, без подсчета ходов */
extern struct time_config mode04 = {.count_move=-1, .time_ms=540050, .adding_time=0, .sandglass=-1};

/* 5 режим(Classic) - 2 часа на партию, без подсчета ходов */
extern struct time_config mode05 = {.count_move=-1, .time_ms=720050, .adding_time=0, .sandglass=-1};

/* 6 режим(Fischer) - 3 минуты на партию, добавление 2х секунд после хода */
extern struct time_config mode06 = {.count_move=-1, .time_ms=18250, .adding_time=200, .sandglass=-1};

/* 7 режим(Fischer) - 25 минут на партию, добавление 10 секунд после хода */
extern struct time_config mode07 = {.count_move=-1, .time_ms=150050, .adding_time=1000, .sandglass=-1};

/* 8 режим(Fischer) - 1:30 минут на партию, добавление 30 секунд после хода */
extern struct time_config mode08 = {.count_move=-1, .time_ms=543050, .adding_time=3000, .sandglass=-1};

/* 9 режим(Classic) - 2 часа на 40 ходов */
extern struct time_config mode09 = {.count_move=40, .time_ms=720050, .adding_time=0, .sandglass=-1};

/* 10 режим(Classic) - 1 час на 20 ходов */
extern struct time_config mode10 = {.count_move=20, .time_ms=360050, .adding_time=0, .sandglass=-1};

/* Пробный режим */
extern struct time_config conf[3] = {{.count_move=5, .time_ms=60050, .adding_time=0, .sandglass=-1},
                                     {.count_move=3, .time_ms=18050, .adding_time=0, .sandglass=-1},
                                     {.count_move=-1, .time_ms=24050, .adding_time=0, .sandglass=-1}
};

void init_conf() {
    // conf[0] = mode11;
    // conf[1] = mode12;
    // conf[2] = mode13;
}