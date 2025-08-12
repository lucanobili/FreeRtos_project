
/* Standard includes. */
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Priorities at which the tasks are created. */
#define mainTASK2_PRIORITY		( tskIDLE_PRIORITY + 3 )
#define	mainTASK1_PRIORITY		( tskIDLE_PRIORITY + 1 )

static TaskHandle_t tsk1;

static void task1( void *pvParameters );
static void task2( void *pvParameters );

/*** SEE THE COMMENTS AT THE TOP OF THIS FILE ***/
void Preemption( void )
{
	/* Start the three tasks as described in the comments at the top of this file. */
	xTaskCreate( task1,			                /* The function that implements the task. */
				"TSK1", 						/* The text name assigned to the task - for debug only as it is not used by the kernel. */
				configMINIMAL_STACK_SIZE, 		/* The size of the stack to allocate to the task. */
				NULL, 							/* The parameter passed to the task - not used in this simple case. */
				mainTASK1_PRIORITY,             /* The priority assigned to the task. */
				&tsk1 );						/* The task handle is not required, so NULL is passed. */

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


static void taskJob(){
	for(int i = 0; i < 100000000; i++);
}

static void task2( void *pvParameters )
{
	/* Prevent the compiler warning about the unused parameter. */
	( void ) pvParameters;

	int count = 0;
	for(;;) {
        for (int i = 0; i < 2; i++) {
            taskJob();
        }
		count++;
		printf("Task 2 \n\r");
		if(count == 3){
			vTaskDelete(NULL);
		}
	}

}
/*-----------------------------------------------------------*/

static void task1( void *pvParameters )
{

	/* Prevent the compiler warning about the unused parameter. */
	( void ) pvParameters;
	int count = 0;
	for(;;) {
        for (int i = 0; i < 3; i++) {
            taskJob();
        }
		count++;
		printf("Task 1 \n\r");
		if(count == 3){
			xTaskCreate( task2, "TSK2", configMINIMAL_STACK_SIZE, NULL, mainTASK2_PRIORITY, NULL ); 
		}
	}

}

