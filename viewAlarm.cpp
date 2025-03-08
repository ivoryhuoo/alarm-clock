#include "viewAlarm.h"

ViewAlarm::ViewAlarm(QWidget *parent) : QWidget(parent) {
    setWindowTitle("View Alarms");
    setWindowFlags(Qt::Window);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *closeButton = new QPushButton("Close", this);
    layout->addWidget(closeButton);

    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

    setLayout(layout);
}
