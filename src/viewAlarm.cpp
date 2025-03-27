#include "viewAlarm.h"
#include "alarm_details.h"
#include <QHBoxLayout>
#include <QDebug>

/**
 * @brief Constructs a ViewAlarm window.
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
 */
void ViewAlarm::updateAlarmList(const QList<QTime> &newAlarms, const QList<QString> &newLabels, const QList<QString> &newRepeats) {
    qDebug() << "Updating alarm list. Total alarms:" << newAlarms.size();

    // Update stored alarm lists
    alarms = newAlarms;
    alarmLabels = newLabels;
    alarmRepeats = newRepeats;


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
    for (int i = 0; i < alarms.size(); ++i) {
        QString alarmText = alarmLabels[i] + " - " + alarms[i].toString("HH:mm");

        QPushButton *alarmButton = new QPushButton(alarmText, this);
        alarmButton->setStyleSheet("QPushButton { background-color: #bb86fc; color: white; border-radius: 5px; padding: 10px; }");
        connect(alarmButton, &QPushButton::clicked, this, &ViewAlarm::handleAlarmClick);

        alarmButtons.insert(alarmButton, alarmLabels[i]); // Store button-label mapping
        alarmsLayout->addWidget(alarmButton);
    }
}


/**
 * @brief Handles alarm button clicks by opening a new window.
 */
void ViewAlarm::handleAlarmClick() {
    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton && alarmButtons.contains(senderButton)) {
        QString alarmLabel = alarmButtons.value(senderButton);
        qDebug() << "Alarm clicked:" << alarmLabel;

        int index = alarmLabels.indexOf(alarmLabel);
        if (index == -1) return; // If alarm is not found, return

        QTime alarmTime = alarms[index];

        // Open AlarmDetails with real alarm values
        QString repeat = alarmRepeats[index];
        AlarmDetails *detailsWindow = new AlarmDetails(alarmTime, repeat, alarmLabel, "Default", this);


        // Connect modifications
        connect(detailsWindow, &AlarmDetails::alarmModified, this, [=](QTime newTime, QString newRepeat, QString newLabel, QString newSound) {
            alarms[index] = newTime;
            alarmLabels[index] = newLabel;
            updateAlarmList(alarms, alarmLabels, alarmRepeats);
        });

        // Connect deletions
        connect(detailsWindow, &AlarmDetails::alarmDeleted, this, &ViewAlarm::removeAlarm);

        detailsWindow->exec();
    }
}


/**
 * @brief Removes an alarm from the UI and the file.
 */
void ViewAlarm::removeAlarm(const QString &alarmLabel) {
    qDebug() << "Removing alarm:" << alarmLabel;

    int index = alarmLabels.indexOf(alarmLabel);
    if (index == -1) return;

    alarms.removeAt(index);
    alarmLabels.removeAt(index);

    // Remove from UI
    for (auto it = alarmButtons.begin(); it != alarmButtons.end(); ++it) {
        if (it.value() == alarmLabel) {
            delete it.key(); // Delete the button
            alarmButtons.erase(it);
            break;
        }
    }

    updateAlarmList(alarms, alarmLabels, alarmRepeats);

}
