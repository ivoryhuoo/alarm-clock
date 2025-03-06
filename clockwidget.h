#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>
#include <QLCDNumber>
#include <QVBoxLayout>
#include <QTimer>
#include <QTime>

class ClockWidget : public QWidget {
    Q_OBJECT

public:
    explicit ClockWidget(QWidget *parent = nullptr);

private slots:
    void updateTime();

private:
    QLCDNumber *clockDisplay;
};

#endif // CLOCKWIDGET_H
