#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "move.h"

//Fucntion that contains the logic for the elevators movement
void move()
{
    for (int f = 0; f < N_FLOORS; f++)
    {
        for (int b = 0; b < N_BUTTONS; b++)
        {
            if (ord.order[f][b] == 1) //Checks if there is a placed order
            {
                int iter = last_floor;
                while (f != last_floor) //Executing order
                {
//------------------------------------------ Funtions to be run during the move-funtion call ------------------------------------------------
                    if (check_button_pressed() == 1) {
                        add_order(c_f);
                    }
                    last_floor_func();
                    stop();
                    floor_light();
//-------------------------------------------------------------------------------------------------------------------------------------------

                    if (f - last_floor < 0) //Checking if there is a placed order to be executed on the way down to the order
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

                    else if (f - last_floor > 0 ) //Checking if there is a placed order to be executed on the way up to the order
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
                order_execute(); //Executing the order
                break;
            }  
        }
    }
}
