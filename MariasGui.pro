QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    category.cpp \
    categoryeditor.cpp \
    csvreader.cpp \
    dataset.cpp \
    globaldata.cpp \
    main.cpp \
    mainwindow.cpp \
    statisticswindow.cpp

HEADERS += \
    category.h \
    categoryeditor.h \
    config.h \
    csvreader.h \
    dataset.h \
    globaldata.h \
    mainwindow.h \
    statisticswindow.h

FORMS += \
    mainwindow.ui \
    statisticswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
