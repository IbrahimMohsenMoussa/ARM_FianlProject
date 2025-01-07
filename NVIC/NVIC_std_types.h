

#ifndef MCAL_NVIC_NVIC_STD_TYPES_H_
#define MCAL_NVIC_NVIC_STD_TYPES_H_
#include "std_types.h"
typedef uint8 NVIC_IRQType;
typedef uint8 NVIC_IRQPriorityType;

typedef uint8 NVIC_ExceptionPriorityType;

typedef enum
{
    EXCEPTION_RESET_TYPE,
    EXCEPTION_NMI_TYPE,
    EXCEPTION_HARD_FAULT_TYPE,
    EXCEPTION_MEM_FAULT_TYPE,
    EXCEPTION_BUS_FAULT_TYPE,
    EXCEPTION_USAGE_FAULT_TYPE,
    EXCEPTION_SVC_TYPE,
    EXCEPTION_DEBUG_MONITOR_TYPE,
    EXCEPTION_PEND_SV_TYPE,
    EXCEPTION_SYSTICK_TYPE
}NVIC_ExceptionType;


#endif /* MCAL_NVIC_NVIC_STD_TYPES_H_ */

