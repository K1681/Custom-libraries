/*
    Ultrasonic.h - Library for easy use of the  HCSR04 module.
    Created by Mohammed Khalid, October 2, 2023.
    Released into private domain.
*/
#include "Arduino.h"
#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(void)
{
    trigger = NULL;
    echo  = NULL;
    speed_of_sound = default_peed_of_sound;
}

Ultrasonic::Ultrasonic(uint8_t trigger, uint8_t echo)
{
    this->trigger = trigger;
    this->echo = echo;
    speed_of_sound = default_peed_of_sound;
}

void Ultrasonic::begin(void)
{
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    digitalWrite(trigger, LOW);
}

double Ultrasonic::distance(void)
{
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);

    return (double)(((double)pulseIn(echo, HIGH) * speed_of_sound) / (double)2);
}

double Ultrasonic::get_distance(int number_of_readings = 1)
{
    if(number_of_readings == 0)
    {
        return 0;
    }
    double average_distance = 0;
    for(int i = 0; i < number_of_readings; i++)
    {
        average_distance += distance();
    }
    return (double)(average_distance/(double)number_of_readings);
}

void Ultrasonic::set_speed_of_sound(double speed_of_sound)
{
    this->speed_of_sound = speed_of_sound;
}

double Ultrasonic::get_speed_of_sound(void)
{
    return speed_of_sound;
}

void Ultrasonic::reset_speed_of_sound(void)
{
    speed_of_sound = default_peed_of_sound;
}
