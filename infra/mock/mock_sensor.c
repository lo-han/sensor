#include "trigger.h"

#include <unistd.h>

Bool WaitSignal() {
    sleep(1);
    return _true;
}
