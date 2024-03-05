#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "move.h"

void move()
{
    for (int f = 0; f < N_FLOORS; f++)
    {
        for (int b = 0; b < N_BUTTONS; b++)
        {
            if (ord.order[f][b] == 1)
            {
                int iter = last_floor;
                while (f != last_floor)
                {
                    last_floor_func();
                    stop();
                    if (f - last_floor < 0) // Sjekker om det evt er ordre på vei ned mot bestilling
                    {
                        elevio_motorDirection(DIRN_DOWN);
                        for (int i = iter-1; i > f; i--)
                        {
                            if ((ord.order[i][1] == 1 || ord.order[i][2] == 1) && last_floor == i)
                            {
                                order_execute();
                            }
                        }
                    }

                    else if (f - last_floor > 0 ) // Sjekker om det evt er ordre på vei opp mot bestilling
                    {
                        elevio_motorDirection(DIRN_UP);
                        for (int i = iter+1; i < f; i++)
                        {
                            if ((ord.order[i][0] == 1 || ord.order[i][2] == 1) && last_floor == i)
                            {
                                order_execute();
                            }
                        }
                    }
                }
                    order_execute();
                    break;
            }  
        }
    }
}
