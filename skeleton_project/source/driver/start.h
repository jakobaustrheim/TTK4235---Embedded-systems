#pragma once


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