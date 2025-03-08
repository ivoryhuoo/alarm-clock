#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "clockwidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void openSetAlarm();
    void openViewAlarms();
    void handleAlarmSet(QTime time);

private:
    ClockWidget *clockWidget;
    QPushButton *setAlarmButton;
    QPushButton *viewAlarmsButton;
    QList<QTime> alarms;
};

#endif // MAINWINDOW_H
