#ifndef ALARMDETAILS_H
#define ALARMDETAILS_H

#include <QDialog>
#include <QTimeEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

class AlarmDetails : public QDialog {
    Q_OBJECT

public:
    explicit AlarmDetails(QTime time, QString repeat, QString label, QString sound, QWidget *parent = nullptr);

signals:
    void alarmModified(QTime time, QString repeat, QString label, QString sound); // Signal emitted when modifying the alarm
    void alarmDeleted(const QString &alarmLabel); // Signal emitted when an alarm is deleted

private slots:
    void modifyAlarm();  // Handles modifying an alarm
    void onDeleteClicked(); // Handles deleting an alarm

private:
    QTimeEdit *timeEdit;
    QComboBox *repeatComboBox;
    QLineEdit *labelEdit;
    QComboBox *soundComboBox;
    QPushButton *modifyButton;
    QPushButton *deleteButton;
    QPushButton *closeButton;
};

#endif // ALARMDETAILS_H
