#ifndef DEBUGGERSTATE_H
#define DEBUGGERSTATE_H

#include "LtDbg/LtDbg/Response.hpp"

class DebuggerState
{
public:
    static DebuggerState * Instance();

    DbgResponsePtr lastResponse;

private:
    DebuggerState();

    static DebuggerState * _instance;
};


#endif // DEBUGGERSTATE_H
