#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTime>
#include <QTimer>  // Include QTimer
#include "clockwidget.h"
#include "setalarmwindow.h"
#include "viewAlarm.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    QList<QTime> getAlarms() const;
    QList<QString> getAlarmLabels() const;

private slots:
    void openSetAlarm();
    void openViewAlarms();
    void handleAlarmSet(QTime time, QString repeat, QString label, QString sound);
    void checkAlarms();  // Function to check alarms every second
    void snoozeAlarm(int index, int minutes);  // Snooze function

private:
    QPushButton *setAlarmButton;
    QPushButton *viewAlarmsButton;
    ViewAlarm *viewAlarmWindow;
    ClockWidget *clockWidget;

    QList<QTime> alarms;
    QList<QString> alarmLabels;

    QTimer *alarmCheckTimer;  // Declare alarmCheckTimer
};

#endif // MAINWINDOW_H
