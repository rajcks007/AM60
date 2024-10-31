#include "usart.h"
#include <ioavr.h>
#include "bluetooth.h"

//
//void USART_init(const USART_t *const usart_initStruct, USART_t *const usart){
//    usart->BAUDCTRLA = usart_initStruct->BAUDCTRLA;
//    usart->BAUDCTRLB = usart_initStruct->BAUDCTRLB;
//    usart->CTRLA = usart_initStruct->CTRLA;
//    usart->CTRLB = usart_initStruct->CTRLB;
//    usart->CTRLC = usart_initStruct->CTRLC;
//}
//
//void USART_send(USART_t *const usart, const uint8_t data){
//    while((usart->STATUS & USART_DREIF_bm) == 0);
//    usart->DATA = data;
//}
//
//
//
///***************************************************************************************
//                          UART_A USB Rx INT von Bluetooth Modul WT 32A
//INT UART_A = USB wird von Rx ausgel@t   INT High Level
//**************************************************************************************/
//#pragma vector = USARTC1_RXC_vect
//__interrupt void Int_RX_UARTA( void ){
//    if((USARTC1.STATUS & (1 << USART_RXCIF_bp)) )       //USART A RXC = 1 wenn neuer CHAR im UDR
//    {
//        bt_buf.Rx_Puffer[bt_buf.RxLast ] = USARTC1.DATA;       /*Read the character + setze autom Flag zur𣫪*/
//        bt_buf.RxLast++;
//        if(bt_buf.RxLast >= USART_BUF_SIZE) bt_buf.RxLast = 0; /*--- Modify buffer pointers ---*/
//        bt_buf.RxCount++;
//    }
//}
