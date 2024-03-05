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

// called_floor get_order() // Returns the value and buttontype of a button if one is pressed
// {
//     for (int f = 0; f < N_FLOORS; f++)
//     {
//         for (int b = 0; b < N_BUTTONS; b++)
//         {
//             int btn_pressed = elevio_callButton(f, b);
//             if (btn_pressed == 1)
//             {
//                 c_f.floor = f;
//                 c_f.button = b;
//                 return c_f;
//             }
//         }
//     }
// }

void add_order(called_floor c) // Sets the value of the given floor and button to one, thereby placing a order
{
    int floor = c.floor;
    ButtonType button = c.button;
    ord.order[floor][button] = 1;
}

int check_order()
{
    for (int f = 0; f < N_FLOORS; f++)
    {
        for (int b = 0; b < N_BUTTONS; b++)
        {
            if (ord.order[f][b] == 1)
            {
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

void open_door()
{
    elevio_motorDirection(DIRN_STOP);
    elevio_doorOpenLamp(1);
    for (int _ = 0; _ < 150; _++)
    {
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

    else if (elevio_stopButton() == 1)
    {
        flush_order();
        elevio_stopLamp(1);
        elevio_motorDirection(DIRN_STOP);
        while (elevio_stopButton())
        {
            elevio_motorDirection(DIRN_STOP);
        }
        elevio_stopLamp(0);
    }
}

void obstruction()
{
    if (elevio_floorSensor() != -1 && elevio_obstruction() == 1)
    { // Må legge til funksjonalitet så den første sjekker om døren er åpen
        while (elevio_obstruction() == 1)
        {
            elevio_motorDirection(DIRN_STOP);
            elevio_doorOpenLamp(1);
        }
        open_door();
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