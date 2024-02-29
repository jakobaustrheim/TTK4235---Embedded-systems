#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "elevio.h"
#include "utilities.h"
#include "con_load.h"

int get_floor() // Returns the value of the pressed button
{
    for (int f = 0; f < N_FLOORS; f++)
    {
        for (int b = 0; b < N_BUTTONS; b++)
        {
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed == 1)
            {
                int next_floor = f;
                return next_floor;
            }
        }
    }
}

ButtonType get_button() // Returns the button-type of the pressed button
{
    for (int f = 0; f < N_FLOORS; f++)
    {
        for (int b = 0; b < N_BUTTONS; b++)
        {
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed == 1)
            {
                ButtonType button = b;
                return button;
            }
        }
    }
}

void add_order() // Sets the value of the given floor and button to one
{
    int floor = get_floor();
    ButtonType button = get_button();

    for (int f = 0; f < N_FLOORS; f++)
    {
        if (f == floor)
        {
            for (int b = 0; b < N_BUTTONS; b++)
            {
                if (b == button)
                {
                    ord.order[f][b] = 1;
                }
            }
        }
    }
}

void remove_order() // Sets the value of the executed order to zero
{
    int current_floor = elevio_floorSensor();

    for (int f = 0; f < N_FLOORS; f++)
    {
        if (f == current_floor)
        {
            for (int b = 0; b < N_BUTTONS; b++)
            {
                ord.order[f][b] = 0;
            }
        }
    }
}

void door() {
    int current_floor = elevio_floorSensor();
    if(current_floor != -1)
    {
        elevio_doorOpenLamp(1);
    }
    else {
        elevio_doorOpenLamp(0);
    }
}