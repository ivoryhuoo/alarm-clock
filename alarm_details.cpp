#include "alarm_details.h"

/**
 * @brief Constructs the AlarmDetails window.
 * @param alarmLabel The label of the alarm to display.
 */
AlarmDetails::AlarmDetails(QString alarmLabel, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Alarm Details");
    setFixedSize(250, 150);

    QVBoxLayout *layout = new QVBoxLayout(this);

    alarmLabelDisplay = new QLabel("Alarm: " + alarmLabel, this);
    layout->addWidget(alarmLabelDisplay);

    closeButton = new QPushButton("Close", this);
    layout->addWidget(closeButton);

    connect(closeButton, &QPushButton::clicked, this, &QDialog::close);

    setLayout(layout); // Ensure layout is applied
}
