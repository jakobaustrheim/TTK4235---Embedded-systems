#pragma once

#include "elevio.h"
#include "utilities.h"
#include "con_load.h"
#include "move.h"

typedef struct Order
{
    int order[4][3]; //A matrix of four rows representing the four different floors, and thee columns for the three different button-types.
} Order;

typedef struct
{
    int floor;
    ButtonType button;
} called_floor;


typedef enum {
    START,
    MOVING,
    WAITING,
    STOP,
    OBSTRUCTION,
    HANDLING_ORDER,
    DESTINATION,

} elevator_states;

extern Order ord; // Creating an instance of the order-matrix
extern called_floor c_f; 
extern int last_floor;

// called_floor get_order();
void add_order(called_floor c);
void remove_order();
void open_door();
void order_execute();
void start();
void flush_order();
void stop();
int check_order();
void floor_light();
void last_floor_func();

//struct timespec tim = {.tv_sec = 3, .tv_sec = 0};

