#include "mainwindow.h"
#include "setalarmwindow.h"
#include <QDebug> // Needed for qDebug()


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    clockWidget = new ClockWidget(this);
    setAlarmButton = new QPushButton("Set Alarm", this);
    viewAlarmsButton = new QPushButton("View Alarms", this);

    layout->addWidget(clockWidget);
    layout->addWidget(setAlarmButton);
    layout->addWidget(viewAlarmsButton);

    connect(setAlarmButton, &QPushButton::clicked, this, &MainWindow::openSetAlarm);

    setCentralWidget(centralWidget);
}

void MainWindow::openSetAlarm() {
    SetAlarmWindow *setAlarmDialog = new SetAlarmWindow(this);
    connect(setAlarmDialog, &SetAlarmWindow::alarmSet, this, &MainWindow::handleAlarmSet);
    setAlarmDialog->exec(); // Open as a modal dialog
}

void MainWindow::handleAlarmSet(QTime time, QString repeat, QString label, QString sound) {
    qDebug() << "Alarm set for:" << time.toString("HH:mm")
             << "| Repeat:" << repeat
             << "| Label:" << label
             << "| Sound:" << sound;
}

void MainWindow::openViewAlarms() {
    qDebug() << "View Alarms button clicked!";  // Placeholder, you can add UI later
}


