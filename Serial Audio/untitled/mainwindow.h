#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "arduinoserial.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_connectButton_pressed();
    void on_volumeKnob_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    bool statusFlag;
};

#endif // MAINWINDOW_H
