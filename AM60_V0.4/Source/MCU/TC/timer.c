/**
*@file                  timer.c
*
*/
#include <ioavr.h>
#include "delay.h"
#include "board_conf.h"
#include "common.h"
#include "LCD.h"
#include "battery.h"
#include "bluetooth.h"
#include "bm83.h"

#define BATTERY_MEASUREMENT_PERIOD_SEC      (3)   // measure battery level ever x seconds

/**
@brief          use to impliment a LCD on-off
*/
extern volatile bool Lcd_on_flag;
/**
@brief          use to impliment a LCD on-off
*/


static void TIM_init_C0 (void);
static void TIM_init_C1 (void);
static void TIM_init_D0 (void);
static void TIM_init_D1 (void);
static void TIM_init_E0 (void);
static void TIM_init_E1 (void);

static uint32_t cntdown_to_next_bat_lvl_meas = 0;

extern bool check_bat_lvl;
extern bool is_pulse_active;
extern uint32_t wait_time_ms;
extern uint8_t count_up;

void TIM_init(void){
    TIM_init_C0();
    TIM_init_C1();
    TIM_init_D0();
    TIM_init_D1();
    TIM_init_E0();
    TIM_init_E1();
}

static void TIM_init_C0 (void){
    TCC0.CTRLA = 0;                  
    TCC0.CTRLB = __TC0_CTRLB;        
    TCC0.CTRLC = __TC0_CTRLC;       
    TCC0.CTRLD = __TC0_CTRLD;        
    TCC0.CTRLE = __TC0_CTRLE;        
    TCC0.INTCTRLA = __TC0_INTCTRLA;  
    TCC0.INTCTRLB = __TC0_INTCTRLB;  
    TCC0.CTRLFSET = __TC0_CTRLFSET;  
    TCC0.CCA = __TC0_CCA;            
    TCC0.CCB = __TC0_CCB;            
    TCC0.CCC = __TC0_CCC;           
    TCC0.CCD = __TC0_CCD;            
}

static void TIM_init_C1 (void){
    TCC1.CTRLA = 0;                 
    TCC1.CTRLB = __TC1_CTRLB;        
    TCC1.CTRLC = __TC1_CTRLC;        
    TCC1.CTRLD = __TC1_CTRLD;        
    TCC1.CTRLE = __TC1_CTRLE;        
    TCC1.INTCTRLA = __TC1_INTCTRLA;  
    TCC1.INTCTRLB = __TC1_INTCTRLB;  
    TCC1.CTRLFSET = __TC1_CTRLFSET;  
    TCC1.CCA = 0;                    
    TCC1.CCB = 0;        
    TCC1.PER = __TC1_PER;
}

static void TIM_init_D0 (void){
    TCD0.CTRLA = 0;                  
    TCD0.CTRLB = __TD0_CTRLB;        
    TCD0.CTRLC = __TD0_CTRLC;      
    TCD0.CTRLD = __TD0_CTRLD;        
    TCD0.CTRLE = __TD0_CTRLE;        
    TCD0.INTCTRLA = __TD0_INTCTRLA;  
    TCD0.INTCTRLB = __TD0_INTCTRLB;  
    TCD0.CTRLFSET = __TD0_CTRLFSET;  
    TCD0.CCA = __TD0_CCA;           
    TCD0.CCB = __TD0_CCB;            
    TCD0.PER = __TD0_PER;            
    TCD0.CNT = __TD0_PER;
}

static void TIM_init_D1 (void){
    TCD1.CTRLA = 0;                  
    TCD1.CTRLB = __TD1_CTRLB;        
    TCD1.CTRLC = __TD1_CTRLC;        
    TCD1.CTRLD = __TD1_CTRLD;       
    TCD1.CTRLE = __TD1_CTRLE;        
    TCD1.INTCTRLA = __TD1_INTCTRLA;  
    TCD1.INTCTRLB = __TD1_INTCTRLB;  
    TCD1.CTRLFSET = __TD1_CTRLFSET;  
    TCD1.CCA = 0;                    
    TCD1.CCB = 0;    
    TCD1.PER = __TD1_PER;           
    TCD1.CNT = __TD1_PER;
}

// Used to periodically measure battery voltage
static void TIM_init_E0(void){
    TCE0.CTRLA = 0;                  
    TCE0.CTRLB = __TE0_CTRLB;        
    TCE0.CTRLC = __TE0_CTRLC;        
    TCE0.CTRLD = __TE0_CTRLD;       
    TCE0.CTRLE = __TE0_CTRLE;        
    TCE0.INTCTRLA = __TE0_INTCTRLA;  
    TCE0.INTCTRLB = (TC0_CCAINTLVL1_bm | TC0_CCAINTLVL0_bm);  
    TCE0.CTRLFSET = __TE0_CTRLFSET;  
    TCE0.CCA = __TE0_CCA;                    
    TCE0.CCB = __TE0_CCB;   
    TCE0.CCC = __TE0_CCC;
    TCE0.CCD = __TE0_CCD;
    TCE0.PER = __TE0_PER;            
    TCE0.CNT = 0;
}

static void TIM_init_E1(void){
    TCE1.CTRLA = 0;                  
    TCE1.CTRLB = __TE1_CTRLB;        
    TCE1.CTRLC = __TE1_CTRLC;        
    TCE1.CTRLD = __TE1_CTRLD;       
    TCE1.CTRLE = __TE1_CTRLE;        
    TCE1.INTCTRLA = __TE1_INTCTRLA;  
    TCE1.INTCTRLB = (TC0_CCAINTLVL1_bm | TC0_CCAINTLVL0_bm);  
    TCE1.CTRLFSET = __TE1_CTRLFSET;  
    TCE1.CCA = __TE1_CCA;                    
    TCE1.CCB = __TE1_CCB;   
    TCE1.PER = __TE1_PER;            
    TCE1.CNT = 0;
}


void TIM_start_C0(void){
    TCC0.CTRLA = __TC0_CTRLA;
}
void TIM_stop_C0(void){
    TCC0.CTRLA = 0;                  
}

// mutesymbol blinkt
void TIM_start_C1(void){
    TCC1.PER = __TC1_PER;
    TCC1.CTRLA = __TC1_CTRLA;
}
void TIM_stop_C1(void){
    TCC1.CTRLA = 0;                  
}

void TIM_start_D0(void){
     TCD0.CTRLA = __TD0_CTRLA;
}
void TIM_stop_D0(void){
    TCD0.CTRLA = 0;                      
}

void TIM_start_D1(void){
    TCD1.CCA = __TD1_PER;
    TCD1.CNT = 0;
    TCD1.CTRLA = __TD1_CTRLA;
}
void TIM_stop_D1(void){
    TCD1.CTRLA = 0;                      
}
void TIM_start_E0(void){
    TCE0.CCA = __TE0_PER;
    TCE0.CNT = 0;
    TCE0.CTRLA = __TE0_CTRLA; 
}
void TIM_stop_E0(void){
    TCE0.CTRLA = 0;                  
}

void TIM_start_E1(void){
    TCE1.CCA = __TE1_PER; 
    TCE1.CTRLA = __TE1_CTRLA;
}
void TIM_stop_E1(void){
    TCE1.CTRLA = 0;                  
}




#pragma vector = TCC1_CCA_vect
__interrupt void TC1_compA( void ){
    INV_BIT(LCD_T4_PORT, LCD_T4_PIN);
}

#pragma vector = TCD1_CCA_vect
__interrupt void TD1_compA( void ){ 
    LCD_toggle_elements();
}


#pragma vector = TCE0_CCA_vect
__interrupt void TE0_compA( void ){
    cntdown_to_next_bat_lvl_meas++;
    count_up++;
    if(cntdown_to_next_bat_lvl_meas == BATTERY_MEASUREMENT_PERIOD_SEC){
        cntdown_to_next_bat_lvl_meas = 0;
        check_bat_lvl = true;
    }
    if((count_up == (wait_time_ms / 1000)) && is_pulse_active){
        INV_BIT(BM83_PWR_PORT, BM83_PWR_PIN);       // creates pulse for x seconds
        count_up = 0;
        is_pulse_active = false;
    }
}

#pragma vector = TCE1_CCA_vect
__interrupt void TE1_compA( void ){
    Lcd_on_flag = false;
    TCE1.CNT = 0;
}
