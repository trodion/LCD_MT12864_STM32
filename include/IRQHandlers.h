#ifndef IRQHANDLERS
#define IRQHANDLERS


void TIM6_DAC_IRQHandler(void); /* Прерывания по переполнению таймера, отсчет 10 мс */
void TIM7_IRQHandler(void); /* Прерывания для перерисовки экрана */
void init_time(); /* Заполнить структуру  time в соответсвии с выбранным режимом игры */

#endif