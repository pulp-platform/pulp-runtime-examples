#include <stdio.h>
#include <pulp.h>
#include <stdint.h>

#define BUFFER_SIZE 256

uint8_t tx_buffer[BUFFER_SIZE];


int main()
{
  printf("Entering test\n");

  if (uart_open(0, 115200))
    return -1;


  for (int i=0; i<BUFFER_SIZE; i++)
  {
    tx_buffer[i] = i;
  }

  uart_write(0, tx_buffer, BUFFER_SIZE);

  uart_close(0);

  return 0;
}
