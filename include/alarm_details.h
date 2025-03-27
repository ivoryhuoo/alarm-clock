/**
 * @file alarm_details.h
 * @brief  Header file for the AlarmDetails class.
 * 
 * This file contains the definition of the AlarmDetails class, which provides
 * a dialog for modifying and deleting alarm details.
 * 
 * @author Group 27
 * @date Sunday, March 30
 */

#ifndef ALARMDETAILS_H
#define ALARMDETAILS_H

#include <QDialog>
#include <QTimeEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

/**
 * @class AlarmDetails
 * @brief Dialog for modifying and deleting alarm details.
 * 
 * The AlarmDetails class allows users to edit alarm settings such as time,
 * repeat frequency, label, and sound. It emits signals when alarms are
 * modified or deleted.
 */

class AlarmDetails : public QDialog {
    Q_OBJECT

public:
/**
     * @brief Constructs an AlarmDetails dialog.
     * 
     * Initializes the dialog with the given alarm parameters.
     * 
     * @param time The initial time of the alarm.
     * @param repeat The repeat setting of the alarm.
     * @param label The label of the alarm.
     * @param sound The selected alarm sound.
     * @param parent The parent widget (default is nullptr).
     */

    explicit AlarmDetails(QTime time, QString repeat, QString label, QString sound, QWidget *parent = nullptr);

signals:
    /**
     * @brief Emitted when an alarm is modified.
     * @param time The updated time of the alarm.
     * @param repeat The updated repeat setting.
     * @param label The updated alarm label.
     * @param sound The updated alarm sound.
     */

    void alarmModified(QTime time, QString repeat, QString label, QString sound); 
    
     /**
     * @brief Emitted when an alarm is deleted.
     * @param alarmLabel The label of the deleted alarm.
     */

    void alarmDeleted(const QString &alarmLabel); 
    

private slots:
    /**
     * @brief Handles modifying an alarm.
     * 
     * This slot is triggered when the modify button is clicked, updating
     * the alarm details and emitting the alarmModified signal.
     */
    void modifyAlarm();  

    /**
     * @brief Handles deleting an alarm.
     * 
     * This slot is triggered when the delete button is clicked, emitting
     * the alarmDeleted signal.
     */

    void onDeleteClicked(); // Handles deleting an alarm

private:
    QTimeEdit *timeEdit; ///< Widget for selecting the alarm time
    QComboBox *repeatComboBox; ///< Dropdown for selecting the repeat frequency.
    QLineEdit *labelEdit; ///< Input field for setting the alarm label.
    QComboBox *soundComboBox; ///< Dropdown for selecting the alarm sound.
    QPushButton *modifyButton;  ///< Button for modifying the alarm.
    QPushButton *deleteButton;  ///< Button for deleting the alarm.
    QPushButton *closeButton; ///< Button for closing the dialog.
};

#endif // ALARMDETAILS_H
