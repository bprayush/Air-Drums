#include "arduinoserial.h"
#include <QDebug>
#include <iostream>
#include <QTimer>
#include <QList>
#include <QSerialPortInfo>

ArduinoSerial::ArduinoSerial()
{
    //EMPTY CONSTRUCTOR
}

//FUNCTION TO CONNEC TO THE SERIAL DEVICE
bool ArduinoSerial::connect(QString port)
{
    //SET THE PORT NAME
    qDebug() << "Connected Port: " << port << endl;
    serial.setPortName(port);
    //SET THE BAUD RATE OF THE PORT (USED 9600)
    serial.setBaudRate(QSerialPort::Baud9600);
    //SET PARITY BIT
    serial.setParity(QSerialPort::NoParity);
    //SET DATA BITS
    serial.setDataBits(QSerialPort::Data8);
    //SET STOP BITS
    serial.setStopBits(QSerialPort::OneStop);
    //SET FLOW CONTROL
    serial.setFlowControl(QSerialPort::NoFlowControl);

    //OPEN THE SERIAL CONNECTION IF NOT OPENED
    if(!serial.isOpen())
        serial.open(QIODevice::ReadWrite);

    qDebug() << "Connection status: " << serial.isOpen();

    return serial.isOpen();
}

//FUNCTION TO GET THE DATA FROM THE ARDUINO OF RESPECTIVE SENSORS
int ArduinoSerial::getData(QByteArray selectBit)
{
    //SET THE SELECTOIN BIT TO GET THE DATA OF CORRESPONDING SENSOR
    this->selectBit = selectBit;

    readData();

    //RETURN THE OBTAINED DATA
    return data;
}

void ArduinoSerial::readData()
{
    //ONLY TRY TO GET DATA IF THE SERIAL DEVICE IS CONNECTED
    if(serial.isOpen() && serial.isReadable())
    {

        //QBYTEARRAY TO STORE THE INCOMING DATA
        QByteArray array;
        //THE SELECTOIN BIT
        QByteArray caller = this->selectBit;
        serial.flush();
        //WAIT FOR SERIAL DEVICE TO SEND/RECIVE DATA
        serial.waitForBytesWritten(10);
        serial.waitForReadyRead(10);

        //SERIAL WRITE VALUE OF caller TO GET CORRESPONDING VALUES
        serial.write(caller);

        //GET THE CORRESPONDING VALUE
        array = serial.read(4);
        //STORE THE OBTAINED DATA IN INTEGER FORM
        data = array.toInt();

        //DEBUGGIN
        qDebug() << "Data from sensor " << this->selectBit << ": " << data;
    }
}

QStringList ArduinoSerial::portList()
{
    QStringList list;
    foreach(QSerialPortInfo info, QSerialPortInfo::availablePorts())
    {
        list.append(info.portName());
        //qDebug() << "Name: " << info.portName() << endl;
        //qDebug() << "Manufacturer: " << info.manufacturer() << endl;
    }

    return list;
}
