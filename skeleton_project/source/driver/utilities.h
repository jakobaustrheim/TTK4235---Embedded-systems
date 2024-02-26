#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "elevio.h"

struct Order
{
    int order[4][3]; //A matrix of four rows representing the four different floors, and thee columns for the three different button-types.
};

struct Order o = {.order = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}; // Initilizing the matrix with zeroes

int get_floor();
ButtonType get_button();
void add_order();
void remove_order();


