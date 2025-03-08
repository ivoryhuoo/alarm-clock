#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "clockwidget.h"
#include "setalarmwindow.h"
#include "viewAlarm.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void openSetAlarm();
    void openViewAlarms();
    void handleAlarmSet(QTime time, QString repeat, QString label, QString sound);

private:
    ClockWidget *clockWidget;
    QPushButton *setAlarmButton;
    QPushButton *viewAlarmsButton;
    ViewAlarm *viewAlarmWindow; // Pointer to the ViewAlarm window
};

#endif // MAINWINDOW_H
