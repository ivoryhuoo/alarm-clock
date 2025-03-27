/**
 * @file ViewAlarm.h
 * @brief Header file for the ViewAlarm class
 * 
 * This file defines the ViewAlarm class, which provides a GUI for displaying active alarms.
 * 
 * @author Group27
 * @date Sunday, March 30
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
#include <QFile>
#include <QTextStream>
#include <QSoundEffect>

struct Alarm {
    QTime time;
    QString label;
    QString sound;  // "ring1", "ring2", or "ring3"
    QString repeat; // "Never", "Daily", etc.
    bool isActive = true;

    QString toString() const {
        return time.toString("hh:mm ap") + " - " + label + 
               " (" + sound + ", " + repeat + ")";
    }
};

/**
 * @class ViewAlarm
 * @brief A widget for displaying and managing active alarms.
 *
 * The ViewAlarm class provides a user interface for listing active alarms as buttons.
 * Users can interact with these alarms through the GUI.
 */
class ViewAlarm : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs a ViewAlarm instance.
     *
     * Initializes the alarm display layout and related UI components.
     *
     * @param parent The parent widget (default is nullptr).
     */
    explicit ViewAlarm(QWidget *parent = nullptr);

    /**
     * @brief Updates the list of alarms displayed.
     *
     * This function refreshes the UI to show updated alarm times and labels.
     *
     * @param alarms List of alarm times.
     * @param labels List of alarm labels.
     */

    void updateAlarmList(const QList<Alarm> &alarms);

private:
    QVBoxLayout *alarmsLayout; /**< Layout to hold alarm buttons */
    QMap<QPushButton*, Alarm> alarmButtons; /**< Map buttons to labels */
    QList<Alarm> alarms; /**< Stores alarms */
    QList<QString> alarmLabels; /**< Stores alarm labels */
    QList<QString> alarmRepeats; /**< Stores alarm repeat settings */

signals:
    void alarmModified(const Alarm &alarm);
    void alarmDeleted(const QString &label);
    

private slots:
    /**
     * @brief Handles user interactions with an alarm button.
     *
     * This slot is triggered when an alarm button is clicked.
     */
    void handleAlarmClick();

    /**
     * @brief Removes an alarm from the list.
     *
     * This function removes an alarm entry based on the provided label.
     *
     * @param alarmLabel The label of the alarm to be removed.
     */
    void removeAlarm(const QString &alarmLabel);
};

#endif // VIEWALARM_H
