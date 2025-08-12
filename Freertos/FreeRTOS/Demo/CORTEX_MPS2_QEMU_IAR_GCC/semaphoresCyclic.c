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
SemaphoreHandle_t sem1c, sem2c, sem3c, sem4c, mutexc;
int counter;

/*---------------------------- START of the TASKS' CODE ----------------------------*/

void task1c(void *pvParameters)
{
	( void ) pvParameters;

	for( ;; ) 
	{
		xSemaphoreTake( sem1c , portMAX_DELAY );
		printf("Task 1\r\n");
		xSemaphoreGive( sem2c );
		xSemaphoreGive( sem3c );
	}

	vTaskDelete( NULL );
}

void task2c(void *pvParameters) 
{
	( void ) pvParameters;

	for( ;; ) 
	{
		xSemaphoreTake( sem2c , portMAX_DELAY );
		xSemaphoreTake( mutexc, portMAX_DELAY );
    	printf("Task 2\r\n");
    	xSemaphoreGive( mutexc );
		xSemaphoreGive( sem4c );
	}

	vTaskDelete( NULL );
}

void task3c(void *pvParameters) 
{
	( void ) pvParameters;

	for( ;; ) 
	{
		xSemaphoreTake( sem3c , portMAX_DELAY );
		xSemaphoreTake( mutexc, portMAX_DELAY );
    	printf("Task 3\r\n");
    	xSemaphoreGive( mutexc );
		xSemaphoreGive( sem4c );
	}

	vTaskDelete( NULL );
}

void task4c(void *pvParameters) 
{
	( void ) pvParameters;

	for( ;; ) 
	{
		xSemaphoreTake( sem4c , portMAX_DELAY );
		xSemaphoreTake( sem4c , portMAX_DELAY );
		printf("Task 4\r\n%d\r\n\n", counter++);

		/* Artificial Delay of the Task Cycle */
		vTaskDelay( pdMS_TO_TICKS( 1000UL ) );		
		xSemaphoreGive( sem1c );
	}
	
	vTaskDelete( NULL );
}

/*---------------------------- END of the TASKS' CODE ----------------------------*/



/*---------------------------- START of the MAIN CODE ----------------------------*/

void semaphoresCyclic( void )
{
	sem1c = xSemaphoreCreateCounting(1, 1);
    sem2c = xSemaphoreCreateCounting(1, 0);
	sem3c = xSemaphoreCreateCounting(1, 0);
    sem4c = xSemaphoreCreateCounting(2, 0);
	mutexc = xSemaphoreCreateMutex();

	if( sem1c != NULL && sem2c != NULL && sem3c != NULL && sem4c != NULL )
	{
		/* Create the tasks */
		xTaskCreate(task1c, "task1", configMINIMAL_STACK_SIZE,  NULL, TASK_PRIORITY, NULL);                
		xTaskCreate(task2c, "task2", configMINIMAL_STACK_SIZE,  NULL, TASK_PRIORITY, NULL); 
		xTaskCreate(task3c, "task3", configMINIMAL_STACK_SIZE,  NULL, TASK_PRIORITY, NULL);          
		xTaskCreate(task4c, "task4", configMINIMAL_STACK_SIZE,  NULL, TASK_PRIORITY, NULL); 

		/* Start the tasks */
		vTaskStartScheduler();
	}	

	for( ;; );
}

/*---------------------------- END of the MAIN CODE ----------------------------*/