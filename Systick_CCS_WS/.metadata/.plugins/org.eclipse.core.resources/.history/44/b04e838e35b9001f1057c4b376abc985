/*
 * Systick.h
 *
 *  Created on: 13 Dec 2024
 *      Author: MSI
 */

#ifndef MCAL_SYSTICK_SYSTICK_H_
#define MCAL_SYSTICK_SYSTICK_H_

#include "Systick_std_types"

/*Description: Initialize the SysTick timer with the specified time in milliseconds
 *using interrupts. This function is used to setup the timer to generate periodic
 *interrupts every specified time in milliseconds.*/
void SyTick_Init(SYSTICK_TIMEMS a_TimeInMilliSeconds);

/*Description: Initialize the SysTick timer with the specified time in milliseconds
 *using polling or busy-wait technique. The function should exit when the time is
 *elapsed and stops the timer at the end.*/
void SysTick_StartBusyWait(SYSTICK_TIMEMS a_TimeInMilliSeconds);

/*Description: Handler for SysTick interrupt use to call the call-back function.*/
void SysTick_Handler(void);

/*Description: Function to setup the SysTick Timer call back to be executed in
 *SysTick Handler.*/
void SysTick_SetCallBack(volatile void (*Ptr2Func)(void));
/*Description: Stop the SysTick timer.*/
void SysTick_Stop(void);
/*Description: Start/Resume the SysTick timer.*/
void SysTick_Start(void);

/*Description: Function to De-initialize the SysTick Timer.*/
void SysTick_DeInit(void);

#endif /* MCAL_SYSTICK_SYSTICK_H_ */
