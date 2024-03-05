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
        printf("State: %u", state);
        start();
        floor_light();
        state = WAITING;

    case WAITING:
        printf("State: %u", state);
        floor_light();
        stop();
        for (int f = 0; f < N_FLOORS; f++){
            for (int b = 0; b < N_BUTTONS; b++) {
                int btn_pressed = elevio_callButton(f, b);
                    if (btn_pressed == 1) {
                        c_f.floor = f;
                        c_f.button = b;
                        add_order(c_f);
                        state = MOVING;
                    }
                    else {
                        state = WAITING;
                    }
            }
        }

    case HANDLING_ORDER:
        printf("State: %u", state);
        stop();
        elevio_buttonLamp(1,1,1);
        add_order(c_f);
        state = MOVING;
    
    case MOVING:
        printf("State: %u", state);
        stop();
        elevio_buttonLamp(2,1,1);
        move();
        state = WAITING;

    default:
        break;
     }
}


int main()
{
    elevio_init();
    elevator_states s = START;
    while(1) {
        state_machine(s);

    }
    return 0;
}
