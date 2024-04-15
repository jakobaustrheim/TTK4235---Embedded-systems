#include "uart.h"
#include "gpio.h"

void uart_init()
{
    GPIO->PIN_CNF[6] = (1 << 0);
    GPIO->PIN_CNF[8] = (0 << 0);

    UART->PSELTXD = (1 << 6);
    UART->PSELRXD = (1 << 8);

    UART->BAUDRATE = 0x00275000;
    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;

    UART->ENABLE = (4 << 0);

    UART->TASKS_STARTRX = 1;
}

void uart_send(char letter)
{
    UART->TASKS_STARTTX = 1;
    UART->EVENTS_TXDRDY = 0;
    UART->TXD = letter;
    while (!(UART->EVENTS_TXDRDY))
    {
    }
    UART->TASKS_STOPTX = 1;
}

char uart_read()
{
    UART->EVENTS_RXDRDY = 0;
    if (UART->EVENTS_RXDRDY == 1)
    {
        return UART->RXD;
    }
    else
    {
        return '\0';
    }
}