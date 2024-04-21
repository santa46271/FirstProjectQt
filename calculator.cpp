#include "calculator.h"
#include <QGridLayout>
#include <QRegularExpression>

Calculator::Calculator(QWidget* pparent): QWidget(pparent) {
    plcd = new QLCDNumber(12);
    plcd->setSegmentStyle(QLCDNumber::Flat);
    plcd->setFrameStyle(QFrame::Plain);
    plcd->setMinimumSize(200,50);

    QChar arBtn[4][4] = { {'7', '8', '9', '/'},
                          {'4', '5', '6', '*'},
                          {'1', '2', '3', '-'},
                         {'0', '.', '=', '+'}};

    // Layout setup
    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(plcd, 0, 0, 1, 4);
    ptopLayout->addWidget(createBtn("CE"), 1, 3);

    for (int i=0; i<4; ++i) {
        for (int j=0; j<4;++j) {
            ptopLayout->addWidget(createBtn(arBtn[i][j]), i+2, j);
        }
    }
    this->setLayout(ptopLayout);
    this->resize(230,350);
}

QPushButton* Calculator::createBtn(const QString& qstr) {
    QPushButton* pbtn = new QPushButton(qstr);
    pbtn->setMinimumSize(50, 50);
    connect(pbtn, SIGNAL(clicked()), SLOT(slotBtnClicked()));
    return pbtn;
}

void Calculator::slotBtnClicked() {
    QString qstrClc = ((QPushButton*)sender())->text();

    if (qstrClc == "CE") {
        stk.clear();
        qstrRes = "";
        plcd->display("0");
        return;
    }

    static QRegularExpression regExp("[0-9]");
    if (qstrClc.contains(regExp)) {
        qstrRes+=qstrClc;
        plcd->display(qstrRes);
    }
    else if (qstrClc == ".") {
        if (qstrRes.isEmpty()) {
            qstrRes+="0.";
            plcd->display(qstrRes);
        }
        else if(!qstrRes.contains(".")){
            qstrRes+=".";
            plcd->display(qstrRes);
        }
    }
    else {
        if (stk.count()>=2) {
            stk.push(qstrRes);
            calculate();
            stk.clear();
            stk.push(QString().setNum(plcd->value()));
            if (qstrClc!="=")
                stk.push(qstrClc);
            qstrRes = "";
        }
        else {
            if (qstrRes!="")
                stk.push(qstrRes);
            if (!stk.back().contains(QRegularExpression("[/*-+]")) && qstrClc !="=")
                stk.push(qstrClc);
            qstrRes="";
        }
    }
}

void Calculator::calculate() {
    double operand2 = stk.pop().toDouble();
    QString Operation = stk.pop();
    double operand1 = stk.pop().toDouble();
    double result =0;

    if (Operation == "-") result = operand1 - operand2;
    if (Operation == "+") result = operand1 + operand2;
    if (Operation == "/") result = operand1 / operand2;
    if (Operation == "*") result = operand1 * operand2;

    plcd->display(result);
}
