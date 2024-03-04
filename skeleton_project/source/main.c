#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/move.h"
#include "driver/utilities.h"
#include "driver/con_load.h"

//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

void state_machine(elevator_states state) {
    switch (state)
    {
    case START:
        start();
        state = WAITING;

    case WAITING:
    //vi må while her for å vente på første bestilling før ci går i moving state
    //add order funker ikke
     for (int f = 0; f < N_FLOORS; f++){
        for (int b = 0; b < N_BUTTONS; b++) {
            int btn_pressed = elevio_callButton(f, b);
            if (btn_pressed == 1) {
                add_order();
            }
        }
        }
        stop();  
        if (check_order() == 1)
        {  
            elevio_buttonLamp(3,1,1);
            //state = MOVING;

        }
        else 
        {
            //add_order();
            stop();
            //elevio_buttonLamp(2,1, 1);
        }

    case MOVING:
        //add_order();
        stop();
    
    default:
        break;
     }
}


int main()
{
    elevio_init();
    elevator_states s = START;
    while(1) {
        floor_light();

        state_machine(s);

    }
    return 0;
}
