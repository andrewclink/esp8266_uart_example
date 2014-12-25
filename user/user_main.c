#include <ets_sys.h>
#include <osapi.h>
#include <os_type.h>

#include "driver/uart.h"

os_event_t uart_recv_queue[32];
void uart_recv_task(os_event_t * event)
{
  switch(event->sig)
  {
    case SIG_UART0_RX:
    {
      os_printf("r: %c\n", event->par);
      break;
    }

    default:
      break;
  }
  
  
}

void user_init(void)
{
  uart_init(BIT_RATE_115200, BIT_RATE_115200);
  os_delay_us(1000000);
  os_printf("\r\nos_printf()\r\n");
  os_delay_us(1000000);
  uart0_sendStr("\r\nuart0_sendStr\r\n");

  
  // install receive task
  system_os_task(uart_recv_task, 0, uart_recv_queue, 32);
}
