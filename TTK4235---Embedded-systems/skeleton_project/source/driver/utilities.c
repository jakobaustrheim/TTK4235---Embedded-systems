#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "utilities.h"

// Defining the global instances of order, called_floor, last_floor and elevator_states
Order ord = {.order = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}; //Initializing the order matrix with zeroes, hence no orders
called_floor c_f;
int last_floor;
elevator_states s = START; //Initialzing the elevator_states as START

// Sets the value of the given floor and button to one, thereby placing a order. Also makes a call to the lights_on() function
void add_order(called_floor c) 
{
    int floor = c.floor;
    ButtonType button = c.button;
    ord.order[floor][button] = 1;
    lights_on(c);
}

//Bool-function that checks whether a button is pressed by returning 1 while changing the values of the global struct c_f (Called floor)
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

// Sets the value of the executed order to zero, while also callin the lights_off() function
void remove_order() 
{
    last_floor_func();

    for (int f = 0; f < N_FLOORS; f++)
    {
        if (f == last_floor)
        {
            for (int b = 0; b < N_BUTTONS; b++)
            {
                ord.order[f][b] = 0;
                lights_off(f,b);
            }
        }
    }
}

//Removes all current orders by giving all the elements in the order matrix the value 0, while also calling the light_off() function
void flush_order()
{
    for (int f = 0; f < N_FLOORS; f++)
    {
        for (int b = 0; b < N_BUTTONS; b++)
        {
            ord.order[f][b] = 0;
            lights_off(f,b);
        }
    }
}

//Opens the door for three seconds while also checking for for obstructions and newly placed orders
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

//Calls two funtions that will execute the order
void order_execute()
{
    remove_order();
    open_door();
}

//Getting the elevator to a defined start state
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

//Stops the elevator given that the stop-button is pressed
void stop()
{
    if (elevio_stopButton() == 1 && elevio_floorSensor() != -1) //If the stop-button is pressed while in a floor
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

    else if (elevio_stopButton()) //If the stop-button is pressed while inbetween two floors
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

//Will run if the obstruction latch is high. Checks for the stop-button calls and new orders
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

//Updates the floor_light given the current floor
void floor_light()
{
    int floor = elevio_floorSensor();
    if (floor >= 0 && floor < N_FLOORS)
    {
        elevio_floorIndicator(floor);
    }
}

//Updates the global value last_floor. The function makes sure that last_floor only can be changes to a value between 0-3 (defined floors)
void last_floor_func()
{
    if (elevio_floorSensor() != -1)
    {
        last_floor = elevio_floorSensor();
    }
}

//Switches the order lights on given a placed order
void lights_on(called_floor c)
{
    int floor = c.floor;
    ButtonType button = c.button;
    elevio_buttonLamp(floor,button,1);
}

//Switches the order lights off given a removed or flushed order
void lights_off(int floor, ButtonType button) {
    elevio_buttonLamp(floor,button,0);
}
