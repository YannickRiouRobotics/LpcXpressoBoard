#include "../include/gps.h"
#include "../include/uart.h"

GPS DecodeGps()
{
    int buffcar;
    
    int i =0;
 
    char NMEAString[83];
    GPS myGps;
   
    
    for(i=0;i<83;i++)
    {
        NMEAString[i] = ' ';
    }
    
    buffcar = UART1_Getchar();
    if(buffcar == '$')
    {
        UART1_Getstring(NMEAString,0);
        UART0_PrintString(NMEAString); // FOR DEBUG ONLY
    }
    for(i=0;i<5;i++)
    {
        myGps.NMEA_header[i] = NMEAString[i];
    }
    
    myGps.hours = ((NMEAString[6]-48) *10) + (NMEAString[7]-48);
   
    myGps.minutes = ((NMEAString[8]-48) *10) + (NMEAString[9]-48);
    
    
    myGps.status = NMEAString[17];
    
    myGps.latitude[0] = (((NMEAString[19] -48)*10) + (NMEAString[20]-48));
    myGps.latitude[1] = (((NMEAString[21] -48)*10) + (NMEAString[22]-48));
    
                
    return myGps;
    
}


void GpsInit()
{
    UART1_Init(115200); //UART to GPS
    
    // Init GPS to choose update rate
    UART1_PrintString("$PMTK220,1000*1F\r\n");
    waitMs(500);
    UART1_PrintString("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
    waitMs(500);
    UART1_PrintString("$PMTK300,1000,0,0,0,0*1C\r\n");
    waitMs(500);
    UART0_PrintString("GPS Init OK\n");
}