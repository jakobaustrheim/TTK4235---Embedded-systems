#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "order.h"
#include "con_load.h"


int next_floor() {
    for (int f = 0; f < N_FLOORS; f++)
        {
            for (int b = 0; b < N_BUTTONS; b++)
            {
                int btnPressed = elevio_callButton(f, b);
                if (btnPressed == 1) {
                    int next_floor = f;
                }
            }         
        }
    return next_floor;
}

ButtonType return_button() {
    for (int f = 0; f < N_FLOORS; f++)
        {
            for (int b = 0; b < N_BUTTONS; b++)
            {
                int btnPressed = elevio_callButton(f, b);
                if (btnPressed == 1) {
                    ButtonType button = b;
                }
            }         
        }
    return button;
}

void add_order() {
    struct queue q;
    ButtonType button = return_button();
    if (button == BUTTON_CAB)
    {
        if ()
        {
            
        }
        
    }
    

}