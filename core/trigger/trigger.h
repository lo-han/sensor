#ifndef __TRIGGER_H__
#define __TRIGGER_H__

typedef enum _b
{
    _false = 0,
    _true
} Bool;

/********************************************************************
 * Callback for chain reaction
 ********************************************************************/
typedef void (*StageTrigger)(void *);

/********************************************************************
 * This function waits for a report from a sensor,
 * returns a boolean type
 * and calls the StageTrigger function when activated.
 *
 * Inputs:
 *  - StageTrigger
 *  - Parameter to be passed to StageTrigger
 * Output:
 *  - Bool
 ********************************************************************/
Bool Trigger(StageTrigger stage, void *parameter);

/********************************************************************
 * Wait for signal respond
 ********************************************************************/
Bool WaitSignal();

#endif