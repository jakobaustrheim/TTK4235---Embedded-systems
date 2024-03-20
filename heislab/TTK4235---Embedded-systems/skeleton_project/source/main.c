//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 

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/move.h"
#include "driver/utilities.h"
#include "driver/con_load.h"


//Elevator state-machine. Utilizing a switch-case given the elevator-states struct
void state_machine(elevator_states state) {

    switch (state)
    {
    case START:
        start();
        floor_light();
        state = WAITING;

    case WAITING:
        floor_light();
        stop();
        if(check_button_pressed())
        {
            add_order(c_f);
            state = MOVING;
        }
        else
        {
            state = WAITING;
        }

    case STOP:
        stop();
        state = WAITING;


    case MOVING:
        stop();
        move();
        state = WAITING;

    default:
        break;
     }
}


int main()
{
    elevio_init();
    while(1) {
        state_machine(s); //Running the elevator
    }
    return 0;
}
