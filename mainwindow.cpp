#include "mainwindow.h"
#include "setalarmwindow.h"
#include "viewAlarm.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    clockWidget = new ClockWidget(this);
    setAlarmButton = new QPushButton("Set Alarm", this);
    viewAlarmsButton = new QPushButton("View Alarms", this);
    viewAlarmWindow = nullptr;

    layout->addWidget(clockWidget);
    layout->addWidget(setAlarmButton);
    layout->addWidget(viewAlarmsButton);

    connect(setAlarmButton, &QPushButton::clicked, this, &MainWindow::openSetAlarm);
    connect(viewAlarmsButton, &QPushButton::clicked, this, &MainWindow::openViewAlarms);

    setCentralWidget(centralWidget);
}

void MainWindow::openSetAlarm() {
    SetAlarmWindow *setAlarmDialog = new SetAlarmWindow(this);
    connect(setAlarmDialog, &SetAlarmWindow::alarmSet, this, &MainWindow::handleAlarmSet);
    setAlarmDialog->exec();
}

void MainWindow::handleAlarmSet(QTime time, QString repeat, QString label, QString sound) {
    qDebug() << "Alarm set for:" << time.toString("HH:mm")
             << "| Repeat:" << repeat
             << "| Label:" << label
             << "| Sound:" << sound;

    alarms.append(time);
    alarmLabels.append(label);

    if (viewAlarmWindow) {
        viewAlarmWindow->updateAlarmList(alarms, alarmLabels);
    }
}

void MainWindow::openViewAlarms() {
    qDebug() << "View Alarms button clicked!";

    if (!viewAlarmWindow) {
        viewAlarmWindow = new ViewAlarm(this);
    }

    viewAlarmWindow->updateAlarmList(alarms, alarmLabels); // Update with latest alarms
    viewAlarmWindow->show();
}
