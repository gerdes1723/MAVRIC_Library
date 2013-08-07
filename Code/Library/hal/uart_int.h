/*
 * uart_int.h
 *
 * Created: 11/06/2012 14:08:44
 *  Author: sfx
 */ 


#ifndef UART_INT_H_
#define UART_INT_H_
#include "compiler.h"
#include "buffer.h"
#include "conf_usart_serial.h"
#include "streams.h"


usart_config_t *init_UART_int(int UID);

usart_config_t *get_UART_handle(int UID);


/************************************************************************/
/* blocking operation to retrieve a received byte from uart             */
/************************************************************************/
char uart_int_get_byte(usart_config_t *usart_opt);

/************************************************************************/
/* returns number of received bytes in the receive buffer               */
/************************************************************************/
int uart_int_bytes_available(usart_config_t *usart_opt);

/************************************************************************/
/* non-blocking operation to append a byte to the uart send buffer      */
/* if buffer is full, the command has no effect  (returns -1).          */
/************************************************************************/
short uart_int_send_byte(usart_config_t *usart_opt, char data);


/** 
 * blocking operation to flush the uart buffer. Returns once the last byte has been passed to hardware for transmission.
 */
void uart_int_flush(usart_config_t *usart_opt );

/************************************************************************/
/* Registers a stream interface with the UART transmitter (data put     */
/* into the stream will be sent). This function will create a blocking  */
/* interface - if the output buffer is full, the function will block    */
/* until there is space.                                                */
/************************************************************************/
void register_write_stream(usart_config_t *usart_opt, byte_stream_t *stream);

/************************************************************************/
/* Registers a stream interface with the UART transmitter (data put     */
/* into the stream will be sent). This function will create a non-      */
/* blocking interface. If the output buffer is full, the function will  */
/* overwrite the oldest data in the buffer.                             */
/************************************************************************/
void register_write_stream_nonblocking(usart_config_t *usart_opt, byte_stream_t *stream);

void register_read_stream(usart_config_t *usart_opt,  byte_stream_t *stream);

#endif /* UART_INT_H_ */
