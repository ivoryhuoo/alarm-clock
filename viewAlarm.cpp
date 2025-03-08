#include "viewAlarm.h"

ViewAlarm::ViewAlarm(QWidget *parent) : QWidget(parent) {
    setWindowTitle("View Alarms");
    setWindowFlags(Qt::Window);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Active Alarms:", this);
    layout->addWidget(titleLabel);

    // List widget to display alarms
    alarmListWidget = new QListWidget(this);
    layout->addWidget(alarmListWidget);

    QPushButton *closeButton = new QPushButton("Close", this);
    layout->addWidget(closeButton);

    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

    setLayout(layout);
}

// Method to update alarm list
void ViewAlarm::updateAlarmList(const QList<QTime> &alarms, const QList<QString> &labels) {
    alarmListWidget->clear(); // Clear old data

    for (int i = 0; i < alarms.size(); ++i) {
        QString alarmText = labels[i] + " - " + alarms[i].toString("HH:mm");
        alarmListWidget->addItem(alarmText);
    }
}
