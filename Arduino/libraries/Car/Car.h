/*
    Car.h - Library for internal use.
    Created by Mohammed Khalid, October 2, 2023.
    Released into private domain.
*/
#ifndef Car_h
#define Car_h
#include "Arduino.h"
#include <Motor.h>
#include <Ultrasonic.h>
#include <Bluetooth.h>

class Car
{
    private:
    enum Directions {first, forward, backward, left, right, stop, last}directions;

    Motor left_tyres, right_tyres;
    Ultrasonic front_sensor, back_sensor;
    Bluetooth controller;
    int direction, speed;

    void check_sorroundings(void);
    void move(void);

    public:
    int turn_delay = 2000;

    Car(void);
    Car(Motor left_tyres, Motor right_tyres, Ultrasonic front_sensor, Ultrasonic back_sensor, Bluetooth controller);
    void begin(int baud_rate = 9600);
    int distance_to_speed(double distance);
    void operate(void);  // #original.
    // void operate(int operation = -1);
};

#endif
