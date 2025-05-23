/**
 * @file mainwindow.h
 * @brief Main window of the Rise and Pi alarm clock application.
 * 
 * This file defines the MainWindow class, which serves as the central interface
 * for the alarm clock application. It includes functionality for setting alarms,
 * viewing alarms, checking for triggered alarms, and snoozing alarms.
 * 
 * The main window consists of:
 * - A digital clock display.
 * - Buttons for setting and viewing alarms.
 * - A timer that checks active alarms every second.
 * 
 * @author Group 27
 * @date March 14, 2025
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTime>
#include <QTimer>  
#include <QSet>
#include <QSound>
#include "clockwidget.h"
#include "setalarmwindow.h"
#include "viewAlarm.h"

/**
 * @class MainWindow
 * @brief The main application window for the Rise and Pi alarm clock.
 * 
 * This class manages the alarm clock interface, allowing users to set,
 * view, and manage alarms. It periodically checks for active alarms
 * and triggers notifications when an alarm goes off.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructs the MainWindow.
     * @param parent Pointer to the parent QWidget (default: nullptr).
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Retrieves the list of set alarm times.
     * @return A QList of QTime objects representing the alarm times.
     */
    QList<QTime> getAlarms() const;

    /**
     * @brief Retrieves the list of alarm labels.
     * @return A QList of QString objects representing the alarm labels.
     */
    QList<QString> getAlarmLabels() const;

private slots:
    /**
     * @brief Opens the Set Alarm window to create a new alarm.
     */
    void openSetAlarm();

    /**
     * @brief Opens the View Alarms window to display active alarms.
     */
    void openViewAlarms();

    /**
     * @brief Handles a newly set alarm.
     * @param time The time of the alarm.
     * @param repeat The repeat setting of the alarm.
     * @param label The label for the alarm.
     * @param sound The sound associated with the alarm.
     */
    void handleAlarmSet(QTime time, QString repeat, QString label, QString sound);

    /**
     * @brief Checks active alarms and triggers notifications when an alarm matches the current time.
     */
    void checkAlarms(); 

    /**
     * @brief Snoozes a triggered alarm for a specified duration.
     * @param index The index of the alarm in the list.
     * @param minutes The number of minutes to snooze the alarm.
     */
    void snoozeAlarm(int index, int minutes);
    void playAlarmSound(const QString &soundName); 
    void stopAlarmSound(); 

private:
    QPushButton *setAlarmButton;  //< Button to open the Set Alarm window 
    QPushButton *viewAlarmsButton; //< Button to open the View Alarms window 
    ViewAlarm *viewAlarmWindow; //< Pointer to the View Alarm window 
    ClockWidget *clockWidget; //< Widget displaying the current time 
    QList<QTime> alarms; //< List of active alarm times 
    QList<QString> alarmLabels; //< List of labels associated with alarms 
    QList<QString> alarmRepeats; //<Stores repeat setting
    QList<QString> alarmSounds; //< Stores sound choices for alarms
    QSound *alarmPlayer = nullptr; //< Pointer to the QSound object that plays the alarm sound
    QSet<QString> dismissedToday; //<Track dismissed alarms (by label + date)
    QTimer *alarmCheckTimer; //< Timer that checks alarms every second 
    QList<bool> alarmIsSnoozed; //< Boolean for snoozing an alarm
    QVector<QTime> originalAlarmTimes; //< Keep track of original alarm time set 
};

#endif // MAINWINDOW_H
