#include "time_control.h"

/* 1 режим(blitz) - 10 минут на партию, без подсчета ходов */
extern struct time_config mode01 = {.count_move=1, .time_ms=60100, .adding_time=0, .sandglass=-1};

/* 2 режим(rapid) - 30 минут на партию, без подсчета ходов */
extern struct time_config mode02 = {.count_move=1, .time_ms=180100, .adding_time=0, .sandglass=-1};

/* 3 режим(Classic) - 1 час на партию, без подсчета ходов */
extern struct time_config mode03 = {.count_move=1, .time_ms=360100, .adding_time=0, .sandglass=-1};

/* 4 режим(Classic) - 1:30 минут на партию, без подсчета ходов */
extern struct time_config mode04 = {.count_move=1, .time_ms=540100, .adding_time=0, .sandglass=-1};

/* 5 режим(Classic) - 2 часа на партию, без подсчета ходов */
extern struct time_config mode05 = {.count_move=1, .time_ms=720100, .adding_time=0, .sandglass=-1};