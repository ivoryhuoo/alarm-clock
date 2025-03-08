#ifndef SETALARMWINDOW_H
#define SETALARMWINDOW_H

#include <QDialog>
#include <QTimeEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class SetAlarmWindow : public QDialog {
    Q_OBJECT

public:
    explicit SetAlarmWindow(QWidget *parent = nullptr);

signals:
    void alarmSet(QTime time); // Signal to notify MainWindow

private slots:
    void saveAlarm();

private:
    QTimeEdit *timeEdit;
    QPushButton *saveButton;
    QLabel *errorLabel;
};

#endif // SETALARMWINDOW_H
