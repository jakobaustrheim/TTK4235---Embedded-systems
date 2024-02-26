#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "elevio.h"
#include "con_load.h"
#include "move.h"
#include "utilities.h"

void execute_order()
{
    for (int f = 0; f < N_FLOORS; f++)
    {
        for (int b = 0; b < N_BUTTONS; b++)
        {
            if (b == 2)
            {
                move();
            }
        }
    }
}

void move()
{
    int current_floor = elevio_floorSensor();
    for (int f = 0; f < N_FLOORS; f++)
    {
        if (o.order[f][2])
        {
            if (f < current_floor)
            {
                elevio_motorDirection(DIRN_DOWN);
                for (int i = f; i < current_floor; i++)
                {
                    if (o.order[i][1] == 1 || o.order[i][2] == 1)
                    {
                        // Må legge inn en kode som stopper motoren i gitt mengde tid
                        remove_order();
                    }
                    {
                    }
                }
            }

            // Tilsvarende logikk som for turer nedover her.

            else if (f > current_floor)
            {
                elevio_motorDirection(DIRN_UP);
            }
            else
            {
                elevio_motorDirection(DIRN_STOP);
                remove_order();
            }
        }
    }
}
