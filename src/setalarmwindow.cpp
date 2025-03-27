#include "setalarmwindow.h"

/**
 * @file setalarmwindow.cpp
 * @brief Constructs the SetAlarmWindow dialog and initializes its components.
 * @param parent The parent widget.
 *
 * @author Group 27
 * @date Friday, March 14
 */

SetAlarmWindow::SetAlarmWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Set Alarm");

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
    // Placeholder names, modify these 
    soundComboBox->addItem("Default");
    soundComboBox->addItem("Beep");
    soundComboBox->addItem("Chime");
    soundComboBox->addItem("Birdsong");
    soundComboBox->addItem("Classic Alarm");

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
 * @details
 * This function validates the selected time and label, then emits the `alarmSet` signal
 * with the selected time, repeat option, label, and sound. If the time or label is invalid,
 * an error message is displayed.
 *
 * @author Group 27
 * @date March 14
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
