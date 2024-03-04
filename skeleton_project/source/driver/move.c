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

// void execute_order()
// {
//     for (int f = 0; f < N_FLOORS; f++)
//     {
//         for (int b = 0; b < N_BUTTONS; b++)
//         {
//             if (b == 2)
//             {
//                 move();
//             }
//         }
//     }
// }

void move()
{
    int current_floor = elevio_floorSensor();
    if (elevio_floorSensor() != -1)
    {

        for (int f = 0; f < N_FLOORS; f++)
        {
            add_order();
            if (ord.order[f][2]) // Sjekker om det er ordre i cab
            {
                if (f < current_floor) // Sjekker om det evt er ordre på vei ned mot bestilling
                {
                    elevio_motorDirection(DIRN_DOWN);
                    for (int i = f; i < current_floor; i++)
                    {
                        if ((ord.order[i][1] == 1 || ord.order[i][2] == 1) & current_floor == i)
                        {
                            order_execute();
                        }
                    }
                }

                else if (f > current_floor) // Sjekker om det evt er ordre på vei opp mot bestilling
                {
                    elevio_motorDirection(DIRN_UP);
                    for (int i = current_floor; i < f; i++)
                    {
                        if ((ord.order[i][0] == 1 || ord.order[i][2] == 1) & current_floor == i)
                        {
                            order_execute();
                        }
                    }
                }

                else // Utfører ordre
                {
                    order_execute();
                }
            }
            else if (ord.order[f][0])
            {
                    if (f < current_floor) // Sjekker om det evt er ordre på vei ned mot bestilling
                    {
                        elevio_motorDirection(DIRN_DOWN);
                        for (int i = f; i < current_floor; i++)
                        {
                            if ((ord.order[i][1] == 1 || ord.order[i][2] == 1) & current_floor == i)
                            {
                                order_execute();
                            }
                        }
                    }

                    else if (f > current_floor) // Sjekker om det evt er ordre på vei opp mot bestilling
                    {
                        elevio_motorDirection(DIRN_UP);
                        for (int i = current_floor; i < f; i++)
                        {
                            if ((ord.order[i][0] == 1 || ord.order[i][2] == 1) & current_floor == i)
                            {
                                order_execute();
                            }
                        }
                    }

                    else // Utfører ordre
                    {
                        order_execute();
                    }
            }
            else if (ord.order[f][1])
            {
                    if (f < current_floor) // Sjekker om det evt er ordre på vei ned mot bestilling
                    {
                        elevio_motorDirection(DIRN_DOWN);
                        for (int i = f; i < current_floor; i++)
                        {
                            if ((ord.order[i][1] == 1 || ord.order[i][2] == 1) & current_floor == i)
                            {
                                order_execute();
                            }
                        }
                    }

                    else if (f > current_floor) // Sjekker om det evt er ordre på vei opp mot bestilling
                    {
                        elevio_motorDirection(DIRN_UP);
                        for (int i = current_floor; i < f; i++)
                        {
                            if ((ord.order[i][0] == 1 || ord.order[i][2] == 1) & current_floor == i)
                            {
                                order_execute();
                            }
                        }
                    }

                    else // Utfører ordre
                    {
                        order_execute();
                    }
            }
        }
    }

    // else {
    //     while (elevio_floorSensor() == -1)
    //     {
    //         elevio_motorDirection(DIRN_DOWN);
    //     }
    //     elevio_motorDirection(DIRN_STOP);
    //     move();
    // }
}
