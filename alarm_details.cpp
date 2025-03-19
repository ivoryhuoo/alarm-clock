#include "alarm_details.h"

/**
 * @brief Constructs the AlarmDetails window.
 * @param alarmLabel The label of the alarm to display.
 */
AlarmDetails::AlarmDetails(QString alarmLabel, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Alarm Details");
    setFixedSize(250, 150);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    alarmLabelDisplay = new QLabel("Alarm: " + alarmLabel, this);
    mainLayout->addWidget(alarmLabelDisplay);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    
    deleteButton = new QPushButton("Delete", this);
    closeButton = new QPushButton("Close", this);

    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(closeButton);

    mainLayout->addLayout(buttonLayout);

    connect(closeButton, &QPushButton::clicked, this, &QDialog::close);
    connect(deleteButton, &QPushButton::clicked, this, &AlarmDetails::onDeleteClicked);

    setLayout(mainLayout);
}

/**
 * @brief Handles the deletion of the alarm.
 */
void AlarmDetails::onDeleteClicked() {
    emit alarmDeleted(alarmLabelDisplay->text().remove("Alarm: ")); // Emit signal with alarm label
    close(); // Close the dialog
}