#pragma once

typedef struct 
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

} elevator_states;

extern Order ord; // Initilizing the matrix with zeroes
extern called_floor c_f; 

called_floor get_order();
void add_order();
void remove_order();
void open_door();
void order_execute();
void start();
void flush_order();
void stop();
int check_order();
void floor_light();

//struct timespec tim = {.tv_sec = 3, .tv_sec = 0};

