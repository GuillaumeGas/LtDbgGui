#include "debuggerstate.h"

DebuggerState * DebuggerState::_instance = nullptr;

DebuggerState::DebuggerState()
{

}

DebuggerState * DebuggerState::Instance()
{
    if (_instance == nullptr)
    {
        _instance = new DebuggerState();
    }

    return _instance;
}
