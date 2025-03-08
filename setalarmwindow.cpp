#include "setalarmwindow.h"

SetAlarmWindow::SetAlarmWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Set Alarm");
    
    QVBoxLayout *layout = new QVBoxLayout(this);

    timeEdit = new QTimeEdit(this);
    timeEdit->setDisplayFormat("HH:mm"); // 24-hour format
    saveButton = new QPushButton("Save Alarm", this);
    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color: red;"); // Show errors in red

    layout->addWidget(timeEdit);
    layout->addWidget(saveButton);
    layout->addWidget(errorLabel);

    connect(saveButton, &QPushButton::clicked, this, &SetAlarmWindow::saveAlarm);
}

void SetAlarmWindow::saveAlarm() {
    QTime selectedTime = timeEdit->time();
    
    if (!selectedTime.isValid()) {
        errorLabel->setText("Invalid time! Please enter a valid time.");
        return;
    }

    emit alarmSet(selectedTime); // Send the selected time to MainWindow
    accept(); // Close the dialog
}
