# sensor
Sensor is a digital representation of a detection device.
It relies on events and can be ported for different scenarios.

## Supported sensors 

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

## Build

> Currently sensor doesn't implement any infrastrcture, and for that reason a mock is being used

``` bash
mkdir obj
make
```

## Tests

### Run unit tests

``` bash
cd tests
python3 run_tests.py
```

### Run static checks

``` bash
cd tests
python3 run_static_check.py
```

## Contribute

_Any idea or improvement is welcome. Feel free to branch and Pull Request for contributions, just, please, don't commit directly to develop or main histories. You can also get in contact with 'lohan.chuan123@gmail.com' or fork the repository._
