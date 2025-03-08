#ifndef VIEWALARM_H
#define VIEWALARM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class ViewAlarm : public QWidget {
    Q_OBJECT

public:
    explicit ViewAlarm(QWidget *parent = nullptr);
};

#endif
