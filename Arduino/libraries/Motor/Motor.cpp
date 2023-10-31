/*
    Motor.h - Library for easy use of the L239 ic.
    Created by Mohammed Khalid, October 1, 2023.
    Released into private domain.
*/
#include "Arduino.h"
#include "Motor.h"

Motor::Motor(void)
{
    enable = NULL;
    p1 = NULL;
    p2 = NULL;
    speed = 0;
}

Motor::Motor(uint8_t enable, uint8_t p1, uint8_t p2)
{
    this->enable = enable;
    this->p1 = p1;
    this->p2 = p2;
    speed = 0;
}

void Motor::begin(void)
{
    pinMode(enable, OUTPUT);
    pinMode(p1, OUTPUT);
    pinMode(p2, OUTPUT);
    digitalWrite(enable, LOW);
    digitalWrite(p1, LOW);
    digitalWrite(p2, LOW);
}

void Motor::set_speed(int speed)
{
    if(speed > 0)
    {
        if(speed > 255)
        {
            speed = 255;
        }
        digitalWrite(p1, HIGH);
        digitalWrite(p2, LOW);
        analogWrite(enable, speed);
        this->speed = speed;
    }
    else if(speed == 0)
    {
        digitalWrite(p1, LOW);
        digitalWrite(p2, LOW);
        analogWrite(enable, speed);
        this->speed = speed;
    }
    else
    {
        if(speed < -255)
        {
            speed = -255;
        }
        digitalWrite(p1, LOW);
        digitalWrite(p2, HIGH);
        analogWrite(enable, -speed);
        this->speed = speed;
    }
}

int Motor::get_speed(void)
{
    return speed;
}
