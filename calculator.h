#pragma once

#include <QWidget>
#include <QStack>
#include <QLCDNumber>
#include <QPushButton>

class Calculator : public QWidget
{
    Q_OBJECT

private:
    QLCDNumber* plcd;
    QStack<QString> stk;
    QString qstrRes;


public:
    Calculator(QWidget* pparent = nullptr);
    QPushButton* createBtn(const QString& qstr);
    void calculate();

public slots:
    void slotBtnClicked();
};
