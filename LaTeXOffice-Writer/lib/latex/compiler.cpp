
#include "compiler.h"

QString TeXCompiler::searchCompilerBinary()
{
#ifdef Q_OS_UNIX
    QDirIterator dirIt("/usr/texbin", QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        dirIt.next();
        qDebug() << "Searching at" + dirIt.filePath();
        if (QFileInfo(dirIt.filePath()).isFile())
            if (QFileInfo(dirIt.filePath()).completeBaseName() == "pdflatex"
                && QFileInfo(dirIt.filePath()).isExecutable()) {
                return dirIt.filePath();
            }
    }
    QDirIterator secondDirIt("/usr/bin", QDirIterator::Subdirectories);
    while (secondDirIt.hasNext()) {
        secondDirIt.next();
        qDebug() << "Searching at" + secondDirIt.filePath();
        if (QFileInfo(secondDirIt.filePath()).isFile())
            if (QFileInfo(secondDirIt.filePath()).completeBaseName() == "pdflatex"
                && QFileInfo(secondDirIt.filePath()).isExecutable()) {
                return secondDirIt.filePath();
            }
    }
    return "";
#endif
#ifdef Q_OS_WIN

    QDirIterator dirIt(getenv("PROGRAMFILES"),
                       QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        dirIt.next();
        qDebug() << "Searching at" + dirIt.filePath();
        if (QFileInfo(dirIt.filePath()).isFile())
            if (QFileInfo(dirIt.filePath()).completeBaseName() == "pdflatex"
                && QFileInfo(dirIt.filePath()).isExecutable()) {
                return dirIt.filePath();
            }
    }
        return "";
#endif

    }

    QString TeXCompiler::searchBiBTeXBinary() {
#ifdef Q_OS_UNIX
        QDirIterator dirIt("/usr/texbin", QDirIterator::Subdirectories);
        while (dirIt.hasNext()) {
            dirIt.next();
            qDebug() << "Searching at" + dirIt.filePath();
            if (QFileInfo(dirIt.filePath()).isFile())
                if (QFileInfo(dirIt.filePath()).completeBaseName() == "bibtex"
                    && QFileInfo(dirIt.filePath()).isExecutable()) {
                    return dirIt.filePath();
                }
        }
        QDirIterator secondDirIt("/usr/bin", QDirIterator::Subdirectories);
        while (secondDirIt.hasNext()) {
            secondDirIt.next();
            qDebug() << "Searching at" + secondDirIt.filePath();
            if (QFileInfo(secondDirIt.filePath()).isFile())
                if (QFileInfo(secondDirIt.filePath()).completeBaseName() == "bibtex"
                    && QFileInfo(secondDirIt.filePath()).isExecutable()) {
                    return secondDirIt.filePath();
                }
        }
        return "";
#endif
#ifdef Q_OS_WIN
        QDirIterator dirIt(getenv("PROGRAMFILES"),
                           QDirIterator::Subdirectories);
        while (dirIt.hasNext()) {
            dirIt.next();
            qDebug() << "Searching at" + dirIt.filePath();
            if (QFileInfo(dirIt.filePath()).isFile())
                if (QFileInfo(dirIt.filePath()).completeBaseName() == "bibtex"
                    && QFileInfo(dirIt.filePath()).isExecutable()) {
                    return dirIt.filePath();
                }
        }
            return "";
#endif

        }

        QString TeXCompiler::searchHTMLConverterBinary() {
#ifdef Q_OS_UNIX
            QDirIterator dirIt("/usr/texbin", QDirIterator::Subdirectories);
            while (dirIt.hasNext()) {
                dirIt.next();
                qDebug() << "Searching at" + dirIt.filePath();
                if (QFileInfo(dirIt.filePath()).isFile())
                    if (QFileInfo(dirIt.filePath()).completeBaseName() == "latex2html"
                        && QFileInfo(dirIt.filePath()).isExecutable()) {
                        return dirIt.filePath();
                    }
            }
            QDirIterator secondDirIt("/usr/bin", QDirIterator::Subdirectories);
            while (secondDirIt.hasNext()) {
                secondDirIt.next();
                qDebug() << "Searching at" + secondDirIt.filePath();
                if (QFileInfo(secondDirIt.filePath()).isFile())
                    if (QFileInfo(secondDirIt.filePath()).completeBaseName() == "latex2html"
                        && QFileInfo(secondDirIt.filePath()).isExecutable()) {
                        return secondDirIt.filePath();
                    }
            }
            return "";
#endif
#ifdef Q_OS_WIN

            QDirIterator dirIt(getenv("PROGRAMFILES"),
                               QDirIterator::Subdirectories);
            while (dirIt.hasNext()) {
                dirIt.next();
                qDebug() << "Searching at" + dirIt.filePath();
                if (QFileInfo(dirIt.filePath()).isFile())
                    if (QFileInfo(dirIt.filePath()).completeBaseName() == "latex2html"
                        && QFileInfo(dirIt.filePath()).isExecutable()) {
                        return dirIt.filePath();
                    }
            }
                return "";
#endif

            }
            QString TeXCompiler::searchRTFConverterBinary() {
#ifdef Q_OS_UNIX
                QDirIterator dirIt("/usr/texbin", QDirIterator::Subdirectories);
                while (dirIt.hasNext()) {
                    dirIt.next();
                    qDebug() << "Searching at" + dirIt.filePath();
                    if (QFileInfo(dirIt.filePath()).isFile())
                        if (QFileInfo(dirIt.filePath()).completeBaseName() == "latex2rtf"
                            && QFileInfo(dirIt.filePath()).isExecutable()) {
                            return dirIt.filePath();
                        }
                }
                QDirIterator secondDirIt("/usr/bin", QDirIterator::Subdirectories);
                while (secondDirIt.hasNext()) {
                    secondDirIt.next();
                    qDebug() << "Searching at" + secondDirIt.filePath();
                    if (QFileInfo(secondDirIt.filePath()).isFile())
                        if (QFileInfo(secondDirIt.filePath()).completeBaseName() == "latex2rtf"
                            && QFileInfo(secondDirIt.filePath()).isExecutable()) {
                            return secondDirIt.filePath();
                        }
                }
                return "";
#endif
#ifdef Q_OS_WIN
                QDirIterator dirIt(getenv("PROGRAMFILES"),
                                   QDirIterator::Subdirectories);
                while (dirIt.hasNext()) {
                    dirIt.next();
                    qDebug() << "Searching at" + dirIt.filePath();
                    if (QFileInfo(dirIt.filePath()).isFile())
                        if (QFileInfo(dirIt.filePath()).completeBaseName() == "latex2rtf"
                            && QFileInfo(dirIt.filePath()).isExecutable()) {
                            return dirIt.filePath();
                        }
                }
                    return "";
#endif

                }
                QString TeXCompiler::searchTXTConverterBinary() {
#ifdef Q_OS_UNIX
                    QDirIterator dirIt("/usr/texbin", QDirIterator::Subdirectories);
                    while (dirIt.hasNext()) {
                        dirIt.next();
                        qDebug() << "Searching at" + dirIt.filePath();
                        if (QFileInfo(dirIt.filePath()).isFile())
                            if (QFileInfo(dirIt.filePath()).completeBaseName() == "detex"
                                && QFileInfo(dirIt.filePath()).isExecutable()) {
                                return dirIt.filePath();
                            }
                    }
                    QDirIterator secondDirIt("/usr/bin", QDirIterator::Subdirectories);
                    while (secondDirIt.hasNext()) {
                        secondDirIt.next();
                        qDebug() << "Searching at" + secondDirIt.filePath();
                        if (QFileInfo(secondDirIt.filePath()).isFile())
                            if (QFileInfo(secondDirIt.filePath()).completeBaseName() == "detex"
                                && QFileInfo(secondDirIt.filePath()).isExecutable()) {
                                return secondDirIt.filePath();
                            }
                    }
                    return "";
#endif
#ifdef Q_OS_WIN
                    QDirIterator dirIt(getenv("PROGRAMFILES"),
                                       QDirIterator::Subdirectories);
                    while (dirIt.hasNext()) {
                        dirIt.next();
                        qDebug() << "Searching at" + dirIt.filePath();
                        if (QFileInfo(dirIt.filePath()).isFile())
                            if (QFileInfo(dirIt.filePath()).completeBaseName() == "detex"
                                && QFileInfo(dirIt.filePath()).isExecutable()) {
                                return dirIt.filePath();
                            }
                    }
                        return "";
#endif

                    }

                    QString TeXCompiler::loadPDFCompilerPathSettings() {
                        QFile file("settings/pdfcompilerpath.los");
                        file.open(QIODevice::ReadOnly);
                        QTextStream in(&file);
                        QString line;
                        while (!in.atEnd()) {
                            line = in.readLine();
                        }
                        file.close();
                        return line;
                    }


                    void TeXCompiler::savePDFCompilerPathSettings(QString compilerPath) {
                        if (!QDir("settings").exists()) {
                            QDir().mkdir("settings");
                        }
                        if (QFile("settings/pdfcompilerpath.los").exists()) {
                            QFile("settings/pdfcompilerpath.los").remove();
                        }
                        QString filename = "settings/pdfcompilerpath.los";
                        QFile file(filename);
                        if (file.open(QIODevice::ReadWrite)) {
                            QTextStream stream(&file);
                            stream << compilerPath << endl;
                        }
                    }

                    QString TeXCompiler::loadBIBCompilerPathSettings() {
                        QFile file("settings/bibcompilerpath.los");
                        file.open(QIODevice::ReadOnly);
                        QTextStream in(&file);
                        QString line;
                        while (!in.atEnd()) {
                            line = in.readLine();
                        }
                        file.close();
                        return line;
                    }


                    void TeXCompiler::saveBIBCompilerPathSettings(QString compilerPath) {
                        if (!QDir("settings").exists()) {
                            QDir().mkdir("settings");
                        }
                        if (QFile("settings/bibcompilerpath.los").exists()) {
                            QFile("settings/bibcompilerpath.los").remove();
                        }
                        QString filename = "settings/bibcompilerpath.los";
                        QFile file(filename);
                        if (file.open(QIODevice::ReadWrite)) {
                            QTextStream stream(&file);
                            stream << compilerPath << endl;
                        }
                    }

                    QString TeXCompiler::loadHTMLConverterPathSettings() {
                        QFile file("settings/htmlconverterpath.los");
                        file.open(QIODevice::ReadOnly);
                        QTextStream in(&file);
                        QString line;
                        while (!in.atEnd()) {
                            line = in.readLine();
                        }
                        file.close();
                        return line;
                    }


                    void TeXCompiler::saveHTMLConverterPathSettings(QString compilerPath) {
                        if (!QDir("settings").exists()) {
                            QDir().mkdir("settings");
                        }
                        if (QFile("settings/htmlconverterpath.los").exists()) {
                            QFile("settings/htmlconverterpath.los").remove();
                        }
                        QString filename = "settings/htmlconverterpath.los";
                        QFile file(filename);
                        if (file.open(QIODevice::ReadWrite)) {
                            QTextStream stream(&file);
                            stream << compilerPath << endl;
                        }
                    }

                    QString TeXCompiler::loadTXTConverterPathSettings() {
                        QFile file("settings/txtconverterpath.los");
                        file.open(QIODevice::ReadOnly);
                        QTextStream in(&file);
                        QString line;
                        while (!in.atEnd()) {
                            line = in.readLine();
                        }
                        file.close();
                        return line;
                    }


                    void TeXCompiler::saveTXTConverterPathSettings(QString compilerPath) {
                        if (!QDir("settings").exists()) {
                            QDir().mkdir("settings");
                        }
                        if (QFile("settings/txtconverterpath.los").exists()) {
                            QFile("settings/txtconverterpath.los").remove();
                        }
                        QString filename = "settings/txtconverterpath.los";
                        QFile file(filename);
                        if (file.open(QIODevice::ReadWrite)) {
                            QTextStream stream(&file);
                            stream << compilerPath << endl;
                        }
                    }

                    QString TeXCompiler::loadRTFConverterPathSettings() {
                        QFile file("settings/rtfconverterpath.los");
                        file.open(QIODevice::ReadOnly);
                        QTextStream in(&file);
                        QString line;
                        while (!in.atEnd()) {
                            line = in.readLine();
                        }
                        file.close();
                        return line;
                    }


                    void TeXCompiler::saveRTFConverterPathSettings(QString compilerPath) {
                        if (!QDir("settings").exists()) {
                            QDir().mkdir("settings");
                        }
                        if (QFile("settings/rtfconverterpath.los").exists()) {
                            QFile("settings/rtfconverterpath.los").remove();
                        }
                        QString filename = "settings/rtfconverterpath.los";
                        QFile file(filename);
                        if (file.open(QIODevice::ReadWrite)) {
                            QTextStream stream(&file);
                            stream << compilerPath << endl;
                        }
                    }



