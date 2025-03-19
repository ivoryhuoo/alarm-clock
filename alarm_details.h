#ifndef ALARMDETAILS_H
#define ALARMDETAILS_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class AlarmDetails : public QDialog {
    Q_OBJECT

public:
    explicit AlarmDetails(QString alarmLabel, QWidget *parent = nullptr);

private:
    QLabel *alarmLabelDisplay;
    QPushButton *closeButton;
};

#endif // ALARMDETAILS_H
