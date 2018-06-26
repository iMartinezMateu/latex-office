#include "writer.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Writer w;
    QTranslator *qtTranslator = new QTranslator();
    QTranslator *translator = new QTranslator();
    a.setWindowIcon((QIcon(":/icon/icon.ico")));
    QFile themeSettingsFile("settings/theme.los");
    if (qtTranslator->load("qt_" + QLocale::system().name(), ":/languages")) {
        a.installTranslator(translator);
    }
    if (translator->load("writer_" + QLocale::system().name(), ":/languages")) {
        a.installTranslator(translator);
    }
    if (themeSettingsFile.exists()) {
        themeSettingsFile.open(QIODevice::ReadOnly);
        QTextStream in(&themeSettingsFile);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            QFile themeFile(line);
            themeFile.open(QIODevice::ReadOnly | QIODevice::Text);
            QString styleSheet = QLatin1String(themeFile.readAll());
            a.setStyleSheet(styleSheet);
            themeFile.close();
            break;
        }

    }
    w.show();
    return a.exec();
}
