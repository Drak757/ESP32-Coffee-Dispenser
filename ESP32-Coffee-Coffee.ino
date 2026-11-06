#include <ESP32Servo.h>

Servo coffeeServo;

const int servoPin = 18;

const int lightButton = 19;
const int mediumButton = 21;
const int strongButton = 22;

unsigned long dispenseStartTime = 0;
unsigned long dispenseDuration = 0;

int dispenserState = 0;

void setup()
{
    pinMode(lightButton, INPUT_PULLUP);
    pinMode(mediumButton, INPUT_PULLUP);
    pinMode(strongButton, INPUT_PULLUP);

    coffeeServo.attach(servoPin);
    coffeeServo.write(0);
}

void loop()
{
    unsigned long currentTime = millis();

    // STATE 0 = IDLE
    if (dispenserState == 0)
    {
        if (digitalRead(lightButton) == LOW)
        {
            coffeeServo.write(90);

            dispenseStartTime = currentTime;
            dispenseDuration = 125;

            dispenserState = 1;
        }

        else if (digitalRead(mediumButton) == LOW)
        {
            coffeeServo.write(90);

            dispenseStartTime = currentTime;
            dispenseDuration = 175;

            dispenserState = 1;
        }

        else if (digitalRead(strongButton) == LOW)
        {
            coffeeServo.write(90);

            dispenseStartTime = currentTime;
            dispenseDuration = 225;

            dispenserState = 1;
        }
    }

    // STATE 1 = DISPENSING
    else if (dispenserState == 1)
    {
        if (currentTime - dispenseStartTime >= dispenseDuration)
        {
            coffeeServo.write(0);

            dispenserState = 0;
        }
    }
}