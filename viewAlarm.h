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
#include <QFile>
#include <QTextStream>

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
    void removeAlarm(const QString &alarmLabel);
};

#endif // VIEWALARM_H
