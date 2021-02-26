
#ifndef circularbuffer__H
#define circularbuffer__H

#ifdef __cplusplus
extern "C" {
#endif

#include <mtypes.h>
#include <mio.h>

typedef struct circular_buf_t circular_buf_t;
typedef circular_buf_t* cbuf_handle_t;

// The hidden definition of our circular buffer structure
struct circular_buf_t {
    uint8_t * buffer;
    size_t head;
    size_t tail;
    size_t max; //of the buffer
    BOOL32 full;
};

/// Pass in a storage buffer and size
/// Returns a circular buffer handle
cbuf_handle_t circular_buf_init(uint8_t* buffer, size_t size);

/// Free a circular buffer structure.
/// Does not free data buffer; owner is responsible for that
void circular_buf_free(cbuf_handle_t cbuf);

/// Reset the circular buffer to empty, head == tail
void circular_buf_reset(cbuf_handle_t cbuf);

/// Put version 1 continues to add data if the buffer is full
/// Old data is overwritten
void circular_buf_put(cbuf_handle_t cbuf, uint8_t data);

/// Put Version 2 rejects new data if the buffer is full
/// Returns 0 on success, -1 if buffer is full
UINT32 circular_buf_put2(cbuf_handle_t cbuf, uint8_t data);

/// Retrieve a value from the buffer
/// Returns 0 on success, -1 if the buffer is empty
UINT32 circular_buf_get(cbuf_handle_t cbuf, uint8_t * data);

/// Returns true if the buffer is empty
BOOL32 circular_buf_empty(cbuf_handle_t cbuf);

/// Returns true if the buffer is full
BOOL32 circular_buf_full(cbuf_handle_t cbuf);

/// Returns the maximum capacity of the buffer
size_t circular_buf_capacity(cbuf_handle_t cbuf);

/// Returns the current number of elements in the buffer
size_t circular_buf_size(cbuf_handle_t cbuf);
