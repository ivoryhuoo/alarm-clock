#ifndef VIEWALARM_H
#define VIEWALARM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QTime>

class ViewAlarm : public QWidget {
    Q_OBJECT

public:
    explicit ViewAlarm(QWidget *parent = nullptr);
    void updateAlarmList(const QList<QTime> &alarms, const QList<QString> &labels); // New method

private:
    QListWidget *alarmListWidget;
};

#endif // VIEWALARM_H
