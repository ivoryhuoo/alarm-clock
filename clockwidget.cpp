#include "clockwidget.h"

ClockWidget::ClockWidget(QWidget *parent) : QWidget(parent), currentTimeZone(QTimeZone::systemTimeZone()) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);   // Removes extra space between widgets
    layout->setContentsMargins(0, 0, 0, 0); // Removes margins around the layout

    // LCD Clock Display
    clockDisplay = new QLCDNumber(this);
    clockDisplay->setDigitCount(8);
    layout->addWidget(clockDisplay);

    // Label for Timezone Selector
    timezoneLabel = new QLabel("Change Time Zone:", this);
    layout->addWidget(timezoneLabel);

    // Timezone Selector
    timezoneSelector = new QComboBox(this);
    QStringList timezones;
    for (const QByteArray &tzId : QTimeZone::availableTimeZoneIds()) {
        timezones.append(QString(tzId));
    }
    timezoneSelector->addItems(timezones);
    timezoneSelector->setCurrentText(QString(currentTimeZone.id())); // Set default timezone
    layout->addWidget(timezoneSelector);

    // Timer for Clock Update
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ClockWidget::updateTime);
    connect(timezoneSelector, &QComboBox::currentTextChanged, this, &ClockWidget::changeTimezone);

    timer->start(1000);
    updateTime();
}

// Updates the clock based on the selected timezone
void ClockWidget::updateTime() {
    QDateTime currentTime = QDateTime::currentDateTimeUtc().toTimeZone(currentTimeZone);
    clockDisplay->display(currentTime.toString("hh:mm:ss"));
}

// Updates the timezone when a new one is selected
void ClockWidget::changeTimezone(const QString &timezoneId) {
    currentTimeZone = QTimeZone(timezoneId.toUtf8());
    updateTime(); // Immediately update the time display
}
