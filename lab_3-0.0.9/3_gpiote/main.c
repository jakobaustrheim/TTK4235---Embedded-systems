#include <stdint.h>
#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

void button_init()
{
    GPIO->PIN_CNF[13] = (3 << 2);
}

int main()
{
    void button_init();
    for (int i = 17; i <= 20; i++)
    {
        GPIO->DIRSET = (1 << i);
        GPIO->OUTSET = (1 << i);
    }

    GPIOTE->CONFIG[0] = 1 | (13 << 8) | (2 << 16);

    GPIOTE->CONFIG[1] = 3 | (17 << 8) | (3 << 16) | (1 << 20); // Task mode, toogle og satt til hvert sitt lys GPIO 17 - 20
    GPIOTE->CONFIG[2] = 3 | (18 << 8) | (3 << 16) | (1 << 20);
    GPIOTE->CONFIG[3] = 3 | (19 << 8) | (3 << 16) | (1 << 20);
    GPIOTE->CONFIG[4] = 3 | (20 << 8) | (3 << 16) | (1 << 20);

    // Setter PPI-registrene og kobler eventet mot hver sin task
    PPI->PPI_CH[0].EEP = (uint32_t) & (GPIOTE->EVENTS_IN[0]); // EEP = EventEndPoint
    PPI->PPI_CH[0].TEP = (uint32_t) & (GPIOTE->OUT[1]);       // TEP = TaskEndPoint

    PPI->PPI_CH[1].EEP = (uint32_t) & (GPIOTE->EVENTS_IN[0]); // EEP = EventEndPoint
    PPI->PPI_CH[1].TEP = (uint32_t) & (GPIOTE->OUT[2]);       // TEP = TaskEndPoint

    PPI->PPI_CH[2].EEP = (uint32_t) & (GPIOTE->EVENTS_IN[0]); // EEP = EventEndPoint
    PPI->PPI_CH[2].TEP = (uint32_t) & (GPIOTE->OUT[3]);       // TEP = TaskEndPoint

    PPI->PPI_CH[3].EEP = (uint32_t) & (GPIOTE->EVENTS_IN[0]); // EEP = EventEndPoint
    PPI->PPI_CH[3].TEP = (uint32_t) & (GPIOTE->OUT[4]);       // TEP = TaskEndPoint
    PPI->CHENSET = 0b1111;
    PPI->CHG[0] = 0b1111;
    PPI->PPI_TASKS[0].EN = 1;

    while (1) {}

    return 0;
}
