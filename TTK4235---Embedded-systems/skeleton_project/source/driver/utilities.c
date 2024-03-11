#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "utilities.h"


Order ord = {.order = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};

called_floor c_f;

int last_floor;

elevator_states s = START;

void add_order(called_floor c) // Sets the value of the given floor and button to one, thereby placing a order
{
    int floor = c.floor;
    ButtonType button = c.button;
    ord.order[floor][button] = 1;
    elevio_buttonLamp(floor,button,1);
}

int check_button_pressed()
{
    for (int f = 0; f < N_FLOORS; f++)
    {
        for (int b = 0; b < N_BUTTONS; b++)
        {
            if (elevio_callButton(f,b))
            {
                c_f.floor = f;
                c_f.button = b;
                return 1;
            }
        }
    }
    return 0;
}

void remove_order() // Sets the value of the executed order to zero
{
    last_floor_func();

    for (int f = 0; f < N_FLOORS; f++)
    {
        if (f == last_floor)
        {
            for (int b = 0; b < N_BUTTONS; b++)
            {
                ord.order[f][b] = 0;
                elevio_buttonLamp(f,b,0);
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
            elevio_buttonLamp(f,b,0);
        }
    }
}

void open_door()
{
    elevio_motorDirection(DIRN_STOP);
    elevio_doorOpenLamp(1);
    for (int _ = 0; _ < 150; _++)
    {
        if (elevio_stopButton()) {
            stop();
        }
        if (elevio_obstruction())
        {
            if (check_button_pressed() == 1) {
            add_order(c_f);
            }
            obstruction();
            open_door();
        }
        if (check_button_pressed() == 1) {
            add_order(c_f);
        }
        nanosleep(&(struct timespec){0, 20 * 1000 * 1000}, NULL);
    }
    elevio_doorOpenLamp(0);
}

void order_execute()
{
    remove_order();
    open_door();
}

void start()
{
    elevio_stopLamp(0);
    elevio_doorOpenLamp(0);
    for (int f = 0; f < N_FLOORS; f++)
    {
        for (int b = 0; b < N_BUTTONS; b++)
        {
            elevio_buttonLamp(f, b, 0);
        }
    }
    while (elevio_floorSensor() == -1)
    {
        elevio_motorDirection(DIRN_DOWN);
    }
    elevio_motorDirection(DIRN_STOP);
}

void stop_state() {
    if (elevio_stopButton() == 1) {
        s = STOP;
    }
}

void stop()
{
    if (elevio_stopButton() == 1 && elevio_floorSensor() != -1)
    {
        flush_order();
        elevio_stopLamp(1);
        elevio_motorDirection(DIRN_STOP);
        while (elevio_stopButton())
        {
            elevio_motorDirection(DIRN_STOP);
            elevio_doorOpenLamp(1);
        }
        elevio_stopLamp(0);
        open_door();
    }

    else if (elevio_stopButton())
    {
        flush_order();
        elevio_stopLamp(1);
        while (elevio_floorSensor() == -1)
        {
            flush_order();
            if (check_button_pressed()) {
                add_order(c_f);
                elevio_stopLamp(0);
                s = MOVING;
                break;
            }
            else {
                elevio_motorDirection(DIRN_STOP);
            }
        }
    }
}

void obstruction()
{
    while (elevio_obstruction())
    {
        if (check_button_pressed() == 1) {
            add_order(c_f);
        }
        if (elevio_stopButton())
        {
            stop();
        }
        elevio_motorDirection(DIRN_STOP);
        elevio_doorOpenLamp(1);
    }
}

void floor_light()
{
    int floor = elevio_floorSensor();
    if (floor >= 0 && floor < N_FLOORS)
    {
        elevio_floorIndicator(floor);
    }
}

void last_floor_func()
{
    if (elevio_floorSensor() != -1)
    {
        last_floor = elevio_floorSensor();
    }
}
