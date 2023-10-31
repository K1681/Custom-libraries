/*
    Motor.h - Library for easy use of the L239 ic.
    Created by Mohammed Khalid, October 1, 2023.
    Released into private domain.
*/
#ifndef Motor_h
#define Motor_h
#include "Arduino.h"

class Motor
{
    private:
    uint8_t enable, p1, p2;
    int speed;

    public:
    Motor(void);
    Motor(uint8_t enable, uint8_t p1, uint8_t p2);
    void begin(void);
    void set_speed(int speed);
    int get_speed(void);
};

#endif
