#include <iostream>
#include "global.h"

enum HandlingRequestState
{
    IDLE_IN_HANDLING_PROCESS,
    CHECKING_REQUEST,
    PROCESS,
    FORMAT_ERROR_REPLY,
    FORMAT_NORMAL_REPLY
};
// define initial state
HandlingRequestState handlingRequestState = IDLE_IN_HANDLING_PROCESS;
// define criteria
bool requestReception();
bool errorInAddress();
bool checkOK();
bool errorInRequestData();
bool broadcastMode();
bool errorInProcess();
bool endOfProcess();
bool doneNormalReply();
bool doneFormatError();

// define run state functions
void runIdleInHandlingState();
void runCheckingRequestState();
void runProcessRequestState();
void runFormatNormalReplyState();
void runFormatErrorReplyState();

// run the handle request process
void handleRequestProcess()
{
    switch (handlingRequestState)
    {
    case IDLE_IN_HANDLING_PROCESS:
        runIdleInHandlingState();
        if (requestReception())
        {
            handlingRequestState = CHECKING_REQUEST;
        }
        break;
    case CHECKING_REQUEST:
        runProcessRequestState();
        if (checkOK())
        {
            handlingRequestState = PROCESS;
        }
        if (errorInAddress())
        {
            handlingRequestState = IDLE_IN_HANDLING_PROCESS;
        }
        if (errorInRequestData())
        {
            handlingRequestState = FORMAT_ERROR_REPLY;
        }
        break;
    case PROCESS:
        runProcessRequestState();
        if (broadcastMode())
        {
            handlingRequestState = IDLE_IN_HANDLING_PROCESS;
        }
        if (errorInProcess())
        {
            handlingRequestState = FORMAT_ERROR_REPLY;
        }
        if (endOfProcess())
        {
            handlingRequestState = FORMAT_NORMAL_REPLY;
        }
        break;
    case FORMAT_ERROR_REPLY:
        runFormatErrorReplyState();
        if (doneFormatError())
        {
            handlingRequestState = IDLE_IN_HANDLING_PROCESS;
        }
        break;
    case FORMAT_NORMAL_REPLY:
        runFormatNormalReplyState();
        if (doneNormalReply())
        {
            handlingRequestState = IDLE_IN_HANDLING_PROCESS;
        }
        break;
    }
}