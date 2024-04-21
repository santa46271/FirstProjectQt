#include "calculator.h"

#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Calculator calc;
    calc.resize(230,350);
    calc.setWindowFlags(Qt::Window|Qt::WindowSystemMenuHint|Qt::WindowCloseButtonHint);
    calc.show();
    return app.exec();
}
