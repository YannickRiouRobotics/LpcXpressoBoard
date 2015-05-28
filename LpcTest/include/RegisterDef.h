/* 
 * File:   RegisterDef.h
 * Author: Yannick
 *
 * Created on 2 décembre 2012, 13:50
 */

#ifndef REGISTERDEF_H
#define	REGISTERDEF_H

// Redefine integer 
#define int32 uint32_t
#define int16 uint16_t
       
//Define of register to power peripherals
#define TIMER0_PWR (1 << 1)
#define TIMER1_PWR (1 << 2)
#define TIMER2_PWR (1 << 22)
#define TIMER3_PWR (1 << 23)
#define UART0_PWR (1 << 3)
#define UART1_PWR (1 << 4)
#define UART2_PWR (1 << 24)
#define UART3_PWR (1 << 25)
#define PWM1_PWR (1 << 6)
#define GPIO_PWR (1 << 15)

// Register to read timers value    
#define T0_Time LPC_TIM0->TC
#define T1_Time LPC_TIM1->TC
#define T2_Time LPC_TIM2->TC
#define T3_Time LPC_TIM3->TC





    
    
//Functions prototypes
void CPUInit();
void TIMER0_IRQHandler();
void waitMs(uint16_t MsTime);
void PWMInit(uint8_t PWM_Number, uint16_t Period);
void Blink();
void LedOn();
void LedOff();


#endif	/* REGISTERDEF_H */

