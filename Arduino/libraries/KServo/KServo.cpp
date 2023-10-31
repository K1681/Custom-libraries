/*
    KServo.h - Improved library for servo.
    Created by Mohammed Khalid, October 31, 2023.
    Released into private domain.
*/
#include "Arduino.h"
#include "KServo.h"

KServo::KServo(void)
{
    servo_pin = NULL;
    min_angle = 0;
    max_angle = 180;
    min_pwm = abs_min_pwm;
    max_pwm = abs_max_pwm;
    angle = 0;
    servo_attached = 0;
}

void KServo::attach(uint8_t servo_pin, double min_angle = -1, double max_angle = -1, int min_pwm = -1, int max_pwm = -1)
{
    this->servo_pin = servo_pin;
    if(min_angle != -1)
    {
        this->min_angle = min_angle;
    }
    if(max_angle != -1)
    {
        this->max_angle = max_angle;
    }
    if(min_pwm != -1)
    {
        if(min_pwm < abs_min_pwm)
        {
            min_pwm = abs_min_pwm;
        }
        else if(min_pwm > abs_max_pwm)
        {
            min_pwm = abs_max_pwm;
        }
        this->min_pwm = min_pwm;
    }
    if(max_pwm != -1)
    {
        if(max_pwm < abs_min_pwm)
        {
            max_pwm = abs_min_pwm;
        }
        else if(min_pwm > abs_max_pwm)
        {
            max_pwm = abs_max_pwm;
        }
        this->max_pwm = max_pwm;
    }
    angle = this->min_angle;
    pinMode(servo_pin, OUTPUT);
    write(angle);
    servo_attached = 1;
}

void KServo::detach(void)
{
    servo_attached = 0;
}

int KServo::attached(void)
{
    return servo_attached;
}

void KServo::write(double angle)
{
    if(servo_attached = 0)
    {
        return;
    }
    analogWrite(servo_pin, min_pwm + (int)(((angle - min_angle)*((double)(max_pwm - min_pwm)))/(max_angle - min_angle)));
    this->angle = angle;
}

void KServo::write_pwm(int pwm)
{
    if(servo_attached = 0)
    {
        return;
    }
    analogWrite(servo_pin, pwm);
    angle = min_angle + (((double)(pwm - min_pwm))*(max_angle - min_angle))/((double)(max_pwm - min_pwm));
}

double KServo::read(void)
{
    return angle;
}
