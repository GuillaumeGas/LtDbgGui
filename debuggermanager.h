#ifndef DebuggerManager_H
#define DebuggerManager_H

#include "LtDbg/LtDbg/Dbg.hpp"
#include "LtDbg/LtDbg/Response.hpp"
#include "cmdwidget.hpp"
#include "stacktracewidget.h"
#include "asmwidget.h"

class DebuggerManager
{
public:
    static DebuggerManager * Instance();

    void Initialize(Dbg * const dbg, CmdWidget * const cmdWidget, StackTraceWidget * const stackTraceWidget, AsmWidget * const asmWidget);
    void ConnectToDebugger(const std::string pipename);
    void ExecuteCommand(const std::string input, KeDebugContext * context = nullptr);
    void LoadSymbols(std::vector<std::string> & symbolsPaths);

    DbgResponsePtr lastResponse;

private:
    DebuggerManager();
    void RetrieveDisassembly();
    void RetrieveStacktrace();

    static DebuggerManager * _instance;

    Dbg * _dbg;
    CmdWidget * _cmdWidget;
    StackTraceWidget * _stackTraceWidget;
    AsmWidget * _asmWidget;
    bool _initialized;
};


#endif // DebuggerManager_H
