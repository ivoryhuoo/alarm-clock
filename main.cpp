#include <QApplication>
#include "clockwidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ClockWidget clock;
    clock.show();
    return app.exec();
}
