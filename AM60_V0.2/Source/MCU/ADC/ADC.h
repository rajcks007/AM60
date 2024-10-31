/**
*@file          ADC.h
*/
#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void Init_ADC_Kanal (ADC_t *ADC, uint8_t CH_Nr, uint8_t Def_Nr);
uint16_t ADC_Sample_Single (ADC_t *ADC, uint8_t CH_Nr, uint8_t Anzahl, uint16_t Delay);
void ADC_SET_Calibration_BYTE (void );
void Init_ADC_bat_lvl (void);
void ADC_init(void);

#endif //ADC_H