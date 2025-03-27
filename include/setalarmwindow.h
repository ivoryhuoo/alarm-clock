/**
 * @file setalarmwindow.h
 * @brief Header file for the SetAlarmWindow class.
 * 
 * This file contains the declaration of the SetAlarmWindow class, which is a dialog that allows
 * the user to set an alarm. It includes options for selecting the time, repeat option, label, and sound.
 * The alarm settings can be saved and emitted to the main window.
 * 
 * @author Group 27
 * @date Friday, March 14
 */

#ifndef SETALARMWINDOW_H
#define SETALARMWINDOW_H

#include <QDialog>
#include <QTimeEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

/**
 * @class SetAlarmWindow
 * @brief The SetAlarmWindow class provides a dialog for setting an alarm.
 * 
 * The SetAlarmWindow class allows users to set an alarm by selecting a time, a repeat option, a label, and a sound.
 * The alarm settings are saved when the user clicks the save button. A signal is emitted to the main window with the 
 * alarm details, which include the time, repeat option, label, and sound.
 * 
 */

class SetAlarmWindow : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructs a SetAlarmWindow dialog.
     * @param parent The parent widget, default is nullptr.
     */
    explicit SetAlarmWindow(QWidget *parent = nullptr);

signals:
    /**
     * @brief Signal emitted when an alarm is set.
     * @param time The selected time for the alarm.
     * @param repeat The repeat option for the alarm.
     * @param label The label for the alarm.
     * @param sound The selected sound for the alarm.
     */
    void alarmSet(QTime time, QString repeat, QString label, QString sound); // Updated Signal

private slots:
    /**
     * @brief Slot to handle saving the alarm.
     */
    void saveAlarm();

private:
    QTimeEdit *timeEdit;         ///< Time selection widget. 
    QComboBox *repeatComboBox;  ///< Repeat option selection widget. 
    QLineEdit *labelEdit;        ///< Alarm label input widget. 
    QComboBox *soundComboBox;   ///< Sound selection widget. 
    QPushButton *saveButton;     ///< Button to save the alarm. 
    QLabel *errorLabel;         ///< Label to display error messages. 
}

#endif // SETALARMWINDOW_H
