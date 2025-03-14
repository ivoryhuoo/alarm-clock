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
#include <QListWidget>
#include <QTime>

/**
 * @brief The ViewAlarm class provides a GUI for displaying active alarms.
 * 
 * @details This class extends QWidget and presents a list of active alarms in a QListWidget.
 * Users can view alarms with associated labels and close the window when needed.
 */

class ViewAlarm : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs a ViewAlarm widget.
     * 
     * @param[in] parent Pointer to the parent widget. Defaults to nullptr.
     */

    explicit ViewAlarm(QWidget *parent = nullptr);

    /**
     * @brief Updates the alarm list displayed in the widget.
     * 
     * @details This function clears the existing list and populates it with 
     * new alarms and their labels.
     * 
     * @param[in] alarms A list of QTime objects representing alarm times.
     * @param[in] labels A list of QString objects representing alarm labels.
     */

    void updateAlarmList(const QList<QTime> &alarms, const QList<QString> &labels); // New method

private:
    QListWidget *alarmListWidget; /**< Widget to display the list of alarms. */
};

#endif // VIEWALARM_H
