#-------------------------------------------------
#
# Project created by QtCreator 2015-07-05T12:02:00
#
#-------------------------------------------------

QT       += core gui   network xml webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "LaTeX Office Math"
TEMPLATE = app
TRANSLATIONS = math_es_ES.ts
win32:RC_ICONS += icon.ico
macx:ICON = icon.icns

SOURCES += main.cpp\
        math.cpp \
        dialog_label.cpp \
        dialog_symbol.cpp \
        lib/latex/commands.cpp


HEADERS  += math.h \
        dialog_label.h \
        dialog_symbol.h \
        lib/latex/commands.h


FORMS    += math.ui  \
            dialog_label.ui \
            dialog_symbol.ui

RESOURCES += \
    resources.qrc
