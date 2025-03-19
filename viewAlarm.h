/**
 * @file viewAlarm.h
 * @brief Definition of the ViewAlarm class.
 * 
 * This file defines the ViewAlarm class, which provides a graphical interface 
 * for displaying a list of active alarms with their associated labels.
 * 
 * The widget consists of:
 * - A QLabel for the title.
 * - A QListWidget to display the alarms.
 * - A QPushButton to close the window.
 * 
 * @author Group 27
 * @date Friday, March 14
 */
#ifndef VIEWALARM_H
#define VIEWALARM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QTime>
#include <QMap>
#include <QScrollArea>

/**
 * @brief The ViewAlarm class provides a GUI for displaying active alarms as individual buttons.
 */
class ViewAlarm : public QWidget {
    Q_OBJECT

public:
    explicit ViewAlarm(QWidget *parent = nullptr);
    void updateAlarmList(const QList<QTime> &alarms, const QList<QString> &labels);

private:
    QVBoxLayout *alarmsLayout; /**< Layout to hold alarm buttons */
    QMap<QPushButton*, QString> alarmButtons; /**< Map buttons to labels */

private slots:
    void handleAlarmClick();
};

#endif // VIEWALARM_H
