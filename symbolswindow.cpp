#include "symbolswindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include <vector>

#include "parameters.h"
#include "debuggermanager.h"

SymbolsWindow::SymbolsWindow() : QDialog(nullptr)
{
    _mainLayout = new QVBoxLayout;
    _textEdit = new QTextEdit;
    _buttonsLayout = new QHBoxLayout;
    _browseButton = new QPushButton("Browse...");
    _okButton = new QPushButton("Ok");
    _cancelButton = new QPushButton("Cancel");

    _buttonsLayout->addWidget(_okButton);
    _buttonsLayout->addWidget(_cancelButton);

    _mainLayout->addWidget(_textEdit);
    _mainLayout->addWidget(_browseButton);
    _mainLayout->addLayout(_buttonsLayout);

    setLayout(_mainLayout);
    resize(800, 200);

    connect(_browseButton, SIGNAL(clicked()), this, SLOT(MyBrowse()));
    connect(_okButton, SIGNAL(clicked()), this, SLOT(MySaveAndClose()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(accept()));

    MyReadConfFile();
}

SymbolsWindow::~SymbolsWindow() {}

void SymbolsWindow::MyBrowse()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open a file", "",
                                                    "Binary files (*.img *.sys *.exe)");

    _textEdit->append(filePath);
}

void SymbolsWindow::MySaveAndClose()
{
    QString content = _textEdit->toPlainText();
    QStringList list = content.split('\n');

    Parameters::Instance()->ClearSymbolPaths();

    for (const QString& it : list)
    {
        Parameters::Instance()->AddSymbolsPath(it.toStdString());
    }

    Parameters::Instance()->Save();

    DebuggerManager::Instance()->LoadSymbols(Parameters::Instance()->symbolsPaths);

    accept();
}

void SymbolsWindow::MyReadConfFile()
{
    const std::vector<std::string> & list = Parameters::Instance()->symbolsPaths;

    for(const std::string & it : list)
    {
        _textEdit->append(QString(it.c_str()));
    }
}
