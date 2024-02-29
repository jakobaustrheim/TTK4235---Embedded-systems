#pragma once


typedef struct 
{
    int order[4][3]; //A matrix of four rows representing the four different floors, and thee columns for the three different button-types.
} Order;

extern Order ord = {.order = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}; // Initilizing the matrix with zeroes

int get_floor();
ButtonType get_button();
void add_order();
void remove_order();

//struct timespec tim = {.tv_sec = 3, .tv_sec = 0};

