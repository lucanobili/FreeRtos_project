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

/******************************************************************************
 * This project provides two demo applications.  A simple blinky style project,
 * and a more comprehensive test and demo application.  The
 * mainCREATE_SIMPLE_BLINKY_DEMO_ONLY setting in main.c is used to select
 * between the two.  See the notes on using mainCREATE_SIMPLE_BLINKY_DEMO_ONLY
 * in main.c.  This file implements the simply blinky version.
 *
 * This file only contains the source code that is specific to the basic demo.
 * Generic functions, such FreeRTOS hook functions, are defined in main.c.
 ******************************************************************************
 *
 * main_blinky() creates one queue, one software timer, and two tasks.  It then
 * starts the scheduler.
 *
 * The Queue Send Task:
 * The queue send task is implemented by the prvQueueSendTask() function in
 * this file.  It uses vTaskDelayUntil() to create a periodic task that sends
 * the value 100 to the queue every 200 (simulated) milliseconds.
 *
 * The Queue Send Software Timer:
 * The timer is an auto-reload timer with a period of two (simulated) seconds.
 * Its callback function writes the value 200 to the queue.  The callback
 * function is implemented by prvQueueSendTimerCallback() within this file.
 *
 * The Queue Receive Task:
 * The queue receive task is implemented by the prvQueueReceiveTask() function
 * in this file.  prvQueueReceiveTask() waits for data to arrive on the queue.
 * When data is received, the task checks the value of the data, then outputs a
 * message to indicate if the data came from the queue send task or the queue
 * send software timer.
 */

/* Standard includes. */
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include <limits.h>
#include <stdint.h>
#include "task.h"
#include "timers.h"
#include "queue.h"

/* Priorities at which the tasks are created. */
#define mainQUEUE_RECEIVE_TASK_PRIORITY		( tskIDLE_PRIORITY + 2 )
#define	mainQUEUE_SEND_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )
#define	priotask		( tskIDLE_PRIORITY + 1)

/* The rate at which data is sent to the queue.  The times are converted from
milliseconds to ticks using the pdMS_TO_TICKS() macro. */
#define mainTASK_SEND_FREQUENCY_MS			pdMS_TO_TICKS( 200UL )
#define mainTASK_SEND_FREQUENCY_MS1			pdMS_TO_TICKS( 4000UL )

#define mainTIMER_SEND_FREQUENCY_MS			pdMS_TO_TICKS( 2000UL )


/* The number of items the queue can hold at once. */
#define mainQUEUE_LENGTH					( 2 )

/* The values sent to the queue receive task from the queue send task and the
queue send software timer respectively. */
#define mainVALUE_SENT_FROM_TASK			( 100UL )
#define mainVALUE_SENT_FROM_TASK1			( 400UL )
#define mainVALUE_SENT_FROM_TIMER			( 200UL )

/*-----------------------------------------------------------*/

/*
 * The tasks as described in the comments at the top of this file.
 */
static void TSK_A( void *pvParameters );
static void TSK_B( void *pvParameters );
static void TSK_C( void *pvParameters );
static void TSK_D( void *pvParameters );




/*
 * The callback function executed when the software timer expires.
 */
static void prvQueueSendTimerCallback( TimerHandle_t xTimerHandle );

/*-----------------------------------------------------------*/

/* A software timer that is started from the tick hook. */
static TimerHandle_t xTimer = NULL;

/* notifications */
static TaskHandle_t xHandlingTask;

#define T1_BIT    0x01
#define T2_BIT    0x02
#define capacityA 20
#define capacityB 30
#define capacityAperiodic 10
#define A_PERIOD 40
#define B_PERIOD 70

/*-----------------------------------------------------------*/
#define TASK1_STACK_SIZE  configMINIMAL_STACK_SIZE * 4
/*** SEE THE COMMENTS AT THE TOP OF THIS FILE ***/
void main_edf_aperiodic( void )
{
   const TickType_t xTimerPeriod = mainTIMER_SEND_FREQUENCY_MS;

   xTaskCreateEDF( TSK_A, "A", TASK1_STACK_SIZE, NULL, 1 , NULL, A_PERIOD);
   xTaskCreateEDF( TSK_B, "B", TASK1_STACK_SIZE, NULL, 1 , NULL, B_PERIOD);
   xTaskCreateEDFaperiodic( TSK_C, "C", TASK1_STACK_SIZE, NULL, 1, NULL, A_PERIOD);
   xTaskCreateEDFaperiodic( TSK_D, "D", TASK1_STACK_SIZE, NULL, 1, NULL, A_PERIOD);


 
	/* Create the software timer, but don't start it yet. */
	
			/* Start the tasks and timer running. */
	vTaskStartScheduler();

		/* If all is well, the scheduler will now be running, and the following
		line will never be reached.  If the following line does execute, then
		there was insufficient FreeRTOS heap memory available for the idle and/or
		timer tasks	to be created.  See the memory management section on the
		FreeRTOS web site for more details.  NOTE: This demo uses static allocation
		for the idle and timer tasks so this line should never execute. */
		for( ;; );
}
/*-----------------------------------------------------------*/

/* Task to be created. */

void TSK_A( void *pvParameters)
{
	( void ) pvParameters;
   TickType_t xNextWakeTimeA;
   const TickType_t xFrequency = A_PERIOD;
   xNextWakeTimeA = 0;

   for( ;; ){
      TickType_t count = capacityA;
      TickType_t x;
      TickType_t time = xTaskGetTickCount() ;
      while( count > 0)
      {  
         if( (x = xTaskGetTickCount()) > time ){
            time = x;
            count = count -1 ; 
         }  
      }
      vTaskDelayUntil( &xNextWakeTimeA, xFrequency );
   }
}

void TSK_C( void *pvParameters)
{
	( void ) pvParameters;
   TickType_t count = capacityAperiodic;
   TickType_t x;
   TickType_t time = xTaskGetTickCount() ;
   while( count > 0)
      {  
         if( (x = xTaskGetTickCount()) > time ){
            time = x;
            count = count -1 ; 
         }  
      }
   vTaskDelete(NULL); 
}

void TSK_D( void *pvParameters)
{ 
	( void ) pvParameters;
   TickType_t count = capacityAperiodic;
   TickType_t x;
   TickType_t time = xTaskGetTickCount() ;
   while( count > 0)
      {  
         if( (x = xTaskGetTickCount()) > time ){
            time = x;
            count = count -1 ; 
         }  
      }
   vTaskDelete(NULL); 
}


void TSK_B( void *pvParameters)
{
	( void ) pvParameters;
   TickType_t xNextWakeTimeB;
   const TickType_t xFrequency = B_PERIOD;
   xNextWakeTimeB = 0;
   
   for( ;; ){
      TickType_t count = capacityB;
      TickType_t x;
      TickType_t time = xTaskGetTickCount() ;
      while( count > 0)
      {  
         if( (x = xTaskGetTickCount()) > time ){
            time = x;
            count = count -1 ; 
         }      
      }
      vTaskDelayUntil( &xNextWakeTimeB, xFrequency );
   }
}