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
 * @headerfile setalarmwindow.h
 * @brief The SetAlarmWindow class provides a dialog for setting an alarm.
 *
 * @details
 * This class allows the user to set an alarm by selecting a time, repeat option, label, and sound.
 * The alarm settings can be saved and emitted to the main window.
 * 
 * @author Group 27
 * @date Friday, March 14
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
};

#endif // SETALARMWINDOW_H
