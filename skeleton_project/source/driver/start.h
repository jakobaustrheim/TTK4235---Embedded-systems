#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "elevio.h"

void start_position() {

    while (elevio_floorSensor() == -1)
    {
        elevio_motorDirection(DIRN_DOWN);
        if (elevio_floorSensor() != -1)
        {
            elevio_motorDirection(DIRN_STOP);
        }
        
    }
}