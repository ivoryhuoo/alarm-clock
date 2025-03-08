#ifndef SETALARMWINDOW_H
#define SETALARMWINDOW_H

#include <QDialog>
#include <QTimeEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

class SetAlarmWindow : public QDialog {
    Q_OBJECT

public:
    explicit SetAlarmWindow(QWidget *parent = nullptr);

signals:
    void alarmSet(QTime time, QString repeat, QString label, QString sound); // Updated Signal

private slots:
    void saveAlarm();

private:
    QTimeEdit *timeEdit;
    QComboBox *repeatComboBox;
    QLineEdit *labelEdit;
    QComboBox *soundComboBox;
    QPushButton *saveButton;
    QLabel *errorLabel;
};

#endif // SETALARMWINDOW_H
