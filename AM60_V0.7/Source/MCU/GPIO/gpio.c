/**
*@file          GPIO.c
*
*
*/

#include <ioavr.h>
#include "GPIO.h"
#include "board_conf.h"
#include "common.h"
#include "timer.h"
#include "bluetooth.h"
#include "main.h"
#include "delay.h"

static void GPIO_init_pins (PORT_t *PORT_Adr, uint8_t SRLEN, uint8_t INVEN, uint8_t *OPC, uint8_t *ISC);
static void Register_in_Feld (uint8_t *Feld, uint8_t Reg7, uint8_t Reg6, uint8_t Reg5, uint8_t Reg4, uint8_t Reg3, uint8_t Reg2, uint8_t Reg1, uint8_t Reg0);
static void GPIO_init_PORTA(void);
static void GPIO_init_PORTB(void);
static void GPIO_init_PORTC(void);
static void GPIO_init_PORTD(void);
static void GPIO_init_PORTE(void);
static void GPIO_init_PORTF(void);
static void GPIO_init_PORTR(void);

extern operating_param_t op_param;

void GPIO_init (void){
    GPIO_init_PORTA();
    GPIO_init_PORTB();
    GPIO_init_PORTC();
    GPIO_init_PORTD();
    GPIO_init_PORTE();
    GPIO_init_PORTF();
    GPIO_init_PORTR();
}


static void GPIO_init_PORTA(void){
    uint8_t REG_1[8], REG_2[8];
    PORTA_OUT = __PA_OUT;                    
    PORTA_DIR = __PA_DIR;                    
    CLR_BIT(PORTA_INTCTRL, 0x0f);             
    SET_BIT(PORTA_INTCTRL, __PA_INT0_CTRL);   
    SET_BIT(PORTA_INTCTRL, __PA_INT1_CTRL << 2); 
    PORTA_INT0MASK = __PA_INT0_Mask;         
    PORTA_INT1MASK = __PA_INT1_Mask;         
    Register_in_Feld  (REG_1, __PA_PIN_OP);  
    Register_in_Feld  (REG_2, __PA_PIN_IS);
    GPIO_init_pins(&PORTA, __PA_PIN_SR, 0, REG_1, REG_2);
}

static void GPIO_init_PORTB(void){
    uint8_t REG_1[8], REG_2[8];
    PORTB_OUT = __PB_OUT;                   
    PORTB_DIR = __PB_DIR;                    
    CLR_BIT(PORTB_INTCTRL, 0x0f);             
    SET_BIT(PORTB_INTCTRL, __PB_INT0_CTRL); 
    SET_BIT(PORTB_INTCTRL, __PB_INT1_CTRL << 2); 
    PORTB_INT0MASK = __PB_INT0_Mask;        
    PORTB_INT1MASK = __PB_INT1_Mask;         
    Register_in_Feld  (REG_1, __PB_PIN_OP);  
    Register_in_Feld  (REG_2, __PB_PIN_IS);
    GPIO_init_pins(&PORTB, __PB_PIN_SR, 0, REG_1, REG_2);
}

static void GPIO_init_PORTC(void){
    uint8_t REG_1[8], REG_2[8];
    PORTC_OUT = __PC_OUT;                  
    PORTC_DIR = __PC_DIR;                   
    CLR_BIT(PORTC_INTCTRL, 0x0f);            
    SET_BIT(PORTC_INTCTRL, __PC_INT0_CTRL); 
    SET_BIT(PORTC_INTCTRL, __PC_INT1_CTRL << 2); 
    PORTC_INT0MASK = __PC_INT0_Mask;         
    PORTC_INT1MASK = __PC_INT1_Mask;         
    Register_in_Feld  (REG_1, __PC_PIN_OP);  
    Register_in_Feld  (REG_2, __PC_PIN_IS);
    GPIO_init_pins(&PORTC, __PC_PIN_SR, 0, REG_1, REG_2);
}

static void GPIO_init_PORTD(void){
    uint8_t REG_1[8], REG_2[8];
    PORTD_OUT = __PD_OUT;                    
    PORTD_DIR = __PD_DIR;                   
    CLR_BIT(PORTD_INTCTRL, 0x0f);            
    SET_BIT(PORTD_INTCTRL, __PD_INT0_CTRL);   
    SET_BIT(PORTD_INTCTRL, __PD_INT1_CTRL << 2);
    PORTD_INT0MASK = __PD_INT0_Mask;         
    PORTD_INT1MASK = __PD_INT1_Mask;        
    Register_in_Feld  (REG_1, __PD_PIN_OP);  
    Register_in_Feld  (REG_2, __PD_PIN_IS);
    GPIO_init_pins(&PORTD, __PD_PIN_SR, 0, REG_1, REG_2);
}

static void GPIO_init_PORTE(void){
    uint8_t REG_1[8], REG_2[8];
    PORTE_OUT = __PE_OUT;                    
    PORTE_DIR = __PE_DIR;                   
    CLR_BIT(PORTE_INTCTRL, 0x0f);             
    SET_BIT(PORTE_INTCTRL, __PE_INT0_CTRL);  
    SET_BIT(PORTE_INTCTRL, __PE_INT1_CTRL << 2);
    PORTE_INT0MASK = __PE_INT0_Mask;        
    PORTE_INT1MASK = __PE_INT1_Mask;         
    Register_in_Feld  (REG_1, __PE_PIN_OP);  
    Register_in_Feld  (REG_2, __PE_PIN_IS);
    GPIO_init_pins(&PORTE, __PE_PIN_SR, 0, REG_1, REG_2);
}

static void GPIO_init_PORTF(void){
    uint8_t REG_1[8], REG_2[8];
    PORTF_OUT = __PF_OUT;                    
    PORTF_DIR = __PF_DIR;                    
    CLR_BIT(PORTF_INTCTRL, 0x0f);             
    SET_BIT(PORTF_INTCTRL, __PF_INT0_CTRL);   
    SET_BIT(PORTF_INTCTRL, __PF_INT1_CTRL << 2); 
    PORTF_INT0MASK = __PF_INT0_Mask;         
    PORTF_INT1MASK = __PF_INT1_Mask;        
    Register_in_Feld  (REG_1, __PF_PIN_OP);  
    Register_in_Feld  (REG_2, __PF_PIN_IS);
    GPIO_init_pins(&PORTF, __PF_PIN_SR, 0, REG_1, REG_2);
}

static void GPIO_init_PORTR(void){
    uint8_t REG_1[8], REG_2[8];
    PORTR_OUT = __PR_OUT;                    
    PORTR_DIR = __PR_DIR;                    
    CLR_BIT(PORTR_INTCTRL, 0x0f);             
    SET_BIT(PORTR_INTCTRL, __PR_INT0_CTRL);   
    SET_BIT(PORTR_INTCTRL, __PR_INT1_CTRL << 2); 
    PORTR_INT0MASK = __PR_INT0_Mask;         
    PORTR_INT1MASK = __PR_INT1_Mask;         
    Register_in_Feld  (REG_1, __PR_PIN_OP);  
    Register_in_Feld  (REG_2, __PR_PIN_IS);
    GPIO_init_pins(&PORTR, __PR_PIN_SR, 0, REG_1, REG_2);
}




/*****************************************************************************************************
                                 GPIO_init_pins
Alle Pins eines Ports werden configuriert siehe S.142
PORT_PIN_CTRL_Adr : Adr Pin = des zu configurierenten Ports
SRLEN   : > 0 Slew Rate Enable
INVEN   : > 0 Invert I/O Enable
OPC     : Feld mit 8 Output and Pull Configuration Zust寤en
ISC     : Feld mit 8 Input/Sense Configuration Zust寤en
*******************************************************************************************************/
static void GPIO_init_pins (PORT_t *PORT_Adr, uint8_t SRLEN, uint8_t INVEN, uint8_t *OPC, uint8_t *ISC){
    uint8_t i, mask;
    uint8_t *Adr;
    Adr = (uint8_t *)&PORT_Adr->PIN0CTRL;             //Pointer auf PORT PIN CTRL setzen
    for(i = 0; i < 8; i++) *(Adr + i) = 0;                  //Alle PORT PIN CTRL l@chen
    for(i = 0; i < 8; i++)    {
        mask = 1;
        if((SRLEN & mask) > 0) SET_BIT(*(Adr + i), BIT_7);      // Bit 7: Slew Rate Limit Enable
        if((INVEN & mask) > 0) SET_BIT(*(Adr + i), BIT_6);      // Bit 6: Invert I/O Enable
        SET_BIT(*(Adr + i), OPC[i] << 3);                       // Bit 5-3: Output and Pull Configuration
        SET_BIT(*(Adr + i), ISC[i]);                            // Bit 2-0: Input/Sense Configuration
    }
}

static void Register_in_Feld (uint8_t *Feld, uint8_t Reg7, uint8_t Reg6, uint8_t Reg5, uint8_t Reg4, uint8_t Reg3, uint8_t Reg2, uint8_t Reg1, uint8_t Reg0){
    Feld[0] = Reg0;
    Feld[1] = Reg1;
    Feld[2] = Reg2;
    Feld[3] = Reg3;
    Feld[4] = Reg4;
    Feld[5] = Reg5;
    Feld[6] = Reg6;
    Feld[7] = Reg7;
}

// I N T E R R U P T S
#pragma vector = PORTB_INT0_vect
__interrupt void GPIO_portB_int0( void ){
   if(!bt_is_connected()){
        BT_set_connection_status(NOT_PAIRED);
    }
    else{ 
        BT_set_connection_status(PAIRED);
    }
}

#pragma vector = PORTB_INT1_vect
__interrupt void GPIO_portB_int1( void ){
    if(BUTTON_RIGHT_PORT.IN & BUTTON_RIGHT_PIN){   
        op_param.button_right_pushed = true;
    }
}

#pragma vector = PORTD_INT0_vect
__interrupt void GPIO_portD_int0( void ){
    if(BUTTON_LEFT_PORT.IN & BUTTON_LEFT_PIN){
        op_param.button_left_pushed = true; 
        CLR_BIT(PORTD.INT0MASK, MUTE_AUDIO_BIT);
        BT_toggle_mute();
        SET_BIT(PORTD.INT0MASK, MUTE_AUDIO_BIT);
    }
}


