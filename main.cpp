#include "bluetooth.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Bluetooth w;
    w.show();



    return a.exec();
}
