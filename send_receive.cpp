#include <iostream>
#include "global.h"

enum TransferAndReceiveState
{
    InitialState,
    IDLE_IN_TRANMISSION_PROCESS,
    RECEIVE,
    CHECKFRAME,
    TRANSMIT
};
// define initial process state
TransferAndReceiveState transmisionState;

// define run function for each state
void runInitialState();
void runIdleState();
void runReceiveState();
void runEntryRecieveState();
void runCheckingFrameState();
void runTransmitState();
void runEntryTransmitState();
void runEntryInitialState();

// define criteria
bool receivedChar();
bool haveTransmitRequestSignal();

// run transfer and receive communication process
void trasferAndRecieveMain()
{
    switch (transmisionState)
    {
    case InitialState:
        runInitialState();
        if ((time_value < STOP_TIME) && (receivedChar()))
        {
            runEntryInitialState();
        }
        if ((time_value > STOP_TIME))
        {
            transmisionState = IDLE_IN_TRANMISSION_PROCESS;
        }
        break;
    case IDLE_IN_TRANMISSION_PROCESS:
        runIdleState();
        if (haveTransmitRequestSignal)
        {
            transmisionState = TRANSMIT;
        }
        if (receivedChar)
        {
            transmisionState = RECEIVE;
        }
        break;
    case TRANSMIT:
        runTransmitState();
        if (time_value < STOP_TIME)
        {
            runEntryTransmitState();
        }
        if (time_value > STOP_TIME)
        {
            transmisionState = IDLE_IN_TRANMISSION_PROCESS;
        }
        break;
    case RECEIVE:
        runReceiveState();
        if (time_value < MAX_DURATION_BETWEEN_CHAR)
        {
            runEntryRecieveState();
        }
        if (time_value > MAX_DURATION_BETWEEN_CHAR)
        {
            transmisionState = CHECKFRAME;
        }
        break;
    case CHECKFRAME:
        runCheckingFrameState();
        if (time_value > STOP_TIME)
        {
            transmisionState = IDLE_IN_TRANMISSION_PROCESS;
        }
        break;
    }
}
