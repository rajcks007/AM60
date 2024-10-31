/**
*@file          board_conf.h
*
*/

#ifndef BOARD_CONF_H
#define BOARD_CONF_H
#include <ioavr.h>
#include "bin.h"


/*********************************** EEprom Adressen **********************************/
#define __Filter_EEAdr        (0x10)    // 1 Byte Filtereinstellung
#define __Kalibration_EEAdr   (0x30)    // 2 Byte Kalibrations wert;



// ----         ----            DMAC

// ----         ----            System Clock

#define CLKsys    16000000UL  /*Clock System  = PLL * CLK quarz, Osc, ext clock */
#define __C_CTRL     0x04  
#define __C_PSCTRL   0x00   
#define __C_LOCK     0x00  


//......................... Oscillator - ext Quarz ............................................
#define __O_CTRL     0x10 
#define __O_Status   0x10  
#define __O_XOSCCTRL 0x00 
#define __O_PLLCTRL  0x08   


// ----         ----            Power Management

// ----         ----            Reset System

// ----         ----            bat_lvltery Backup System

// ----         ----            Watchdog Timer

// ----         ----            Interrupts
#define __PMIC_CTRL     0x07   //00---011 S.128 PMIC Control REG

// ----         ----            GPIO
#define BT_PWR_PIN              (BIT_6)         ///< power supply of BT
#define BT_PWR_PORT             (PORTA.OUT)
#define BT_UART_RX_PIN          (BIT_7)        
#define BT_UART_RX_PORT         (PORTC.IN)
#define BT_UART_TX_PIN          (BIT_6)
#define BT_UART_TX_PORT         (PORTB.OUT)
#define BT_UART_RTS_PIN         (BIT_5)         ///< Ready to send
#define BT_UART_RTS_PORT        (PORTC)
#define BT_UART_CTS_PIN         (BIT_4)         ///< Clear to send        
#define BT_UART_CTS_PORT        (PORTC)
#define BT_P3_2_PIN             (BIT_3)         ///< GPIO Pin
#define BT_P3_2_PORT            (PORTB.OUT)
#define BT_P2_6_PIN             (BIT_0)         ///< GPIO Pin
#define BT_P2_6_PORT            (PORTB.IN)
#define BT_RST_N_PORT           (PORTB.OUT)         ///< Reset Pin
#define BT_RST_N_PIN            (BIT_7)

#define GYRO_CS_PORT            (PORTD.OUT)
#define GYRO_CS_PIN             (BIT_4)         ///< Chip select

#define LCD_B0_PORT             (PORTA.OUT)         ///< Outer Part of bat_lvltery symbol
#define LCD_B0_PIN              (BIT_0)
#define LCD_B1_PORT             (PORTA.OUT)         ///< first (left) bar of bat_lvltery symbol
#define LCD_B1_PIN              (BIT_1)
#define LCD_B2_PORT             (PORTA.OUT)         ///< second bar of bat_lvltery symbol        
#define LCD_B2_PIN              (BIT_2)         
#define LCD_B3_PORT             (PORTA.OUT)         ///< third bar of bat_lvltery symbol
#define LCD_B3_PIN              (BIT_4)
#define LCD_B4_PORT             (PORTA.OUT)         ///< fourth (right) bar of bat_lvltery symbol
#define LCD_B4_PIN              (BIT_5)

#define LCD_T1_PORT             (PORTD.OUT)
#define LCD_T1_PIN              (BIT_7)
#define LCD_T2_PORT             (PORTE.OUT)
#define LCD_T2_PIN              (BIT_0)
#define LCD_T3_PORT             (PORTR.OUT)
#define LCD_T3_PIN              (BIT_0)
#define LCD_T4_PORT             (PORTR.OUT)
#define LCD_T4_PIN              (BIT_1)
#define LCD_1A_PORT             (PORTE.OUT)
#define LCD_1A_PIN              (BIT_1)
#define LCD_1B_PORT             (PORTE.OUT)
#define LCD_1B_PIN              (BIT_2)
#define LCD_1C_PORT             (PORTE.OUT)
#define LCD_1C_PIN              (BIT_3)
#define LCD_1D_PORT             (PORTE.OUT)
#define LCD_1D_PIN              (BIT_4)
#define LCD_1E_PORT             (PORTE.OUT)
#define LCD_1E_PIN              (BIT_5)
#define LCD_1F_PORT             (PORTE.OUT)
#define LCD_1F_PIN              (BIT_6)
#define LCD_1G_PORT             (PORTE.OUT)
#define LCD_1G_PIN              (BIT_7)
#define LCD_COMM_PORT           (PORTF.OUT)
#define LCD_COMM_PIN            (BIT_0)
#define LCD_2A_PORT             (PORTF.OUT)
#define LCD_2A_PIN              (BIT_1)
#define LCD_2B_PORT             (PORTF.OUT)
#define LCD_2B_PIN              (BIT_2)
#define LCD_2C_PORT             (PORTF.OUT)
#define LCD_2C_PIN              (BIT_3)
#define LCD_2D_PORT             (PORTF.OUT)
#define LCD_2D_PIN              (BIT_4)
#define LCD_2E_PORT             (PORTF.OUT)
#define LCD_2E_PIN              (BIT_5)
#define LCD_2F_PORT             (PORTF.OUT)
#define LCD_2F_PIN              (BIT_6)
#define LCD_2G_PORT             (PORTF.OUT)
#define LCD_2G_PIN              (BIT_7)

#define EN_BAT_MEAS_PORT        (PORTD.OUT)
#define EN_BAT_MEAS_PIN         (BIT_6)

#define FLASHLIGHT_PORT            (PORTD.OUT)          
#define FLASHLIGHT_PIN       BIT_5              
#define LCD_BACKLIGHT_BIT    BIT_1              
#define LCD_BACKLIGHT_PORT    (PORTD.OUT)             

#define MUTE_AUDIO_PORT           (PORTD.OUT)          // Mute on / off
#define MUTE_AUDIO_BIT            (BIT_0)              // Power on / off

#define FILTER_SELECT_PORT      (PORTB.OUT)          //
#define FILTER_SELECT_MASK      (BIT_1)              // 0 = Low Pass, 1 = High Pass ein

#define FILTER_ON_OFF_PORT      (PORTB.OUT)          //
#define FILTER_ON_OFF_MASK      (BIT_6)              // 0 = Filter off, 1 filter on

#define EXT_SENSOR_DETECTION_PORT  (PORTB.IN)           // ext Sensor ist angeschlossen
#define EXT_SENSOR_DETECTION_PIN  (BIT_4)              // 1= ext Sensor ist angeschlossen

#define EXT_SENSOR_SELECT_PORT   (PORTB.OUT)          // 1= ext Sensor ist aktiv zum Messen
#define EXT_SENSOR_SELECT_PIN   (BIT_5)              // 1= ext Sensor ist aktiv zum Messen


#define POWER_ON_PORT           (PORTD.OUT)          // Power on / off
#define POWER_ON_PIN           (BIT_3)              // Power on / off

#define BUTTON_LEFT_PORT        (PORTD )             
#define BUTTON_LEFT_PIN        (BIT_2)              

#define BUTTON_RIGHT_PORT       (PORTB)              
#define BUTTON_RIGHT_PIN       (BIT_2)    



//............................ P O R T  A .........................................
#define __PA_DIR        b01110111            /*  Data direction register 0/1 IN/OUT */  // alles IN, "OUT" siehe"Check_Hardwareversion"
#define __PA_OUT        b00110111            /*  Data register 0/1 : low/high Level */
#define __PA_PIN_SR     0x00            /*  Pins Slew Rate: 0/1: disable/enable*/
#define __PA_PIN_OP     0,0,0,0,0,0,0,0 /* Pins Output/Pull: 0:OP/IP; 2:OP/IP+PD; 3:OP/IP+PU;*/

#define __PA_INT0_Mask  b00000000            /*  Pins Interrupt 0 Mask Register*/
#define __PA_INT1_Mask  b00000000            /*  Pins Interrupt 1 Mask Register*/
#define __PA_INT0_CTRL  0x02            /* Pins Int 0 Level 0: off; 1:Low; 2:med; 3:high*/
#define __PA_INT1_CTRL  0x02            /* Pins Int 1 Level 0: off; 1:Low; 2:med; 3:high*/
#define __PA_PIN_IS     0,0,0,0,0,0,0,0 /* Pins INT Sens: 0:both edge; 1:rising; 2:falling; 3:low level*/

//..........................2.. P O R T  B .........................................
#define __PB_DIR        b11101010            /*  Data direction register 0/1 IN/OUT */
#define __PB_OUT        b00000000            /*  Data register 0/1 : low/high Level */
#define __PB_PIN_SR     b00000001            /*  Pins Slew Rate: 0/1: disable/enable*/
#define __PB_PIN_OP     0,0,0,3,0,0,0,2 /* Pins Output/Pull: 0:OP/IP; 2:OP/IP+PD; 3:OP/IP+PU;*/

#define __PB_INT0_Mask  b00000000            /*  Pins Interrupt 0 Mask Register*/
#define __PB_INT1_Mask  b00000100            /*  Pins Interrupt 1 Mask Register*/
#define __PB_INT0_CTRL  2            /* Pins Int 0 Level 0: off; 1:Low; 2:med; 3:high*/
#define __PB_INT1_CTRL  2            /* Pins Int 1 Level 0: off; 1:Low; 2:med; 3:high*/
#define __PB_PIN_IS     0,0,0,0,0,1,0,0 /* Pins INT Sens: 0:both edge; 1:rising; 2:falling; 3:low level*/

//............................ P O R T  C .........................................
#define __PC_DIR        b00000000            /*  Data direction register 0/1 IN/OUT */
#define __PC_OUT        0x00            /*  Data register 0/1 : low/high Level */
#define __PC_PIN_SR     0x00            /*  Pins Slew Rate: 0/1: disable/enable*/
#define __PC_PIN_OP     0,0,0,0,0,0,3,3 /* Pins Output/Pull: 0:OP/IP; 2:OP/IP+PD; 3:OP/IP+PU;*/

#define __PC_INT0_Mask  b00000000            /*  Pins Interrupt 0 Mask Register*/
#define __PC_INT1_Mask  b00001100            /*  Pins Interrupt 1 Mask Register*/
#define __PC_INT0_CTRL  0            /* Pins Int 0 Level 0: off; 1:Low; 2:med; 3:high*/
#define __PC_INT1_CTRL  0x02            /* Pins Int 1 Level 0: off; 1:Low; 2:med; 3:high*/
#define __PC_PIN_IS     0,0,0,0,0,0,0,0 /* Pins INT Sens: 0:both edge; 1:rising; 2:falling; 3:low level*/

//............................ P O R T  D .........................................
#define __PD_DIR        b11111011            /*  Data direction register 0/1 IN/OUT */
#define __PD_OUT        0x00            /*  Data register 0/1 : low/high Level */
#define __PD_PIN_SR     0x00            /*  Pins Slew Rate: 0/1: disable/enable*/
#define __PD_PIN_OP     0,0,0,0,0,0,0,0 /* Pins Output/Pull: 0:OP/IP; 2:OP/IP+PD; 3:OP/IP+PU;*/

#define __PD_INT0_Mask  b00000100            /*  Pins Interrupt 0 Mask Register*/
#define __PD_INT1_Mask  0x00            /*  Pins Interrupt 1 Mask Register*/
#define __PD_INT0_CTRL  0x02            /* Pins Int 0 Level 0: off; 1:Low; 2:med; 3:high*/
#define __PD_INT1_CTRL  0x00            /* Pins Int 1 Level 0: off; 1:Low; 2:med; 3:high*/
#define __PD_PIN_IS     0,0,0,0,0,1,0,0 /* Pins INT Sens: 0:both edge; 1:rising; 2:falling; 3:low level*/


//............................ P O R T  E .........................................
#define __PE_DIR        b11111111            /*  Data direction register 0/1 IN/OUT */
#define __PE_OUT        b11111111            /*  Data register 0/1 : low/high Level */
#define __PE_PIN_SR     0x00            /*  Pins Slew Rate: 0/1: disable/enable*/
#define __PE_PIN_OP     0,0,0,0,0,0,0,0 /* Pins Output/Pull: 0:OP/IP; 2:OP/IP+PD; 3:OP/IP+PU;*/

#define __PE_INT0_Mask  0x00            /*  Pins Interrupt 0 Mask Register*/
#define __PE_INT1_Mask  0x00            /*  Pins Interrupt 1 Mask Register*/
#define __PE_INT0_CTRL  0x00            /* Pins Int 0 Level 0: off; 1:Low; 2:med; 3:high*/
#define __PE_INT1_CTRL  0x00            /* Pins Int 1 Level 0: off; 1:Low; 2:med; 3:high*/
#define __PE_PIN_IS     0,0,0,0,0,0,0,0 /* Pins INT Sens: 0:both edge; 1:rising; 2:falling; 3:low level*/


//............................ P O R T  F .........................................
#define __PF_DIR        b11111111       /*  Data direction register 0/1 IN/OUT */
#define __PF_OUT        b11111111            /*  Data register 0/1 : low/high Level */
#define __PF_PIN_SR     0x00            /*  Pins Slew Rate: 0/1: disable/enable*/
#define __PF_PIN_OP     0,0,0,0,0,0,0,0 /* Pins Output/Pull: 0:OP/IP; 2:OP/IP+PD; 3:OP/IP+PU;*/

#define __PF_INT0_Mask  0x00            /*  Pins Interrupt 0 Mask Register*/
#define __PF_INT1_Mask  0x00            /*  Pins Interrupt 1 Mask Register*/
#define __PF_INT0_CTRL  0x00            /* Pins Int 0 Level 0: off; 1:Low; 2:med; 3:high*/
#define __PF_INT1_CTRL  0x00            /* Pins Int 1 Level 0: off; 1:Low; 2:med; 3:high*/
#define __PF_PIN_IS     0,0,0,0,0,0,0,0 /* Pins INT Sens: 0:both edge; 1:rising; 2:falling; 3:low level*/

//............................ P O R T  R.........................................
#define __PR_DIR        b00000011      /*  Data direction register 0/1 IN/OUT */
#define __PR_OUT        b00000011            /*  Data register 0/1 : low/high Level */
#define __PR_PIN_SR     0x00            /* Pins Slew Rate: 0/1: disable/enable*/
#define __PR_PIN_OP     0,0,0,0,0,0,0,0 /* Pins Output/Pull: 0:OP/IP; 2:OP/IP+PD; 3:OP/IP+PU;*/

#define __PR_INT0_Mask  0x00            /* Pins Interrupt 0 Mask Register*/
#define __PR_INT1_Mask  0x00            /* Pins Interrupt 1 Mask Register*/
#define __PR_INT0_CTRL  0x00            /* Pins Int 0 Level 0: off; 1:Low; 2:med; 3:high*/
#define __PR_INT1_CTRL  0x00            /* Pins Int 1 Level 0: off; 1:Low; 2:med; 3:high*/
#define __PR_PIN_IS     0,0,0,0,0,0,0,0 /* Pins INT Sens: 0:both edge; 1:rising; 2:falling; 3:low level*/


// ----         ----            Timer / Counter
#define __TC0_1_usec   0x0010  /*   16 = 16000000 *   10        / (1000 000 *   1   )  */
#define __TC0_10_usec  0x0087  /*  160 = 16000000 *   10        / (1000 000 *   1   )  */
#define __TC0_100_usec 0x0638  /* 1600 = 16000000 *  100        / (1000 000 *   1   )  */
#define __TC0_1_msec   0x3E80  /*16000 = 16000000 * 1000        / (1000 000 *   1   )  */
#define __TC0_CTRLA    0x01    //----0111 S.165 Timer Control A  -- !!! Beachte Power Management !!!
/*7:4 fix 0, 3:0 Clock select  off bis clk/1024  */
#define __TC0_CTRLB    0x00    //0001-000 S.165 Timer Control B   0x00 = No Compare, normal Operation
/*7:4 Compare or Capture output enable A-D,3 fix0, 2:0 Waveform Generation   */
#define __TC0_CTRLC    0x00    //----0000 S.166 Timer Control C
/*7:4 fix 0, 3:0 Compare Output Value -> f𲠔imer Betrieb = 0; */
#define __TC0_CTRLD    0x00    //00000000 S.167 Timer Control D
/*7:5 Event Action, 4: Delay Event, 3:0 Event Source  */
/* -> f𲠔imer Betrieb = 0;  */
#define __TC0_CTRLE    0x00    //-------0 S.168 Timer Control E
/*7:1 fix 0, 0: 8 Bit Mode -> f𲠔imer Betrieb = 0;  */
#define __TC0_INTCTRLA 0x00    //----0000 S-168 Timer Interrupt Enable REG A
/*7:3 fix 0, 3:2 Timer Error Int Level, 1:0 Over/Under-flow Int Level  */
#define __TC0_INTCTRLB 0x00    //00000000 S-168 Timer Interrupt Enable REG B
/*7:0 Timer Compare or Capture Int Level A-D Channels  */
/*pro Timer Typ0 =4 Typ1 =2 Compare/Capture Channels  */
#define __TC0_CTRLFSET 0x00    //----0000 S-169 Timer Control Timer Clear/SET  REG F
/*7:4 fix 0, 3:2 Timer/Conder Command, 1:Lock Updater, 0:Counter Direction  */
#define __TC0_CCA   __TC0_1_usec  //S-173 16Bit Wert f𲠔imer Compare/Capture REG A
#define __TC0_CCB   __TC0_10_usec //S-173 16Bit Wert f𲠔imer Compare/Capture REG B
#define __TC0_CCC   __TC0_100_usec//S-173 16Bit Wert f𲠔imer Compare/Capture REG B
#define __TC0_CCD   __TC0_1_msec  //S-173 16Bit Wert f𲠔imer Compare/Capture REG B

//Takte = CLKcpu   * zeit[usec] / (1000 000 *  Teiler)
#define TC1_200msec    ((15625 / 5) * 3)    

#define __TC1_CTRLA    0x07    //----0111 S.165 Timer Control A    -- !!! Beachte Power Management !!!
/*7:4 fix 0, 3:0 Clock select  off bis clk/1024  */
#define __TC1_CTRLB    0x00    //0000-000 S.165 Timer Control B   0x00 = No Compare, normal Operation
/*7:4 Compare or Capture enable A-B,3 fix0, 2:0 Waveform Generation   */
#define __TC1_CTRLC    0x00    //----0000 S.166 Timer Control C
/*7:4 fix 0, 3:0 Compare Output Value -> f𲠔imer Betrieb = 0; */
#define __TC1_CTRLD    0x00    //00000000 S.167 Timer Control D
/*7:5 Event Action, 4: Delay Event, 3:0 Event Source  */
/* -> f𲠔imer Betrieb = 0;  */
#define __TC1_CTRLE    0x00    //-------0 S.168 Timer Control E
/*7:1 fix 0, 0: 8 Bit Mode -> f𲠔imer Betrieb = 0;  */
#define __TC1_INTCTRLA 0x01    //----0000 S-168 Timer Interrupt Enable REG A
/*7:3 fix 0, 3:2 Timer Error Int Level, 1:0 Over/Under-flow Int Level  */
#define __TC1_INTCTRLB 1    //00000001 S-168 Timer Interrupt Enable REG B
/*7:0 Timer Compare or Capture Int Level A-B Channels  */
/*pro Timer Typ0 =4 Typ1 =2 Compare/Capture Channels  */
#define __TC1_CTRLFSET 1    //----0001 S-169 Timer Control Timer Clear/SET REG F
/*7:4 fix 0, 3:2 Timer/Conder Command, 1:Lock Updater, 0:Counter Direction  */
#define __TC1_CCA      0x0000  //S-173 16Bit Wert f𲠔imer Compare/Capture REG A
#define __TC1_CCB      0x0000  //S-173 16Bit Wert f𲠔imer Compare/Capture REG B
#define __TC1_PER  TC1_200msec //S-173 16Bit Wert f𲠐erodisches Reload im Normal Modus

//                     ........Timer D0 mit 2 Capture/Compare Reg..........
//                     NF-sampeling: Abtastrate Grundfrequenz = 125 usec f𲠁DC
//Takte = CLKcpu   * zeit[usec] / (1000 000 *  Teiler)
#define __TD0_1msec    0x0F    // 15 = 16000000 *   1000  / (1000 000 * {clk=1024} ) {1msec}

#define __TD0_CTRLA    0x01    //----0111 S.165 Timer Control A   -- !!! Beachte Power Management !!!
/*7:4 fix 0, 3:0 Clock select  off bis clk/1024  */
#define __TD0_CTRLB    0x01    //0000-000 S.165 Timer Control B   0x00 = No Compare, normal Operation
/*7:4 Compare or Capture enable A-D,3 fix0, 2:0 Waveform Generation   */
#define __TD0_CTRLC    0x00    //----0000 S.166 Timer Control C
/*7:4 fix 0, 3:0 Compare Output Value -> f𲠔imer Betrieb = 0; */
#define __TD0_CTRLD    0x00    //00000000 S.167 Timer Control D
/*7:5 Event Action, 4: Delay Event, 3:0 Event Source  */
/* -> f𲠔imer Betrieb = 0;  */
#define __TD0_CTRLE    0x00    //-------0 S.168 Timer Control E
/*7:1 fix 0, 0: 8 Bit Mode -> f𲠔imer Betrieb = 0;  */
#define __TD0_INTCTRLA 0x00    //----0000 S-168 Timer Interrupt Enable REG A
/*7:3 fix 0, 3:2 Timer Error Int Level, 1:0 Over/Under-flow Int Level  */
#define __TD0_INTCTRLB 0x00    //00000001 S-168 Timer Interrupt Enable REG B
/*7:0 Timer Compare or Capture Int Level A-D Channels  */
/*pro Timer Typ0 =4 Typ1 =2 Compare/Capture Channels  */
#define __TD0_CTRLFSET 0x00    //----0001 S-169 Timer Control Timer Clear/SET  REG F
/*7:4 fix 0, 3:2 Timer/Conder Command, 1:Lock Updater, 0:Counter Direction  */
#define __TD0_CCA      0x0000  //S-173 16Bit Wert f𲠔imer Compare/Capture REG A
#define __TD0_CCB      0x0000  //S-173 16Bit Wert f𲠔imer Compare/Capture REG B
#define __TD0_PER  __TD0_1msec //S-173 16Bit Wert f𲠐erodisches Reload im Normal Modus


//                     ........Timer D1 mit 2 Capture/Compare Reg..........
//                     LCD Takt f𲠓egmente
//Takte = CLKcpu   * zeit[usec] / (1000 000 *  Teiler)
#define __TD1_1sec    0x3D09   // 15625 = 16000000 *   1000000  / (1000 000 * {clk=1024} ) {1sec}
//#define __TD1_64msec  0x0E1    // 15 msec f𲠶4 Hz Takt
#define __TD1_64msec  0x1c2    // 15 msec f𲠶4 Hz Takt

#define __TD1_CTRLA    0x07    //----0111 S.165 Timer Control A    -- !!! Beachte Power Management !!!
/*7:4 fix 0, 3:0 Clock select  off bis clk/1024  */
#define __TD1_CTRLB    0x01    //0000-000 S.165 Timer Control B   0x00 = No Compare, normal Operation
/*7:4 Compare or Capture output enable A-D,3 fix0, 2:0 Waveform Generation   */
#define __TD1_CTRLC    0x00    //----0000 S.166 Timer Control C
/*7:4 fix 0, 3:0 Compare Output Value -> f𲠔imer Betrieb = 0; */
#define __TD1_CTRLD    0x00    //00000000 S.167 Timer Control D
/*7:5 Event Action, 4: Delay Event, 3:0 Event Source  */
/* -> f𲠔imer Betrieb = 0;  */
#define __TD1_CTRLE    0x00    //-------0 S.168 Timer Control E
/*7:1 fix 0, 0: 8 Bit Mode -> f𲠔imer Betrieb = 0;  */
#define __TD1_INTCTRLA 0x00    //----0010 S-168 Timer Interrupt Enable REG A
/*7:3 fix 0, 3:2 Timer Error Int Level, 1:0 Over/Under-flow Int Level  */
#define __TD1_INTCTRLB 0x01    //00000001 S-168 Timer Interrupt Enable REG B
/*7:0 Timer Compare or Capture Int Level A-D Channels  */
/*pro Timer Typ0 =4 Typ1 =2 Compare/Capture Channels  */
#define __TD1_CTRLFSET 0x00    //----0001 S-169 Timer Control Timer Clear/SET  REG F
/*7:4 fix 0, 3:2 Timer/Conder Command, 1:Lock Updater, 0:Counter Direction (0=up,1=down) */
#define __TD1_CCA __TD1_64msec //S-173 16Bit Wert f𲠔imer Compare/Capture REG A
#define __TD1_CCB      0x0000  //S-173 16Bit Wert f𲠔imer Compare/Capture REG B
#define __TD1_PER __TD1_64msec //S-173 16Bit Wert f𲠐erodisches Reload im Normal Modus



#define __TE0_CTRLA    (TC0_CLKSEL2_bm | TC0_CLKSEL1_bm | TC0_CLKSEL0_bm)   
#define __TE0_CTRLB    (TC0_CCAEN_bm)   
#define __TE0_CTRLC    0x00    
#define __TE0_CTRLD    0x00    
#define __TE0_CTRLE    0x00    
#define __TE0_INTCTRLA 0x00   
#define __TE0_INTCTRLB 0x00   
#define __TE0_CTRLFSET 0x00    
#define __TE0_CCA      15625            // 1 second based on f := 16 MHz with prescaler 1024
#define __TE0_CCB      0  
#define __TE0_CCC      0  
#define __TE0_CCD      0  
#define __TE0_PER      15625 

#define __TE1_CTRLA    (TC1_CLKSEL2_bm | TC1_CLKSEL1_bm | TC1_CLKSEL0_bm)   
#define __TE1_CTRLB    BIT_4//(TC1_CCAEN_bm)   
#define __TE1_CTRLC    0x00    
#define __TE1_CTRLD    0x00    
#define __TE1_CTRLE    0x00    
#define __TE1_INTCTRLA 0x00   
#define __TE1_INTCTRLB b00000011   
#define __TE1_CTRLFSET 0x00    
#define __TE1_CCA      15625            // 1 second based on f := 16 MHz with prescaler 1024
#define __TE1_CCB      0  
#define __TE1_PER      15625 

#define __TF0_CTRLA    (TC1_CLKSEL2_bm | TC1_CLKSEL1_bm | TC1_CLKSEL0_bm) 
#define __TF0_CTRLC    0x00    
#define __TF0_CTRLD    0x00    
#define __TF0_CTRLE    0x00    
#define __TF0_INTCTRLA 0x00   
#define __TF0_INTCTRLB 0x00   
#define __TF0_CTRLFSET 0x00    
#define __TF0_CCA      15625            // 1 second based on f := 16 MHz with prescaler 1024
#define __TF0_CCB      0  
#define __TF0_CCC      0  
#define __TF0_CCD      0  
#define __TF0_PER      15625 



// ----         ----            Advanced Waveform Extension

// ----         ----            High-Resolution Extension

// ----         ----            Real Time Counter
#define __C_RTCCTRL    0x00    // ----0100 S.86 RTC Control REG  -- !!! Beachte Power Management !!!
/*7:4 fix 0, 3:1-Clock Source 000=int 1KHz ULP (ultralow Power), 001=1,024KHz von ext 32KHz Quarz, */
/* 010=1KHz von int 32KHz RC, 101=ext RC, 110=32KHz von int 32KHZ RC, 111=ext clock an TOSC1; 0: RTC clock enable*/
#define __RTC_CTRL     0x07    //-----111 S.191 Timer Control A  hier /1024
/*7:3 fix 0, 2:0 Clock select  off bis clk/1024  */
#define __RTC_INTCTRL  0x05    //----0101 S.192 Real Time Interrupt Control
/*7:4 fix 0, 3:2 Compare INT Level, 1:0 Overflow INT Level*/
#define __RTC_PER      0xFD20  //64800=18Std,  16Bit  S.194 Real Time Counter Period REG
/*Wenn Counter den Wert "RTC_PER" erreicht wird Overflow INT gesetzt*/
#define __RTC_COMP     0x20    //0x00  16Bit  S.194 Real Time Compare REG
/*Wenn Counter den Wert "RTC_COMP" erreicht wird Compare INT gesetzt*/
#define __CRTCCTRL_8564 0x03   //bei RTC 8564 ist ext Quarz verbaut
#define __CRTCCTRL_3029 0x0F   //bei RTC 3029 wird temp komp Takt von RTC genutzt

// ----         ----            32-Bit Real Time Counter

// ----         ----            Two Wire Interface
#define TWI_I2C                     TWIC                // Two Wire Interface
#define TWI_INT1                    TWIC_TWIM_vect

// ----         ----            Serial Peripheral Interface


// ----         ----            USART
#define USART_OFF (*(USART_t *) 0x000)                   // USART aus

//                .............UART A: Bluetooth WT-32A 115200 Baud; UARTE0: PE2=RX; PE3=TX;
// Berechnung: CPU 16MHz; Baudrate 115200; BSEL 983; Bscale -7; CLK2X 0; Error: 115212 = 0,01%
#define __USART_A               (USARTC1)          // UART_A PIN Adresse
#define __USART_A_INT_vect      (USARTC1_RXC_vect) // UART_A Adresse INT vector
#define __USART_A_BSEL   0x03d7 //0011 11010111: 983 S.254 BSEL aus Exel "Baudrate XMEGA"
#define __USART_A_BSCALE (-7)   //1001: -7 S.254 Bscale aus Exel "Baudrate XMEGA" (1111=-1)(1001=-7) (0111=7) (1000=-8:verboten)
#define __USART_A_CTRLA  0x30   //--110000 S.251 USART Control REG A
/*7:6 fix 0; 5:4 Receive Complete INT Level; 3:2 Transmit Complete INT Level; 1:0 Data REG Empty INT Level*/
#define __USART_A_CTRLB  0x18   //---11000 S.251 USART Control REG B
/*7:5 fix 0; 4:RXEN; 3:TXEN; 2:CLK2X; 1:MPCM; 0:TXB8*/
#define __USART_A_CTRLC  0x03   //00000011 S.252 USART Control REG C
/*7:6 USART Communication Mode; 5:4 Parity Mode; 3:Stop Bit; 2:0 Char Size*/

// ----         ----            IR Communication Module

// ----         ----            AES / DES Crypto

// ----         ----            Analog-to-Digital Converter
//Es gibt 1 ADCs  ADC_A : Port A;
//In CTRL_A k@nen bis zu 4 Eingangs-Kan孥 gleichzeitig (Kanal Nr 0-3 nacheinander versetzt um 1 clock) gestartet werden
//Jedem Eingangs-Kanal kann ein beliebiger Pin des ADC zugeordnet werden
//Als Quellen k@nen Port.Pins oder Interne Quellen wie Vcc, tempeatur.. gew婬t werden
//Setzen der Start-Bits (Gruppe in CTRL A; Einzel in ADCA_CHx_CTRL) startet die Wandlung einmal
//wir benutzten internal , signed, unsigned Single end ; differential Eingang
//f𲠳ingle end (PORT PIN) signed setzt der ADC die 0 auf 1/2 Vref; >1/2 Vref = +; <1/2 Vref = -;

//.............feste Register Definitionen -- nicht 寤ern
//ADC Channel CTRL Gain S.309     x1         x2        x4        x8       x16       x32       x64
#define Def_ADC_Gain(X) uint8_t (X) [7]= {(0x00<<2),(0x01<<2),(0x02<<2),(0x03<<2),(0x04<<2),(0x05<<2),(0x06<<2)}
//ADC Channel CTRL Input Mode      Internal posetiv input    Singel-ended postiv input  || FAST  kein Differenzeingang zul
#define Def_ADC_InMo(X) uint8_t (X) [2]= {           (0x00<<0),                (0x01<<0) }
//ADC Channel Mux CTRL  MUX POS intern   Temperatur  Bandgap   Vcc/10   DAC output
#define Def_ADC_MPi(X)  uint8_t (X) [4]= {           (0x00<<3),(0x01<<3),(0x02<<3),(0x03<<3) }
//ADC Channel Mux CTRL  MUX POS Port Pins            Pin 2     Pin 3     Pin 4     Pin 5     Pin 6      Pin 7
#define Def_ADC_MPPP(X) uint8_t (X) [8]= {(0x00<<3),(0x01<<3),(0x02<<3),(0x03<<3),(0x04<<3),(0x05<<3),(0x06<<3),(0x07<<3)}
//ADC Channel INT CTRL  Level     off      low      medium     high
#define Def_ADC_INTL(X) uint8_t (X) [4]= {(0x00<<0),(0x01<<0),(0x02<<0),(0x03<<0)}
//............................. ADC  A .........................
#define ADC_A_aktiv     OK   //aktiviert das init von Kanal A   -- !!! Beachte Power Management !!!
//.......................PORTA ADC A: Eingaben f𲠁DC A alle Kan孥
#define __ADC_A_CTRL_A   0x00  //00000000: S.302 ADC Control A Register
/*7:6 DMASEL OFF=0; 5:2 START Gruppen Conversion;*/
/*1:FLUSH 1=restart ADC  0: ADC Enable =1*/
#define __ADC_A_CTRL_B   0x00  //0000000-: S.302 ADC Control B Register
/*7:Impedance Gain; 6:5 Current limit; 4:CONVMODE unsigned=0 signed=1; 3:Freerun 0=No */
/*2:1Resulution 00=12Bit right adjust; 0: fix 0*/
#define __ADC_A_REFCTRL  0x00  //---00-00: S.303 REFCTRL ADC Referenz Control Register
/*7:5 fix 0; 4:3 Referenz 00= 1.0V Int, 01= Vcc/1.6; 3:2 fix 0; */
/*1: Bandgap 1=ON 0:TEMPREF 1:Tempref enable*/
#define __ADC_A_EVCTRL   0x00  //00000000: S.304 EVCTRL ADC Event Control Register
/*7:6 Sweep Channel Sweep 0; 5:3 Event Channel input */
/*2:0 ADC Event Mode 0=No event inputs*/
#define __ADC_A_PRESCALE  0x05  //-----101: S.305 Prescaler ADC Prescaler Register
/*7:3 fix 0; 2:0 Prescaler CLKper/Presc 000:4; 001:8; 010:16; */
/*011:32; 100:64; 101:128; 110:256; 111:512 */

//..............................PORT A ADC A: FAST Chanels 0-7 Defs f𲠤ie 4 XMEGA virtuelle Kan孥 --> in AZBI wird alles eizeln in Setup initialisiert
// FAST Chanel       7 6 5 4 3 2 1 0 || PORT A PIN Def:  0:PA0 Zeitsignal, 1:PA1 Gleichrichter Sig , 2:bat_lvl, 3:Test NF 0,5V Anhebung+Random, 4:----, 5:--, 6:--, 7:--
#define __ADC_A_Gain 0,0,0,0,0,0,0,0 /*Gain S.310: 0:x1; 1:x2; 2:x4; 3:x8; 4:x16; 5:x32; 6:64*/
#define __ADC_A_Mode 0,0,0,0,0,0,1,1 /*Input Mode S.310: (unsigned Mode CON=0): 0:Internal positiv Input; 1:(Port Pin Source) Single ended positiv Input; */
/*                  (signed Mode   CON=1): 0:Internal positiv Input; 1:(Port Pin Source) Single ended positiv Input; 2:Diff input 3:Diff input+Gain)*/
#define __ADC_A_Mux  0,0,0,0,0,0,7,3 /*Mux pos S.311: bei Input Mode=0 (intern Source): Input 0:Temperatur, 1:Bandgap Volt, 2:Vcc/10, 3:DAC output*/
/*Input Mode=1 (Port Pin Source): Port A Pin Nr 0-7
  Mux neg S.311: Beachte -> FAST these bits are not in use.*/
#define __ADC_A_INT  0,0,0,0,0,0,0,0 /*INT S.312: 0:kein, INT aktiv low-high level: 1-3 */

  // ----         ----            Digital-to-Analog Converter
  // 1x 12 Bit DAC in Port B -> DAC B; Der DAC k@nen 𢥲 Sample and Hold je zwei
  // Port Pins bedienen; Im Status Register (S.324) kann gepr𦴠werden ob der Wert ausgeben ist;

  // .........PORT B Pin2+3 unbenutzt
#define DAC_B_aktiv NOT_OK    //aktiviert das init von DAC A   -- !!! Beachte Power Management !!!
#define __DC_B_CTRLA   0x04    //---001-0: S.320 DAC A Control Register A
/*7:5 fix 0; 4: IDOEN 1:DAC out 𢥲 ADC Mux; 3:CH1EN 1:CH 1=Pin3 enable*/
/*2:CH0EN 1:CH 0 = Pin2 enable; 1: fix 0; 0: Enable 1:DAC A enable */
#define __DC_B_CTRLB   0x00    //-00---00: S.320 DAC A Control Register B
/*7: fix 0; 6:5 CHSEL channel select 00:single, 01--, 10:Duel, 11--;*/
/*4:2 fix 0; 1: CH1TRIG: CH1 Event Trigger Mode; 1: CH2TRIG: CH2 Event Trigger Mode; */
#define __DC_B_CTRLC   0x10    //---10--0: S.321 DAC A Control Register C
/*7:5 fix 0; 4:3 RefSEL Refenz 00:INT1V, 01: AVcc, 10:AREFA, 11:AREFB;*/
/*2:1 fix 0; 0: LEFTADJ 1: CHO+CH1 Data left-ajustet */
#define __DC_B_EVCTRL  0x00    //-----000: S.322 DAC A Event Control Register
//7:3 fix 0; 2:0 EVSEL 000-111 Event channel x as input to DAC */
#define __DC_B_TIMCTRL 0x34    //-0110100: S.322 DAC A Timing Control Register
//7: fix 0; 6:4 CONINTVAL Intervall zwischen Wandlungen, kleinster zul Wert 1CH 1us 2CH 1,5us */
/* bei 16 MHz 1us : -> max 16 CLk  ; 1,5us -> max 24 Clk  S 323 1-128 CLK m@lich */
/*3:0 REFRESH: Refresh in dual Channel Mode  S/H schneller 30 us*/
/* bei 16 MHz 30 us -> 16*30 = max 480 Clk S323 15-65536 m@lich*/


// ----         ----            Analog Comperator
// je 2 Analog Comperatoren in Port A -> AC A; Port B -> AC B; Die Comperatoren k@nen einzeln
// oder paarweise mit Fensterfkt genutzt werden. IN1 = MUX POS; IN2 = MUX NEG
// Status Abfrage S. 334

//AC_A0: IN1=Pin A3; IN2=Ref VCC*(1/64); INT bei IN1>IN2 rising Signal; INT Level low, No Hysterese
#define AC_A_aktiv   NOT_OK  //aktiviert das init von AC A0 + A1   -- !!! Beachte Power Management !!!
//AC A0: aktiv
//AC A1: -----
#define __AC_A0_CTRL   0xD1    //11010000: S.331 AC A0 Control Register
/*7:6 INTMode INT at 00: ouptput toggle, 01 --, 10: falling output; 11 rising output*/
/*5:4 INTLVL INT Level  0:kein, INT aktiv low-high level: 1-3 */
/*3: HS Mode 1:High-Speed; 2:1 HYSMODE Hyterese 0:No,01 Small, 02 large,11--, */
/*0: Enable AC A0 -> wird in Init nicht gesetzt*/
#define __AC_A0_Mux    0x1F    //--011111: S.332 AC A0 MUX Control Register
/*7:6 --, 5:3 MUXPOS Input 1: 000-110: Pin0-Pin6, 111: DAC Output */
/*2:0 MUNEG Input 2: 000-100 Pin 0,1,3,5,7, 101:DAC, 110:BandGAP, 111:Vcc geteilt*/
#define __AC_A1_CTRL   0x00    //00000000: S.331 AC A1 Control Register
/*7:6 INTMode INT at 00: ouptput toggle, 01 --, 10: falling output; 11 rising output*/
/*5:4 INTLVL INT Level  0:kein, INT aktiv low-high level: 1-3 */
/*3: HS Mode 1:Hig-Speed; 2:1 HYSMODE Hyterese 0:No,01 Small, 02 large,11--, */
/*0: Enable AC A1 -> wird in Init nicht gesetzt*/
#define __AC_A1_Mux    0x00    //--000000: S.332 AC A1 MUX Control Register
/*7:6 --, 5:3 MUXPOS Input 1: 000-110: Pin0-Pin6, 111: DAC Output */
/*2:0 MUNEG Input 2: 000-100 Pin 0,1,3,5,7, 101:DAC, 110:BandGAP, 111:Vcc geteilt*/
#define __AC_A_CTRA    0x00    //-------0: S.333 AC A CTRLA Control Register
/*7:1 fix 0; 0: 1=AC output an Pin 7*/
#define __AC_A_CTRB    0x00    //--000000: S.333 AC A CTRLB Control Register
/*7:6 fix 0; 5:0 scalefaktor -> Vscale = Vcc*(scalefaktor +1) / 64 siehe AC Mux Bit 7*/
#define __AC_A_WinCTRL 0x00    //---00000: S.334 AC A Window Fkt Control Register
/*7:5 fix 0; 4:Wen: 1:Enable Window Mode; 3:2 Window Mode INT at 00: above Window,*/
/*  01: inside Win; 10: Below Win; 11:Outside Win; 1:0: WININTLVL: INT Level  0:kein, INT aktiv low-high level: 1-3 */

#define AC_B_aktiv  NOT_OK   //aktiviert das init von AC B   -- !!! Beachte Power Management !!!



// ----         ----            EEPROM


// ----         ----            Timer

// ----         ----            USART


/*.......Power Management............ S.97/98*/
//Powerdown und Powersave siehe entsprechende Routine; Idle siehe Timer TC0 f𲠡llgemeine Zeitschleifen
//Wenn hier Bits gesetzt sind, muss vor der Benutzung des Moduls die dazugeh@ende CL wieder durch l@hen des Bits aktiviert werden
// !!!!!!!!!!!!! Bit = 1 -> Modul nicht aktiv !!!!!!!!!!!!!

#define __Power_PRGEN  0x1F   //---11011: S98 0/1 Clock(CL) l嶦t/stop -> alle diese Module sollten zuvor gestoppt sein
/* 7:4 fix 0; 4:Cl AES Modul; 3:CL EBI ; 2:CL RTC; 1:CL Event Sys; 0:CL DMA*/
#define __Power_PRPA   0x05   //-----101: S99 0/1 Clock(CL) l嶦t/stop -> alle diese Module sollten zuvor gestoppt sein
/* 7:3 fix 0; 2:Cl DACs; 1:CL ADC ; 0:CL AC;*/
#define __Power_PRPB   0x07   //-----111: siehe __Power_PRPA
#define __Power_PRPC   0x7F   //-1010100: S99 0/1 Clock(CL) l嶦t/stop -> alle diese Module sollten zuvor gestoppt sein
/* 7:fix 0; 6:Cl TWI; 5:CL USART0 ; 4:CL USART1; 3:CL SPI; 2:CL HIRES Timer; 1:CL Timer 1; 0:CL Timer 0; */
#define __Power_PRPD   0x7C   //-1111100: siehe __Power_PRPC
#define __Power_PRPE   0x7F   //-0000100: siehe __Power_PRPC
#define __Power_PRPF   0x7F   //-0000000: siehe __Power_PRPC





// .........DMA  Info: Atmel AVR1304 Using the XMEGA DMA Controller
//CH0: hier  Trigger durch ADCA, Burst 2 BYTE, Block 176 Burst = 352 byte, Transfer Repeat 2 Block dann Reload Destin Adr
// Data transfer:  Burst Mode: 1,2,4 oder 8 Byte werden pro DMA Aufruf transportiert;
//                 Block Mode: Block mit L寧e X (max 64K) wird 𢥲tragen ist Block 100 BYTE, Burst = 4 BYTE dann ist Block nach 25 Burst Aurufen beendet
//                             reicht ein Block nicht kann mit Repeat Mode x mal Block L寧e definiert werden
//            DMA Transaction:  beinhaltet: alle Blockdaten mit x mal repeat sind 𢥲tragen
// Address mode :  Sowohl Source memory wie auch destination address kann fix oder inc oder dec angesprochen werden
// Repeat       :  Anz Block Transfer in REPCNT auf 0 und REPEAT in CTRLA auf 1 = unlimeted repeats; sonst Anzahl in REPCNT
#define DMA_aktiv  NOT_OK          //aktiviert das init von DMA A
//....................DMA 0
#define __DMA_CTRL   0x80      //10--0000: S.53 DMA Control Register
/*7: DMA Enable; 6:DMA Reset; 5:4-; 3:2 Double Puff mode; 1:0 Channel Priority*/
#define __DMA0_CTRLA  0x85     //1000-101: S.55 DMA Channel CTRLA
/*7: Ch enable; 6:Ch Reset; 5:Repeat Mode; 4: Ch Transfer Request; 3-; 2:Ch Single Shot; 1:0 Ch Burst Lengh*/
#define __DMA0_CTRLB  0x00     //00000000: S.56 DMA Channel CTRLB
/*7:busy Flag; 6:Block transfer Flag; 5:Error INT Flag; 4:DMA Transaction complete Flag */
/*3:2 Error Int Level 0: off; 1:Low; 2:med; 3:high;  1:0 Transaction complete INT Level 0-3*/
#define __DMA0_ADDRCTRL 0x9D   //10011101: S.57 DMA Channel Address Control Register  !!rmsn=(reloaded mit Startwert nach ...)!!
/*7:6 DMA Ch Source Adr Reload 00:No rmsn; 01: rmsn "Block transfer"; 10: rmSn "burst transfer"; 11: rmSn "Transaction" ;*/
/*5:4 DMA Ch Source Adr Mode   00:Fixed; 01:inc; 10:dec; 11:- */
/*3:2 DMA Ch Destin Adr Reload 00:No rmsn; 01: rmsn "Block transfer"; 10: rmSn "burst transfer"; 11: rmSn "Transaction" ;*/
/*1:0 DMA Ch Destin Adr Mode   00:Fixed; 01:inc; 10:dec; 11:- */
#define __DMA0_TRIGSRC 0x10    // 0x10: ADCA = 0x10      S.59 DMA Trigger Sources
#define __DMA0_TRFCNT   352    // max 0xffff,   S.60 DMA Block Transfer Count: number of byte in a block transfer
#define __DMA0_REPCNT    0     // max 0xFF : Anzahl Repeat of TRFCNT
#define __DMA0S_adr ADCA.CH0RES// Name der Source: Variablen name muߠin System-1 verf𧢡r sein -> hier ADCA Kanal 0

#define __DMA0D_adr Puffer     // Name der Destination hier Puffer




#endif  // BOARD_CONF_H