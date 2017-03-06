#ifndef ARDUINOSERIAL_H
#define ARDUINOSERIAL_H
#include <QSerialPort>
#include <QString>
#include <QObject>
#include <QStringList>
#include <QMediaPlayer>
#include <QTimer>

class ArduinoSerial: public QObject
{
    Q_OBJECT

public:
    ArduinoSerial();
    bool connect(QString port);
    QStringList portList();
    bool disConnect();
    ~ArduinoSerial();
    void setVolume(int volume);
    void play();
    void stop();

private:
    QSerialPort serial;
    ArduinoSerial *arduino;
    char data;
    QByteArray selectBit;
    QMediaPlayer *player;
    QMediaPlayer *player1;
    QMediaPlayer *player2;
    QTimer  *timer;

private slots:
    void getData();

};

#endif // ARDUINOSERIAL_H
