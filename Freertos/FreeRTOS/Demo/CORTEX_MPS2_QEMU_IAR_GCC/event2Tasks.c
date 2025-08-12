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
#include "queue.h"
#include "event_groups.h"

/* Priorities at which the tasks are created. */
#define TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )

/*---------------------------- START of the TASKS' CODE ----------------------------*/
#define TASK2_BIT (1 << 0)
#define TASK3_BIT (1 << 1)

EventGroupHandle_t eventGroup;

void Task2(void *pvParameters) {
    while (1) {
        // Attendiamo l'evento che indica che è il turno di Task2
        EventBits_t bits = xEventGroupWaitBits(eventGroup, TASK2_BIT, pdTRUE, pdFALSE, portMAX_DELAY);
        
        if (bits & TASK2_BIT) {
            // Stampiamo il messaggio
            printf("Print Task 2\n\r");
            vTaskDelay( pdMS_TO_TICKS( 500UL ) );	
            
            // Notifichiamo l'evento di Task3 per permettere il suo turno
            xEventGroupSetBits(eventGroup, TASK3_BIT);
        }
    }
}

void Task3(void *pvParameters) {
    while (1) {
        // Attendiamo l'evento che indica che è il turno di Task3
        EventBits_t bits = xEventGroupWaitBits(eventGroup, TASK3_BIT, pdTRUE, pdFALSE, portMAX_DELAY);
        
        if (bits & TASK3_BIT) {
            // Stampiamo il messaggio
            printf("Print Task 3\n\r");
            vTaskDelay( pdMS_TO_TICKS( 500UL ) );	
            
            // Notifichiamo l'evento di Task2 per permettere il suo turno
            xEventGroupSetBits(eventGroup, TASK2_BIT);
        }
    }
}


void Task1(void *pvParameters) {
    // Inizializziamo il gruppo di eventi
        eventGroup = xEventGroupCreate();

    // Creiamo i task Task2 e Task3
    xTaskCreate(Task2, "Task2", 100, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(Task3, "Task3", 100, NULL, TASK_PRIORITY, NULL);

    // Inizialmente notifichiamo Task2 per farlo partire
    xEventGroupSetBits(eventGroup, TASK2_BIT);

    // Task1 non fa nulla, può terminare o eseguire altre operazioni
    vTaskDelete(NULL);
}


/*---------------------------- END of the TASKS' CODE ----------------------------*/



/*---------------------------- START of the MAIN CODE ----------------------------*/

void event2Tasks( void )
{
	// Creiamo il task Task1
    xTaskCreate(Task1, "Task1", 100, NULL, 1, NULL);

    // Avviamo il sistema operativo FreeRTOS
    vTaskStartScheduler();

    // Non dovremmo mai raggiungere questo punto
    return 0;

	for( ;; );
}

/*---------------------------- END of the MAIN CODE ----------------------------*/