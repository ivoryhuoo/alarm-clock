/**
 * @file clockwidget.cpp
 * @brief Implementation file for the ClockWidget class.
 *
 * This file contains the implementation of the ClockWidget class, which
 * provides a digital clock with a selectable timezone.
 *
 * @author Group 27
 * @date Sunday, March 30
 */

#include "clockwidget.h"

/**
 * @brief Constructs the ClockWidget.
 * Initializes the clock display, timezone selector, and updates the time periodically.
 * @param parent The parent widget (default is nullptr).
 */

ClockWidget::ClockWidget(QWidget *parent) : QWidget(parent), currentTimeZone(QTimeZone::systemTimeZone()) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);   // Removes extra space between widgets
    layout->setContentsMargins(0, 0, 0, 0); // Removes margins around the layout

    // Clock Display
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

/**
 * @brief Updates the clock display based on the selected timezone.
 */
void ClockWidget::updateTime() {
    QDateTime currentTime = QDateTime::currentDateTimeUtc().toTimeZone(currentTimeZone);
    clockDisplay->display(currentTime.toString("hh:mm:ss"));
}

/**
 * @brief Updates the timezone when a new one is selected.
 *
 * @param timezoneId The ID of the new timezone.
 */
void ClockWidget::changeTimezone(const QString &timezoneId) {
    currentTimeZone = QTimeZone(timezoneId.toUtf8());
    updateTime(); // Immediately update the time display
}
