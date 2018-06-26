#include "math.h"
#include <QApplication>
#include <QTranslator>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator *qtTranslator = new QTranslator();
    QTranslator *translator = new QTranslator();
    a.setWindowIcon((QIcon(":/icon/icon.ico")));
   if (qtTranslator->load("qt_" + QLocale::system().name(), ":/languages")) {
       a.installTranslator(translator);
    }
    if (translator->load("math_" + QLocale::system().name(), ":/languages")) {
        a.installTranslator(translator);
    }
    a.setWindowIcon((QIcon(":/icon/icon.ico")));
    Math w;
    w.show();

    return a.exec();
}
