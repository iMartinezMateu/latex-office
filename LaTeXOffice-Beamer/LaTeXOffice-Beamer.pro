#-------------------------------------------------
#
# Project created by QtCreator 2015-07-03T13:23:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET =  "LaTeX Office Beamer"
TEMPLATE = app
win32:RC_ICONS += icon.ico
macx:ICON = icon.icns

SOURCES += main.cpp\
        beamer.cpp

HEADERS  += beamer.h

FORMS    += beamer.ui

RESOURCES += \
    resources.qrc
