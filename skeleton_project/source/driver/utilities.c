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

Order ord = {.order = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};

called_floor c_f;


called_floor get_order() // Returns the button-type of the pressed button
{
    for (int f = 0; f < N_FLOORS; f++)
    {
        for (int b = 0; b < N_BUTTONS; b++)
        {
            int btn_pressed = elevio_callButton(f, b);
            if (btn_pressed == 1)
            {
                c_f.floor = f;
                c_f.button = b;
                return c_f;
            }
        }
    }
}


void add_order() // Sets the value of the given floor and button to one
{
    called_floor c_f = get_order();
    int floor = c_f.floor;
    ButtonType button = c_f.button;

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

int check_order()
{
    for (int f = 0; f < N_FLOORS; f++)
    {
        for (int b = 0; b < N_BUTTONS; b++)
        {
            if (ord.order[f][b] = 1)
            {
                return 1;
            }
        }
    }
    return 0;
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

void flush_order()
{
    for (int f = 0; f < N_FLOORS; f++)
    {
        for (int b = 0; b < N_BUTTONS; b++)
        {
            ord.order[f][b] = 0;
        }

    }
}

void open_door() {
    elevio_motorDirection(DIRN_STOP);
    elevio_doorOpenLamp(1);
    for (int _ = 0; _ < 150; _++)
    {
        //add_order( a,  c);
        nanosleep(&(struct timespec){0, 20 * 1000 * 1000}, NULL);
    }
    elevio_doorOpenLamp(0);
}


void order_execute() {
    open_door();
    remove_order();
}

void start() {
    elevio_stopLamp(0);
    elevio_doorOpenLamp(0);
    while (elevio_floorSensor() == -1)
        {
            elevio_motorDirection(DIRN_DOWN);
        }
        elevio_motorDirection(DIRN_STOP);
    
}

void stop() {
    if (elevio_stopButton() & elevio_floorSensor() != -1) {
        flush_order();
        elevio_stopLamp(1);
        elevio_motorDirection(DIRN_STOP);
        while (elevio_stopButton()) {
            elevio_motorDirection(DIRN_STOP);
            elevio_doorOpenLamp(1);
        }
        elevio_stopLamp(0);
        open_door();
    }

    else if (elevio_stopButton()) {
        flush_order();
        elevio_stopLamp(1);
        elevio_motorDirection(DIRN_STOP);
        while (elevio_stopButton()) {
            elevio_motorDirection(DIRN_STOP);
        }
        elevio_stopLamp(0);
    }
}

void obstruction() {
    if(elevio_floorSensor() != -1 & elevio_obstruction() == 1) { //Må legge til funksjonalitet så den første sjekker om døren er åpen
        while(elevio_obstruction() == 1) {
            elevio_motorDirection(DIRN_STOP);
            elevio_doorOpenLamp(1);
        }
        open_door();
    }
}

void floor_light() {
    int floor = elevio_floorSensor();
    if (floor >= 0 & floor < N_FLOORS) 
    {
        elevio_floorIndicator(floor);
    }
}