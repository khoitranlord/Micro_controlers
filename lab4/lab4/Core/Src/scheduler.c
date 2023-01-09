/*
 * scheduler.c
 *
 *  Created on: Nov 11, 2022
 *      Author: AdminPC
 */
#include "scheduler.h"
#include "stdint.h"
#include <stddef.h>
#include <stdlib.h>

unsigned char Error_code_G = 0;

TaskLL SCH_tasks_G;

void SCH_Init(void)
{
    SCH_tasks_G.head = NULL;
    SCH_tasks_G.size = 0;
    //unsigned char i;
    //for (i = 0; i < SCH_MAX_TASKS; i++)
    //{
    //    SCH_Delete_Task(i);
    //}
    // Reset the global e r ro r v a ri abl e
    // − SCH_Delete_Task ( ) will generate an error code ,
    // ( because the task array is empty)
    //Error_code_G = 0;
//    timer_init();
//    watchdog_init();
}

void SCH_Update(void)
{
    if (SCH_tasks_G.head->task.Delay == 0) {
        SCH_tasks_G.head->task.RunMe = 1;
    } else {
        SCH_tasks_G.head->task.Delay--;
    }
/**
    unsigned char Index;
    // NOTE: calculations are in *TICKS* ( not milliseconds )
    for (Index = 0; Index < SCH_MAX_TASKS; Index++)
    {
        // Check if there is a task at this location
        if (SCH_tasks_G[Index].pTask)
            if (SCH_tasks_G[Index].Delay == 0)
            {
                // The task is due to run
                // Inc . the ’RunMe’ flag
                SCH_tasks_G[Index].RunMe += 1;
                if (SCH_tasks_G[Index].Period)
                {
                    // Schedule periodic tasks to run aga
                    SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
                }
            }
                else
                {
                    // Not yet ready to run : just decrement the delay
                    SCH_tasks_G[Index].Delay -= 1;
                }
    }
**/
}


unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD)
{
		taskNode *node = (taskNode *)malloc(sizeof(taskNode));
	    node->task.pTask = pFunction;
	    node->task.Delay = DELAY;
	    node->task.Period = PERIOD;
	    if (TICKS > 0) {
	        node->task.Delay /= TICKS;
	    }
	    node->task.RunMe = 0;

	    uint8_t idx = 0;
	       if (SCH_tasks_G.size == 0) {
	           SCH_tasks_G.head = node;
	       } else {
	           taskNode *cur = SCH_tasks_G.head;
	           taskNode *prev = NULL;
	           while (cur != NULL && node->task.Delay > cur->task.Delay) {
	               node->task.Delay -= cur->task.Delay;
	               prev = cur;
	               cur = cur->pNext;
	               idx++;
	           }
	           if (prev == NULL) {
	               node->pNext = cur;
	               cur->task.Delay -= node->task.Delay;
	               SCH_tasks_G.head = node;
	           } else {
	           	//add vao giua 2 node
	               prev->pNext = node;
	               node->pNext = cur;
	               if (cur) {
	                   cur->task.Delay -= node->task.Delay;
	               }
	           }
	       }
	       SCH_tasks_G.size++;
	       return idx;

	    // init gia tri cho node
	/**
    unsigned char Index = 0;
    // Fi r s t find a gap in the array ( i f there i s one)
    while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS))
    {
        Index++;
    }
    if (Index == SCH_MAX_TASKS)
    {
        // Task listisfull
        // Set the global error variable
        Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
        // Also return an e r ro r code
        return SCH_MAX_TASKS;
    }
    // I f we ’re here , there is a space in the task array
    SCH_tasks_G[Index].pTask = pFunction;
    SCH_tasks_G[Index].Delay = DELAY;
    SCH_tasks_G[Index].Period = PERIOD;
    SCH_tasks_G[Index].RunMe = 0;
    // return position of task ( to allow later deletion )
    return Index;
    **/
}
void SCH_Dispatch_Tasks(void)
{
	if (SCH_tasks_G.head->task.RunMe == 1) {
	        (*SCH_tasks_G.head->task.pTask)();

	        if (SCH_tasks_G.head->task.Period > 0) { //ko add vo lai -oneshot task
	            SCH_Add_Task(SCH_tasks_G.head->task.pTask, SCH_tasks_G.head->task.Period, SCH_tasks_G.head->task.Period);
	        }

	        SCH_Delete_Task(0);
	    }
	/**
    unsigned char Index;
    // Dispatches (runs ) the next task ( i f one i s ready )
    for (Index = 0; Index < SCH_MAX_TASKS; Index++)
    {
        if (SCH_tasks_G[Index].RunMe > 0)
        {
            (*SCH_tasks_G[Index].pTask)(); // Run the task
            SCH_tasks_G[Index].RunMe -= 1; // Reset / reduce RunMe flag
            // Periodic tasks will automatically run again
            // − if this is a ’one shot ’ task , remove it from the array
            if (SCH_tasks_G[Index].Period == 0)
            {
                SCH_Delete_Task(Index);
            }
        }
    }
    // Report system status
    SCH_Report_Status();
    // The scheduler enters idle mode at this point
    SCH_Go_To_Sleep();
    **/
}

unsigned char SCH_Delete_Task(const tByte TASK_INDEX)
{
	/**
    unsigned char Return_code;
    if (SCH_tasks_G[TASK_INDEX].pTask == 0)
    {
        // No task at this location . . .
        //
        // Set the global error variable
        Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
        // . . . also return an error code
        Return_code = RETURN_ERROR;
    }
    else
    {
        Return_code = RETURN_NORMAL;
    }
    SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
    SCH_tasks_G[TASK_INDEX].Delay = 0;
    SCH_tasks_G[TASK_INDEX].Period = 0;
    SCH_tasks_G[TASK_INDEX].RunMe = 0;
    return Return_code; // return status
    **/
	 if (TASK_INDEX < 0 || TASK_INDEX >= SCH_tasks_G.size)
	        return;

	    taskNode *temp = SCH_tasks_G.head;
	    if (TASK_INDEX == 0) {
	        SCH_tasks_G.head = temp->pNext;
	        SCH_tasks_G.head->task.Delay += temp->task.Delay;
	    } else {
	        uint32_t Index = 0;
	        taskNode *cur = SCH_tasks_G.head;

	        while (Index < TASK_INDEX - 1) {
	            cur = cur->pNext;
	            Index++;
	        }
	        temp = cur->pNext;
	        cur->pNext = temp->pNext;
	        cur->pNext->task.Delay += temp->task.Delay;
	    } //lam cho chac
	    free(temp);
	    temp = NULL;
	    SCH_tasks_G.size--;
}

void SCH_Go_To_Sleep()
{
    // todo : Optional
//	HAL_SuspendTick();
//	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

void SCH_Report_Status(void)
{
#ifdef SCH_REPORT_ERRORS
    // ONLY APPLIES IF WE ARE REPORTING ERRORS
    // Check fo r a new e r ro r code
    if (Error_code_G != Last_error_code_G)
    {
        // Negative l o gic on LEDs assumed
        Error_port = 255 − Error_code_G;
        Last_error_code_G = Error_code_G;
        if (Error_code_G != 0)
        {
            Error_tick_count_G = 60000;
        }
        else
        {
            Error_tick_count_G = 0;
        }
    }
    else
    {
        if (Error_tick_count_G != 0)
        {
            if (−−Error_tick_count_G == 0)
            {
                Error_code_G = 0; // Reset e r ro r code
            }
        }
    }
#endif
}
