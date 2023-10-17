#ifndef IRQHANDLERS
#define IRQHANDLERS

void EXTI0_IRQHandler(void); /* Обработчик прерывания от синей кнопки на МК */
void TIM6_DAC_IRQHandler(void); /* Прерывания по переполнению таймера, отсчет 1 сек */

#endif