/**
 * @file ViewAlarm.cpp
 * @brief The ViewAlarm class displays a list of active alarms in a scrollable window.
 * 
 * This class provides functionality to view, update, and delete alarms through an interactive UI.
 * 
 * @author Group 27
 * @date Sunday, March 30
 */


#include "viewAlarm.h"
#include "alarm_details.h"
#include <QHBoxLayout>
#include <QDebug>

/**
 * @brief Constructs a ViewAlarm window.
 * 
 * Initializes the window with a scrollable list of alarms and a close button.
 * 
 * @param parent The parent widget (default is nullptr).
 */

ViewAlarm::ViewAlarm(QWidget *parent) : QWidget(parent) {
    setWindowTitle("View Alarms");
    setWindowFlags(Qt::Window);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Active Alarms:", this);
    mainLayout->addWidget(titleLabel);

    // Scrollable area to hold buttons
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget *scrollWidget = new QWidget();
    alarmsLayout = new QVBoxLayout(scrollWidget);
    scrollWidget->setLayout(alarmsLayout);

    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea);

    // Close button
    QPushButton *closeButton = new QPushButton("Close", this);
    mainLayout->addWidget(closeButton);
    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

    setLayout(mainLayout);
}

/**
 * @brief Updates the displayed alarm list, replacing each alarm with a button.
 * 
 * This method clears the existing alarm buttons and repopulates the list based on the
 * provided newAlarms and newLabels.
 * 
 * @param newAlarms A list of QTime objects representing the alarm times.
 * @param newLabels A list of QString objects representing the alarm labels.
 */
void ViewAlarm::updateAlarmList(const QList<Alarm> &newAlarms) {
    qDebug() << "Updating alarm list. Total alarms:" << newAlarms.size();

    // Clear old buttons
    QLayoutItem *child;
    while ((child = alarmsLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }
    alarmButtons.clear();

    // Add each alarm as a separate button
    for (int i = 0; i < newAlarms.size(); ++i) {
        QString alarmText = newAlarms[i].label + " - " + newAlarms[i].time.toString("HH:mm");

        QPushButton *alarmButton = new QPushButton(alarmText, this);
        alarmButton->setStyleSheet("QPushButton { background-color: #bb86fc; color: white; border-radius: 5px; padding: 10px; }");
        connect(alarmButton, &QPushButton::clicked, this, &ViewAlarm::handleAlarmClick);

        alarmButtons.insert(alarmButton, newAlarms[i]); // Store button-label mapping
        alarmsLayout->addWidget(alarmButton);
    }
}


/**
 * @brief Handles alarm button clicks by opening a new window with alarm details.
 * 
 * This method retrieves the clicked alarm's details and opens an AlarmDetails
 * dialog, allowing the user to modify or delete the alarm.
 */

 void ViewAlarm::handleAlarmClick() {
    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton && alarmButtons.contains(senderButton)) {
        // Get the full Alarm object from the button mapping
        Alarm alarm = alarmButtons.value(senderButton);
        qDebug() << "Alarm clicked:" << alarm.toString();

        // Open AlarmDetails with the complete alarm data
        AlarmDetails *detailsWindow = new AlarmDetails(
            alarm.time,
            alarm.repeat,
            alarm.label,
            alarm.sound,  // Now using the actual sound from struct
            this
        );

        // Connect modifications
        connect(detailsWindow, &AlarmDetails::alarmModified, this, [=](QTime newTime, QString newRepeat, QString newLabel, QString newSound) {
            // Create updated alarm struct
            Alarm updatedAlarm = alarm;
            updatedAlarm.time = newTime;
            updatedAlarm.repeat = newRepeat;
            updatedAlarm.label = newLabel;
            updatedAlarm.sound = newSound;
            
            emit alarmModified(updatedAlarm);  // Emit signal with complete struct
        });

        // Connect deletions (unchanged)
        connect(detailsWindow, &AlarmDetails::alarmDeleted, this, &ViewAlarm::removeAlarm);

        detailsWindow->exec();
    }
}

/**
 * @brief Removes an alarm from the UI and the stored list.
 * 
 * This method deletes the alarm from both the UI and the internal alarm list
 * when the user chooses to remove an alarm.
 * 
 * @param alarmLabel The label of the alarm to be removed.
 */

void ViewAlarm::removeAlarm(const QString &alarmLabel) {
    // Find and remove the alarm from the buttons map
    for (auto it = alarmButtons.begin(); it != alarmButtons.end(); ++it) {
        if (it.value().label == alarmLabel) {  // Compare against the alarm's label
            qDebug() << "Removing alarm:" << alarmLabel;
            
            // Delete the button widget
            delete it.key();
            alarmButtons.erase(it);
            
            // Emit signal to notify MainWindow
            emit alarmDeleted(alarmLabel);
            break;
        }
    }
}
