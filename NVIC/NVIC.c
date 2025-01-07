#include "NVIC.h"
#include "MCAL/tm4c123gh6pm_registers.h"
#include "common_macros.h"


static volatile uint32 *const ptr2_NVIC_PRI0 = &NVIC_PRI0_REG;
static volatile uint32 *const ptr2_NVIC_EN0 = &NVIC_EN0_REG;
static volatile uint32 *const ptr2_NVIC_DIS0 = &NVIC_DIS0_REG;

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
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    if (IRQ_Num < ARM_EXCEPTIONS_NUM || IRQ_Num > NVIC_TOTALEXCEPTIONS)
        return;

    uint8 l_enRegNum = (IRQ_Num - ARM_EXCEPTIONS_NUM) / NVIC_ENABLE_BITS_PER_REG;
    uint8 l_enBitNum = (IRQ_Num - ARM_EXCEPTIONS_NUM) % NVIC_ENABLE_BITS_PER_REG;

    SET_BIT(ptr2_NVIC_EN0[l_enRegNum], l_enBitNum);
}

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
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{
    if (IRQ_Num < ARM_EXCEPTIONS_NUM || IRQ_Num > NVIC_TOTALEXCEPTIONS)
        return;  // Only external IRQs (16–138) are valid.

    uint8 l_disRegNum = (IRQ_Num - ARM_EXCEPTIONS_NUM) / NVIC_ENABLE_BITS_PER_REG;
    uint8 l_disBitNum = (IRQ_Num - ARM_EXCEPTIONS_NUM) % NVIC_ENABLE_BITS_PER_REG;

    SET_BIT(ptr2_NVIC_DIS0[l_disRegNum], l_disBitNum);
}
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
                         NVIC_IRQPriorityType IRQ_Priority){

    if (IRQ_Num < ARM_EXCEPTIONS_NUM || IRQ_Num > NVIC_TOTALEXCEPTIONS)
            return;

        uint8 l_priRegNum = (IRQ_Num - ARM_EXCEPTIONS_NUM) / NVIC_PRIORITY_BITS_PER_REG;
        uint8 l_priBitNum = NVIC_PRIORITY_FIRST_BIT + NVIC_PRIORITY_BITS_OFFEST*((IRQ_Num - ARM_EXCEPTIONS_NUM) % NVIC_PRIORITY_BITS_PER_REG);
        ptr2_NVIC_PRI0[l_priRegNum] = (ptr2_NVIC_PRI0[l_priRegNum] & ~(NVIC_PRIORITYMASK << l_priBitNum)) | (IRQ_Priority << l_priBitNum);

}
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
void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{
    switch (Exception_Num)
    {
    case EXCEPTION_MEM_FAULT_TYPE:
        SET_BIT(NVIC_SYSTEM_SYSHNDCTRL, NVIC_MEM_MANGEMENT_ENBITMASK);
        break;
    case EXCEPTION_BUS_FAULT_TYPE:
        SET_BIT(NVIC_SYSTEM_SYSHNDCTRL, NVIC_BUS_FAULT_ENBITMASK);
        break;
    case EXCEPTION_USAGE_FAULT_TYPE:
        SET_BIT(NVIC_SYSTEM_SYSHNDCTRL, NVIC_USAGE_FAULT_ENBITMASK);
        break;
    default:
        break;
    }
}

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
                               NVIC_ExceptionPriorityType Exception_Priority)
{
    switch (Exception_Num)
    {
    case EXCEPTION_MEM_FAULT_TYPE:
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~(NVIC_PRIORITYMASK << NVIC_MEM_MANGEMENT_PRIBITMASK)) | (Exception_Priority << NVIC_MEM_MANGEMENT_PRIBITMASK);
        break;
    case EXCEPTION_BUS_FAULT_TYPE:
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~(NVIC_PRIORITYMASK << NVIC_BUS_FAULT_PRIBITMASK)) | (Exception_Priority << NVIC_BUS_FAULT_PRIBITMASK);
        break;
    case EXCEPTION_USAGE_FAULT_TYPE:
        NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~(NVIC_PRIORITYMASK << NVIC_USAGE_FAULT_PRIBITMASK)) | (Exception_Priority << NVIC_USAGE_FAULT_PRIBITMASK);
        break;
    case EXCEPTION_SVC_TYPE:
        NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & ~(NVIC_PRIORITYMASK << NVIC_SVCALL_PRIBITMASK)) | (Exception_Priority << NVIC_SVCALL_PRIBITMASK);
        break;
    case EXCEPTION_DEBUG_MONITOR_TYPE:
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~(NVIC_PRIORITYMASK << NVIC_DEBUG_PRIBITMASK)) | (Exception_Priority << NVIC_DEBUG_PRIBITMASK);
        break;
    case EXCEPTION_PEND_SV_TYPE:
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~(NVIC_PRIORITYMASK << NVIC_PENDSV_PRIBITMASK)) | (Exception_Priority << NVIC_PENDSV_PRIBITMASK);
        break;
    case EXCEPTION_SYSTICK_TYPE:
        NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~(NVIC_PRIORITYMASK << NVIC_SYSTICK_PRIBITMASK)) | (Exception_Priority << NVIC_SYSTICK_PRIBITMASK);
        break;
    default:
        break;
    }
}
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

void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
    switch (Exception_Num)
    {
    case EXCEPTION_MEM_FAULT_TYPE:
        CLEAR_BIT(NVIC_SYSTEM_SYSHNDCTRL, NVIC_MEM_MANGEMENT_ENBITMASK);
        break;
    case EXCEPTION_BUS_FAULT_TYPE:
        CLEAR_BIT(NVIC_SYSTEM_SYSHNDCTRL, NVIC_BUS_FAULT_ENBITMASK);
        break;
    case EXCEPTION_USAGE_FAULT_TYPE:
        CLEAR_BIT(NVIC_SYSTEM_SYSHNDCTRL, NVIC_USAGE_FAULT_ENBITMASK);
        break;
    default:
        break;
    }
}

