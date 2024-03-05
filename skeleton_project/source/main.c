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
        printf("State: %s /n");
        start();
        floor_light();
        state = WAITING;

    case WAITING:
        printf("State: %s /n");
        floor_light();
        stop_state();
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

    case STOP:
        printf("State: %s /n");
        stop();
        state = WAITING;

    case MOVING:
        printf("State: %s /n");
        stop_state();
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
    while(1) {
        state_machine(s);

    }
    return 0;
}
