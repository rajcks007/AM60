/**
*@file  measurement.h
*/

#ifndef MEASUREMENT_H
#define MEASUREMENT_H
#include "common.h"

typedef struct {const uint16_t sampling_rate; const uint16_t sample_size; const uint8_t mean_size;} MEAS_meas_par_t;
typedef struct {
    uint8_t arr[4];     // values
    uint8_t index;      // current position in array
} floating_mean_val_t;

void Init_ADC_NF_Signal (void);

void NF_Signal_sampling (ADC_t *ADC, uint8_t CH_Nr, uint16_t *const Sample_data, const uint16_t Anzahl, uint16_t Abtastfrequenz);
uint16_t MEAS_fit_to_calib_val(const uint16_t calib_val, const uint16_t meas_val);
uint16_t MEAS_read_val (const MEAS_meas_par_t *const mP, const uint16_t calib_val);
uint16_t MEAS_read_calib_val(void);
uint16_t MEAS_reset_calibration (void);
uint8_t MEAS_calculate_floating_mean_val(const floating_mean_val_t* const floating_mean_val);
void MEAS_push_back(floating_mean_val_t* const floating_mean_val, const uint8_t val);

#endif // MEASUREMENT_H