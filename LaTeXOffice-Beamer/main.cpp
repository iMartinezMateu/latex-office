#include "beamer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon((QIcon(":/icon/icon.ico")));
    Beamer w;
    w.show();

    return a.exec();
}
