#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Drum Machine!");
    ui->connectButton->setText("Connect");
    ui->exitButton->setText("Exit");
    ui->volumeKnob->setMaximum(100);
    ui->spinBox->setMaximum(100);
    ui->volumeLabel->setText("<center><b>Volume</b></center>");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connectButton_pressed()
{
    arduino->connect("/dev/ttyACM1");
}
