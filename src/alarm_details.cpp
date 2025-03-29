/**
 * @file alarm_details.cpp
 * @brief Implementation file for the AlarmDetails class.
 *
 * This file contains the implementation of the AlarmDetails class, which
 * provides a dialog for modifying or deleting an alarm.
 *
 * @author Group 27
 * @date Sunday, March 30
 */

#include "alarm_details.h"
#include <QDebug>


/**
 * @brief Constructs the AlarmDetails window.
 *
 * Initializes the alarm modification interface, allowing users to update or delete an alarm.
 *
 * @param time The alarm's time.
 * @param repeat The alarm's repeat setting.
 * @param label The alarm's label.
 * @param sound The alarm's sound setting.
 * @param parent The parent widget (default is nullptr).
 */
AlarmDetails::AlarmDetails(QTime time, QString repeat, QString label, QString sound, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Modify Alarm");

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Time Selection
    layout->addWidget(new QLabel("Change Time:"));
    timeEdit = new QTimeEdit(time, this);
    timeEdit->setDisplayFormat("HH:mm");
    layout->addWidget(timeEdit);

    // Repeat Dropdown
    layout->addWidget(new QLabel("Repeat:"));
    repeatComboBox = new QComboBox(this);
    repeatComboBox->addItem("Never");
    repeatComboBox->addItem("Every Sunday");
    repeatComboBox->addItem("Every Monday");
    repeatComboBox->addItem("Every Tuesday");
    repeatComboBox->addItem("Every Wednesday");
    repeatComboBox->addItem("Every Thursday");
    repeatComboBox->addItem("Every Friday");
    repeatComboBox->addItem("Every Saturday");
    repeatComboBox->setCurrentText(repeat);
    layout->addWidget(repeatComboBox);

    // Label Input
    layout->addWidget(new QLabel("Change Label:"));
    labelEdit = new QLineEdit(label, this);
    layout->addWidget(labelEdit);

    // Sound Dropdown
    layout->addWidget(new QLabel("Sound:"));
    soundComboBox = new QComboBox(this);
    soundComboBox->addItem("Classic");
    soundComboBox->addItem("Beep");
    soundComboBox->addItem("Rooster");

    soundComboBox->setCurrentText(sound);
    layout->addWidget(soundComboBox);

    // Buttons
    modifyButton = new QPushButton("Modify Alarm", this);
    deleteButton = new QPushButton("Delete Alarm", this);
    closeButton = new QPushButton("Close", this);

    //Create button layout which holds modify, delete and close buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(modifyButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(closeButton);

    //Include button layout to main layout
    layout->addLayout(buttonLayout);

    //Connect button signals to their slots
    connect(modifyButton, &QPushButton::clicked, this, &AlarmDetails::modifyAlarm);
    connect(deleteButton, &QPushButton::clicked, this, &AlarmDetails::onDeleteClicked);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::close);

    setLayout(layout);
}

/**
 * @brief Handles the modification of the alarm.
 * Emits a signal with the updated alarm details and closes the dialog.
 */

void AlarmDetails::modifyAlarm() {
    qDebug() << "[MODIFY ALARM WINDOW] Emitting repeat value:" << repeatComboBox->currentText();
    emit alarmModified(timeEdit->time(), repeatComboBox->currentText(), labelEdit->text(), soundComboBox->currentText());
    close(); // Close the dialog
}

/**
 * @brief Handles the deletion of the alarm.
 * Emits a signal with the alarm label and closes the dialog.
 */

void AlarmDetails::onDeleteClicked() {
    emit alarmDeleted(labelEdit->text()); // Emit signal with alarm label
    close(); // Close the dialog
}
