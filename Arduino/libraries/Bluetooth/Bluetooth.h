/*
    Bluetooth.h - Library for easy use of the HC05 bluetooth module.
    Created by Mohammed Khalid, October 1, 2023.
    Released into private domain.
*/
#ifndef Bluetooth_h
#define Bluetooth_h
#include "Arduino.h"
#include <SoftwareSerial.h>

class Bluetooth
{
    private:
    static const int buffer_len = 50;
    uint8_t rx, tx;
    SoftwareSerial* device;
    void flush(SoftwareSerial* port);

    public:
    char data[buffer_len];
    Bluetooth(void);
    Bluetooth(uint8_t rx, uint8_t tx);
    void begin(int baud_rate);
    char* get_data(int wait = 0);
    void send_data(char* data);
};

#endif
