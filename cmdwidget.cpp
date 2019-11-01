#include "cmdwidget.hpp"
#include "debuggerstate.h"
#include "LtDbg/LtDbg/Exceptions.hpp"

#include <QKeyEvent>

CmdWidget::CmdWidget(QWidget * parent) : QWidget(parent)
{
    _mainLayout = new QVBoxLayout;

    _cmdTextEdit = new QTextEdit;
    _cmdTextEdit->setReadOnly(true);

    _cmdLineEdit = new QLineEdit(this);
    _cmdLineEdit->setFocus();

    _mainLayout->addWidget(_cmdTextEdit);
    _mainLayout->addWidget(_cmdLineEdit);

    SetEnabled(false);
    setLayout(_mainLayout);
}

void CmdWidget::AddInfo(const QString message)
{
    _cmdTextEdit->append("[Info] " + message);
}

void CmdWidget::AddError(const QString message)
{
    _cmdTextEdit->append("[Error] " + message);
}

void CmdWidget::SetDebugger(Dbg * const debugger)
{
    _dbg = debugger;
}

void CmdWidget::SetEnabled(const bool enabled)
{
    _cmdLineEdit->setEnabled(enabled);
}

void CmdWidget::ExecuteCommand()
{
    try {
    QString cmdStr = _cmdLineEdit->text();
    DbgResponsePtr res;

    if (cmdStr.size() == 0 && _commandsHistory.size() == 0)
        return;

    if (cmdStr.size() == 0)
    {
        res = _dbg->ExecuteCommand(_commandsHistory[_commandIndex - 1].toStdString(), DebuggerState::Instance()->lastResponse->context);
    }
    else
    {
        res = _dbg->ExecuteCommand(cmdStr.toStdString());
    }

    _cmdTextEdit->append(QString (res->content.c_str()));

    DebuggerState::Instance()->lastResponse = res;

    if (_commandsHistory.size() == 0)
    {
        _commandsHistory.push_back(cmdStr);
        _commandIndex = _commandsHistory.size();
    }
    else if ( _commandsHistory.back() != cmdStr)
    {
        _commandsHistory.push_back(cmdStr);
        _commandIndex = _commandsHistory.size();
    }

    _cmdLineEdit->setText("");
    } catch (const DbgException & exc) {
        AddError("An error occured");
        AddError(QString(exc.ToString().c_str()));
    }
}

void CmdWidget::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
    case Qt::Key_Return:
        ExecuteCommand();
        break;
    case Qt::Key_Up:
        _cmdLineEdit->setText(GetPreviousCommand());
        break;
    case Qt::Key_Down:
        _cmdLineEdit->setText(GetNextCommand());
        break;
    }
}

QString CmdWidget::GetPreviousCommand()
{
    if (_commandsHistory.size() == 0)
        return _cmdLineEdit->text();

    if ((_commandIndex - 1) < 0)
        return _commandsHistory[_commandIndex];

    return _commandsHistory[--_commandIndex];
}

QString CmdWidget::GetNextCommand()
{
    if (_commandsHistory.size() == 0)
        return "";

    if ((_commandIndex + 1) >= _commandsHistory.size())
    {
        if ((_commandIndex + 1) == _commandsHistory.size())
            _commandIndex++;
        return "";
    }

    return _commandsHistory[++_commandIndex];
}
