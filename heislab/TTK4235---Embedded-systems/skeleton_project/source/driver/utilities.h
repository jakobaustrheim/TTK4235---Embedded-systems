#pragma once

#include "elevio.h"
#include "utilities.h"
#include "con_load.h"
#include "move.h"

//Struct named Order which will contain a matrix that is updated given a order
typedef struct Order
{
    int order[4][3]; //Matrix of four rows representing the four different floors, and thee columns for the three different button-types.
} Order;

//Struct named called_button which contains a int-type member variable for floor, and a ButtonType-type for button
typedef struct
{
    int floor;
    ButtonType button;
} called_floor;

//Enum containing the different sates of the FSM in main.c
typedef enum {
    START,
    MOVING,
    WAITING,
    STOP
} elevator_states;

//Creating an instance of the elevator_statese enum
extern elevator_states s;

//Creating an instance of the order struct
extern Order ord; 

//Creating an instance of the called_floor struct
extern called_floor c_f; 

//Declearing the global variable, last_floor
extern int last_floor;

//Declearing functions that are defined in the .c file
void add_order(called_floor c);
void remove_order();
void open_door();
void order_execute();
void start();
void flush_order();
void stop();
int check_button_pressed();
void floor_light();
void last_floor_func();
void obstruction();
void lights_on(called_floor c);
void lights_off(int floor, ButtonType button);