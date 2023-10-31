/*
    KServo.h - Improved library for servo.
    Created by Mohammed Khalid, October 31, 2023.
    Released into private domain.
*/
#ifndef KServo_h
#define KServo_h
#include "Arduino.h"

class KServo
{
    private:
    static const int abs_min_pwm = 0, abs_max_pwm = 255;

    public:
    uint8_t servo_pin;
    double min_angle, max_angle, angle;
    int min_pwm, max_pwm, servo_attached;

    KServo(void);
    void attach(uint8_t servo_pin, double min_angle = -1, double max_angle = -1, int min_pwm = -1, int max_pwm = -1);
    void detach(void);
    int attached(void);
    void write(double angle);
    void write_pwm(int pwm);
    double read(void);
};

#endif
