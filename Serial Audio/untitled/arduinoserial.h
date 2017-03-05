#ifndef ARDUINOSERIAL_H
#define ARDUINOSERIAL_H
#include <QSerialPort>
#include <QString>
#include <QObject>

class ArduinoSerial
{

public:
    ArduinoSerial();
    void connect(QString port);
    int getData(QByteArray selectBit);

private:
    QSerialPort serial;
    int data;
    QByteArray selectBit;
    void readData();

};

#endif // ARDUINOSERIAL_H
