/**
 * @file    ring_buffer.c
 *
 *  Ring-Puffer
 *
 * @date    28.03.2019
 * @author  O. Soletskiy
 */

#include "ring_buffer.h"

 /**
  * Returns the number of elements in the ring buffer
  *
  * \param b Pointer to initialized buffer
  * \return  Number of elements in the ring buffer
  */
static  uint16_t fifo_count(ring_buffer_t const* b) {
  uint_fast16_t head = b->head;
  uint_fast16_t tail = b->tail;
  return (b ? (head - tail) : 0);
}

/**
 * Returns the empty/full status of the ring buffer
 *
 * \param b Pointer to initialized buffer
 * \return  true if the ring buffer is full, false if it is not.
 */
static bool fifo_full(ring_buffer_t const* b) {
  return (b ? (fifo_count(b) == b->max) : true);
}

/**
 * Returns the empty/full status of the ring buffer
 *
 * \param b Pointer to initialized buffer
 * \return  true if the ring buffer is empty, false if it is not.
 */
bool fifo_empty(ring_buffer_t const* b) {
  return (b ? (fifo_count(b) == 0) : true);
}

/**
 * Looks at the data from the head of the list without removing it
 *
 * \param b Pointer to initialized buffer
 * \return  byte of data, or zero if nothing in the list
 *
 * \note Use Empty function to see if there is data to retrieve
 */
uint8_t fifo_peak(ring_buffer_t const* b) {
  if (b)
    return (b->buffer[b->tail]);

  return 0;
}

/**
 * Gets the data from the front of the list, and removes it
 *
 * \param b Pointer to initialized buffer
 * \return  the data, or zero if nothing in the list
 *
 * \note Use Empty function to see if there is data to retrieve
 */
uint8_t fifo_get(ring_buffer_t* b) {
  uint8_t data_byte = 0;

  if (!fifo_empty(b)) {
    data_byte = b->buffer[b->tail];
    b->tail = (b->tail + 1) % b->max;
  }
  return data_byte;
}

/**
 * Adds an element of data to the FIFO
 *
 * \param b Pointer to initialized buffer
 * \param data_byte Data to put into buffer
 * \return  true on successful add, false if not added
 */
bool fifo_put(ring_buffer_t* b, const uint8_t data_byte) {
  bool status = false;        /* return value */

  if (b) {
    /* limit the ring to prevent overwriting */
    if (!fifo_full(b)) {
      b->buffer[b->head] = data_byte;
      b->head = (b->head + 1) % b->max;
      status = true;
    }
  }

  return status;
}

/**
 * Configures the ring buffer
 *
 * \param b Pointer to buffer, to be initialized
 * \param buffer Pointer to the buffer of data
 * \param buffer_len Length of the buffer
 */
void fifo_init(ring_buffer_t* b, volatile uint8_t* buffer, uint16_t buffer_len) {
  if (b) {
    b->head = 0;
    b->tail = 0;
    b->buffer = buffer;
    b->max = buffer_len - 1;
  }

  return;
}

uint16_t fifo_get_count(ring_buffer_t const* b) {
  return fifo_count(b);
}

/**
 * Reset the ring buffer
 *
 * \param b Pointer to buffer, to be initialized
 */
void fifo_reset(ring_buffer_t* b) {
  if (b) {
    b->head = 0;
    b->tail = 0;
  }
}