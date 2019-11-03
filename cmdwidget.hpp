#ifndef CMDWIDGET_HPP
#define CMDWIDGET_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>

#include "LtDbg/LtDbg/Dbg.hpp"

class CmdWidget : public QWidget
{
    Q_OBJECT 
public:
    CmdWidget(QWidget * parent = nullptr);

    void AddInfo(const QString message);
    void AddError(const QString message);
    void AddText(const QString message);

    void SetDebugger(Dbg * const debugger);
    void SetEnabled(const bool enabled);

private slots:
    void ExecuteCommand();

private:
    void keyPressEvent(QKeyEvent * event);
    QString GetPreviousCommand();
    QString GetNextCommand();

    QVBoxLayout * _mainLayout;

    QTextEdit * _cmdTextEdit;
    QLineEdit * _cmdLineEdit;

    QVector<QString> _commandsHistory;
    int _commandIndex;

    Dbg * _dbg;
};

#endif // CMDWIDGET_HPP
