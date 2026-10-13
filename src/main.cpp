#include "mainwindow.h"
#include "colourwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ColourWindow w;
    w.show();
    return a.exec();
}
