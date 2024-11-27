/**
 * \file    ring_buffer.h
 *
 *  Ring-Puffer
 *
 * \date    28.03.2019
 * \author  O. Soletskiy
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
  volatile uint_fast16_t head;    /* first byte of data (index to put/write)  */
  volatile uint_fast16_t tail;    /* last byte of data (index to get/read)*/
  volatile uint8_t *buffer;       /* block of memory or array of data */
  uint_fast16_t max;              /* max index of the buffer */
} ring_buffer_t;

bool fifo_empty(ring_buffer_t const *b);
uint8_t fifo_peak(ring_buffer_t const *b);
uint8_t fifo_get(ring_buffer_t *b);
bool fifo_put(ring_buffer_t *b, const uint8_t data_byte);
void fifo_init(ring_buffer_t *b, volatile uint8_t *buffer, uint16_t buffer_len);
uint16_t fifo_get_count(ring_buffer_t const *b);
void fifo_reset(ring_buffer_t *b);

#endif /* RING_BUFFER_H_ */
