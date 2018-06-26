#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T17:06:28
#
#-------------------------------------------------
LANGUAGE = C++
QT       += core gui printsupport network
CONFIG += qt warn_off c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET =  "LaTeX Office Viewer"
TEMPLATE = app
TRANSLATIONS = viewer_es_ES.ts
win32:RC_ICONS += icon.ico
macx:ICON = icon.icns


HEADERS  += viewer.h \
    lib/latex/file.h \
    lib/latex/constants.h \
    lib/latex/commands.h \
    lib/latex/packages.h \
    dialog_compilersettings.h \
    lib/latex/compiler.h \
    documentviewer.h \
    documentplaceholder.h \
    constants.h \
    dialog_log.h \
    lib/latex/bibliography.h \
    dialog_loading.h \
    dialog_documentunlock.h \
    lib/assistivetechnologies/documentlock.h \
    lib/tiny-aes/aes.h \
    dialog_find.h \
    documentslideshow.h \
    slideshowplaceholder.h \
    window_slideshow.h \
    remotecontrolserver.h
SOURCES += main.cpp\
        viewer.cpp \
    lib/latex/file.cpp \
    lib/latex/commands.cpp \
    dialog_compilersettings.cpp \
    lib/latex/compiler.cpp \
    documentviewer.cpp \
    documentplaceholder.cpp \
    dialog_log.cpp \
    lib/latex/bibliography.cpp \
    dialog_loading.cpp \
    dialog_documentunlock.cpp \
    lib/assistivetechnologies/documentlock.cpp \
    lib/tiny-aes/aes.cpp \
    dialog_find.cpp \
    documentslideshow.cpp \
    slideshowplaceholder.cpp \
    window_slideshow.cpp \
    remotecontrolserver.cpp

OTHER_FILES += style.astylerc

FORMS    += viewer.ui \
    dialog_compilersettings.ui \
    documentviewer.ui \
    dialog_log.ui \
    dialog_documentunlock.ui \
    dialog_find.ui \
    dialog_loading.ui \
    documentslideshow.ui \
    window_slideshow.ui

macx {
    LIBS += -L /usr/local/lib -lz -lpoppler-qt5 -lquazip -lssl

    ES_LPROJ.files      =  packaging/mac/es.lproj/locversion.plist
    ES_LPROJ.path       = Contents/Resources/es.lproj

}
unix:!macx {
    INCLUDEPATH += /usr/include/poppler/qt5 \
            /usr/include/quazip
    LIBS += -L /usr/lib -lz -lpoppler-qt5 -lquazip -lssl
}

RESOURCES += resources.qrc

!unix|win32: LIBS += -lz -lpoppler-qt5 -lquazip -lssl
INCLUDEPATH += \
    /usr/include/poppler/qt5 \
    /include/quazip \
    /usr/local/include/poppler/qt5



QMAKE_LIBDIR += \
    /usr/local/lib

DISTFILES += \
    oil.txt





