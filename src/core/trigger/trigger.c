#include "sensor.h"

#include <stdlib.h>

Bool Trigger(StageTrigger stage, void *parameter) {
    Bool signal = WaitSignal();

    if (signal == _true && stage != NULL) {
        stage(parameter);
        return signal;
    }

    return _false;
}
