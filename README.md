# sensor
Sensor is an abstraction of any physical detection device, by
defining a type that relies on events given a device signal and declaring an interface for portings.

## Supported physical sensors 

_Coming soon_

## Usage example

Sensor can use a `StageTrigger` function to perform a modification on itself
or another entity. This behavior can be observed at `SensorDetect` (synchronous)
and `SensorDetachedDetection` (asynchronous) functions. [API Reference](core/sensor/sensor.h).

### Single sensor

```c
void _activate_sensor(Sensor sensor)
{
    if (sensor != NULL)
    {
        ActivateSensor(sensor);
    }
}

int main()
{
    Sensor sensor = NewSensor();

    SensorDetect(sensor, (StageTrigger) _activate_sensor);

    DestroySensor(&sensor);
}
```

### Multiple sensors (stripe)

```c
void _activate_sensor(Sensor sensor)
{
    if (sensor != NULL)
    {
        ActivateSensor(sensor);
    }
}

int main()
{
    Sensor stripeHead = NewSensor();
    Sensor stripeTail = StackSensor(stripeHead);

    DetachedParams params = {
        stripeTail,
        (StageTrigger)_activate_sensor};

    SensorDetachedDetection(stripeTail, &params);

    DestroySensor(&stripeHead);
    stripeTail = NULL;
}
```

## Tests

### Run unit tests

``` bash
python3 run_tests.py
```

### Run static checks

``` bash
python3 run_static_check.py
```

## Contribute

_Any idea or improvement is welcome. Feel free to branch and Pull Request for contributions, just, please, don't commit directly to develop or main histories. You can also get in contact with 'lohan.chuan123@gmail.com' or fork the repository._
