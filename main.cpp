#include <iostream>
#include "main_control.cpp"
#include "send_receive.cpp"
#include "process_request.cpp"

// super loop
int main()
{
    while (true)
    {
        unitControl();
        trasferAndRecieveMain();
        handleRequestProcess();
    }
}