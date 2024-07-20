#include "sensor.h"

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int main()
{
    Sensor stripeHead = NewSensor();
    Sensor stripeTail = StackSensor(stripeHead);

    for (int i = 0; i < 10; i++)
    {
        stripeTail = StackSensor(stripeTail);
    }

    DestroySensor(&stripeHead);
    stripeTail = NULL;
}
