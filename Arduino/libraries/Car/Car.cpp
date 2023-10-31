/*
    Car.h - Library for internal use.
    Created by Mohammed Khalid, October 2, 2023.
    Released into private domain.
*/
#include "Arduino.h"
#include "Car.h"
#include <Motor.h>
#include <Ultrasonic.h>
#include <Bluetooth.h>
#include <string.h>

Car::Car(void)
{
    direction = stop;
    speed = 0;
}

Car::Car(Motor left_tyres, Motor right_tyres, Ultrasonic front_sensor, Ultrasonic back_sensor, Bluetooth controller)
{
    this->left_tyres = left_tyres;
    this->right_tyres = right_tyres;
    this->front_sensor = front_sensor;
    this->back_sensor = back_sensor;
    this->controller = controller;
    direction = stop;
    speed = 0;
}

void Car::begin(int baud_rate = 9600)
{
    left_tyres.begin();
    right_tyres.begin();
    front_sensor.begin();
    back_sensor.begin();
    controller.begin(baud_rate);
    controller.send_data("Input messages are:-\n1. 'f'\n2. b\n3. l\n4. r\n5. s\n6. e");
}

// #original.
void Car::operate(void)
{
    int number_of_input_messages = 6;
    char input_messages[number_of_input_messages][50] = {"f", "b", "l", "r", "s", "e"};
    char* data = controller.get_data();
    if(data == NULL)
    {
        check_sorroundings();
        move();
    }
    else
    {
        for(int i = 0; i < number_of_input_messages; i++)
        {
            if(strcmp(data, input_messages[i]) == 0)
            {
                switch(i)
                {
                    case 0:
                        direction = forward;
                        break;
                    case 1:
                        direction = backward;
                        break;
                    case 2:
                        direction = left;
                        break;
                    case 3:
                        direction = right;
                        break;
                    case 4:
                        direction = stop;
                        break;
                };
                speed = 255;
            }
        }
        check_sorroundings();
        move();
    }
}

void Car::check_sorroundings(void)
{
    switch(direction)
    {
        case forward:
            speed = distance_to_speed(front_sensor.get_distance());
            break;
        case backward:
            speed = distance_to_speed(back_sensor.get_distance());
            break;
    };
}

void Car::move(void)
{
    switch(direction)
    {
        case forward:
            left_tyres.set_speed(speed);
            right_tyres.set_speed(speed);
            break;
        case backward:
            left_tyres.set_speed(-speed);
            right_tyres.set_speed(-speed);
            break;
        case left:
            left_tyres.set_speed(-255);
            right_tyres.set_speed(255);
            delay(turn_delay);
            left_tyres.set_speed(0);
            right_tyres.set_speed(0);

            direction = stop;
            speed = 0;
            break;
        case right:
            left_tyres.set_speed(255);
            right_tyres.set_speed(-255);
            delay(turn_delay);
            left_tyres.set_speed(0);
            right_tyres.set_speed(0);

            direction = stop;
            speed = 0;
            break;
        case stop:
            left_tyres.set_speed(0);
            right_tyres.set_speed(0);
            speed = 0;
            break;
    }
}
