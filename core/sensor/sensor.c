#include "sensor.h"
#include "safe_memory.h"

#include <stdlib.h>
#include <pthread.h>

#define DEACTIVATED -1

struct _sensor
{
    Bool active;
    pthread_t thread;
    struct _sensor *nextSensor;
};

Sensor NewSensor()
{
    Sensor sensor = NULL;
    Safe_mem_err err = safe_malloc((void **)&sensor, sizeof(struct _sensor));

    if (err == _err_no_error)
    {
        sensor->active = _false;
        sensor->thread = DEACTIVATED;
    }

    return sensor;
}

void ActivateSensor(Sensor sensor)
{
    if (sensor != NULL)
    {
        sensor->active = _true;
    }
}

void DeactivateSensor(Sensor sensor)
{
    if (sensor != NULL)
    {
        sensor->active = _false;
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

void DestroySensor(Sensor stripeHead)
{
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
}

int GetTriggeredSensors(Sensor stripeHead)
{
    if (stripeHead != NULL)
    {
        if (stripeHead->active == _true)
        {
            return 1 + GetTriggeredSensors(stripeHead->nextSensor);
        }
        else if (stripeHead->active == _false)
        {
            return 0 + GetTriggeredSensors(stripeHead->nextSensor);
        }
    }

    return 0;
}
