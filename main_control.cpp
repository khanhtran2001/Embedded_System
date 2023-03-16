// define each State
enum State
{
    NORMAL_STATE,
    EMERGENCY_STATE,
};

enum NormalState
{
    IDLE,
    NORMAL_WORKING,
    NORMAL_STOP,
};

enum NormalWorkingState
{
    TORQUE_CONTROL_STATE,
    SPEED_CONTROL_STATE,
};

// define initial state for each large stage.
State state = NORMAL_STATE;
NormalState normalState = IDLE;
NormalWorkingState normalWorkingState = SPEED_CONTROL_STATE;

// changing condition
bool isStart();
bool isBreakingSignal();
bool doneStop();
bool hasError();
bool pushHardReset();
bool isError();
bool changeStateSignal();

// run unit control process
void unitControl()
{
    State state = NORMAL_STATE;
    switch (state)
    {
    case NORMAL_STATE:
        /* code */
        runNormalState(state);
        if (isError())
        {
            state = EMERGENCY_STATE;
            normalState = IDLE;
            normalWorkingState = SPEED_CONTROL_STATE;
        }
        break;

    case EMERGENCY_STATE:
        runEmergencyState();
        if (pushHardReset)
        {
            state = NORMAL_STATE;
        }
        break;
    }
}

void runNormalState(State state)
{
    switch (state)
    {
    case IDLE:
        // run ideal state
        runIdleState();
        if (isStart())
        {
            normalState = NORMAL_WORKING;
        }
        break;
    case NORMAL_WORKING:
        runNormalWorkingState();
        if (isBreakingSignal())
        {
            normalState = NORMAL_STOP;
            normalWorkingState = SPEED_CONTROL_STATE;
        }
        break;
    case NORMAL_STOP:
        runNormalStopState();
        if (doneStop())
        {
            normalState = IDLE;
        }
        break;
    }
}

void runEmergencyState();

void runIdleState();

void runNormalWorkingState()
{
    switch (normalWorkingState)
    {
    case SPEED_CONTROL_STATE:
        if (changeStateSignal())
        {
            normalWorkingState = SPEED_CONTROL_STATE;
        }
        runSpeedControlState();
        break;

    case TORQUE_CONTROL_STATE:
        if (changeStateSignal())
        {
            normalWorkingState = TORQUE_CONTROL_STATE;
        }
        runTorqueControlState();
        break;
    }
}

void runNormalStopState();

void runSpeedControlState();

void runTorqueControlState();
