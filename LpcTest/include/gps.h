/* 
 * File:   gps.h
 * Author: Yannick
 *
 * Created on 4 juin 2014, 20:33
 */

#ifndef GPS_H
#define	GPS_H



// Gps structure to store different gps values
typedef struct
{
    char NMEA_header[5];        // GPRMC
    int longitude[3];           // Longitude =>  0 : degree , 1 : minutes, 2 :  secondes
    int latitude[3];            // Latitude => 0 : degree , 1 : minutes, 2 :  secondes
    int speed;                  // Speed Value
    int altitude;               // Altitude Value 
    int hours;                  // Hours Value
    int minutes;                // Minutes Value
    char status;
    
}GPS;

GPS DecodeGps();

void GpsInit();


#endif	/* GPS_H */

