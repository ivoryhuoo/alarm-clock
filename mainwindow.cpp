#include "mainwindow.h"
#include "setalarmwindow.h"
#include "viewAlarm.h"
#include <QDebug>
#include <QMessageBox>

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

    // Timer to check alarms every second
    alarmCheckTimer = new QTimer(this);
    connect(alarmCheckTimer, &QTimer::timeout, this, &MainWindow::checkAlarms);
    alarmCheckTimer->start(1000);  // Check every second

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

void MainWindow::checkAlarms() {
    QTime currentTime = QTime::currentTime();
    int currentHour = currentTime.hour();
    int currentMinute = currentTime.minute();

    for (int i = 0; i < alarms.size(); ++i) {
        if (alarms[i].hour() == currentHour && alarms[i].minute() == currentMinute) {
            // Create a message box with Snooze and Dismiss options
            QMessageBox msgBox;
            msgBox.setWindowTitle("Alarm Triggered");
            msgBox.setText(alarmLabels[i] + " has gone off!");
            QPushButton *snoozeButton = msgBox.addButton("Snooze", QMessageBox::ActionRole);
            QPushButton *dismissButton = msgBox.addButton("Dismiss", QMessageBox::RejectRole);

            msgBox.exec(); // Show the pop-up

            if (msgBox.clickedButton() == snoozeButton) {
                snoozeAlarm(i, 5); // Snooze for 5 minutes
                alarms.removeAt(i); // Dismiss the alarm
                alarmLabels.removeAt(i);
                return;
            } else {
                alarms.removeAt(i); // Dismiss the alarm
                alarmLabels.removeAt(i);
            }

            return; // Stop checking after first matched alarm
        }
    }
}

void MainWindow::snoozeAlarm(int index, int minutes) {
    QTime snoozedTime = alarms[index].addSecs(minutes * 60); // Add minutes
    alarms.append(snoozedTime);
    alarmLabels.append(alarmLabels[index] + " (Snoozed)"); // Indicate it's snoozed

    qDebug() << "Alarm snoozed until" << snoozedTime.toString("HH:mm");

    if (viewAlarmWindow) {
        viewAlarmWindow->updateAlarmList(alarms, alarmLabels);
    }
}

