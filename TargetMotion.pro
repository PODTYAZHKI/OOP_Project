#-------------------------------------------------
#
# Project created by QtCreator 2015-09-26T21:07:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32-msvc*{
    LIBS += -luser32
}

TARGET = TargetMotion
TEMPLATE = app


SOURCES += main.cpp\
    character.cpp \
    enemy.cpp \
    hero.cpp \
    widget.cpp \
    customscene.cpp \
    bullet.cpp

HEADERS  += widget.h \
    character.h \
    enemy.h \
    hero.h \
    customscene.h \
    bullet.h \
    character.cpp

FORMS    += widget.ui

RESOURCES += \
    resources/cursor.qrc \
    resources/sprites.qrc
