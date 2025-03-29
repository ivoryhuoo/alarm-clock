/**
 * @file setalarmwindow.cpp
 * @brief Implementation of the SetAlarmWindow class.
 *
 * This file contains the implementation of the SetAlarmWindow class, which provides a dialog
 * for setting an alarm. The user can select a time, a repeat option, a label for the alarm, 
 * and a sound. The settings are validated before being emitted as a signal to the main window.
 *
 * @author Group 27
 * @date Friday, March 14
 */

#include "setalarmwindow.h"

/**
 * @brief Constructs the SetAlarmWindow dialog and initializes its components.
 *
 * This constructor sets up the dialog's layout and widgets, including the time selection, 
 * repeat options, label input, sound selection, and save button. It also connects the save 
 * button to the `saveAlarm` slot for handling the alarm saving functionality.
 *
 * @param parent The parent widget, default is nullptr.
 */

SetAlarmWindow::SetAlarmWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Set Alarm");
    this->resize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Time Selection
    timeEdit = new QTimeEdit(this);
    timeEdit->setDisplayFormat("HH:mm"); // 24-hour format

    // Repeat Alarm Dropdown
    repeatComboBox = new QComboBox(this);
    repeatComboBox->addItem("Never");
    repeatComboBox->addItem("Every Sunday");
    repeatComboBox->addItem("Every Monday");
    repeatComboBox->addItem("Every Tuesday");
    repeatComboBox->addItem("Every Wednesday");
    repeatComboBox->addItem("Every Thursday");
    repeatComboBox->addItem("Every Friday");
    repeatComboBox->addItem("Every Saturday");

    // Alarm Label
    labelEdit = new QLineEdit(this);
    labelEdit->setPlaceholderText("Enter alarm name...");

    // Sound Selection Dropdown 
    soundComboBox = new QComboBox(this);
    // options for sound
    soundComboBox->addItem("Classic");
    soundComboBox->addItem("Beep");
    soundComboBox->addItem("Rooster");

    // Save Button
    saveButton = new QPushButton("Save Alarm", this);
    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color: red;"); // Show errors in red

    // Add Widgets to Layout
    layout->addWidget(new QLabel("Select Time:"));
    layout->addWidget(timeEdit);
    
    layout->addWidget(new QLabel("Repeat:"));
    layout->addWidget(repeatComboBox);
    
    layout->addWidget(new QLabel("Label:"));
    layout->addWidget(labelEdit);
    
    layout->addWidget(new QLabel("Sound:"));
    layout->addWidget(soundComboBox);
    
    layout->addWidget(saveButton);
    layout->addWidget(errorLabel);

    connect(saveButton, &QPushButton::clicked, this, &SetAlarmWindow::saveAlarm);
}

/**
 * @brief Handles the saving of the alarm settings.
 *
 * This function validates the selected time and label, then emits the `alarmSet` signal
 * with the selected time, repeat option, label, and sound. If the time or label is invalid,
 * an error message is displayed.
 */
void SetAlarmWindow::saveAlarm() {
    QTime selectedTime = timeEdit->time();
    QString repeatOption = repeatComboBox->currentText();
    QString alarmLabel = labelEdit->text();
    QString selectedSound = soundComboBox->currentText();

    if (!selectedTime.isValid()) {
        errorLabel->setText("Invalid time! Please enter a valid time.");
        return;
    }

    if (alarmLabel.isEmpty()) {
        errorLabel->setText("Please enter a label for the alarm.");
        return;
    }

    emit alarmSet(selectedTime, repeatOption, alarmLabel, selectedSound); // Send all data to MainWindow
    accept(); // Close the dialog
}
