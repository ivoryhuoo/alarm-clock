#include "clockwidget.h"

ClockWidget::ClockWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    clockDisplay = new QLCDNumber(this);
    clockDisplay->setDigitCount(8);
    layout->addWidget(clockDisplay);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ClockWidget::updateTime);
    timer->start(1000);

    updateTime();
}

void ClockWidget::updateTime() {
    clockDisplay->display(QTime::currentTime().toString("hh:mm:ss"));
}
