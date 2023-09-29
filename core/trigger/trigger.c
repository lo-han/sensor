#include "trigger.h"

Bool Trigger(StageTrigger stage, void *parameter) {
    Bool signal = WaitSignal();

    if (signal == _true) {
        stage(parameter);
        return signal;
    }

    return _false;
}
