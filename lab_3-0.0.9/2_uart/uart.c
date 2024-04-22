#include "uart.h"
#include "gpio.h"

void uart_init()
{
    GPIO->PIN_CNF[6] = 0;
    GPIO->PIN_CNF[8] = 1;

    UART->PSELTXD = 6;
    UART->PSELRXD = 8;

    UART->BAUDRATE = 0x00275000;
    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;

    UART->ENABLE = 4;

    UART->TASKS_STARTRX = 1;
}

void uart_send(char letter)
{
    UART->TASKS_STARTTX = 1;
    UART->TXD = letter;
    while (!(UART->EVENTS_TXDRDY));
    UART->EVENTS_TXDRDY = 0;
}

char uart_read()
{
    UART->TASKS_STARTRX = 1;
    if (UART->EVENTS_RXDRDY)
    {
        UART->EVENTS_RXDRDY = 0;
        return UART->RXD;
    }
    return '\0';
}

void uart_send_str(char ** str){
    UART->TASKS_STARTTX = 1;
    char * letter_ptr = *str;
    while(*letter_ptr != '\0'){
        UART->TXD = *letter_ptr;
        while(!UART->EVENTS_TXDRDY);
        UART->EVENTS_TXDRDY = 0;
        letter_ptr++;
    }
}