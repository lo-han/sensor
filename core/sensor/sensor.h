#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "trigger.h"

typedef struct _sensor *Sensor;

typedef struct _detach_detection_params
{
    Sensor sensor;
    StageTrigger trigger;
} DetachedParams;

Sensor NewSensor();
Sensor StackSensor(Sensor stripeTail);
void DestroySensor(Sensor stripeHead);

void ActivateSensor(Sensor sensor);
void DeactivateSensor(Sensor sensor);

void SensorDetect(Sensor sensor, StageTrigger trigger);
Bool SensorDetachedDetection(Sensor stripeSensor, DetachedParams *params);

int GetTriggeredSensors(Sensor stripeHead);

#endif