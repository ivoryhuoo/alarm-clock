/**
 * @file clockwidget.h
 * @brief Declaration of the ClockWidget class.
 * 
 * This file contains the declaration of the ClockWidget class, which provides
 * a digital clock display that updates in real-time.
 * 
 * The class uses:
 * - `QLCDNumber` to display the time.
 * - `QTimer` to update the time every second.
 * - `QTime` to fetch the current system time.
 * 
 * @author Group 27
 * @date Friday, March 14
 */

#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>
#include <QLCDNumber>
#include <QVBoxLayout>
#include <QTimer>
#include <QTime>

/**
 * @class ClockWidget
 * @brief A widget that displays a digital clock.
 * 
 * The ClockWidget class inherits from `QWidget` and provides a simple
 * LCD-style digital clock that updates every second.
 */
class ClockWidget : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs a ClockWidget instance.
     * 
     * Initializes the LCD display and starts a timer to update the time
     * every second.
     * 
     * @param parent Pointer to the parent QWidget, if any.
     */
    explicit ClockWidget(QWidget *parent = nullptr);

private slots:
    /**
     * @brief Updates the displayed time.
     * 
     * Retrieves the current system time and updates the LCD display
     * with the current time in "hh:mm:ss" format.
     */
    void updateTime();

private:
    QLCDNumber *clockDisplay; ///< Pointer to the LCD number display.
};

#endif // CLOCKWIDGET_H
