
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
CONFIG += c++11
QT       += core gui network opengl serialport xml

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buttonscreator.cpp \
    filecreator.cpp \
    graphcreator.cpp \
    guicreator.cpp \
    main.cpp \
    mapcreator.cpp \
    maplight.cpp \
    mapzoom.cpp \
    networkcreator.cpp \
    playercreator.cpp \
    qcustomplot.cpp \
    showmassives.cpp \
    terminalConsole.cpp \
    terminalCreator.cpp \
    terminalSettings.cpp

HEADERS += \
    buttonscreator.h \
    filecreator.h \
    graphcreator.h \
    guicreator.h \
    mapcreator.h \
    maplight.h \
    mapzoom.h \
    messages.h \
    networkcreator.h \
    playercreator.h \
    qcustomplot.h \
    terminalConsole.h \
    terminalCreator.h \
    terminalSettings.h

FORMS += \
    guicreator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

