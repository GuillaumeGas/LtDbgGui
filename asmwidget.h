#ifndef ASMWIDGET_H
#define ASMWIDGET_H

#include <QTextEdit>

class AsmWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit AsmWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // ASMWIDGET_H
