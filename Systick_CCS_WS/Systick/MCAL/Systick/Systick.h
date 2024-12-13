
#ifndef MCAL_SYSTICK_SYSTICK_H_
#define MCAL_SYSTICK_SYSTICK_H_

#include "Systick_std_types.h"
#define F_CPU (16000000u)

/*********************************************************************
 * Service Name: SysTick_Init
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): a_TimeInMilliSeconds - Time interval in milliseconds
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initialize the SysTick timer with the specified time in milliseconds
 *using interrupts. This function is used to setup the timer to generate periodic
 *interrupts every specified time in milliseconds.
 **********************************************************************/
void SysTick_Init(SYSTICK_TIMEMS a_TimeInMilliSeconds);

/*********************************************************************
* Service Name: SysTick_StartBusyWait
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): a_TimeInMilliSeconds - Time interval in milliseconds
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:
*   Starts the SysTick timer in busy-wait mode for the specified time
*   in milliseconds. The function blocks until the time elapses and stops
*   the timer at the end,The function doesn't block the original
*    intialization unless desired time is less than original time it blocks
*    the callBack function Till the end of the busy Wait
**********************************************************************/
void SysTick_StartBusyWait(SYSTICK_TIMEMS a_TimeInMilliSeconds);

/*********************************************************************
 * Service Name: SysTick_Handler
 * Sync/Async: Asynchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:
 *   Interrupt handler for the SysTick timer. Executes the registered
 *   callback function if available. Increments the counter for busy-wait mode.
 **********************************************************************/
void SysTick_Handler(void);

/*********************************************************************
* Service Name: SysTick_SetCallBack
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): Ptr2Func - Pointer to the callback function
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:
*   Registers a callback function to be executed when the SysTick
*   interrupt is triggered.
**********************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func)(void));
/*********************************************************************
* Service Name: SysTick_Stop
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:
*   Stops the SysTick timer.
**********************************************************************/
void SysTick_Stop(void);
/*********************************************************************
* Service Name: SysTick_Start
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:
*   Resumes/Start the SysTick timer.
**********************************************************************/
void SysTick_Start(void);

/*********************************************************************
* Service Name: SysTick_DeInit
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
*Description: Function to De-initialize the SysTick Timer.
**********************************************************************/
void SysTick_DeInit(void);

#endif /* MCAL_SYSTICK_SYSTICK_H_ */
