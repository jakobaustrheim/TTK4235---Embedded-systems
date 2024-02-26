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


void move() {
    int floor = elevio_floorSensor();
    for (int f = 0; f < N_FLOORS; f++)
        {
            for (int b = 0; b < N_BUTTONS; b++)
            {
                int btnPressed = elevio_callButton(f, b);
                if (btnPressed == 1) {
                    int next_floor = f;
                    ButtonType button = b;
                    while(floor != next_floor) {
                        if (floor < next_floor)
                        {
                            elevio_motorDirection(DIRN_UP);
                        }
                        else 
                        {
                            elevio_motorDirection(DIRN_DOWN);
                        }
                    }

                }
            }
        
        }      
    }

