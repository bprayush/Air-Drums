#include "arduinoserial.h"
#include <QDebug>
#include <iostream>
#include <QTimer>
#include <QList>
#include <QSerialPortInfo>

ArduinoSerial::ArduinoSerial()
{
    player = new QMediaPlayer();
    player1 = new QMediaPlayer();
    player2 = new QMediaPlayer();

    player->setMedia(QUrl("qrc:/sounds/sounds/kick.wav"));
    player1->setMedia(QUrl("qrc:/sounds/sounds/snare.WAV"));
    player2->setMedia(QUrl("qrc:/sounds/sounds/simplehat1.wav"));

    player->play();
    player1->play();
    player2->play();
}

ArduinoSerial::~ArduinoSerial()
{
    disConnect();
}

//FUNCTION TO CONNEC TO THE SERIAL DEVICE
bool ArduinoSerial::connect(QString port)
{
    //SET THE PORT NAME
    //qDebug() << "Connected Port: " << port << endl;
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
        serial.open(QIODevice::ReadOnly);

    //qDebug() << "Connection status: " << serial.isOpen();

    return serial.isOpen();
}

//FUNCTION TO GET THE DATA FROM THE ARDUINO OF RESPECTIVE SENSORS
void ArduinoSerial::getData()
{
    if(serial.isOpen() && serial.isReadable())
    {

        //QBYTEARRAY TO STORE THE INCOMING DATA
        QByteArray array;
        //CLEAR THE SERIAL
        serial.flush();
        //WAIT FOR SERIAL DEVICE TO SEND/RECIVE DATA
        //serial.waitForReadyRead(2);

        //IF THE DATA IS BEIGN SENT THROUGH SERIAL
        if(serial.bytesAvailable() > 0)
        {
            //STORE THE READ BYTE INTO array
            array = serial.read(1);
            if(array[0] == 'a')
            {
                //SLEEP
                for(int i=0; i<100; ++i);
                //STORE THE REST OF THE BYTE IN ARRAY
                array = serial.read(2);
                data = 'a';
                qDebug() << "Hurray A "<< array << endl;
                player->setPosition(0);
                player->play();
            }
            else if(array[0] == 'b')
            {
                //SLEEP
                for(int i=0; i<100; ++i);
                //STORE THE REST OF THE BYTE IN ARRAY
                array = serial.read(2);
                data = 'b';
                qDebug() << "Hurray B " << array << endl;
                player1->setPosition(0);
                player1->play();
            }
            else if(array[0] == 'c')
            {
                //SLEEP
                for(int i=0; i<100; ++i);
                //STORE THE REST OF THE BYTE IN ARRAY
                array = serial.read(2);
                data = 'c';
                qDebug() << "Hurray C" << array << endl;
                player2->setPosition(0);
                player2->play();
            }
            else data = '0';
        }

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

bool ArduinoSerial::disConnect()
{
    qDebug() << "I'm CLosing!" << endl;
    serial.close();
    qDebug() << "Serial status: " << serial.isOpen() << endl;
    return !serial.isOpen();
}

void ArduinoSerial::setVolume(int volume)
{
    player->setVolume(volume);
    player1->setVolume(volume);
    player2->setVolume(volume);
}

void ArduinoSerial::play()
{
    player->setMuted(false);
    player1->setMuted(false);
    player2->setMuted(false);

    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(getData()));
    timer->start(25);
}

void ArduinoSerial::stop()
{
    player->stop();
    player1->stop();
    player2->stop();

    player->setMuted(true);
    player1->setMuted(true);
    player2->setMuted(true);

    timer->stop();
    delete(timer);
}
