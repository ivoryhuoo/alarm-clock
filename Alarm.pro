QT += core gui widgets

CONFIG -= app_bundle

INCLUDEPATH += include

SOURCES += main.cpp \
           src/clockwidget.cpp \
           src/mainwindow.cpp \
           src/setalarmwindow.cpp \
           src/viewAlarm.cpp \
           src/alarm_details.cpp

HEADERS += include/clockwidget.h \
           include/mainwindow.h \
           include/setalarmwindow.h \
           include/viewAlarm.h \
           include/alarm_details.h

# RESOURCES += resources.qrc
