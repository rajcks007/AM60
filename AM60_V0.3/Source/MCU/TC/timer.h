/**
*@file          timer.h
*
*/
#include <stdint.h>
void TIM_init(void);
void TIM_start_C0(void);
void TIM_stop_C0(void);
void TIM_start_C1(void);
void TIM_stop_C1(void);
void TIM_start_D0(void);
void TIM_stop_D0(void);
void TIM_start_D1(void);
void TIM_stop_D1(void);
void TIM_start_E0(void);
void TIM_stop_E0(void);
void TIM_start_E1(void);
void TIM_stop_E1(void);
uint32_t tick (void);