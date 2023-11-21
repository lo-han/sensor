#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "trigger.h"

/********************************************************************
 * Sensor type
 ********************************************************************/
typedef struct _sensor *Sensor;

/********************************************************************
 * State type
 ********************************************************************/
typedef enum _s
{
    state_deactivated = 0,
    state_activated
} State;

/********************************************************************
 * DetachedParams transfer object
 ********************************************************************/
typedef struct _detach_detection_params
{
    Sensor sensor;
    StageTrigger trigger;
} DetachedParams;

/********************************************************************
 * Function to construct a new Sensor.
 *
 * Output:
 *  - Sensor object. It's recommended, if there is the intention to stack
 * Sensors, to keep the first one instantiated, refered as 'stripeHead',
 * in order to prevent memory leaks.
 ********************************************************************/
Sensor NewSensor();

/********************************************************************
 * Function to stack a Sensor to a list of sensors. Externally this
 * method works as a Linked List Stack.
 *
 * Inputs:
 *  - Last allocated sensor of the Stack ('stripeTail'). If there haven't
 * been any call to this function yet, the 'stripeTail' will be the 'stripeHead'.
 * It's also recommended to point 'stripeTail' to a NULL location after calling
 * 'DestroySensor(stripeHead)', in order to prevent undefined behavior.
 * Output:
 *  - New Sensor attached to 'stripeTail'
 ********************************************************************/
Sensor StackSensor(Sensor stripeTail);

/********************************************************************
 * Function to destruct a Sensor.
 *
 * Inputs:
 *  - Sensor object
 ********************************************************************/
void DestroySensor(Sensor *stripeHead);

/********************************************************************
 * Function to change the Sensor's current state to 'activated', given
 * a trigger action.
 *
 * Inputs:
 *  - Sensor object
 ********************************************************************/
void ActivateSensor(Sensor sensor);

/********************************************************************
 * Function to change the Sensor's current state to 'deactivated'.
 *
 * Inputs:
 *  - Sensor object
 ********************************************************************/
void DeactivateSensor(Sensor sensor);

/********************************************************************
 * Function to detect a synchronous action.
 * This function stops the program execution until it receives a signal
 * from the physical sensor.
 *
 * Inputs:
 *  - Sensor object
 *  - StageTrigger object (Callback for chain reaction)
 ********************************************************************/
void SensorDetect(Sensor sensor, StageTrigger trigger);

/********************************************************************
 * Function to detect an asynchronous action.
 * This function creates a parallel execution waiting a signal from
 * the physical sensor and then calling the StageTrigger.
 *
 * Inputs:
 *  - Sensor object
 *  - StageTrigger object (Callback for chain reaction)
 ********************************************************************/
Bool SensorDetachedDetection(Sensor stripeSensor, DetachedParams *params);

/********************************************************************
 * Function to read the Sensor's current state.
 *
 * Inputs:
 *  - Sensor object
 * Output:
 *  - State object
 ********************************************************************/
State GetSensorState(Sensor sensor);

/********************************************************************
 * Function to count all the Sensors active given a Stack.
 *
 * Inputs:
 *  - Sensor's stack head 'stripeHead'
 * Output:
 *  - Number of active sensors
 ********************************************************************/
int GetActiveSensors(Sensor stripeHead);

#endif