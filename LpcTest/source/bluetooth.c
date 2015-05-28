#include "../include/bluetooth.h"
#include "../include/uart.h"

// Send a data through bluetooth
void BluetoothSend(int data)
{
    //Send Start Sequence to identify the frame
    UART3_PrintString("Start");
    
    // Send data 
    UART3_PrintNumber(data);
    
    //Send End Sequence to identify the frame
    UART3_PrintString("End");   
}

// Receive data from bluetooth
char* BluetoothRead(int numberOfCar)
{
    char * pt;
    
   UART3_Getstring(pt,numberOfCar);
}

void BluetoothInit()
{
    UART3_Init(115200); //UART to Bluetooth
}
