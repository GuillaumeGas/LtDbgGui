#include "mainwindow.h"

#include <QMenuBar>
#include <QApplication>

#include "parameters.h"
#include "debuggerstate.h"
#include "LtDbg/LtDbg/Exceptions.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _initView();
    _initMenu();
    _initDebugger();
}

MainWindow::~MainWindow()
{

}

void MainWindow::_initView()
{
    _window = new QWidget;

    _mainLayout = new QVBoxLayout;
    _pipeEditLayout = new QHBoxLayout;

    /* Connexion layout */
    _pipeLineEdit = new QLineEdit;
    _pipeLineEdit->setText(QString(Parameters::Instance()->pipeName.c_str()));
    _connexionButton = new QPushButton("Connect");

    _pipeEditLayout->addWidget(_pipeLineEdit);
    _pipeEditLayout->addWidget(_connexionButton);

    _mainLayout->addLayout(_pipeEditLayout);

    /* Sub windows layout */
    _subWindowsArea = new QMdiArea;

    _stackTraceTextEdit = new StackTraceWidget;
    _asmTextEdit = new AsmWidget;

    _cmdWidget = new CmdWidget;

    _stackTraceSubWindow = _subWindowsArea->addSubWindow(_stackTraceTextEdit);
    _asmSubWindow = _subWindowsArea->addSubWindow(_asmTextEdit);
    _consoleSubWindow = _subWindowsArea->addSubWindow(_cmdWidget);
    _cmdWidget->show();

    _subWindowsArea->tileSubWindows();

    _mainLayout->addLayout(_pipeEditLayout);
    _mainLayout->addWidget(_subWindowsArea);

    _window->setLayout(_mainLayout);
    setCentralWidget(_window);

    connect(_connexionButton, SIGNAL(clicked()), this, SLOT(connectToLtKernel()));
}

void MainWindow::_initMenu()
{
    QMenu * fileMenu = menuBar()->addMenu("File");

    _actionSymbols = new QAction("Load symbols...", this);
    _actionQuit = new QAction("Quit", this);

    fileMenu->addAction(_actionSymbols);
    fileMenu->addAction(_actionQuit);

    connect(_actionQuit, SIGNAL(triggered()), this, SLOT(openSymbolsMenu()));
    connect(_actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::_initDebugger()
{
    _dbg = new Dbg;

    if (_pipeLineEdit->text().length() > 0)
        connectToLtKernel();
}

void MainWindow::openSymbolsMenu()
{
    //Parameters::Instance()->symbolsPath = "";
}

void MainWindow::connectToLtKernel()
{
    const QString pipeName = _pipeLineEdit->text();

    _connexionButton->setDisabled(true);
    _cmdWidget->SetDebugger(nullptr);
    _cmdWidget->SetEnabled(false);

    if (pipeName.length() > 0)
    {
        try {
            _cmdWidget->AddInfo("Trying to connect to LtKernel using pipe '" + pipeName + "'...");
            _dbg->Connect(_pipeLineEdit->text().toStdString());
            _dbg->SetSymbolsPath(Parameters::Instance()->symbolsPath);

            DbgResponsePtr res = _dbg->ExecuteCommand(CMD_CONNECT);
            if (res->status != DBG_STATUS_SUCCESS)
            {
                _cmdWidget->AddError("Connection failed with LtKernel ! (Connect command returned " + QString(res->status));
            }
            else
            {
                DebuggerState::Instance()->lastResponse = res;

                _cmdWidget->SetDebugger(_dbg);
                _cmdWidget->SetEnabled(true);
                _cmdWidget->AddInfo("Connected to LtKernel");
            }
        }
        catch (const DbgException & exc)
        {
            _cmdWidget->AddError("An error occured while trying to connect to LtKernel !");
            _cmdWidget->AddError(QString(exc.ToString().c_str()));
        }
    }
    else
    {
        _cmdWidget->AddInfo("No pipe name");
    }

    _connexionButton->setDisabled(false);
}