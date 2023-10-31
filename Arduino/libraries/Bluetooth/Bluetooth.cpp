/*
    Bluetooth.h - Library for easy use of the HC05 bluetooth module.
    Created by Mohammed Khalid, October 1, 2023.
    Released into private domain.
*/
#include "Arduino.h"
#include "Bluetooth.h"
#include <SoftwareSerial.h>

Bluetooth::Bluetooth(void)
{
    rx = NULL;
    tx = NULL;
    for(int i = 0; i < buffer_len; i++)
    {
        data[i] = '\0';
    }
}

Bluetooth::Bluetooth(uint8_t rx, uint8_t tx)
{
    this->rx = rx;
    this->tx = tx;
    for(int i = 0; i < buffer_len; i++)
    {
        data[i] = '\0';
    }
}

void Bluetooth::begin(int baud_rate)
{
    device = new SoftwareSerial(rx, tx);
    device->begin(baud_rate);
}

char* Bluetooth::get_data(int wait = 0)
{
    for(int i = 0; i < buffer_len; i++)
    {
        data[i] = '\0';
    }
    if(wait)
    {
        while(!device->available()){}
    }
    int counter = 0, ip_present = 0;
    char temp;
    while(device->available() && (counter < buffer_len))
    {
        temp = device->read();
        if((temp == 10) || (temp == 13))
        {
            device->read();
            break;
        }
        data[counter] = temp;
        ip_present = 1;
        counter++;
        delay(1);  // #slowdown
    }
    if(counter < buffer_len)
    {
        data[counter] = '\0';
    }
    data[buffer_len - 1] = '\0';
    if(ip_present)
    {
        return data;
    }
    else
    {
        return NULL;
    }
    flush(device);
}

void Bluetooth::send_data(char* data)
{
    device->println(data);
    flush(device);
}

void Bluetooth::flush(SoftwareSerial* port)
{
    while(port->available())
    {
        port->read();
        delay(1);  // #slowdown
    }
}
