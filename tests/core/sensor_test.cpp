#include <gtest/gtest.h>

extern "C"
{
#include "sensor.h"
#include "trigger.h"
#include <string.h>
#include <stdlib.h>
}

void _activate_sensor_trigger_test(Sensor sensor)
{
    if (sensor != NULL)
    {
        ActivateSensor(sensor);
    }
}

TEST(NewSensor, successful_sensor_instantiation)
{
    Sensor sensor = NewSensor();
    ASSERT_TRUE(sensor != NULL);

    State state = GetSensorState(sensor);

    ASSERT_EQ(state, state_deactivated);

    DestroySensor(&sensor);
}

TEST(DestroySensor, successful_sensor_destroy)
{
    Sensor sensor = NewSensor();
    ASSERT_TRUE(sensor != NULL);

    DestroySensor(&sensor);
    ASSERT_TRUE(sensor == NULL);
}

TEST(DestroySensor, doesnt_dump_core_when_called_with_null)
{
    Sensor sensor = NewSensor();
    ASSERT_TRUE(sensor != NULL);

    DestroySensor(NULL);
    ASSERT_TRUE(sensor != NULL);

    DestroySensor(&sensor);
    ASSERT_TRUE(sensor == NULL);
}

TEST(StackSensor, successful_stack_creation_and_destroy)
{
    Sensor stripeHead = NewSensor();
    ASSERT_TRUE(stripeHead != NULL);

    Sensor stripeTail = StackSensor(stripeHead);
    ASSERT_TRUE(stripeTail != NULL);

    for (int i = 0; i < 10; i++)
    {
        stripeTail = StackSensor(stripeTail);
    }

    DestroySensor(&stripeHead);
    ASSERT_TRUE(stripeHead == NULL);
}

TEST(StackSensor, successful_stack_return_with_wrong_parameter)
{
    Sensor stripeHead = NewSensor();
    ASSERT_TRUE(stripeHead != NULL);

    Sensor stripeTail = StackSensor(stripeHead);
    ASSERT_TRUE(stripeTail != NULL);

    Sensor node1 = StackSensor(stripeHead);
    ASSERT_TRUE(node1 == NULL);

    DestroySensor(&stripeHead);
    ASSERT_TRUE(stripeHead == NULL);
}

TEST(ActivateSensor, successful_sensor_activation)
{
    Sensor sensor = NewSensor();
    ASSERT_TRUE(sensor != NULL);

    State state = GetSensorState(sensor);

    ASSERT_EQ(state, state_deactivated);

    ActivateSensor(sensor);

    state = GetSensorState(sensor);

    ASSERT_EQ(state, state_activated);

    DestroySensor(&sensor);
    ASSERT_TRUE(sensor == NULL);
}

TEST(ActivateSensor, successful_sensor_activation_with_wrong_parameter)
{
    Sensor sensor = NewSensor();
    ASSERT_TRUE(sensor != NULL);

    State state = GetSensorState(sensor);

    ASSERT_EQ(state, state_deactivated);

    ActivateSensor(NULL);

    state = GetSensorState(sensor);

    ASSERT_EQ(state, state_deactivated);

    DestroySensor(&sensor);
    ASSERT_TRUE(sensor == NULL);
}

TEST(DeactivateSensor, successful_sensor_deactivation)
{
    Sensor sensor = NewSensor();
    ASSERT_TRUE(sensor != NULL);

    ActivateSensor(sensor);

    State state = GetSensorState(sensor);

    ASSERT_EQ(state, state_activated);

    DeactivateSensor(sensor);

    state = GetSensorState(sensor);

    ASSERT_EQ(state, state_deactivated);

    DestroySensor(&sensor);
    ASSERT_TRUE(sensor == NULL);
}

TEST(DeactivateSensor, successful_sensor_deactivation_with_wrong_parameter)
{
    Sensor sensor = NewSensor();
    ASSERT_TRUE(sensor != NULL);

    ActivateSensor(sensor);

    State state = GetSensorState(sensor);

    ASSERT_EQ(state, state_activated);

    DeactivateSensor(NULL);

    state = GetSensorState(sensor);

    ASSERT_EQ(state, state_activated);

    DestroySensor(&sensor);
    ASSERT_TRUE(sensor == NULL);
}

TEST(GetSensorState, doesnt_dump_core)
{
    State state = GetSensorState(NULL);
    ASSERT_TRUE(state == state_deactivated);
}

TEST(GetActiveSensors, doesnt_dump_core)
{
    int result = GetActiveSensors(NULL);
    ASSERT_TRUE(result == 0);
}

TEST(GetActiveSensors, successful_stack_active_sensors_count)
{
    Sensor stripeHead = NewSensor();
    ASSERT_TRUE(stripeHead != NULL);

    Sensor stripeTail = StackSensor(stripeHead);
    ASSERT_TRUE(stripeTail != NULL);

    for (int i = 0; i < 10; i++)
    {
        stripeTail = StackSensor(stripeTail);

        if (i % 2 == 0)
        {
            ActivateSensor(stripeTail);
        }
    }

    int activeSensors = GetActiveSensors(stripeHead);

    ASSERT_EQ(activeSensors, 5);

    DestroySensor(&stripeHead);
    ASSERT_TRUE(stripeHead == NULL);
}

TEST(SensorDetect, successful_detection)
{
    Sensor sensor = NewSensor();
    ASSERT_TRUE(sensor != NULL);

    State state = GetSensorState(sensor);
    ASSERT_EQ(state, state_deactivated);

    SensorDetect(sensor, (StageTrigger)&_activate_sensor_trigger_test);

    state = GetSensorState(sensor);
    ASSERT_EQ(state, state_activated);

    DestroySensor(&sensor);
    ASSERT_TRUE(sensor == NULL);
}

TEST(SensorDetect, successful_detached_detection)
{
    Sensor stripeHead = NewSensor();
    ASSERT_TRUE(stripeHead != NULL);
    State state = GetSensorState(stripeHead);
    ASSERT_EQ(state, state_deactivated);

    Sensor node1 = StackSensor(stripeHead);
    ASSERT_TRUE(node1 != NULL);

    DetachedParams params1 = {
        node1,
        (StageTrigger)_activate_sensor_trigger_test};

    Sensor node2 = StackSensor(node1);
    ASSERT_TRUE(node2 != NULL);

    Sensor node3 = StackSensor(node2);
    ASSERT_TRUE(node3 != NULL);

    DetachedParams params3 = {
        node3,
        (StageTrigger)_activate_sensor_trigger_test};

    Sensor node4 = StackSensor(node3);
    ASSERT_TRUE(node4 != NULL);

    SensorDetachedDetection(node1, &params1);
    SensorDetachedDetection(node3, &params3);

    sleep(3);

    state = GetSensorState(stripeHead);
    ASSERT_EQ(state, state_deactivated);
    state = GetSensorState(node1);
    ASSERT_EQ(state, state_activated);
    state = GetSensorState(node2);
    ASSERT_EQ(state, state_deactivated);
    state = GetSensorState(node3);
    ASSERT_EQ(state, state_activated);
    state = GetSensorState(node4);
    ASSERT_EQ(state, state_deactivated);

    DestroySensor(&stripeHead);
    ASSERT_TRUE(stripeHead == NULL);
}

TEST(SensorDetect, successful_detached_detection_with_wrong_parameter)
{
    Sensor stripeHead = NewSensor();
    ASSERT_TRUE(stripeHead != NULL);
    State state = GetSensorState(stripeHead);
    ASSERT_EQ(state, state_deactivated);

    Sensor node1 = StackSensor(stripeHead);
    ASSERT_TRUE(node1 != NULL);

    DetachedParams params = {
        node1,
        (StageTrigger)_activate_sensor_trigger_test};

    Bool response = SensorDetachedDetection(NULL, &params);
    ASSERT_EQ(response, _false);

    response = SensorDetachedDetection(node1, NULL);
    ASSERT_EQ(response, _false);

    response = SensorDetachedDetection(stripeHead, &params);
    ASSERT_EQ(response, _false);

    state = GetSensorState(stripeHead);
    ASSERT_EQ(state, state_deactivated);
    state = GetSensorState(node1);
    ASSERT_EQ(state, state_deactivated);

    DestroySensor(&stripeHead);
    ASSERT_TRUE(stripeHead == NULL);
}
