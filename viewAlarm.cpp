/**
 * @file viewAlarm.cpp
 * @brief Implementation of the ViewAlarm class.
 * 
 * This file implements the ViewAlarm class, which provides a GUI for viewing 
 * a list of active alarms. The class allows users to see alarms along with 
 * their labels and close the window when needed.
 * 
 * The widget consists of:
 * - A QLabel for the title.
 * - A QListWidget to display the alarms.
 * - A QPushButton to close the window.
 * 
 * @author Group 27
 * @date Friday, March 14
 */
#include "viewAlarm.h"

/**
 * @brief Constructs a ViewAlarm window.
 * 
 * @details Initializes the alarm viewing window with a title, a list widget
 * to display alarms, and a close button.
 * 
 * @param[in] parent Pointer to the parent widget. Defaults to nullptr.
 */

ViewAlarm::ViewAlarm(QWidget *parent) : QWidget(parent) {
    setWindowTitle("View Alarms"); /**< Sets the window title to "View Alarms". */
    setWindowFlags(Qt::Window);

    QVBoxLayout *layout = new QVBoxLayout(this); /**< Creates a vertical layout for the window. */

    QLabel *titleLabel = new QLabel("Active Alarms:", this); /**< Creates a label displaying "Active Alarms:". */
    layout->addWidget(titleLabel);

   
    alarmListWidget = new QListWidget(this); /**< Initializes the QListWidget to display alarms. */
    layout->addWidget(alarmListWidget);

    QPushButton *closeButton = new QPushButton("Close", this); /**< Creates a "Close" button. */
    layout->addWidget(closeButton);

    // Connect close button to the close() function of QWidget
    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

    setLayout(layout);
}

/**
 * @brief Updates the displayed alarm list.
 * 
 * @details Clears the existing alarm list and repopulates it with new alarms 
 * and their associated labels.
 * 
 * @param[in] alarms A QList of QTime objects representing alarm times.
 * @param[in] labels A QList of QString objects representing alarm labels.
 */

void ViewAlarm::updateAlarmList(const QList<QTime> &alarms, const QList<QString> &labels) {

    alarmListWidget->clear(); /**< Clears the existing alarm list to avoid duplicates. */

    for (int i = 0; i < alarms.size(); ++i) {

        QString alarmText = labels[i] + " - " + alarms[i].toString("HH:mm"); /**< Formats the alarm display text. */

        alarmListWidget->addItem(alarmText);
    }
}
