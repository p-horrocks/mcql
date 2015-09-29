TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    mcqlutil.cpp \
    serverlink.cpp \
    player.cpp \
    playerlist.cpp

RESOURCES += qml.qrc

CONFIG += c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    mcqlutil.h \
    serverlink.h \
    player.h \
    playerlist.h
