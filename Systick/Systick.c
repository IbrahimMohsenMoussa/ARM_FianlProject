#include "Systick.h"
#include"MCAL/tm4c123gh6pm_registers.h"
#include "common_macros.h"

#define SYSTICK_SEC_TO_MSEC (1000u)
#define SYSTICK_CLOCKSOURCE 2
#define SYSTICK_INTEN  1
#define SYSTICK_Enable  0
static volatile boolean g_EnBusyWait = FALSE;
volatile void (*g_ptr2CallBackFunction)(void) = NULL_PTR;
static volatile uint32 g_counter = 0;
static SYSTICK_TIMEMS g_intialTime = SYSTICK_ZERO;

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

void SysTick_Init(SYSTICK_TIMEMS a_TimeInMilliSeconds)
{
    if (a_TimeInMilliSeconds == SYSTICK_ZERO)
        return;
    g_intialTime = a_TimeInMilliSeconds;
    SYSTICK_CTRL_REG = SYSTICK_ZERO;
    SYSTICK_RELOAD_REG = (uint32) (((F_CPU / SYSTICK_SEC_TO_MSEC)
            * a_TimeInMilliSeconds) - 1);
    SET_BIT(SYSTICK_CTRL_REG, SYSTICK_CLOCKSOURCE);
    SET_BIT(SYSTICK_CTRL_REG, SYSTICK_INTEN);
    SET_BIT(SYSTICK_CTRL_REG, SYSTICK_Enable);
}

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
void SysTick_DeInit(void)
{

    SYSTICK_CTRL_REG = SYSTICK_ZERO;
    SYSTICK_RELOAD_REG = SYSTICK_ZERO;
}

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
void SysTick_Stop(void)
{
    CLEAR_BIT(SYSTICK_CTRL_REG, SYSTICK_Enable);
}

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
void SysTick_Start(void)
{
    SET_BIT(SYSTICK_CTRL_REG, SYSTICK_Enable);
}

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
void SysTick_SetCallBack(volatile void (*ptr2_Func)(void))
{
    g_ptr2CallBackFunction = ptr2_Func;
}

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
 *    initialization unless desired time is less than original time it blocks
 *    the callBack function Till the end of the busy Wait
 **********************************************************************/
void SysTick_StartBusyWait(SYSTICK_TIMEMS a_TimeInMilliSeconds)
{
    g_counter = SYSTICK_ZERO;
    volatile void (*l_ptr2_funcTemp)(void) = g_ptr2CallBackFunction;
    uint16 l_counter = SYSTICK_ZERO;
    if (g_intialTime == SYSTICK_ZERO || (a_TimeInMilliSeconds < g_intialTime))
    {
        SYSTICK_RELOAD_REG = (uint32) (((F_CPU / SYSTICK_SEC_TO_MSEC)
                * a_TimeInMilliSeconds) - 1);
        l_counter = 1;
        g_ptr2CallBackFunction = NULL_PTR;
    }
    else if (a_TimeInMilliSeconds > g_intialTime)
    {
        l_counter = (uint16) (a_TimeInMilliSeconds / g_intialTime);

    }
    g_EnBusyWait = TRUE;
    while (g_counter <= l_counter)
        ;
    g_ptr2CallBackFunction = l_ptr2_funcTemp;
    g_EnBusyWait = FALSE;
    SYSTICK_RELOAD_REG =
            (uint32) (((F_CPU / SYSTICK_SEC_TO_MSEC) * g_intialTime) - 1);
}

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
void SysTick_Handler(void)
{
    if (g_ptr2CallBackFunction != NULL_PTR)
    {
        g_ptr2CallBackFunction();
    }
    if (g_EnBusyWait)
    {
        g_counter++;
    }

}

