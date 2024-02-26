#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "elevio.h"

typedef struct queue
{
    int queue_up[10];
    int queue_down[10];
    int queue_cab[10];
};

int next_floor();
ButtonType button();

