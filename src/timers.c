#include "stm32f100xb.h"
#include "timers.h"

void init_TIM6() {
	// Предделитель
    TIM6->PSC = 8000 - 1;
    // Максимальное значение ва CNT
    TIM6->ARR = 1000;
    // Разрешение генерации прерывания по событию сброса счетчика
    TIM6->DIER |= TIM_DIER_UIE;  
}