#include "../include/LPC17xx.h"
#include <stdlib.h>
#include <stdio.h>

// PCUART0
#define PCUART0_POWERON (1 << 3)
#define PCUART1_POWERON (1 << 4)
#define PCUART2_POWERON (1 << 24)
#define PCUART3_POWERON (1 << 25)

#define PCLK_UART0 6
#define PCLK_UART1 8
#define PCLK_UART2 16
#define PCLK_UART3 18
#define PCLK_UART0_MASK (3 << 6)
#define PCLK_UART1_MASK (3 << 8)
#define PCLK_UART2_MASK (3 << 16)
#define PCLK_UART3_MASK (3 << 18)

#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_RLS		0x04

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80

// ***********************
// Function to set up UART
void UART0_Init(int baudrate)
{
	int pclk;
	unsigned long int Fdiv;

	// PCLK_UART0 is being set to 1/4 of SystemCoreClock
	pclk = SystemCoreClock / 4;	
	
	// Turn on power to UART0
	LPC_SC->PCONP |=  PCUART0_POWERON;
		
	// Turn on UART0 peripheral clock
	LPC_SC->PCLKSEL0 &= ~(PCLK_UART0_MASK);
	LPC_SC->PCLKSEL0 |=  (0 << PCLK_UART0);		// PCLK_periph = CCLK/4
	
	// Set PINSEL0 so that P0.2 = TXD0, P0.3 = RXD0
	LPC_PINCON->PINSEL0 &= ~0xf0;
	LPC_PINCON->PINSEL0 |= ((1 << 4) | (1 << 6));
	
	LPC_UART0->LCR = 0x83;		// 8 bits, no Parity, 1 Stop bit, DLAB=1
    Fdiv = ( pclk / 16 ) / baudrate ;	// Set baud rate
    LPC_UART0->DLM = Fdiv / 256;							
    LPC_UART0->DLL = Fdiv % 256;
    LPC_UART0->LCR = 0x03;		// 8 bits, no Parity, 1 Stop bit DLAB = 0
    LPC_UART0->FCR = 0x07;		// Enable and reset TX and RX FIFO
}

void UART1_Init(int baudrate)
{
	int pclk;
	unsigned long int Fdiv;

	// PCLK_UART0 is being set to 1/4 of SystemCoreClock
	pclk = SystemCoreClock / 4;

	// Turn on power to UART0
	LPC_SC->PCONP |=  PCUART1_POWERON;

	// Turn on UART0 peripheral clock
	LPC_SC->PCLKSEL0 &= ~(PCLK_UART1_MASK);
	LPC_SC->PCLKSEL0 |=  (0 << PCLK_UART1);		// PCLK_periph = CCLK/4

	// Set PINSEL0 so that P0.2 = TXD0, P0.3 = RXD0
	LPC_PINCON->PINSEL0 &= ~0xc0000000;
	LPC_PINCON->PINSEL0 |= (1 << 30);
	LPC_PINCON->PINSEL1 &= ~0xc;
	LPC_PINCON->PINSEL1 |= (1 << 0);

	LPC_UART1->LCR = 0x83;		// 8 bits, no Parity, 1 Stop bit, DLAB=1
    Fdiv = ( pclk / 16 ) / baudrate ;	// Set baud rate
    LPC_UART1->DLM = Fdiv / 256;
    LPC_UART1->DLL = Fdiv % 256;
    LPC_UART1->LCR = 0x03;		// 8 bits, no Parity, 1 Stop bit DLAB = 0
    LPC_UART1->FCR = 0x07;		// Enable and reset TX and RX FIFO
}

void UART2_Init(int baudrate)
{
	int pclk;
	unsigned long int Fdiv;

	// PCLK_UART2 is being set to 1/4 of SystemCoreClock
	pclk = SystemCoreClock / 4;

	// Turn on power to UART2
	LPC_SC->PCONP |=  PCUART2_POWERON;

	// Turn on UART2 peripheral clock
	LPC_SC->PCLKSEL1 &= ~(PCLK_UART2_MASK);
	LPC_SC->PCLKSEL1 |=  (0 << PCLK_UART2);		// PCLK_periph = CCLK/4

	// Set PINSEL0 so that P0.10 = TXD2, P0.11 = RXD2
	LPC_PINCON->PINSEL0 &= ~0xf00000;
	LPC_PINCON->PINSEL0 |= ((1 << 20) | (1 << 22));

	LPC_UART2->LCR = 0x83;		// 8 bits, no Parity, 1 Stop bit, DLAB=1
    Fdiv = ( pclk / 16 ) / baudrate ;	// Set baud rate
    LPC_UART2->DLM = Fdiv / 256;
    LPC_UART2->DLL = Fdiv % 256;
    LPC_UART2->LCR = 0x03;		// 8 bits, no Parity, 1 Stop bit DLAB = 0
    LPC_UART2->FCR = 0x07;		// Enable and reset TX and RX FIFO
}

void UART3_Init(int baudrate)
{
	int pclk;
	unsigned long int Fdiv;

	// PCLK_UART2 is being set to 1/4 of SystemCoreClock
	pclk = SystemCoreClock / 4;

	// Turn on power to UART2
	LPC_SC->PCONP |=  PCUART3_POWERON;

	// Turn on UART2 peripheral clock
	LPC_SC->PCLKSEL1 &= ~(PCLK_UART3_MASK);
	LPC_SC->PCLKSEL1 |=  (0 << PCLK_UART3);		// PCLK_periph = CCLK/4

	// Set PINSEL0 so that P0.0 = TXD3, P0.1 = RXD3
	LPC_PINCON->PINSEL0 &= ~0xf;
	LPC_PINCON->PINSEL0 |= ((1 << 1) | (1 << 3));

	LPC_UART3->LCR = 0x83;		// 8 bits, no Parity, 1 Stop bit, DLAB=1
    Fdiv = ( pclk / 16 ) / baudrate ;	// Set baud rate
    LPC_UART3->DLM = Fdiv / 256;
    LPC_UART3->DLL = Fdiv % 256;
    LPC_UART3->LCR = 0x03;		// 8 bits, no Parity, 1 Stop bit DLAB = 0
    LPC_UART3->FCR = 0x07;		// Enable and reset TX and RX FIFO
}
// ***********************
// Function to send character over UART
void UART0_Sendchar(char c)
{
	while( (LPC_UART0->LSR & LSR_THRE) == 0 );	// Block until tx empty
	
	LPC_UART0->THR = c;
}

void UART1_Sendchar(char c)
{
	while( (LPC_UART1->LSR & LSR_THRE) == 0 );	// Block until tx empty

	LPC_UART1->THR = c;
}

void UART2_Sendchar(char c)
{
	while( (LPC_UART2->LSR & LSR_THRE) == 0 );	// Block until tx empty

	LPC_UART2->THR = c;
}

void UART3_Sendchar(char c)
{
	while( (LPC_UART3->LSR & LSR_THRE) == 0 );	// Block until tx empty

	LPC_UART3->THR = c;
       // LPC_UART3->THR = '\n';
}

// ***********************
// Function to get character from UART
char UART0_Getchar()
{
	char c;
	while( (LPC_UART0->LSR & LSR_RDR) == 0 );  // Nothing received so just block 	
	c = LPC_UART0->RBR; // Read Receiver buffer register
	return c;
}

char UART1_Getchar()
{
	char c;
	while( (LPC_UART1->LSR & LSR_RDR) == 0 );  // Nothing received so just block
	c = LPC_UART1->RBR; // Read Receiver buffer register
	return c;
}

char UART2_Getchar()
{
	char c;
	while( (LPC_UART2->LSR & LSR_RDR) == 0 );  // Nothing received so just block
	c = LPC_UART2->RBR; // Read Receiver buffer register
	return c;
}

char UART3_Getchar()
{
	char c;
	while( (LPC_UART3->LSR & LSR_RDR) == 0 );  // Nothing received so just block
	c = LPC_UART3->RBR; // Read Receiver buffer register
	return c;
}
// ***********************
// Function to get string terminated by '\n' or of the lenght specified from UART
void UART0_Getstring(char* PtString,int lenght)
{
    char c;
    int i = 0;
    
    if(lenght == 0)
    {
        do
        {
            c = UART0_Getchar();
            if(c != '\n')
            {
                PtString[i] = c;
                i++;
            }
        } while(c != '\n');
    }
    else
    {
        do
        {
            c = UART0_Getchar();
            if(c != '\n')
            {
                PtString[i] = c;
                i++;
            }
        } while(c != '\n' && (i < lenght));
        
    }
       
}

void UART1_Getstring(char* PtString,int lenght)
{
    char c;
    int i = 0;
    
    if(lenght == 0)
    {
        do
        {
            c = UART1_Getchar();
            if(c != '\n')
            {
                PtString[i] = c;
                i++;
            }
        } while(c != '\n');
    }
    else
    {
        do
        {
            c = UART1_Getchar();
            if(c != '\n')
            {
                PtString[i] = c;
                i++;
            }
        } while(c != '\n' && (i < lenght));
        
    }
       
}

void UART2_Getstring(char* PtString,int lenght)
{
    char c;
    int i = 0;
    
    if(lenght == 0)
    {
        do
        {
            c = UART2_Getchar();
            if(c != '\n')
            {
                PtString[i] = c;
                i++;
            }
        } while(c != '\n');
    }
    else
    {
        do
        {
            c = UART2_Getchar();
            if(c != '\n')
            {
                PtString[i] = c;
                i++;
            }
        } while(c != '\n' && (i < lenght));
        
    }
}

void UART3_Getstring(char* PtString,int lenght)
{
    char c;
    int i = 0;

    
    
    if(lenght == 0)
    {
        do
        {
            c = UART3_Getchar();
            if(c != '\n')
            {
                PtString[i] = c;
                i++;
            }
        } while(c != '\n');
    }
    else
    {
        do
        {
            c = UART3_Getchar();
            if(c != '\n')
            {
                PtString[i] = c;
                i++;
            }
        } while(c != '\n' && (i < lenght));
        
    }
       
}



// ***********************
// Function to prints the string out over the UART with ln 
// WARNING : UART1 DOES NOT SEND THE CR CARACTER
void UART0_PrintString(char *pcString)
{
	int i = 0;
	// loop through until reach string's zero terminator
	while (pcString[i] != 0)
	{
		UART0_Sendchar(pcString[i]); // print each character
		i++;
	}
        //UART0_Sendchar('\n');
}

void UART1_PrintString(char *pcString)
{
	int i = 0;
	// loop through until reach string's zero terminator
	while (pcString[i] != 0)
	{
		UART1_Sendchar(pcString[i]); // print each character
		i++;
	}
       
}

void UART2_PrintString(char *pcString)
{
	int i = 0;
	// loop through until reach string's zero terminator
	while (pcString[i] != 0)
	{
		UART2_Sendchar(pcString[i]); // print each character
		i++;
	}
        UART2_Sendchar('\n');
}

void UART3_PrintString(char *pcString)
{
	int i = 0;
	// loop through until reach string's zero terminator
	while (pcString[i] != 0)
	{
		UART3_Sendchar(pcString[i]); // print each character
		i++;
	}
        UART3_Sendchar('\n');
}

// ***********************
// Function to prints a number out over the UART

UART0_PrintNumber(int n)
{
    // Variables locales
	char entier[20];
	int signe;
	int i;

	// On récupére le signe du nombre
	if (n < 0) {

		signe = 1;
		n = -n;
	}
	else signe = 0;

	// Remplissage du tableau
	entier[19] = 0;
	i = 18;

	while (n != 0) {

		// On r�cup�re l'unit� de n
		entier[i] = (char) (n%10) + '0';

		// Progression
		n /= 10;
		i--;
	}

	// Si le nombre à afficher est 0
	if (i == 18) {

		entier[i] = '0';
		i--;
	}

	// Ajout du signe
	if (signe) entier[i] = '-';
	else i++;

	// Affichage de l'entier
	UART0_PrintString(&entier[i]);
}

void UART1_PrintNumber(int n)
{
    // Variables locales
	char entier[20];
	int signe;
	int i;

	// On récupére le signe du nombre
	if (n < 0) {

		signe = 1;
		n = -n;
	}
	else signe = 0;

	// Remplissage du tableau
	entier[19] = 0;
	i = 18;

	while (n != 0) {

		// On r�cup�re l'unit� de n
		entier[i] = (char) (n%10) + '0';

		// Progression
		n /= 10;
		i--;
	}

	// Si le nombre à afficher est 0
	if (i == 18) {

		entier[i] = '0';
		i--;
	}

	// Ajout du signe
	if (signe) entier[i] = '-';
	else i++;

	// Affichage de l'entier
	UART1_PrintString(&entier[i]);
}

void UART2_PrintNumber(int n)
{
    // Variables locales
	char entier[20];
	int signe;
	int i;

	// On récupére le signe du nombre
	if (n < 0) {

		signe = 1;
		n = -n;
	}
	else signe = 0;

	// Remplissage du tableau
	entier[19] = 0;
	i = 18;

	while (n != 0) {

		// On r�cup�re l'unit� de n
		entier[i] = (char) (n%10) + '0';

		// Progression
		n /= 10;
		i--;
	}

	// Si le nombre à afficher est 0
	if (i == 18) {

		entier[i] = '0';
		i--;
	}

	// Ajout du signe
	if (signe) entier[i] = '-';
	else i++;

	// Affichage de l'entier
	UART2_PrintString(&entier[i]);
}

void UART3_PrintNumber(int n)
{
    // Variables locales
	char entier[20];
	int signe;
	int i;

	// On récupére le signe du nombre
	if (n < 0) {

		signe = 1;
		n = -n;
	}
	else signe = 0;

	// Remplissage du tableau
	entier[19] = 0;
	i = 18;

	while (n != 0) {

		// On r�cup�re l'unit� de n
		entier[i] = (char) (n%10) + '0';

		// Progression
		n /= 10;
		i--;
	}

	// Si le nombre à afficher est 0
	if (i == 18) {

		entier[i] = '0';
		i--;
	}

	// Ajout du signe
	if (signe) entier[i] = '-';
	else i++;

	// Affichage de l'entier
	UART3_PrintString(&entier[i]);
}