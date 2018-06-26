#include "viewer.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Viewer w;
    QTranslator *qtTranslator = new QTranslator();
    QTranslator *translator = new QTranslator();
    a.setWindowIcon((QIcon(":/icon/icon.ico")));
    if (qtTranslator->load("qt_" + QLocale::system().name(), ":/languages")) {
        a.installTranslator(translator);
    }
    if (translator->load("viewer_" + QLocale::system().name(), ":/languages")) {
        a.installTranslator(translator);
    }
    w.show();
    return a.exec();
}
