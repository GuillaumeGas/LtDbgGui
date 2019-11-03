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

void DebuggerManager::ExecuteCommand(const std::string input, KeDebugContext * context)
{
    DbgResponsePtr res = _dbg->ExecuteCommand(input, context);

    if (res == nullptr)
    {
        _cmdWidget->AddError("The command result is null");
        return;
    }

    if (res->status != DBG_STATUS_SUCCESS)
    {
        _cmdWidget->AddError("Command" + QString(input.c_str()) + " failed with code " + QString(res->status));
        return;
    }

    _cmdWidget->AddText("> " + QString(input.c_str()));
    _cmdWidget->AddText(QString(res->content.c_str()));

    res = _dbg->ExecuteCommand(CMD_STACK_TRACE, "", lastResponse->context);
    if (res == nullptr)
    {
        _cmdWidget->AddError("Failed to retrieve stack trace");
        return;
    }

    if (res->status != DBG_STATUS_SUCCESS)
    {
        _cmdWidget->AddError("Failed to retrieve stack trace, error code : " + QString(res->status));
        return;
    }

    _stackTraceWidget->setText(QString(res->content.c_str()));

    res = _dbg->ExecuteCommand(CMD_DISASS, "", lastResponse->context);
    if (res == nullptr)
    {
        _cmdWidget->AddError("Failed to retrieve stack trace");
        return;
    }

    if (res->status != DBG_STATUS_SUCCESS)
    {
        _cmdWidget->AddError("Failed to retrieve stack trace, error code : " + QString(res->status));
        return;
    }

    _asmWidget->setText(QString(res->content.c_str()));
}
