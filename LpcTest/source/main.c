#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/LPC17xx.h"
#include "../include/uart.h"
#include "../include/RegisterDef.h"
#include "../include/gps.h"




// /!\ Don't forget to shift value when reading GPIO /!\ //


// CPUCLK = 104,57 Mhz
// PLL0_Output = 104,57 *3  


//-------------HELP------------------//

//LPC_GPIOx->FIOPIN |= (1 << y)
// x is for port , ex : P[0]22 x = 0
// y is for pin number, see p128 table 110

/*
 uint16_t cpt = 0;
//Timer 0 interrupt for delay
void TIMER0_IRQHandler()
{
   
    if((LPC_TIM0->IR & 0x01) == 0x01) // if MR0 interrupt
    {
        if(cpt < 1000)
        {
        cpt++;
        }
        else
        {
            cpt = 0;
        }
        LPC_TIM0->IR |= 1 << 0; // Clear MR0 interrupt flag
    }
  
}
*/

void CPUInit()
{
    
    //-----Clock Config--------//
    LPC_SC->CLKSRCSEL |= (1 << 0); // Main Oscillator (12 Mhz) as PLL0 source
    
    //LPC_SC->CLKOUTCFG |= (0 << 0) | (1 << 8) | (0x0F << 4) ; // CPU Clock on CLKOUT P1.27 and CLKOUT enable
                                             // Divide by 16
    
    // M= 5 n=1  
    //Disable and disconnect PLL0
    LPC_SC->PLL0CON |= (0 << 0); //PLLE0
    LPC_SC->PLL0FEED = 0xAA;
    LPC_SC->PLL0FEED = 0x55;
    LPC_SC->PLL0CON |= (0 << 1); //PLLC0
    LPC_SC->PLL0FEED = 0xAA;
    LPC_SC->PLL0FEED = 0x55;
    
    //Config PLL0
    LPC_SC->PLL0CFG |= 0x04; // 4 -> 100 Mhz CPU Clk
    LPC_SC->PLL0FEED = 0xAA;
    LPC_SC->PLL0FEED = 0x55;
    
    //Enable PLL0 
    LPC_SC->PLL0CON |= (1 << 0); //PLLE0
    LPC_SC->PLL0FEED = 0xAA;
    LPC_SC->PLL0FEED = 0x55;
    
    //Clock divider config
    LPC_SC->CCLKCFG |= (2 << 0);
    // CLK = PLL0 /3
    
    //Wait for PLL0 to lock
    while ((LPC_SC->PLL0STAT & 0x4000000) == 0);
    
    //Enable PLL0 
    LPC_SC->PLL0CON |= (1 << 1); //PLLC0
    LPC_SC->PLL0FEED = 0xAA;
    LPC_SC->PLL0FEED = 0x55;
    //-------------------------//
     
    
    //Update the core clock to the one we set up
    SystemCoreClockUpdate();
    
    
    
    NVIC->ICER[0] = 0xFFFFFFFF; // Disable all interrupt
  
    
    //-----TIMER Config--------//
    LPC_SC->PCONP |= TIMER0_PWR;
    LPC_SC->PCONP |= TIMER1_PWR;
    
    LPC_SC->PCLKSEL0 |= (1 << 2) | (1 << 4); // CPU (100 Mhz) clk on Timer0 et Timer1
     
    LPC_TIM0->MCR |= (1 << 0); // Interrupt on match0
    LPC_TIM0->MR0 |= 104058; // interrupt each s
    
    LPC_TIM0->TCR |= (1 << 1); // reset timer 0
    
    
    NVIC->ISER[0] |= (1 << 1); // enable timer0 interrupt
    
    //Launch Timers
    LPC_TIM0->TCR |= (1 << 0);
    LPC_TIM1->TCR |= (1 << 0);
    //------------------------//
     
    
    
    //-----GPIO Config--------//
    LPC_SC->PCONP |= GPIO_PWR;
    
    LPC_GPIO0->FIODIR |= 1 << 22; // puts P0.22 into output mode.
    LPC_PINCON->PINSEL1 |= (0x00 << 12); // P0.22 is GPIO 
  
    //LPC_PINCON->PINSEL4 |= (1 << 0) | (1 << 2) | (1 << 4); // P2.0 & P2.1 & P2.2 in PWM Mode
    //LPC_PINCON->PINMODE1 |= (3 << 0) | (3 << 2) | (3 << 4); // Pulldown on PWM pin
    
    
    // Uart GPIO Configuration
    LPC_PINCON->PINSEL0 |= (1 << 4) | (1 << 6) | (1 << 30) | (1 << 1) | (1 << 3); // TXD1,TXD0, RXD0, TXD3, RXD3
    LPC_PINCON->PINSEL1 |= (1 << 0); // RXD1
    
    LPC_PINCON->PINMODE0 |= (1 << 3)| (1 << 7); // No pull-up or pull-down on RX pins
    LPC_PINCON->PINMODE1 |= (1 << 1);
    
    //------------------------//
    
   
    
    /*
    //-----PWM Config--------//
    LPC_SC->PCONP |= PWM1_PWR;
    LPC_SC->PCLKSEL0 |= 1 << 12; // PWM Clock = SysClock
    
    LPC_PWM1->MR0 = 1040000; // PWM Freq = SysClk / 1040000 -> 10khz 
  
    LPC_PWM1->MCR |= (1 << 1);
    LPC_PWM1->MR2 = 520000; // duty = 1/8
    LPC_PWM1->MR3 = 0; // duty = 0 OFF
    
    LPC_PWM1->TCR |= (1 << 0); // Counter enable
    LPC_PWM1->TCR |= (1 << 3); // PWM enable
    
    LPC_PWM1->PCR |= (0 << 2) | (0 << 3); // Channel 2 & 3 in single edge 
    LPC_PWM1->PCR |= (1 << 10);// enable channel 2 
    LPC_PWM1->PCR |= (1 << 11);// enable channel 3
    */    
    //------------------------//
    
}


void waitMs(uint16_t MsTime)
{
    uint32_t i = 0;

    i= T1_Time + (MsTime*104058);
    
    while(T1_Time < i);
}

void LedOn()
{
    LPC_GPIO0->FIOPIN |= 1 << 22; //P0.22
}

void LedOff()
{
    LPC_GPIO0->FIOPIN &= 0 << 22; //P0.22
}

void Blink()
{
   
    LedOn();
    waitMs(500);
    LedOff();
    waitMs(500);
    
}









char c;
GPS monGps;
char chaine[12];
char textbuff[5];
  
int main (void) 
{
        int i =0,j=0;
        CPUInit();
        
        LedOn();
        
        for(i=0;i<5;i++)
        {
        monGps.NMEA_header[i] =' ';
        }
        
        UART0_Init(115200); //UART to PC
        UART0_PrintString("Cpu Init OK\n");
        UART0_PrintString("Uart Init OK\n");
        GpsInit();
        UART0_PrintString("Gps Init OK\n");
        BluetoothInit();
        UART0_PrintString("Bluetooth Init OK\n");
       
                                                         
        
    
        
	while(1)
        {  
            
            //Blink();
            
            
            
            monGps = DecodeGps();
            UART3_Sendchar(monGps.status);
            waitMs(500);
            
           

            
      
  

            
            
         
        }
	return 0;
  
}
