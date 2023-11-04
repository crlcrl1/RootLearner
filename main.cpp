#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    a.setStyle("Fusion");
    w.show();
    return a.exec();
}
