#include "time_control.h"

/* 1 режим(blitz) - 10 минут на партию, без подсчета ходов */
extern struct time_config mode01 = {.count_move=1, .time_h=0, .time_m=10, .adding_time=0, .sandglass=-1};

/* 2 режим(rapid) - 30 минут на партию, без подсчета ходов */
extern struct time_config mode02 = {.count_move=1, .time_h=0, .time_m=30, .adding_time=0, .sandglass=-1};

/* 3 режим(Classic) - 1 час на партию, без подсчета ходов */
extern struct time_config mode03 = {.count_move=1, .time_h=1, .time_m=0, .adding_time=0, .sandglass=-1};