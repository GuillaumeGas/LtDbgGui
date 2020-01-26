#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

#include "cmdwidget.hpp"
#include "asmwidget.h"
#include "stacktracewidget.h"
#include "symbolswindow.h"
#include "LtDbg/LtDbg/Dbg.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openSymbolsMenu();
    void connectToLtKernel();

private:
    void _initView();
    void _initMenu();
    void _initDebuggerManager();

    QWidget * _window;

    QVBoxLayout * _mainLayout;
    QHBoxLayout * _pipeEditLayout;

    QLineEdit * _pipeLineEdit;
    QPushButton * _connexionButton;

    QMdiArea * _subWindowsArea;
    QMdiSubWindow * _stackTraceSubWindow;
    QMdiSubWindow * _asmSubWindow;
    QMdiSubWindow * _consoleSubWindow;

    StackTraceWidget * _stackTraceTextEdit;
    AsmWidget * _asmTextEdit;
    CmdWidget * _cmdWidget;

    QAction * _actionSymbols;
    QAction * _actionQuit;

    Dbg * _dbg;

    SymbolsWindow * _symbolsWindow;
};

#endif // MAINWINDOW_H
