#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T17:06:28
#
#-------------------------------------------------
LANGUAGE = C++
QT       += core gui concurrent printsupport network xml webkitwidgets
CONFIG += qt warn_off c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET =  "LaTeX Office Writer"
TEMPLATE = app
TRANSLATIONS = writer_es_ES.ts
win32:RC_ICONS += icon.ico
macx:ICON = icon.icns

HEADERS  += writer.h \
    lib/spellchecker.h \
    lib/latex/constants.h \
    lib/latex/commands.h \
    lib/latex/file.h \
    lib/latex/packages.h \
    lib/synctex/synctex_parser.h \
    lib/synctex/synctex_parser_utils.h \
    dialog_symbol.h \
    dialog_newdocument.h \
    dialog_documentpreamble.h \
    dialog_compilersettings.h \
    lib/latex/compiler.h \
    documentviewer.h \
    dialog_find.h \
    documentplaceholder.h \
    dialog_modifyimage.h \
    constants.h \
    compilerthread.h \
    lib/latex/parser.h \
    dialog_chapter.h \
    dialog_section.h \
    dialog_subsection.h \
    dialog_paragraph.h \
    dialog_subsubsection.h \
    dialog_log.h \
    lib/latex/symbols.h \
    dialog_insertimage.h \
    dialog_inserttable.h \
    dialog_modifytable.h \
    dialog_bibliography.h \
    lib/latex/bibliography.h \
    dialog_spellchecker.h \
    dialog_goal.h \
    dialog_dictionarysettings.h \
    lib/assistivetechnologies/documentlock.h \
    lib/tiny-aes/aes.h \
    dialog_documentlock.h \
    dialog_documentunlock.h \
    dialog_modifycodeasset.h \
    dialog_smartkeys.h \
    lib/assistivetechnologies/smartkeys.h \
    lib/assistivetechnologies/timemachine.h \
    lib/assistivetechnologies/timemachinethread.h \
    dialog_timemachine.h \
    dialog_loading.h \
    dialog_themesettings.h \
    caja.h \
    matheditor.h \
    dialog_code.h \
    dialog_timemachinesettings.h \
    dialog_citations.h \
    dialog_references.h \
    dialog_fonts.h \
    dialog_label.h \
    dialog_modifyequation.h
SOURCES += main.cpp\
        writer.cpp \
    lib/latex/commands.cpp \
    lib/latex/file.cpp \
    lib/synctex/synctex_parser.c \
    lib/synctex/synctex_parser_utils.c \
    dialog_symbol.cpp \
    dialog_newdocument.cpp \
    dialog_documentpreamble.cpp \
    dialog_compilersettings.cpp \
    lib/latex/compiler.cpp \
    documentviewer.cpp \
    dialog_find.cpp \
    documentplaceholder.cpp \
    dialog_modifyimage.cpp \
    compilerthread.cpp \
    lib/latex/parser.cpp \
    dialog_chapter.cpp \
    dialog_section.cpp \
    dialog_paragraph.cpp \
    dialog_subsection.cpp \
    dialog_subsubsection.cpp \
    dialog_log.cpp \
    dialog_insertimage.cpp \
    dialog_inserttable.cpp \
    dialog_modifytable.cpp \
    dialog_bibliography.cpp \
    lib/latex/bibliography.cpp \
    lib/spellchecker.cpp \
    dialog_spellchecker.cpp \
    dialog_goal.cpp \
    dialog_dictionarysettings.cpp \
    lib/tiny-aes/aes.cpp \
    dialog_documentlock.cpp \
    dialog_documentunlock.cpp \
    lib/assistivetechnologies/documentlock.cpp \
    dialog_modifycodeasset.cpp \
    dialog_smartkeys.cpp \
    lib/assistivetechnologies/smartkeys.cpp \
    lib/assistivetechnologies/timemachine.cpp \
    lib/assistivetechnologies/timemachinethread.cpp \
    dialog_timemachine.cpp \
    dialog_loading.cpp \
    dialog_themesettings.cpp \
    caja.cpp \
    matheditor.cpp \
    dialog_code.cpp \
    dialog_timemachinesettings.cpp \
    dialog_citations.cpp \
    dialog_references.cpp \
    dialog_fonts.cpp \
    dialog_label.cpp \
    dialog_modifyequation.cpp

OTHER_FILES += style.astylerc lib/mathjax/MathJax.js

FORMS    += writer.ui \
    dialog_symbol.ui \
    dialog_newdocument.ui \
    dialog_documentpreamble.ui \
    dialog_compilersettings.ui \
    documentviewer.ui \
    dialog_find.ui \
    dialog_modifyimage.ui \
    dialog_chapter.ui \
    dialog_section.ui \
    dialog_subsection.ui \
    dialog_subsubsection.ui \
    dialog_paragraph.ui \
    dialog_log.ui \
    dialog_insertimage.ui \
    dialog_inserttable.ui \
    dialog_modifytable.ui \
    dialog_bibliography.ui \
    dialog_spellchecker.ui \
    dialog_goal.ui \
    dialog_dictionarysettings.ui \
    dialog_documentlock.ui \
    dialog_documentunlock.ui \
    dialog_modifycodeasset.ui \
    dialog_smartkeys.ui \
    dialog_email.ui \
    dialog_timemachine.ui \
    dialog_loading.ui \
    dialog_themesettings.ui \
    caja.ui \
    matheditor.ui \
    dialog_code.ui \
    dialog_timemachinesettings.ui \
    dialog_citations.ui \
    dialog_references.ui \
    dialog_fonts.ui \
    dialog_label.ui \
    dialog_modifyequation.ui
macx {
    LIBS += -L /usr/local/lib \
            -lz -lpoppler-qt5 -lquazip -lhunspell-1.3 -lcrypto
    INCLUDEPATH += /usr/local/include/hunspell/

    ES_LPROJ.files      =  packaging/mac/es.lproj/locversion.plist
    ES_LPROJ.path       = Contents/Resources/es.lproj

}
unix:!macx {
    INCLUDEPATH += /usr/include/poppler/qt5 \
            /usr/include/quazip \
            /usr/include/hunspell
    LIBS += -L /usr/lib -lpoppler-qt5 -lz -lquazip -lcrypto -lhunspell
}

RESOURCES += resources.qrc

!unix|win32{
    INCLUDEPATH += C:\poppler
    LIBS+= -LC:\poppler -lpoppler-qt5
    INCLUDEPATH += C:\quazip
    LIBS += -LC:\quazip -lquazip
    INCLUDEPATH += C:\hunspell
    LIBS += -LC:\hunspell -lhunspell
    INCLUDEPATH += C:\zlib
    LIBS += -LC:\zlib -lz
    INCLUDEPATH += C:\crypto
    LIBS += -LC:\crypto -lcrypto

}
INCLUDEPATH += \
    /usr/include/poppler/qt5 \
    /include/quazip \
    /usr/local/include/poppler/qt5



QMAKE_LIBDIR += \
    /usr/local/lib

DISTFILES += \
    oil.txt





