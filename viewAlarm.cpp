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
#include <QHBoxLayout>

/**
 * @brief Constructs a ViewAlarm window.
 */
ViewAlarm::ViewAlarm(QWidget *parent) : QWidget(parent) {
    setWindowTitle("View Alarms");
    setWindowFlags(Qt::Window);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Active Alarms:", this);
    mainLayout->addWidget(titleLabel);

    // Create layout to hold alarms as buttons
    alarmsLayout = new QVBoxLayout();
    mainLayout->addLayout(alarmsLayout);

    QPushButton *closeButton = new QPushButton("Close", this);
    mainLayout->addWidget(closeButton);
    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

    setLayout(mainLayout);
}

/**
 * @brief Updates the displayed alarm list, replacing each alarm with a styled button inside a frame.
 */
void ViewAlarm::updateAlarmList(const QList<QTime> &alarms, const QList<QString> &labels) {
    // Clear old alarms
    QLayoutItem *child;
    while ((child = alarmsLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    // Add each alarm as a separate button inside a frame
    for (int i = 0; i < alarms.size(); ++i) {
        QString alarmText = labels[i] + " - " + alarms[i].toString("HH:mm");

        // Create a frame for styling
        QFrame *frame = new QFrame(this);
        frame->setFrameShape(QFrame::Box);
        frame->setStyleSheet("QFrame { background-color: #333; border-radius: 10px; padding: 8px; }");

        QHBoxLayout *frameLayout = new QHBoxLayout(frame);
        QPushButton *alarmButton = new QPushButton(alarmText, frame);
        alarmButton->setStyleSheet("QPushButton { background-color: #bb86fc; color: white; border-radius: 5px; padding: 5px; }");

        frameLayout->addWidget(alarmButton);
        alarmsLayout->addWidget(frame);
    }
}
