#include "mainwindow.h"
#include <QApplication>
#include "arduinoserial.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QByteArray selectA = "a";
    QByteArray selectB = "b";
    QByteArray selectC = "c";

    /*
        ArduinoSerial *arduino = new ArduinoSerial();
        arduino->connect("/dev/ttyACM1");

        arduino->getData(selectA);
    */
    return a.exec();
}
