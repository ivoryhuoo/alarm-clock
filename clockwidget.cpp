/**
 * @file clockwidget.cpp
 * @brief Implementation of the ClockWidget class.
 * 
 * This file defines the ClockWidget class, which displays the current time
 * using an LCD-style digital clock. The time updates every second.
 * 
 * The widget consists of:
 * - An LCD display to show the time.
 * - A timer that triggers an update every second.
 * 
 * @author Group 27
 * @date Friday, March 14
 */

#include "clockwidget.h"

/**
 * @brief Constructs a ClockWidget instance.
 * 
 * Initializes the LCD clock display and sets up a timer to update the time
 * every second.
 * 
 * @param parent Pointer to the parent QWidget, if any.
 */
ClockWidget::ClockWidget(QWidget *parent) : QWidget(parent) {
    // Create a vertical layout for the widget
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Initialize the LCD display for showing the time
    clockDisplay = new QLCDNumber(this);
    clockDisplay->setDigitCount(8); // Set the display to show 8 characters (hh:mm:ss)

    // Add the LCD display to the layout
    layout->addWidget(clockDisplay);

    // Create a timer that triggers time updates every second
    QTimer *timer = new QTimer(this);

    // Connect the timer's timeout signal to the updateTime() slot
    connect(timer, &QTimer::timeout, this, &ClockWidget::updateTime);

    // Start the timer with a 1-second interval
    timer->start(1000);

    // Immediately update the time when the widget is created
    updateTime();
}

/**
 * @brief Updates the displayed time.
 * 
 * Retrieves the current system time and updates the LCD display
 * with the current time in "hh:mm:ss" format.
 */
void ClockWidget::updateTime() {
    // Get the current system time and format it as "hh:mm:ss"
    QString currentTime = QTime::currentTime().toString("hh:mm:ss");

    // Display the formatted time on the LCD
    clockDisplay->display(currentTime);
}