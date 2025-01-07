
#ifndef MCAL_NVIC_NVIC_H_
#define MCAL_NVIC_NVIC_H_
#include"NVIC_std_types.h"
#warning THis driver only supprts tm123 or any contrler where the priority , enable and disable are mapped in the memmory sequentilay
/*******************************************************************************
 *                           Preprocessor Definitions                          *
 *******************************************************************************/
#define ARM_EXCEPTIONS_NUM 16
#define NVIC_TOTALEXCEPTIONS 154
#define NVIC_ENABLE_BITS_PER_REG 32
#define NVIC_PRIORITY_BITS_PER_REG 4
#define NVIC_PRIORITY_FIRST_BIT (5)
#define NVIC_PRIORITY_BITS_OFFEST (8)

#define NVIC_MEM_MANGEMENT_ENBITMASK 16
#define NVIC_BUS_FAULT_ENBITMASK 17
#define NVIC_USAGE_FAULT_ENBITMASK 18

#define NVIC_MEM_MANGEMENT_PRIBITMASK 5
#define NVIC_BUS_FAULT_PRIBITMASK 13
#define NVIC_USAGE_FAULT_PRIBITMASK 21
#define NVIC_SVCALL_PRIBITMASK 29
#define NVIC_DEBUG_PRIBITMASK 5
#define NVIC_PENDSV_PRIBITMASK 21
#define NVIC_SYSTICK_PRIBITMASK 29
#define NVIC_PRIORITYMASK (0x7)

#define MEM_FAULT_PRIORITY_MASK              0x000000E0
#define MEM_FAULT_PRIORITY_BITS_POS          5

#define BUS_FAULT_PRIORITY_MASK              0x0000E000
#define BUS_FAULT_PRIORITY_BITS_POS          13

#define USAGE_FAULT_PRIORITY_MASK            0x00E00000
#define USAGE_FAULT_PRIORITY_BITS_POS        21

#define SVC_PRIORITY_MASK                    0xE0000000
#define SVC_PRIORITY_BITS_POS                29

#define DEBUG_MONITOR_PRIORITY_MASK          0x000000E0
#define DEBUG_MONITOR_PRIORITY_BITS_POS      5

#define PENDSV_PRIORITY_MASK                 0x00E00000
#define PENDSV_PRIORITY_BITS_POS             21

#define SYSTICK_PRIORITY_MASK                0xE0000000
#define SYSTICK_PRIORITY_BITS_POS            29

#define MEM_FAULT_ENABLE_MASK                0x00010000
#define BUS_FAULT_ENABLE_MASK                0x00020000
#define USAGE_FAULT_ENABLE_MASK              0x00040000

/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmable Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm(" CPSIE I ")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm(" CPSIE F ")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm(" CPSID F ")

/*********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Enables the interrupt for a specific IRQ in the NVIC.
 **********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num);

/*********************************************************************
 * Service Name: NVIC_DisableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Disables the interrupt for a specific IRQ in the NVIC.
 **********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num);

/*********************************************************************
 * Service Name: NVIC_SetPriorityIRQ
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 *                  IRQ_Priority - Priority value to be assigned
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:
 *   Sets the priority for a specific IRQ in the NVIC by configuring
 *   the corresponding priority register and bits. The function ensures
 *   the IRQ number is valid before setting the priority.
 **********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num,
                         NVIC_IRQPriorityType IRQ_Priority);

/*********************************************************************
 * Service Name: NVIC_EnableException
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): Exception_Num - ARM system or fault exception
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Enables specific ARM system or fault exceptions.
 **********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num);

/*********************************************************************
 * Service Name: NVIC_DisableException
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): Exception_Num - ARM system or fault exception to disable
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:
 *   Disables the specified ARM system or fault exception by clearing the
 *   corresponding enable bit in the `SYSHNDCTRL` register. Valid exceptions
 *   include:
 *   - MEM_MANGEMENT: Memory management fault
 *   - BUS_FAULT: Bus fault
 *   - USAGE_FAULT: Usage fault
 **********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num);
/*********************************************************************
 * Service Name: NVIC_SetPriorityException
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): Exception_Num - ARM system or fault exception
 *                 Exception_Priority - Priority value to be set
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the priority value for specific ARM system or fault exceptions.
 **********************************************************************/

void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num,
                               NVIC_ExceptionPriorityType Exception_Priority);

#endif /* MCAL_NVIC_NVIC_H_ */
