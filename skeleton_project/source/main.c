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
        
            stop();
            for (int f = 0; f < N_FLOORS; f++){
                for (int b = 0; b < N_BUTTONS; b++) {
                    int btn_pressed = elevio_callButton(f, b);
                        if (btn_pressed == 1) {
                            c_f.floor = f;
                            c_f.button = b;
                            state = HANDLING_ORDER;
                        }
                        else {
                            state = WAITING;
                        }
                }
            }
    
    case HANDLING_ORDER:
        stop();
        elevio_buttonLamp(1,1,1);
        add_order(c_f);
        state = MOVING;
    
    case MOVING:
        stop();
        elevio_buttonLamp(0,1,1);
        move();

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
