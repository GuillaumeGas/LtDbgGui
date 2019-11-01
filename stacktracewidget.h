#ifndef STACKTRACEWIDGET_H
#define STACKTRACEWIDGET_H

#include <QTextEdit>

class StackTraceWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit StackTraceWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // STACKTRACEWIDGET_H
