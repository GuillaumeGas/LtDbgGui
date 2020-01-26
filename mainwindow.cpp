#include "mainwindow.h"

#include <QMenuBar>
#include <QApplication>

#include "parameters.h"
#include "debuggermanager.h"
#include "LtDbg/LtDbg/Exceptions.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _initView();
    _initMenu();
    _initDebuggerManager();
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
    _stackTraceSubWindow->setWindowTitle("Stack trace");
    _stackTraceSubWindow->setWindowIcon( QIcon(":/icons/iconStack.png") );
    _asmSubWindow = _subWindowsArea->addSubWindow(_asmTextEdit);
    _asmSubWindow->setWindowTitle("Disassembly");
    _asmSubWindow->setWindowIcon( QIcon(":/icons/iconDisassembly.png") );
    _consoleSubWindow = _subWindowsArea->addSubWindow(_cmdWidget);
    _consoleSubWindow->setWindowTitle("Output");
    _consoleSubWindow->setWindowIcon( QIcon(":/icons/iconCmdWidget.png") );
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

    _symbolsWindow = new SymbolsWindow;

    fileMenu->addAction(_actionSymbols);
    fileMenu->addAction(_actionQuit);

    connect(_actionSymbols, SIGNAL(triggered()), _symbolsWindow, SLOT(exec()));
    connect(_actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::_initDebuggerManager()
{
    _dbg = new Dbg;
    Parameters::Instance();
    DebuggerManager::Instance()->Initialize(_dbg, _cmdWidget, _stackTraceTextEdit, _asmTextEdit);

    //if (_pipeLineEdit->text().length() > 0)
      //  connectToLtKernel();
}

void MainWindow::openSymbolsMenu()
{
    /*
     * TODO : ouvrir une fenetre ici avec un textarea, chaque ligne, séparée par un ';' est un chemin vers
     * */
    //Parameters::Instance()->symbolsPath = "";
}

void MainWindow::connectToLtKernel()
{
    const QString pipeName = _pipeLineEdit->text();

    _connexionButton->setDisabled(true);
    _cmdWidget->SetEnabled(false);

    if (pipeName.length() > 0)
    {
        try {
            _cmdWidget->AddInfo("Trying to connect to LtMicros using pipe '" + pipeName + "'...");
            _dbg->Connect(_pipeLineEdit->text().toStdString());

            DebuggerManager::Instance()->ConnectToDebugger(Parameters::Instance()->pipeName);
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
