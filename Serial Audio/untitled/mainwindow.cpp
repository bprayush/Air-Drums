#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QDebug>

ArduinoSerial *arduino;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusFlag = false;

    //CREATE THE ARDUINO OBJECT FROM ARDUINOSERIAL CLASS
    arduino = new ArduinoSerial();

    //SET THE TITLE OF THE WINDOW
    this->setWindowTitle("Drum Machine!");

    //SET THE TEXT OF THE CONNECT BUTTON
    ui->connectButton->setText("Connect");

    //SET THE TEXT OF EXIT BUTTON
    ui->exitButton->setText("Exit");
    //SET MAXIMUM VALUE OF VOLUME KNOB TO 100
    ui->volumeKnob->setMaximum(100);
    //SET THE MAXIMUM VALUE OF SPINX BOX TO 100
    ui->spinBox->setMaximum(100);
    //DISPLAY THE VOLUME LABEL
    ui->volumeLabel->setText("<center><b>Volume</b></center>");
    //DISPLAY THE CONNECTION STATUS AS PER THE CONNECTION
    ui->connectionStatus->setText("<center><font color=red><b>Disconnected!</b></font></center>");

    ui->spinBox->setValue(100);
    ui->volumeKnob->setValue(100);

    QStringList list = arduino->portList();

    ui->comboBox->addItems(list);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connectButton_pressed()
{
    //qDebug() << "Connection: " << arduino->connect(ui->comboBox->currentText());

    if(arduino->connect(ui->comboBox->currentText()) == true && statusFlag == false)
    {
        statusFlag = true;
        ui->connectButton->setText("Disconnect");
        ui->connectionStatus->setText("<center><font color=green><b>Connected!</b></font></center>");
        arduino->play();
    }
    else if(arduino->disConnect() == true && statusFlag == true)
    {
        statusFlag = false;
        ui->connectButton->setText("Connect");
        ui->connectionStatus->setText("<center><font color=red><b>Desconnected!</b></font></center>");
        arduino->stop();
    }

}

void MainWindow::on_volumeKnob_sliderMoved(int position)
{
    arduino->setVolume(position);
}
