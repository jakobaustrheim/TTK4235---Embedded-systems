#include <stdint.h>
#include "uart.h"
#include "gpio.h"

void button_init()
{
	GPIO->PIN_CNF[13] = (3 << 2);
	GPIO->PIN_CNF[14] = (3 << 2);
}

void led_on()
{
	for (int i = 17; i <= 20; i++)
	{
		GPIO->OUTCLR = (1 << i);
	}
}

void led_off()
{
	for (int i = 17; i <= 20; i++)
	{
		GPIO->OUTSET = (1 << i);
	}
}

int main()
{
	int sleep = 0;
	button_init();
	uart_init();
	for (int i = 17; i <= 20; i++)
	{
		GPIO->DIRSET = (1 << i);
		GPIO->OUTSET = (1 << i);
	}

	while (1)
	{
		unsigned int btnLedON = (GPIO->IN >> 13) & 1;

		if (uart_read() != '\0')
		{
			if (!(GPIO->IN & (1 << 13)))
			{
				led_on();
			}

			if (!(GPIO->IN & (1 << 14)))
			{
				led_off();
			}
		}

		char *str[] = {"The average grade in TTK was in 2022, B. "};
		if (!btnLedON)
		{
			uart_send_str(str);
		}
		sleep = 10000;
		while (--sleep)
			;
	}

	return 0;
}
