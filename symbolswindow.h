#ifndef SYMBOLSWINDOW_H
#define SYMBOLSWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>

class SymbolsWindow : public QDialog
{
    Q_OBJECT

public:
    SymbolsWindow();
    ~SymbolsWindow();

public slots:
    void MySaveAndClose();
    void MyBrowse();

private:
    void MyReadConfFile();

    QVBoxLayout * _mainLayout;
    QTextEdit * _textEdit;
    QHBoxLayout * _buttonsLayout;
    QPushButton * _browseButton;
    QPushButton * _okButton;
    QPushButton * _cancelButton;
};

#endif // SYMBOLSWINDOW_H
