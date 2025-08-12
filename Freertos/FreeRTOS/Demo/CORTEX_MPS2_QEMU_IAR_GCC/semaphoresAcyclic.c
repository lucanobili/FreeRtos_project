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
#include "semphr.h"

/* Priorities at which the tasks are created. */
#define TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )

/* Global Variables */
SemaphoreHandle_t sem1, sem2, mutex;

/*---------------------------- START of the TASKS' CODE ----------------------------*/

void task1(void *pvParameters) 
{
	( void ) pvParameters;

	printf("Taks 1\r\n");
    xSemaphoreGive( sem1 );
    xSemaphoreGive( sem1 );
	
	vTaskDelete( NULL );
}

void task2(void *pvParameters) 
{
	( void ) pvParameters;
    TickType_t xNextWakeTime = 5;
    xSemaphoreTake( sem1, portMAX_DELAY );
    xSemaphoreTake( mutex, portMAX_DELAY );
    printf("Taks 2\r\n");
    xSemaphoreGive( mutex );
    vTaskDelay(xNextWakeTime);
    xSemaphoreGive( sem2 );

	vTaskDelete( NULL );
}

void task3(void *pvParameters) 
{
	( void ) pvParameters;
    TickType_t xNextWakeTime = 8;
    xSemaphoreTake( sem1, portMAX_DELAY );
    xSemaphoreTake( mutex, portMAX_DELAY );
    printf("Taks 3\r\n");
    xSemaphoreGive( mutex );
    vTaskDelay(xNextWakeTime);
    xSemaphoreGive( sem2 );

	vTaskDelete( NULL );
}

void task4(void *pvParameters) 
{
	( void ) pvParameters;
    xSemaphoreTake( sem2, portMAX_DELAY );
    xSemaphoreTake( sem2, portMAX_DELAY );
    printf("Taks 4\r\n");

	vTaskDelete( NULL );
}

/*---------------------------- END of the TASKS' CODE ----------------------------*/



/*---------------------------- START of the MAIN CODE ----------------------------*/

void semaphoresAcyclic( void )
{
    sem1 = xSemaphoreCreateCounting(2, 0);			/* A Counting Semaphore with MAX_VALUE = 2 is needed to correctly handle the double xSemaphoreGive( sem1 ); instruction */
    sem2 = xSemaphoreCreateBinary();
    mutex = xSemaphoreCreateMutex();

	/* If the Semaphores have been correctly allocated */
	if( sem1 != NULL && sem2 != NULL && mutex != NULL )				
	{
		/* Create the tasks */
		xTaskCreate(task1, "Task1", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
        xTaskCreate(task2, "Task2", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY, NULL);  
        xTaskCreate(task3, "Task3", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY, NULL);  
        xTaskCreate(task4, "Task4", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY, NULL);         
        
        /* Start the tasks */
		vTaskStartScheduler();
	}

	for( ;; );
}

/*---------------------------- END of the MAIN CODE ----------------------------*/