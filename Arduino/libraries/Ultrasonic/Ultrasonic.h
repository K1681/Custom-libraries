/*
    Ultrasonic.h - Library for easy use of the  HCSR04 module.
    Created by Mohammed Khalid, October 2, 2023.
    Released into private domain.
*/
#ifndef Ultrasonic_h
#define Ultrasonic_h
#include "Arduino.h"

class Ultrasonic
{
    private:
    static const double default_peed_of_sound = 3.42e-4;
    double speed_of_sound;
    uint8_t trigger, echo;
    double distance(void);

    public:
    Ultrasonic(void);
    Ultrasonic(uint8_t trigger, uint8_t echo);
    void begin(void);
    double get_distance(int number_of_readings = 1);
    void set_speed_of_sound(double speed_of_sound);
    double get_speed_of_sound(void);
    void reset_speed_of_sound(void);

};

#endif
