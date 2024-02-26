#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/start.h"
#include "driver/move.h"
#include "driver/utilities.h"


int main()
{
    elevio_init();

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    // elevio_motorDirection(DIRN_UP);

    while (1)
    {
         start_position();

         int floor = elevio_floorSensor();

        // // if(floor == 0){
        // //     elevio_motorDirection(DIRN_UP);
        // // }
        // if (floor >= 0)
        // {
        //     elevio_floorIndicator(floor);
        // }

        // // if(floor == N_FLOORS-1){
        // //     elevio_motorDirection(DIRN_DOWN);
        // // }

        // for (int f = 0; f < N_FLOORS; f++)
        // {
        //     for (int b = 0; b < N_BUTTONS; b++)
        //     {
        //         int btnPressed = elevio_callButton(f, b);
        //         if (btnPressed == 1) {
        //             int floor = f;
        //             ButtonType button = b;
        //         }
        //         elevio_buttonLamp(f, b, btnPressed);
        //     }
        // }

        // move();

        //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

        if (elevio_obstruction())
        {
            elevio_stopLamp(1);
        }
        else
        {
            elevio_stopLamp(0);
        }

        if (elevio_stopButton())
        {
            elevio_motorDirection(DIRN_STOP);
            break;
        }

        nanosleep(&(struct timespec){0, 20 * 1000 * 1000}, NULL);
    }

    return 0;
}
