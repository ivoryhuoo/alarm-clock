/**
 * @file ClockWidget.h
 * @brief Header file for the ClockWidget class.
 *
 * This file defines the ClockWidget class, which displays the current time
 * and allows users to change the timezone.
 *
 * @author Group 27
 * @date Sunday, March 30
 */

#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>
#include <QLCDNumber>
#include <QVBoxLayout>
#include <QTimer>
#include <QTime>
#include <QTimeZone>
#include <QComboBox>
#include <QLabel>

/**
 * @class ClockWidget
 * @brief A widget that displays the current time and supports timezone changes.
 *
 * The ClockWidget class provides a real-time digital clock with a display.
 * It includes a dropdown menu for selecting different timezones.
 */

class ClockWidget : public QWidget {
    Q_OBJECT

public:

    /**
     * @brief Constructs a ClockWidget instance.
     *
     * Initializes the clock display and timezone selection dropdown.
     *
     * @param parent The parent widget (default is nullptr).
     */

    explicit ClockWidget(QWidget *parent = nullptr);

private slots:

    /**
     * @brief Updates the displayed time.
     *
     * This slot is triggered periodically by a timer to refresh the time display.
     */

    void updateTime();

    /**
     * @brief Updates the displayed time based on the selected timezone.
     *
     * This slot is triggered when the user selects a new timezone from the dropdown.
     *
     * @param timezoneId The ID of the selected timezone.
     */

    void changeTimezone(const QString &timezoneId); 

private:
    QLCDNumber *clockDisplay; ///< Display for showing the current time
    QComboBox *timezoneSelector; // Dropdown for timezone selection
    QLabel *timezoneLabel; ///< Label for displaying timezone information.
    QTimeZone currentTimeZone; ///< Stores the currently selected timezone.
};

#endif // CLOCKWIDGET_H
