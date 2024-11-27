#ifndef USART_H
#define USART_H

#include <ioavr.h>
#include <stdint.h>


typedef struct   {
    uint8_t *const Rx_Puffer;                     
    uint16_t Puffer_Laenge;                              
    uint16_t RxFirst;                                    
    uint16_t RxLast;                                   
    uint16_t RxCount;                                    
} USART_buf_t;

void USART_init(const USART_t *const usart_initStruct, USART_t *const usart);
void USART_send(USART_t *const usart, const uint8_t data);

#endif //USART_H