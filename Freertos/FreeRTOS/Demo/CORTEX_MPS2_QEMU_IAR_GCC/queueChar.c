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

/* Priorities at which the tasks are created. */
#define QUEUE_TASKS_PRIORITY		( tskIDLE_PRIORITY + 1 )

/* The number of items the queue can hold at once. */
#define QUEUE_SIZE		( 5 )

/* String that will be sent through the queue. */
#define STRING_TO_SEND "Hi this is the string test\r\n"

/* Global Variables */
QueueHandle_t queue = NULL;

/*---------------------------- START of the TASKS' CODE ----------------------------*/

void queueSendTask(void *pvParameters)
{
	const char *pcStringToSend = (const char *)pvParameters;	/* Cast of the 'pvParameters' to the proper type */ 

    for(;;) 
	{
        for (int i = 0; i < strlen(pcStringToSend); i++) 
		{
            xQueueSend(queue, &pcStringToSend[i], portMAX_DELAY);	/* Write a char in the queue */
			
            vTaskDelay(pdMS_TO_TICKS(200));		/* We use the artificial delay to visualize the emptying of the queue correctly */
        }
    }

	vTaskDelete( NULL );
}

void queueReceiveTask(void *pvParameters) 
{
    ( void ) pvParameters;

	for(;;)
	{
		char receivedChar;

        xQueueReceive(queue, &receivedChar, portMAX_DELAY);		/* Read a char from the queue */
		
		printf("%c", receivedChar);		/* Print the char that has been read */

		vTaskDelay(pdMS_TO_TICKS(500));		/* We use the artificial delay to visualize the emptying of the queue correctly */
	}
		
	vTaskDelete( NULL );
}

/*---------------------------- END of the TASKS' CODE ----------------------------*/



/*---------------------------- START of the MAIN CODE ----------------------------*/

void queueChar( void )
{
	/* Create the queue. */
	queue = xQueueCreate(QUEUE_SIZE, sizeof(char));

	if( queue != NULL )
	{
		/* Create the tasks */
		xTaskCreate(queueSendTask,       
                "QueueSendTask",        
                configMINIMAL_STACK_SIZE,
                (void *)STRING_TO_SEND,        /* We pass the STRING_TO_SEND as a task parameter */
                QUEUE_TASKS_PRIORITY, 
                NULL);                

		xTaskCreate(queueReceiveTask,
                    "QueueReceiveTask",
                    configMINIMAL_STACK_SIZE,
                    NULL,
                    QUEUE_TASKS_PRIORITY,
                    NULL);
		
		/* Start the tasks */
		vTaskStartScheduler();
	}

	for( ;; );
}

/*---------------------------- END of the MAIN CODE ----------------------------*/