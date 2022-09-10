#include "FreeRTOS.h"

#include "task.h"

/* Demo includes. */
#include "basic_io.h"

/* Used as a loop counter to create a very crude delay. */
#define mainDELAY_LOOP_COUNT        ( 0xfffff )

/* The task functions. */
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );

int main( void )
{
	/* Create one of the two tasks. */
  xTaskCreate(    vTask1,     /* Pointer to the function that implements the task. */
                    "Task 1",   /* Text name for the task.  This is to facilitate debugging only. */
                    200,        /* Stack depth in words. */
                    NULL,       /* We are not using the task parameter. */
                    1,          /* This task will run at priority 1. */
                    NULL );     /* We are not using the task handle. */

  /* Create the other task in exactly the same way. */
  xTaskCreate( vTask2, "Task 2", 200, NULL, 1, NULL );

  /* Start the scheduler so our tasks start executing. */
  vTaskStartScheduler();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vTask1( void *pvParameters )
{
	const char *pcTaskName = "Task 1 is running\n";
	volatile unsigned long ul;

  /* As per most tasks, this task is implemented in an infinite loop. */
  for( ;; )
  {
		/* Print out the name of this task. */
		vPrintString( pcTaskName );
			
		/* Delay for a period. */
    for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
    {
			/* This loop is just a very crude delay implementation.  There is
			nothing to do in here.  Later exercises will replace this crude
      loop with a proper delay/sleep function. */
    }
  }
}
/*-----------------------------------------------------------*/

void vTask2( void *pvParameters )
{
	const char *pcTaskName = "Task 2 is running\n";
	volatile unsigned long ul;

  /* As per most tasks, this task is implemented in an infinite loop. */
  for( ;; )
  {
		/* Print out the name of this task. */
		vPrintString( pcTaskName );
			
		/* Delay for a period. */
    for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
    {
			/* This loop is just a very crude delay implementation.  There is
			nothing to do in here.  Later exercises will replace this crude
      loop with a proper delay/sleep function. */
    }
  }
}
