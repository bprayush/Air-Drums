#ifndef ARDUINOSERIAL_H
#define ARDUINOSERIAL_H
#include <QSerialPort>
#include <QString>
#include <QObject>
#include <QStringList>

class ArduinoSerial
{

public:
    ArduinoSerial();
    bool connect(QString port);
    int getData(QByteArray selectBit);
    QStringList portList();

private:
    QSerialPort serial;
    int data;
    QByteArray selectBit;
    void readData();

};

#endif // ARDUINOSERIAL_H
