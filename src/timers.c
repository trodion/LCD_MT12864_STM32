#include "stm32f100xb.h"
#include "timers.h"

void init_TIM6() {
	// Предделитель
    TIM6->PSC = 7999;
    // Максимальное значение ва CNT
    TIM6->ARR = 100;
    // Разрешение генерации прерывания по событию сброса счетчика
    TIM6->DIER |= TIM_DIER_UIE;  
}

void init_TIM7() {
    TIM7->PSC = 7999;
    TIM7->ARR = 1000;
    TIM7->DIER |= TIM_DIER_UIE;
}