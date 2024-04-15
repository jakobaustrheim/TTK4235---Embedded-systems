#include <stdint.h>
#include "uart.h"
#include "gpio.h"

void button_init()
{
	GPIO->PIN_CNF[13] = (3 << 2);
	GPIO->PIN_CNF[14] = (3 << 2);
}

int main()
{
	button_init();
	uart_init();
	for (int i = 17; i <= 20; i++)
	{
		GPIO->DIRSET = (1 << i);
		GPIO->OUTSET = (1 << i);
	}

	while (1)
	{
		if (!(GPIO->IN & (1 << 13)))
		{
			uart_send('A');
		}
		if (!(GPIO->IN & (1 << 14)))
		{
			uart_send('B');
		}
	}

	return 0;
}