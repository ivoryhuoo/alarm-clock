/**
 * @file mainwindow.cpp
 * @brief Implementation of the MainWindow class for the Rise and Pi alarm clock.
 * 
 * This file defines the MainWindow class, which serves as the main interface 
 * for the alarm clock application. It allows users to set, view, and manage alarms. 
 * 
 * The main functionalities include:
 * - Displaying the current time.
 * - Setting new alarms with labels and sounds.
 * - Viewing a list of active alarms.
 * - Checking and triggering alarms when the time matches.
 * - Snoozing and dismissing alarms via a message box.
 * 
 * @author Group 27
 * @date Friday, March 14
 */

#include "mainwindow.h"
#include "setalarmwindow.h"
#include "viewAlarm.h"
#include <QDebug>
#include <QMessageBox>
#include <QSound>

/**
 * @brief Constructs the main application window.
 * 
 * Initializes the clock display, buttons for setting and viewing alarms, 
 * and a timer to check alarms every second.
 * 
 * @param parent Pointer to the parent widget.
 */
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

    alarmCheckTimer = new QTimer(this);
    connect(alarmCheckTimer, &QTimer::timeout, this, &MainWindow::checkAlarms);
    alarmCheckTimer->start(1000);  // Check every second

    setCentralWidget(centralWidget);
}

/**
 * @brief Opens the Set Alarm window.
 * 
 * This function creates and displays a dialog window where users can configure
 * a new alarm, including the time, label, repeat settings, and sound.
 */
void MainWindow::openSetAlarm() {
    SetAlarmWindow *setAlarmDialog = new SetAlarmWindow(this);
    connect(setAlarmDialog, &SetAlarmWindow::alarmSet, this, &MainWindow::handleAlarmSet);
    setAlarmDialog->exec();
}

/**
 * @brief Handles the event when an alarm is set.
 * 
 * Stores the alarm time, label, and updates the alarm list display.
 * 
 * @param time The time the alarm is set for.
 * @param repeat The repeat setting of the alarm.
 * @param label A label/name for the alarm.
 * @param sound The sound file associated with the alarm.
 */
void MainWindow::handleAlarmSet(QTime time, QString repeat, QString label, QString sound) {
    qDebug() << "Alarm set for:" << time.toString("HH:mm")
             << "| Repeat:" << repeat
             << "| Label:" << label
             << "| Sound:" << sound;

    alarms.append(time);
    alarmLabels.append(label);
    alarmRepeats.append(repeat);
    alarmSounds.append(sound);
    alarmIsSnoozed.append(false);


    if (viewAlarmWindow) {
        viewAlarmWindow->updateAlarmList(alarms, alarmLabels, alarmRepeats, alarmIsSnoozed);

    }
}


/**
 * @brief Opens the View Alarms window.
 * 
 * Displays a list of all active alarms.
 */
void MainWindow::openViewAlarms() {
    qDebug() << "View Alarms button clicked!";

    if (!viewAlarmWindow) {
        viewAlarmWindow = new ViewAlarm(this);

        // Only connect once when the window is first created
        connect(viewAlarmWindow, &ViewAlarm::alarmDeleted, this, [=](const QString &label) {
            int index = alarmLabels.indexOf(label);
            if (index != -1) {
                alarms.removeAt(index);
                alarmLabels.removeAt(index);
                alarmSounds.removeAt(index);
                alarmRepeats.removeAt(index);
            }
        });

    }

    viewAlarmWindow->updateAlarmList(alarms, alarmLabels, alarmRepeats, alarmIsSnoozed);
    viewAlarmWindow->show();
}


/**
 * @brief Checks if any alarms match the current time and triggers an alert.
 * 
 * If an alarm matches the current system time, a message box is displayed with
 * options to snooze or dismiss the alarm.
 */
void MainWindow::checkAlarms() {
    QTime currentTime = QTime::currentTime();
    QDate currentDate = QDate::currentDate();
    int currentHour = currentTime.hour();
    int currentMinute = currentTime.minute();

    for (int i = 0; i < alarms.size(); ++i) {
    if (alarms[i].hour() == currentHour && alarms[i].minute() == currentMinute) {
        QString repeatOption = alarmRepeats[i];
        QString label = alarmLabels[i];
        QString sound = alarmSounds[i];
        bool isSnoozed = alarmIsSnoozed[i];

        // Suppress repeat alarms if dismissed today
        QString uniqueKey = label + "|" + currentDate.toString("yyyy-MM-dd");
        if (dismissedToday.contains(uniqueKey)) continue;

        // Play sound
        playAlarmSound(sound);

        QMessageBox msgBox;
        msgBox.setWindowTitle("Alarm Triggered");
        msgBox.setText(label + " has gone off!");
        QPushButton *snoozeButton = msgBox.addButton("Snooze", QMessageBox::ActionRole);
        QPushButton *dismissButton = msgBox.addButton("Dismiss", QMessageBox::RejectRole);
        msgBox.exec();

        if (msgBox.clickedButton() == snoozeButton) {
            snoozeAlarm(i, 1);
            stopAlarmSound();
        }
        else {
            stopAlarmSound();
        }

        if (repeatOption == "Never" || isSnoozed) {
            alarms.removeAt(i);
            alarmLabels.removeAt(i);
            alarmRepeats.removeAt(i);
            alarmSounds.removeAt(i);
            alarmIsSnoozed.removeAt(i);
        } else {
            dismissedToday.insert(uniqueKey);

            static const QMap<QString, Qt::DayOfWeek> repeatMap = {
                {"Every Sunday", Qt::Sunday}, {"Every Monday", Qt::Monday},
                {"Every Tuesday", Qt::Tuesday}, {"Every Wednesday", Qt::Wednesday},
                {"Every Thursday", Qt::Thursday}, {"Every Friday", Qt::Friday},
                {"Every Saturday", Qt::Saturday}
            };

            if (repeatMap.contains(repeatOption)) {
                QDate nextDate = currentDate.addDays(7);
                QDateTime nextAlarmDateTime(nextDate, alarms[i]);
                qDebug() << "[DEBUG] Dismissed repeat alarm:" << label
                         << "— next scheduled for" << nextAlarmDateTime.toString();
            }
        }

        if (viewAlarmWindow) {
            viewAlarmWindow->updateAlarmList(alarms, alarmLabels, alarmRepeats, alarmIsSnoozed);
        }

        return; 
    }
}


}


/**
 * @brief Snoozes an alarm for a given number of minutes.
 * 
 * Moves the alarm forward by the specified number of minutes and updates the alarm list.
 * 
 * @param index The index of the alarm to snooze.
 * @param minutes The number of minutes to snooze for.
 */
void MainWindow::snoozeAlarm(int index, int minutes) {
    QTime snoozedTime = alarms[index].addSecs(minutes * 60);
    
    alarms.append(snoozedTime);
    alarmLabels.append(alarmLabels[index]); 


    alarmRepeats.append(alarmRepeats[index]);
    alarmSounds.append(alarmSounds[index]);
    alarmIsSnoozed.append(true);

    qDebug() << "Alarm snoozed until" << snoozedTime.toString("HH:mm");

    if (viewAlarmWindow) {
        viewAlarmWindow->updateAlarmList(alarms, alarmLabels, alarmRepeats, alarmIsSnoozed);
    }
}

void MainWindow::playAlarmSound(const QString &soundName) {
    QString soundPath;
    if (soundName == "Classic") {
        soundPath = "sounds/ring1.wav";
    } else if (soundName == "Beep") {
        soundPath = "sounds/ring2.wav";
    } else if (soundName == "Rooster") {
        soundPath = "sounds/ring3.wav";
    }

    stopAlarmSound();

    alarmPlayer = new QSound(soundPath, this);
    alarmPlayer->setLoops(QSound::Infinite);  // Infinite loop
    alarmPlayer->play();
}

void MainWindow::stopAlarmSound() {
    if (alarmPlayer) {
        alarmPlayer->stop();
        delete alarmPlayer;
        alarmPlayer = nullptr;
    }
}
