#include "sensor.h"
#include "safe_memory.h"

#include <stdlib.h>
#include <pthread.h>

#define DEACTIVATED -1

struct _sensor
{
    Bool state;
    pthread_t thread;
    struct _sensor *nextSensor;
};

Sensor NewSensor()
{
    Sensor sensor = NULL;
    Safe_mem_err err = safe_malloc((void **)&sensor, sizeof(struct _sensor));

    if (err == _err_no_error)
    {
        sensor->state = _deactivated;
        sensor->thread = DEACTIVATED;
    }

    return sensor;
}

void ActivateSensor(Sensor sensor)
{
    if (sensor != NULL)
    {
        sensor->state = _activated;
    }
}

void DeactivateSensor(Sensor sensor)
{
    if (sensor != NULL)
    {
        sensor->state = _deactivated;
    }
}

void SensorDetect(Sensor sensor, StageTrigger trigger)
{
    Trigger(trigger, sensor);
}

void _sensor_trigger(DetachedParams *params)
{
    if (params != NULL)
    {
        Trigger(params->trigger, params->sensor);
    }
}

Bool SensorDetachedDetection(Sensor sensor, DetachedParams *params)
{
    if (params != NULL && sensor != NULL && params->sensor == sensor)
    {
        pthread_t multiple_detect_thread;
        pthread_create(&multiple_detect_thread, NULL, (void *(*)(void *))_sensor_trigger, params);
        pthread_detach(multiple_detect_thread);

        sensor->thread = multiple_detect_thread;
        return _true;
    }

    return _false;
}

Sensor StackSensor(Sensor stripeTail)
{
    Sensor newSensor = NewSensor();

    stripeTail->nextSensor = newSensor;

    return newSensor;
}

Bool DestroySensor(Sensor stripeHead)
{
    if (stripeHead != NULL && stripeHead->nextSensor != NULL)
    {
        return _false;
    }

    while (stripeHead != NULL)
    {
        Sensor nextSensor = stripeHead->nextSensor;

        if (stripeHead->thread != DEACTIVATED)
        {
            pthread_cancel(stripeHead->thread);
        }

        safe_free_alloc((void **)stripeHead, sizeof(struct _sensor));
        stripeHead = nextSensor;
    }

    return _true;
}

State GetSensorState(Sensor sensor)
{
    if (sensor != NULL)
    {
        return sensor->state;
    }

    return _deactivated;
}

int GetActiveSensors(Sensor stripeHead)
{
    if (stripeHead != NULL)
    {
        if (stripeHead->state == _activated)
        {
            return 1 + GetActiveSensors(stripeHead->nextSensor);
        }
        else if (stripeHead->state == _deactivated)
        {
            return 0 + GetActiveSensors(stripeHead->nextSensor);
        }
    }

    return 0;
}
