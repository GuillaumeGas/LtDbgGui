#include "debuggermanager.h"

DebuggerManager * DebuggerManager::_instance = nullptr;

DebuggerManager::DebuggerManager()
{

}

DebuggerManager * DebuggerManager::Instance()
{
    if (_instance == nullptr)
    {
        _instance = new DebuggerManager();
        _instance->_initialized = false;
    }

    return _instance;
}

void DebuggerManager::Initialize(Dbg * const dbg, CmdWidget * const cmdWidget, StackTraceWidget * const stackTraceWidget, AsmWidget * const asmWidget)
{
    _dbg = dbg;
    _cmdWidget = cmdWidget;
    _stackTraceWidget = stackTraceWidget;
    _asmWidget = asmWidget;

    _initialized = true;
}

void DebuggerManager::ConnectToDebugger(const std::string pipename)
{
    DbgResponsePtr res = _dbg->ExecuteCommand(CMD_CONNECT);
    if (res->status != DBG_STATUS_SUCCESS)
    {
        _cmdWidget->AddError("Connection failed with LtMicros ! (Connect command returned " + QString(res->status));
    }
    else
    {
        lastResponse = res;

        _cmdWidget->SetEnabled(true);
        _cmdWidget->AddInfo("Connected to LtMicros");

        RetrieveDisassembly();
        RetrieveStacktrace();
    }
}

void DebuggerManager::ExecuteCommand(const std::string input, KeDebugContext * context)
{
    DbgResponsePtr res = _dbg->ExecuteCommand(input, context);

    if (res == nullptr)
    {
        _cmdWidget->AddError("The command result is null");
        return;
    }

    if (res->status != DBG_STATUS_SUCCESS && res->status != DBG_STATUS_BREAKPOINT_REACHED)
    {
        _cmdWidget->AddError("Command" + QString(input.c_str()) + " failed with code " + QString::number(res->status));
        return;
    }

    _cmdWidget->AddText("> " + QString(input.c_str()));
    _cmdWidget->AddText(QString(res->content.c_str()));

    // Ask for disassembly and stacktrace to the kernel and display them
    RetrieveStacktrace();
    RetrieveDisassembly();
}

void DebuggerManager::RetrieveDisassembly()
{
    DbgResponsePtr res = _dbg->ExecuteCommand(CMD_DISASS, "100", lastResponse->context);
    if (res == nullptr)
    {
        _cmdWidget->AddError("Failed to retrieve stack trace");
        return;
    }

    if (res->status != DBG_STATUS_SUCCESS && res->status != DBG_STATUS_BREAKPOINT_REACHED)
    {
        _cmdWidget->AddError("Failed to retrieve stack trace, error code : " + QString::number(res->status));
        return;
    }

    _asmWidget->setText(QString(res->content.c_str()));
}

void DebuggerManager::RetrieveStacktrace()
{
    DbgResponsePtr res = _dbg->ExecuteCommand(CMD_STACK_TRACE, "", lastResponse->context);
    if (res == nullptr)
    {
        _cmdWidget->AddError("Failed to retrieve stack trace");
        return;
    }

    if (res->status != DBG_STATUS_SUCCESS && res->status != DBG_STATUS_BREAKPOINT_REACHED)
    {
        _cmdWidget->AddError("Failed to retrieve stack trace, error code : " + QString::number(res->status));
        return;
    }

    _stackTraceWidget->setText(QString(res->content.c_str()));
}
