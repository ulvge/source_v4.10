;/*****************************************************************************/
;/* STM32F10x.s: Startup file for ST STM32F10x device series                  */
;/*****************************************************************************/
;/* <<< Use Configuration Wizard in Context Menu >>>                          */
;/*****************************************************************************/
;/* This file is part of the uVision/ARM development tools.                   */
;/* Copyright (c) 2005-2007 Keil Software. All rights reserved.               */
;/* This software may only be used under the terms of a valid, current,       */
;/* end user licence from KEIL for a compatible version of KEIL software      */
;/* development tools. Nothing else gives you the right to use this software. */
;/*****************************************************************************/


;// <h> Stack Configuration
;//   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;// </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


;// <h> Heap Configuration
;//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;// </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
				IMPORT  ||Image$$ARM_LIB_STACK$$ZI$$Limit||

__Vectors  		DCD     ||Image$$ARM_LIB_STACK$$ZI$$Limit||         ;  0, SP start value.
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     WWDG_IRQHandler           ; Window Watchdog
                DCD     PVD_IRQHandler            ; PVD through EXTI Line detect
                DCD     TAMPER_IRQHandler         ; Tamper
                DCD     RTC_IRQHandler            ; RTC
                DCD     FLASH_IRQHandler          ; Flash
                DCD     RCC_IRQHandler            ; RCC
                DCD     EXTI0_IRQHandler          ; EXTI Line 0
                DCD     EXTI1_IRQHandler          ; EXTI Line 1
                DCD     EXTI2_IRQHandler          ; EXTI Line 2
                DCD     EXTI3_IRQHandler          ; EXTI Line 3
                DCD     EXTI4_IRQHandler          ; EXTI Line 4
                DCD     DMA1_Channel1_IRQHandler    ; DMA1 Channel 1
                DCD     DMA1_Channel2_IRQHandler    ; DMA1 Channel 2
                DCD     DMA1_Channel3_IRQHandler    ; DMA1 Channel 3
                DCD     DMA1_Channel4_IRQHandler    ; DMA1 Channel 4
                DCD     DMA1_Channel5_IRQHandler    ; DMA1 Channel 5
                DCD     DMA1_Channel6_IRQHandler    ; DMA1 Channel 6
                DCD     DMA1_Channel7_IRQHandler    ; DMA1 Channel 7
                DCD     ADC1_2_IRQHandler            ; ADC&ADC2
                DCD     CAN1_TX_IRQHandler  ; CAN TX
                DCD     CAN1_RX0_IRQHandler ; CAN RX0
                DCD     CAN1_RX1_IRQHandler        ; CAN RX1
                DCD     CAN1_SCE_IRQHandler        ; CAN SCE
                DCD     EXTI9_5_IRQHandler        ; EXTI Line 9..5
                DCD     TIM1_BRK_IRQHandler       ; TIM1 Break
                DCD     TIM1_UP_IRQHandler        ; TIM1 Update
                DCD     TIM1_TRG_COM_IRQHandler   ; TIM1 Trigger and Commutation
                DCD     TIM1_CC_IRQHandler        ; TIM1 Capture Compare
                DCD     TIM2_IRQHandler           ; TIM2
                DCD     TIM3_IRQHandler           ; TIM3
                DCD     TIM4_IRQHandler           ; TIM4
                DCD     I2C1_EV_IRQHandler        ; I2C1 Event
                DCD     I2C1_ER_IRQHandler        ; I2C1 Error
                DCD     I2C2_EV_IRQHandler        ; I2C2 Event
                DCD     I2C2_ER_IRQHandler        ; I2C2 Error
                DCD     SPI1_IRQHandler           ; SPI1
                DCD     SPI2_IRQHandler           ; SPI2
                DCD     USART1_IRQHandler         ; USART1
                DCD     USART2_IRQHandler         ; USART2
                DCD     USART3_IRQHandler         ; USART3
                DCD     EXTI15_10_IRQHandler      ; EXTI Line 15..10
                DCD     RTCAlarm_IRQHandler       ; RTC Alarm through EXTI Line
                DCD     OTG_FS_WKUP_IRQHandler      ; USB On-The-Go FS Wakeup through EXTI line interrupt
                DCD		TIM8_BRK_IRQHandler    
                DCD		TIM8_UP_IRQHandler     
                DCD		TIM8_TRG_COM_IRQHandler
                DCD		TIM8_CC_IRQHandler     
                DCD		ADC3_IRQHandler        
                DCD		FSMC_IRQHandler        
                DCD		SDIO_IRQHandler        
		  DCD	TIM5_IRQHandler		;TIM5
		  DCD	SPI3_IRQHandler		;SPI3
		  DCD	USART4_IRQHandler		;USART4
		  DCD	USART5_IRQHandler		;USART5
		  DCD	TIM6_IRQHandler		;TIM6
		  DCD	TIM7_IRQHandler		;TIM7
		  DCD     DMA2_Channel1_IRQHandler    ; DMA2 Channel 1
                DCD     DMA2_Channel2_IRQHandler    ; DMA2 Channel 2
                DCD     DMA2_Channel3_IRQHandler    ; DMA2 Channel 3
                DCD     DMA2_Channel4_IRQHandler    ; DMA2 Channel 4
                DCD     DMA2_Channel5_IRQHandler    ; DMA2 Channel 5
		  DCD	ETH_IRQHandler			    ; Ethernet global interrupt
		  DCD	ETH_WKUP_IRQHandler			;Ethernet Wakeup through EXTI line interrupt
		  DCD	CAN2_TX_IRQHandler			;CAN2 TX
		  DCD	CAN2_RX0_IRQHandler			;CAN2 RX0
		  DCD	CAN2_RX1_IRQHandler			;CAN2 RX1
		  DCD	CAN2_CSE_IRQHandler			;CAN2 CSE
		  DCD	OTG_FS_IRQHandler		;USB OTG FS global interrupt
		  
                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                ;EXPORT  Reset_Handler             [WEAK]
                IMPORT  __main

                CPSID   I
				MOV		R0,#0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)                

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler		PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDG_IRQHandler           [WEAK]
                EXPORT  PVD_IRQHandler            [WEAK]
                EXPORT  TAMPER_IRQHandler         [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]
                EXPORT  FLASH_IRQHandler          [WEAK]
                EXPORT  RCC_IRQHandler            [WEAK]
                EXPORT  EXTI0_IRQHandler          [WEAK]
                EXPORT  EXTI1_IRQHandler          [WEAK]
                EXPORT  EXTI2_IRQHandler          [WEAK]
                EXPORT  EXTI3_IRQHandler          [WEAK]
                EXPORT  EXTI4_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler    [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler    [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler    [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler    [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler    [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler    [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler    [WEAK]
                EXPORT  ADC1_2_IRQHandler            [WEAK]
                EXPORT  CAN1_TX_IRQHandler  [WEAK]
                EXPORT  CAN1_RX0_IRQHandler [WEAK]
                EXPORT  CAN1_RX1_IRQHandler        [WEAK]
                EXPORT  CAN1_SCE_IRQHandler        [WEAK]
                EXPORT  EXTI9_5_IRQHandler        [WEAK]
                EXPORT  TIM1_BRK_IRQHandler       [WEAK]
                EXPORT  TIM1_UP_IRQHandler        [WEAK]
                EXPORT  TIM1_TRG_COM_IRQHandler   [WEAK]
                EXPORT  TIM1_CC_IRQHandler        [WEAK]
                EXPORT  TIM2_IRQHandler           [WEAK]
                EXPORT  TIM3_IRQHandler           [WEAK]
                EXPORT  TIM4_IRQHandler           [WEAK]
                EXPORT  I2C1_EV_IRQHandler        [WEAK]
                EXPORT  I2C1_ER_IRQHandler        [WEAK]
                EXPORT  I2C2_EV_IRQHandler        [WEAK]
                EXPORT  I2C2_ER_IRQHandler        [WEAK]
                EXPORT  SPI1_IRQHandler           [WEAK]
                EXPORT  SPI2_IRQHandler           [WEAK]
                EXPORT  USART1_IRQHandler         [WEAK]
                EXPORT  USART2_IRQHandler         [WEAK]
                EXPORT  USART3_IRQHandler         [WEAK]
                EXPORT  EXTI15_10_IRQHandler      [WEAK]
                EXPORT  RTCAlarm_IRQHandler       [WEAK]
                EXPORT  OTG_FS_WKUP_IRQHandler    [WEAK]
                EXPORT  TIM8_BRK_IRQHandler    	  [WEAK]
                EXPORT  TIM8_UP_IRQHandler        [WEAK]
                EXPORT  TIM8_TRG_COM_IRQHandler   [WEAK]
                EXPORT  TIM8_CC_IRQHandler     	  [WEAK]
                EXPORT  ADC3_IRQHandler        	  [WEAK]
                EXPORT  FSMC_IRQHandler           [WEAK]
                EXPORT  SDIO_IRQHandler        	  [WEAK]

                
                EXPORT  TIM5_IRQHandler						[WEAK]
		  EXPORT  SPI3_IRQHandler						[WEAK]
		  EXPORT  USART4_IRQHandler					[WEAK]
		  EXPORT  USART5_IRQHandler					[WEAK]
		  EXPORT  TIM6_IRQHandler						[WEAK]
		  EXPORT  TIM7_IRQHandler						[WEAK]
		  EXPORT  DMA2_Channel1_IRQHandler    			[WEAK]
                EXPORT  DMA2_Channel2_IRQHandler    			[WEAK]
                EXPORT  DMA2_Channel3_IRQHandler    			[WEAK]
                EXPORT  DMA2_Channel4_IRQHandler    			[WEAK]
                EXPORT  DMA2_Channel5_IRQHandler    			[WEAK]
		  EXPORT  ETH_IRQHandler			    			[WEAK]
		  EXPORT  ETH_WKUP_IRQHandler				[WEAK]
		  EXPORT  CAN2_TX_IRQHandler					[WEAK]
		  EXPORT  CAN2_RX0_IRQHandler				[WEAK]
		  EXPORT  CAN2_RX1_IRQHandler				[WEAK]
		  EXPORT  CAN2_CSE_IRQHandler				[WEAK]
		  EXPORT  OTG_FS_IRQHandler					[WEAK]

WWDG_IRQHandler
PVD_IRQHandler
TAMPER_IRQHandler
RTC_IRQHandler
FLASH_IRQHandler
RCC_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
DMA1_Channel5_IRQHandler
DMA1_Channel6_IRQHandler
DMA1_Channel7_IRQHandler
ADC1_2_IRQHandler
CAN1_TX_IRQHandler
CAN1_RX0_IRQHandler
CAN1_RX1_IRQHandler
CAN1_SCE_IRQHandler
EXTI9_5_IRQHandler
TIM1_BRK_IRQHandler
TIM1_UP_IRQHandler
TIM1_TRG_COM_IRQHandler
TIM1_CC_IRQHandler
TIM2_IRQHandler
TIM3_IRQHandler
TIM4_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
I2C2_EV_IRQHandler
I2C2_ER_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_IRQHandler
EXTI15_10_IRQHandler
RTCAlarm_IRQHandler
OTG_FS_WKUP_IRQHandler
TIM8_BRK_IRQHandler    
TIM8_UP_IRQHandler     
TIM8_TRG_COM_IRQHandler
TIM8_CC_IRQHandler    
ADC3_IRQHandler        
FSMC_IRQHandler        
SDIO_IRQHandler        
TIM5_IRQHandler					
SPI3_IRQHandler						
USART4_IRQHandler					
USART5_IRQHandler					
TIM6_IRQHandler						
TIM7_IRQHandler						
DMA2_Channel1_IRQHandler    			
DMA2_Channel2_IRQHandler    			
DMA2_Channel3_IRQHandler    		
DMA2_Channel4_IRQHandler    			
DMA2_Channel5_IRQHandler    			
ETH_IRQHandler			    			
ETH_WKUP_IRQHandler				
CAN2_TX_IRQHandler					
CAN2_RX0_IRQHandler				
CAN2_RX1_IRQHandler				
CAN2_CSE_IRQHandler				
OTG_FS_IRQHandler				
                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
