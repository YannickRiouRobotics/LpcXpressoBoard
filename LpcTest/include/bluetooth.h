#ifndef BLUETOOTH_H
#define	BLUETOOTH_H

// Change the UART Number if bluetooth isn't on UART3

// Send a data through bluetooth
void BluetoothSend(int data);

// Receive data from bluetooth
char* BluetoothRead(int numberOfCar);

// Initialize Serial for bluetooth
void BluetoothInit();

#endif	/* BLUETOOTH_H */

