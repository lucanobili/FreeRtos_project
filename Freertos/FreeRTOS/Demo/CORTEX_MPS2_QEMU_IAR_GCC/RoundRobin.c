/*
 * FreeRTOS V202212.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/* Standard includes. */
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"


/* Priorities at which the tasks are created. */
#define TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )

/*---------------------------- START of the TASKS' CODE ----------------------------*/

static void taskJob1(){
	for(int i = 0; i < 100000000; i++);
}

void Task2r(void *pvParameters) {
    TickType_t xNextWakeTime = 10;
    while(1){
        taskJob1();
        printf("task 2 \n\r");

    }
}


void Task1r(void *pvParameters) {
    TickType_t xNextWakeTime = 10;
    while(1){
        taskJob1();
        printf("task 1 \n\r");
    }
}


/*---------------------------- END of the TASKS' CODE ----------------------------*/



/*---------------------------- START of the MAIN CODE ----------------------------*/

void RoundRobin( void )
{
	// Creiamo il task Task1
    xTaskCreate(Task1r, "Task1", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(Task2r, "Task2", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    // Avviamo il sistema operativo FreeRTOS
    vTaskStartScheduler();

    // Non dovremmo mai raggiungere questo punto
    return 0;

	for( ;; );
}

/*---------------------------- END of the MAIN CODE ----------------------------*/