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

class ClockWidget : public QWidget {
    Q_OBJECT

public:
    explicit ClockWidget(QWidget *parent = nullptr);

private slots:
    void updateTime();
    void changeTimezone(const QString &timezoneId); // New method for updating timezone

private:
    QLCDNumber *clockDisplay;
    QComboBox *timezoneSelector; // Dropdown for timezone selection
    QLabel *timezoneLabel;
    QTimeZone currentTimeZone;
};

#endif // CLOCKWIDGET_H
