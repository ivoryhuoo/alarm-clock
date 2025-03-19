#ifndef ALARMDETAILS_H
#define ALARMDETAILS_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class AlarmDetails : public QDialog {
    Q_OBJECT

public:
    explicit AlarmDetails(QString alarmLabel, QWidget *parent = nullptr);

signals:
    void alarmDeleted(const QString &alarmLabel); // Signal emitted when an alarm is deleted

private slots:
    void onDeleteClicked();

private:
    QLabel *alarmLabelDisplay;
    QPushButton *closeButton;
    QPushButton *deleteButton;
};

#endif // ALARMDETAILS_H
