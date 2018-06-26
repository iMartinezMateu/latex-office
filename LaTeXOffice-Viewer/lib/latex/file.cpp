#include "file.h"

TeXFile::TeXFile(QString filePath, bool mustReadFile)
{
    file = new QFile(filePath);
    QFileInfo fileInfo(file->fileName());
    _fileName = fileInfo.baseName();
    if (mustReadFile) {
        readFile();
    }
}
TeXFile::~TeXFile()
{
    close();
}

void TeXFile::readFile()
{
    fileContent.clear();
    int lineNumber = 0;
    file->open(QIODevice::ReadOnly);
    QTextStream in(file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        fileContent.append(line);
    }
    foreach (QString line, fileContent) {


        if (line.contains(CMD_TITLE)) {
            QString parsedTitle;

            QRegularExpression re("\\{(.*?)\\}");
            QRegularExpressionMatch match = re.match(line);
            if (match.hasMatch()) {
                parsedTitle = match.captured(1);

            }
            setDocumentTitle(parsedTitle);
            qDebug() << "Document Title: " + getDocumentTitle();
        } else if (line.contains(CMD_AUTHOR)) {
            QString parsedAuthor;
            QRegularExpression re2("\\{(.*?)\\}");
            QRegularExpressionMatch match = re2.match(line);
            if (match.hasMatch()) {
                parsedAuthor = match.captured(1);

            }
            setDocumentAuthor(parsedAuthor);
            qDebug() << "Document Author: " + getDocumentAuthor();
        } else if (line.contains(CMD_DATE)) {
            QString parsedDate;
            QRegularExpression re3("\\{(.*?)\\}");
            QRegularExpressionMatch match = re3.match(line);
            if (match.hasMatch()) {
                parsedDate = match.captured(1);

            }
            setDocumentDate(parsedDate);
            qDebug() << "Document Date: " + getDocumentDate();
        } else if (line.contains(CMD_ADDRESS)) {
            QString parsedAddress;
            QRegularExpression re3("\\{(.*?)\\}");
            QRegularExpressionMatch match = re3.match(line);
            if (match.hasMatch()) {
                parsedAddress = match.captured(1);

            }
            setDocumentAddress(parsedAddress);
            qDebug() << "Document Address: " + getDocumentAddress();
        } else if (line.contains(command.callBegin(ENV_ABSTRACT))) {
            QString parsedAbstract;
            for (int lineNumber = getLineNumber(command.callBegin(ENV_ABSTRACT));
                 lineNumber < getLineNumber(command.callEnd(ENV_ABSTRACT)); lineNumber++) {
                parsedAbstract.append(line.at(lineNumber));
            }
            setDocumentAbstract(parsedAbstract);
            qDebug() << "Document Abstract: " + getDocumentAbstract();
        }
        if (line.contains(command.callBegin(ENV_DOCUMENT))) {
            setTeXCommand(command.callEndOfDump(), lineNumber);
        }
        if (!getDocumentTitle().isEmpty() && !getDocumentAuthor().isEmpty()
            && !getDocumentDate().isEmpty() && !getDocumentAddress().isEmpty()
            && !getDocumentAbstract().isEmpty()) {
            break;
        }

        lineNumber++;
    }
    qDebug() << "File read succesfully!";
    file->close();
}
QString TeXFile::getCLSFile()
{
    foreach (QString line, fileContent) {
        if (line.contains(command.callDocumentClass())) {
            QRegularExpression re("\\{(.*?)\\}");
            QRegularExpressionMatch match = re.match(line);
            if (match.hasMatch()) {
                QString clsFileName = match.captured(1);
                return clsFileName.append(".cls");

            }
        }

    }
    return "";

}

QString TeXFile::getSTYFile()
{
    foreach (QString line, fileContent) {
        if (line.contains(CMD_USE_PACKAGE)) {

            QRegularExpression re("\\{(.*?)\\}");
            QRegularExpressionMatch match = re.match(line);
            if (match.hasMatch()) {
                QString styFileName = match.captured(1);
                if (styFileName.contains('/'))
                    if (QFile(styFileName.append(".sty")).exists()) {
                        return styFileName.append(".sty");
                    } else if (styFileName.contains('\\'))
                        if (QFile(styFileName.append(".sty")).exists()) {
                            return styFileName.append(".sty");
                        } else if (QFile(getDirectory() + "/" + styFileName.append(".sty")).exists()) {
                            return styFileName.append(".sty");
                        }
            }
        }

    }
    return "";
}
void TeXFile::saveFile()
{
    file->open(QIODevice::WriteOnly | QFile::Truncate);
    QTextStream out(file);
    for (int i = 0; i < fileContent.length(); i++) {
        out << fileContent.at(i) + "\n";
    }
    qDebug() << "File wrote succesfully!";
    if (fileContentHistory.count() > MAX_UNDO_REDO_ACTIONS) {
        fileContentHistory.removeLast();
    }
    fileContentHistory.append(fileContent);
    if (_currentActionIndex < MAX_UNDO_REDO_ACTIONS) {
        _currentActionIndex++;
    }
    file->close();
}
void TeXFile::saveFile(QString filePath)
{
    QFile *newFile = new QFile(filePath);
    newFile->open(QIODevice::WriteOnly | QFile::Truncate);
    QTextStream out(newFile);
    for (int lineNumber = 0; lineNumber < fileContent.length(); lineNumber++) {
        out << fileContent.at(lineNumber) + "\n";
    }
    qDebug() << "File wrote succesfully!";
    newFile->close();
}
int TeXFile::getLineNumber(QString searchString)
{
    QString currentLine;
    for (int lineNumber = 0; lineNumber < fileContent.length(); lineNumber++) {
        currentLine = fileContent.at(lineNumber);
        if (currentLine.contains(searchString)) {
            qDebug() << "Line " + QString::number(lineNumber) + " with " + searchString + " found!";
            return lineNumber;
        }
    }
    return -1;
}
void TeXFile::setBeginDocumentCommand()
{
    int preambleLine = getDocumentPreamble();
    fileContent.insert(preambleLine + 1, command.callBegin(ENV_DOCUMENT));
    // qDebug() << "Begin of Document was setted!";
}
void TeXFile::setEndDocumentCommand()
{
    int endDocumentLine = getEndDocumentCommand();
    if (endDocumentLine != -1) {
        fileContent.removeAt(endDocumentLine);
    }
    fileContent.insert(fileContent.length(), command.callEnd(ENV_DOCUMENT));
    qDebug() << "End of Document was setted!";
}
int TeXFile::getBeginDocumentCommand()
{
    return getLineNumber(command.callBegin(ENV_DOCUMENT));
}
int TeXFile::getEndDocumentCommand()
{
    return getLineNumber(command.callEnd(ENV_DOCUMENT));
}
void TeXFile::setArabicLanguage()
{
    int duplicatedLanguageLine = getArabicLanguage();
    if (duplicatedLanguageLine != -1) {
        qDebug() << "Arabic language definition already exists!";
    } else {
        setPackage(PACK_ARABTEX);
    }
    qDebug() << "Arabic language definition was set correctly!";
}
int TeXFile::removeArabicLanguage()
{
    int definitionLanguageLine = getArabicLanguage();
    if (definitionLanguageLine != -1) {
        fileContent.removeAt(definitionLanguageLine);
    }
    return definitionLanguageLine;
}
int TeXFile::getArabicLanguage()
{
    return getPackage(PACK_ARABTEX);
}
void TeXFile::setBulgarianLanguage()
{
    QVector<int> duplicatedLanguageLines = getBulgarianLanguage();
    foreach (int duplicatedLanguageLine, duplicatedLanguageLines) {
        if (duplicatedLanguageLine != -1) {
            qDebug() << "Bulgarian language definition already exists!";
        } else {
            QString arguments = FONT_ENC_T1;
            arguments.append(",");
            arguments.append(FONT_ENC_T2A);
            setPackage(PACK_FONTENC, arguments);
            setPackage(PACK_INPUTENC, ENC_UTF8);
            setPackage(PACK_BABEL, LANG_BULGARIAN);
        }
    }
    qDebug() << "Bulgarian language definition was set correctly!";
}
QVector<int> TeXFile::removeBulgarianLanguage()
{
    QVector<int> definitionLanguageLines = getBulgarianLanguage();
    foreach (int definitionLanguageLine , definitionLanguageLines) {
        if (definitionLanguageLine != -1) {
            fileContent.removeAt(definitionLanguageLine);
        }
    }
    return definitionLanguageLines;
}
QVector<int> TeXFile::getBulgarianLanguage()
{
    QVector<int> positions;
    QString arguments = FONT_ENC_T1;
    arguments.append(",");
    arguments.append(FONT_ENC_T2A);
    positions.append(getPackage(PACK_FONTENC, arguments));
    positions.append(getPackage(PACK_INPUTENC, ENC_UTF8));
    positions.append(getPackage(PACK_BABEL, LANG_BULGARIAN));
    return positions ;
}
void TeXFile::setRussianLanguage()
{
    QVector<int> duplicatedLanguageLines = getRussianLanguage();
    foreach (int duplicatedLanguageLine , duplicatedLanguageLines) {
        if (duplicatedLanguageLine != -1) {
            qDebug() << "Russian language definition already exists!";
        } else {
            QString arguments = FONT_ENC_T1;
            arguments.append(",");
            arguments.append(FONT_ENC_T2A);
            setPackage(PACK_FONTENC, arguments);
            setPackage(PACK_INPUTENC, ENC_UTF8);
            setPackage(PACK_BABEL, LANG_RUSSIAN);
        }
    }
    qDebug() << "Russian language definition was set correctly!";
}
QVector<int> TeXFile::removeRussianLanguage()
{
    QVector<int> definitionLanguageLines = getRussianLanguage();
    foreach (int definitionLanguageLine , definitionLanguageLines) {
        if (definitionLanguageLine != -1) {
            fileContent.removeAt(definitionLanguageLine);
        }
    }
    return definitionLanguageLines;
}
QVector<int> TeXFile::getRussianLanguage()
{
    QVector<int> positions ;
    QString arguments = FONT_ENC_T1;
    arguments.append(",");
    arguments.append(FONT_ENC_T2A);
    positions.append(getPackage(PACK_FONTENC, arguments));
    positions.append(getPackage(PACK_INPUTENC, ENC_UTF8));
    positions.append(getPackage(PACK_BABEL, LANG_RUSSIAN));
    return positions ;
}
void TeXFile::setUkrainianLanguage()
{
    QVector<int> duplicatedLanguageLines = getUkrainianLanguage();
    foreach (int duplicatedLanguageLine , duplicatedLanguageLines) {
        if (duplicatedLanguageLine != -1) {
            qDebug() << "Ukranian language definition already exists!";
        } else {
            QString arguments = FONT_ENC_T1;
            arguments.append(",");
            arguments.append(FONT_ENC_T2A);
            setPackage(PACK_FONTENC, arguments);
            setPackage(PACK_INPUTENC, ENC_UTF8);
            setPackage(PACK_BABEL, LANG_UKRAINIAN);
        }
    }
    qDebug() << "Ukranian language definition was set correctly!";
}
QVector<int> TeXFile::removeUkrainianLanguage()
{
    QVector<int> definitionLanguageLines = getUkrainianLanguage();
    foreach (int definitionLanguageLine , definitionLanguageLines) {
        if (definitionLanguageLine != -1) {
            fileContent.removeAt(definitionLanguageLine);
        }
    }
    return definitionLanguageLines;
}
QVector<int> TeXFile::getUkrainianLanguage()
{
    QVector<int> positions ;
    QString arguments = FONT_ENC_T1;
    arguments.append(",");
    arguments.append(FONT_ENC_T2A);
    positions.append(getPackage(PACK_FONTENC, arguments));
    positions.append(getPackage(PACK_INPUTENC, ENC_UTF8));
    positions.append(getPackage(PACK_BABEL, LANG_UKRAINIAN));
    return positions ;
}
void TeXFile::setChineseLanguage()
{
    int duplicatedLanguageLine = getChineseLanguage();
    if (duplicatedLanguageLine != -1) {
        qDebug() << "Chinese language definition already exists!";
    } else {
        setPackage(PACK_CJK);
    }
    qDebug() << "Chinese language definition was set correctly!";
}
int TeXFile::removeChineseLanguage()
{
    int definitionLanguageLine = getChineseLanguage();
    if (definitionLanguageLine != -1) {
        fileContent.removeAt(definitionLanguageLine);
    }
    return definitionLanguageLine;
}
int TeXFile::getChineseLanguage()
{
    return getPackage(PACK_CJK);
}
void TeXFile::setCzechLanguage()
{
    int duplicatedLanguageLine = getCzechLanguage();
    if (duplicatedLanguageLine != -1) {
        qDebug() << "Czech language definition already exists!";
    } else {
        setPackage(PACK_BABEL, LANG_CZECH);
    }
    qDebug() << "Czech language definition was set correctly!";
}
int TeXFile::removeCzechLanguage()
{
    int definitionLanguageLine = getCzechLanguage();
    if (definitionLanguageLine != -1) {
        fileContent.removeAt(definitionLanguageLine);
    }
    return definitionLanguageLine;
}
int TeXFile::getCzechLanguage()
{
    return getPackage(PACK_BABEL, LANG_CZECH);
}
void TeXFile::setFinnishLanguage()
{
    int duplicatedLanguageLine = getFinnishLanguage();
    if (duplicatedLanguageLine != -1) {
        qDebug() << "Finnish language definition already exists!";
    } else {
        setPackage(PACK_BABEL, LANG_FINNISH);
    }
    qDebug() << "Finnish language definition was set correctly!";
}
int TeXFile::removeFinnishLanguage()
{
    int definitionLanguageLine = getFinnishLanguage();
    if (definitionLanguageLine != -1) {
        fileContent.removeAt(definitionLanguageLine);
    }
    return definitionLanguageLine;
}
int TeXFile::getFinnishLanguage()
{
    return getPackage(PACK_BABEL, LANG_FINNISH);
}
void TeXFile::setFrenchLanguage()
{
    int duplicatedLanguageLine = getFrenchLanguage();
    if (duplicatedLanguageLine != -1) {
        qDebug() << "French language definition already exists!";
    } else {
        setPackage(PACK_BABEL, LANG_FRENCH);
    }
    qDebug() << "French language definition was set correctly!";
}
int TeXFile::removeFrenchLanguage()
{
    int definitionLanguageLine = getFrenchLanguage();
    if (definitionLanguageLine != -1) {
        fileContent.removeAt(definitionLanguageLine);
    }
    return definitionLanguageLine;
}
int TeXFile::getFrenchLanguage()
{
    return getPackage(PACK_BABEL, LANG_FRENCH);
}
void TeXFile::setGermanLanguage()
{
    int duplicatedLanguageLine = getGermanLanguage();
    if (duplicatedLanguageLine != -1) {
        qDebug() << "German language definition already exists!";
    } else {
        setPackage(PACK_BABEL, LANG_GERMAN);
    }
    qDebug() << "German language definition was set correctly!";
}
int TeXFile::removeGermanLanguage()
{
    int definitionLanguageLine = getGermanLanguage();
    if (definitionLanguageLine != -1) {
        fileContent.removeAt(definitionLanguageLine);
    }
    return definitionLanguageLine;
}
int TeXFile::getGermanLanguage()
{
    return getPackage(PACK_BABEL, LANG_GERMAN);
}
void TeXFile::setGreekLanguage()
{
    QVector<int> duplicatedLanguageLines = getGreekLanguage();
    foreach (int duplicatedLanguageLine  , duplicatedLanguageLines) {
        if (duplicatedLanguageLine != -1) {
            qDebug() << "Greek language definition already exists!";
        } else {
            setPackage(PACK_BABEL, LANG_GREEK);
            setPackage(PACK_INPUTENC, ENC_ISO8859);
        }
    }
    qDebug() << "Greek language definition was set correctly!";
}
QVector<int> TeXFile::removeGreekLanguage()
{
    QVector<int> definitionLanguageLines = getGreekLanguage();
    foreach (int definitionLanguageLine , definitionLanguageLines) {
        if (definitionLanguageLine != -1) {
            fileContent.removeAt(definitionLanguageLine);
        }
    }
    return definitionLanguageLines;
}
QVector<int> TeXFile::getGreekLanguage()
{
    QVector<int> positions ;
    positions.append(getPackage(PACK_BABEL, LANG_GREEK));
    positions.append(getPackage(PACK_INPUTENC, ENC_ISO8859));
    return positions ;
}
void TeXFile::setIcelandicLanguage()
{
    QVector<int> duplicatedLanguageLines = getIcelandicLanguage();
    foreach (int duplicatedLanguageLine  , duplicatedLanguageLines) {
        if (duplicatedLanguageLine != -1) {
            qDebug() << "Icelandic language definition already exists!";
        } else {
            setPackage(PACK_BABEL, LANG_ICELANDIC_FAROESE);
            setPackage(PACK_FONTENC, FONT_ENC_T1);
        }
    }
    qDebug() << "Icelandic language definition was set correctly!";
}
QVector<int> TeXFile::removeIcelandicLanguage()
{
    QVector<int> definitionLanguageLines = getIcelandicLanguage();
    foreach (int definitionLanguageLine , definitionLanguageLines) {
        if (definitionLanguageLine != -1) {
            fileContent.removeAt(definitionLanguageLine);
        }
    }
    return definitionLanguageLines;
}
QVector<int> TeXFile::getIcelandicLanguage()
{
    QVector<int> positions;
    positions.append(getPackage(PACK_BABEL, LANG_ICELANDIC_FAROESE));
    positions.append(getPackage(PACK_INPUTENC, FONT_ENC_T1));
    return positions ;
}
void TeXFile::setFaroeseLanguage()
{
    QVector<int> duplicatedLanguageLines = getFaroeseLanguage();
    foreach (int duplicatedLanguageLine  , duplicatedLanguageLines) {
        if (duplicatedLanguageLine != -1) {
            qDebug() << "Faroese language definition already exists!";
        } else {
            setPackage(PACK_BABEL, LANG_ICELANDIC_FAROESE);
            setPackage(PACK_FONTENC, FONT_ENC_T1);
        }
    }
    qDebug() << "Faroese language definition was set correctly!";
}
QVector<int> TeXFile::removeFaroeseLanguage()
{
    QVector<int> definitionLanguageLines = getFaroeseLanguage();
    foreach (int definitionLanguageLine , definitionLanguageLines) {
        if (definitionLanguageLine != -1) {
            fileContent.removeAt(definitionLanguageLine);
        }
    }
    return definitionLanguageLines;
}
QVector<int> TeXFile::getFaroeseLanguage()
{
    QVector<int> positions;
    positions.append(getPackage(PACK_BABEL, LANG_ICELANDIC_FAROESE));
    positions.append(getPackage(PACK_INPUTENC, FONT_ENC_T1));
    return positions ;
}
void TeXFile::setItalianLanguage()
{
    int duplicatedLanguageLine = getItalianLanguage();
    if (duplicatedLanguageLine != -1) {
        qDebug() << "Italian language definition already exists!";
    } else {
        setPackage(PACK_BABEL, LANG_ITALIAN);
    }
    qDebug() << "Italian language definition was set correctly!";
}
int TeXFile::removeItalianLanguage()
{
    int definitionLanguageLine = getItalianLanguage();
    if (definitionLanguageLine != -1) {
        fileContent.removeAt(definitionLanguageLine);
    }
    return definitionLanguageLine;
}
int TeXFile::getItalianLanguage()
{
    return getPackage(PACK_BABEL, LANG_ITALIAN);
}
void TeXFile::setKoreanLanguage()
{
    int duplicatedLanguageLine = getKoreanLanguage();
    if (duplicatedLanguageLine != -1) {
        qDebug() << "Korean language definition already exists!";
    } else {
        setPackage(PACK_BABEL, LANG_KOREAN);
    }
    qDebug() << "Korean language definition was set correctly!";
}
int TeXFile::removeKoreanLanguage()
{
    int definitionLanguageLine = getKoreanLanguage();
    if (definitionLanguageLine != -1) {
        fileContent.removeAt(definitionLanguageLine);
    }
    return definitionLanguageLine;
}
int TeXFile::getKoreanLanguage()
{
    return getPackage(PACK_BABEL, LANG_KOREAN);
}
void TeXFile::setPersianLanguage()
{
    int duplicatedLanguageLine = getPersianLanguage();
    if (duplicatedLanguageLine != -1) {
        qDebug() << "Persian language definition already exists!";
    } else {
        setPackage(PACK_BABEL, LANG_PERSIAN);
    }
    qDebug() << "Persian language definition was set correctly!";
}
int TeXFile::removePersianLanguage()
{
    int definitionLanguageLine = getPersianLanguage();
    if (definitionLanguageLine != -1) {
        fileContent.removeAt(definitionLanguageLine);
    }
    return definitionLanguageLine;
}
int TeXFile::getPersianLanguage()
{
    return getPackage(PACK_BABEL, LANG_PERSIAN);
}
void TeXFile::setPolishLanguage()
{
    QVector<int> duplicatedLanguageLines = getPolishLanguage();
    foreach (int duplicatedLanguageLine  , duplicatedLanguageLines) {
        if (duplicatedLanguageLine != -1) {
            qDebug() << "Polish language definition already exists!";
        } else {
            setPackage(PACK_INPUTENC, ENC_UTF8);
            setPackage(PACK_POLSKI);
            setPackage(PACK_BABEL, LANG_POLISH);
        }
    }
    qDebug() << "Polish language definition was set correctly!";
}
QVector<int> TeXFile::removePolishLanguage()
{
    QVector<int> definitionLanguageLines = getPolishLanguage();
    foreach (int definitionLanguageLine , definitionLanguageLines) {
        if (definitionLanguageLine != -1) {
            fileContent.removeAt(definitionLanguageLine);
        }
    }
    return definitionLanguageLines;
}
QVector<int> TeXFile::getPolishLanguage()
{
    QVector<int> positions;
    positions.append(getPackage(PACK_INPUTENC, ENC_UTF8));
    positions.append(getPackage(PACK_POLSKI));
    positions.append(getPackage(PACK_BABEL, LANG_POLISH));
    return positions ;
}
void TeXFile::setPortugueseLanguage()
{
    int duplicatedLanguageLine = getPortugueseLanguage();
    if (duplicatedLanguageLine != -1) {
        qDebug() << "Portuguese language definition already exists!";
    } else {
        setPackage(PACK_BABEL, LANG_PORTUGUESE);
    }
    qDebug() << "Portuguese language definition was set correctly!";
}
int TeXFile::removePortugueseLanguage()
{
    int definitionLanguageLine = getPortugueseLanguage();
    if (definitionLanguageLine != -1) {
        fileContent.removeAt(definitionLanguageLine);
    }
    return definitionLanguageLine;
}
int TeXFile::getPortugueseLanguage()
{
    return getPackage(PACK_BABEL, LANG_PORTUGUESE);
}
void TeXFile::setSlovakLanguage()
{
    QVector<int> duplicatedLanguageLines = getSlovakLanguage();
    foreach (int duplicatedLanguageLine  , duplicatedLanguageLines) {
        if (duplicatedLanguageLine != -1) {
            qDebug() << "Slovak language definition already exists!";
        } else {
            setPackage(PACK_BABEL, LANG_SLOVAK);
            setPackage(PACK_FONTENC, FONT_ENC_IL2);
        }
    }
    qDebug() << "Slovak language definition was set correctly!";
}
QVector<int> TeXFile::removeSlovakLanguage()
{
    QVector<int> definitionLanguageLines = getSlovakLanguage();
    foreach (int definitionLanguageLine , definitionLanguageLines) {
        if (definitionLanguageLine != -1) {
            fileContent.removeAt(definitionLanguageLine);
        }
    }
    return definitionLanguageLines;
}
QVector<int> TeXFile::getSlovakLanguage()
{
    QVector<int> positions;
    positions.append(getPackage(PACK_BABEL, LANG_SLOVAK));
    positions.append(getPackage(PACK_FONTENC, FONT_ENC_IL2));
    return positions ;
}
void TeXFile::setSpanishLanguage()
{
    QVector<int> duplicatedLanguageLines = getSpanishLanguage();
    foreach (int duplicatedLanguageLine  , duplicatedLanguageLines) {
        if (duplicatedLanguageLine != -1) {
            qDebug() << "Spanish language definition already exists!";
        } else {
            setPackage(PACK_BABEL, LANG_SPANISH);
            setPackage(PACK_INPUTENC, ENC_UTF8);
        }
    }
    qDebug() << "Spanish language definition was set correctly!";
}
QVector<int> TeXFile::removeSpanishLanguage()
{
    QVector<int> definitionLanguageLines = getSpanishLanguage();
    foreach (int definitionLanguageLine , definitionLanguageLines) {
        if (definitionLanguageLine != -1) {
            fileContent.removeAt(definitionLanguageLine);
        }
    }
    return definitionLanguageLines;
}
QVector<int> TeXFile::getSpanishLanguage()
{
    QVector<int> positions;
    positions.append(getPackage(PACK_BABEL, LANG_SPANISH));
    positions.append(getPackage(PACK_INPUTENC, ENC_UTF8));
    return positions ;
}
void TeXFile::setTibetanLanguage()
{
    int duplicatedLanguageLine = getTibetanLanguage();
    if (duplicatedLanguageLine != -1) {
        qDebug() << "Tibetan language definition already exists!";
    } else {
        setPackage(PACK_CTIB);
    }
    qDebug() << "Tibetan language definition was set correctly!";
}
int TeXFile::removeTibetanLanguage()
{
    int definitionLanguageLine = getTibetanLanguage();
    if (definitionLanguageLine != -1) {
        fileContent.removeAt(definitionLanguageLine);
    }
    return definitionLanguageLine;
}
int TeXFile::getTibetanLanguage()
{
    return getPackage(PACK_CTIB);
}
void TeXFile::setEnglishLanguage()
{
    int duplicatedLanguageLine = getEnglishLanguage();
    if (duplicatedLanguageLine != -1) {
        qDebug() << "English language definition already exists!";
    } else {
        setPackage(PACK_BABEL, LANG_ENGLISH);
    }
    qDebug() << "English language definition was set correctly!";
}
int TeXFile::removeEnglishLanguage()
{
    int definitionLanguageLine = getEnglishLanguage();
    if (definitionLanguageLine != -1) {
        fileContent.removeAt(definitionLanguageLine);
    }
    return definitionLanguageLine;
}
int TeXFile::getEnglishLanguage()
{
    return getPackage(PACK_BABEL, LANG_ENGLISH);
}
void TeXFile::setMainFont(QString fontName)
{
    int preambleLine = getDocumentPreamble();
    int beginDocumentLine = getBeginDocumentCommand();
    if (preambleLine != -1 && beginDocumentLine != -1) {
        deleteMainFont();
        fileContent.insert(beginDocumentLine - preambleLine + 1,
                           command.callSetMainFont(fontName));
        qDebug() << "Font " + fontName + "  was set correctly!";
    } else {
        qDebug() << ("Document preamble or document beginning was not set! The font " + fontName +
                     " was not set correctly...");
    }
}
int TeXFile::getMainFont(QString fontName)
{
    return getLineNumber(command.callSetMainFont(fontName));
}
void TeXFile::deleteMainFont()
{
    int mainFontLine = getLineNumber(command.callSetMainFont());
    if (mainFontLine != -1) {
        fileContent.removeAt(mainFontLine);
    }
}
void TeXFile::setPackage(QString packageName)
{
    int duplicatedPackageLine = getPackage(packageName);
    int preambleLine = getDocumentPreamble();
    int beginDocumentLine = getBeginDocumentCommand();
    if (preambleLine != -1 && beginDocumentLine != -1) {
        if (duplicatedPackageLine != -1) {
            qDebug() << "Package " + packageName + " already exists!";
        } else {
            fileContent.insert(beginDocumentLine - preambleLine ,
                               command.callUsePackage(packageName));
        }
        qDebug() << "Package " + packageName + "  was set correctly!";
    } else {
        qDebug() << preambleLine;
        qDebug() << beginDocumentLine;
        qDebug() << "Document preamble or document beginning was not set! The package " +
                 packageName + " was not set correctly...";
    }
}
void TeXFile::setPackage(QString packageName, QString packageOptions)
{
    int duplicatedPackageLine = getPackage(packageName, packageOptions);
    int preambleLine = getDocumentPreamble();
    int beginDocumentLine = getBeginDocumentCommand();
    if (preambleLine != -1 && beginDocumentLine != -1) {
        if (duplicatedPackageLine != -1) {
            qDebug() << "Package " + packageName + " already exists!";
        } else {
            fileContent.insert(beginDocumentLine - preambleLine,
                               command.callUsePackage(packageName, packageOptions));
        }
        qDebug() << "Package " + packageName + " with options " + packageOptions +
                 " was set correctly!";
    } else {
        qDebug() << "Document preamble or document beginning was not set! The package " +
                 packageName + " was not set correctly...";
    }
}
int TeXFile::getPackage(QString packageName)
{
    return getLineNumber(command.callUsePackage(packageName));
}
int TeXFile::getPackage(QString packageName, QString packageOptions)
{
    return getLineNumber(command.callUsePackage(packageName, packageOptions));
}
int TeXFile::getBibliographyLine()
{
    return getLineNumber(CMD_BIBLIOGRAPHY);
}

void TeXFile::setTeXCommand(QString commandDefinition)
{
    int endDocumentLine = getEndDocumentCommand();
    int bibliographyLine = getBibliographyLine();
    if (endDocumentLine != -1) {
        fileContent.insert(endDocumentLine, commandDefinition);
    } else {
        setEndDocumentCommand();
        if (bibliographyLine == -1) {
            fileContent.insert(getLineNumber(command.callEnd(ENV_DOCUMENT)), commandDefinition);
        } else {
            fileContent.insert(bibliographyLine, commandDefinition);
        }
    }
    qDebug() << "Command " + commandDefinition + " was set correctly!";
}
void TeXFile::setTeXCommand(QString command, int lineNumber)
{
    fileContent.insert(lineNumber, command);
    qDebug() << "Command  " + command + " was set correctly in position " + QString::number(
                 lineNumber) + " !";
}
void TeXFile::replaceTeXCommand(QString newCommand, int lineNumberToReplace)
{
    fileContent.replace(lineNumberToReplace, newCommand);
}
void TeXFile::deleteTeXCommand(int lineNumberToDelete)
{
    fileContent.removeAt(lineNumberToDelete);
    qDebug() << "Deleted " + QString::number(lineNumberToDelete);
}
void TeXFile::deleteTeXCommand(QString lineToDelete)
{
    QString currentLine;
    for (int lineNumber = 0; lineNumber < fileContent.length(); lineNumber++) {
        currentLine = fileContent.at(lineNumber);
        if (currentLine.compare(lineToDelete) == 0) {
            fileContent.removeAt(lineNumber);
        }
    }
}

void TeXFile::setDocumentPreamble(QString classFile)
{
    fileContent.insert(1, command.callDocumentClass(classFile));
    qDebug() << "Document Preamble was set correctly!";

}

void TeXFile::setDocumentPreamble(QString documentType, QString documentFontSize,
                                  QString paperLayout, QString paperSize, QString documentLayout, QString chapterLayout,
                                  QString columnLayout)
{
    _documentType = documentType;
    _documentFontSize = documentFontSize;
    _paperLayout = paperLayout;
    _paperSize = paperSize;
    _documentLayout = documentLayout;
    _chapterLayout = chapterLayout;
    _columnLayout = columnLayout;
    fileContent.insert(1, command.callDocumentClass(documentFontSize + "," + paperLayout + ","
                                                    + paperSize + "," +
                                                    documentLayout + "," + chapterLayout + "," + columnLayout, documentType));
    qDebug() << "Document Preamble was set correctly!";
}
int TeXFile::getDocumentPreamble()
{

    return getLineNumber(CMD_DOCUMENT_CLASS);
}
void TeXFile::clearCommands()
{
    fileContent.clear();
}
void TeXFile::writePlainText(QString content)
{
    setTeXCommand(content.append(CMD_LINE_BREAK));
}
void TeXFile::writePlainText(QString content, int lineNumber)
{
    setTeXCommand(content.append(CMD_LINE_BREAK), lineNumber);
}
void TeXFile::setNewLine()
{
    setTeXCommand(command.callLineBreak());
}
void TeXFile::setNewLine(int lineNumber)
{
    setTeXCommand(command.callLineBreak(), lineNumber);
}
void TeXFile::setNewParagraph()
{
    setTeXCommand(command.callParagraph());
}
void TeXFile::setNewParagraph(int lineNumber)
{
    setTeXCommand(command.callParagraph(), lineNumber);
}
void TeXFile::setNewPage()
{
    setTeXCommand(command.callNewPage());
    setTeXCommand(command.callThisPageStyle(PAGESTYLE_EMPTY));
    setTeXCommand(command.callMBox(""));
}
void TeXFile::setNewPage(int lineNumber)
{
    setTeXCommand(command.callNewPage(), lineNumber);
    setTeXCommand(command.callThisPageStyle(PAGESTYLE_EMPTY), lineNumber);
    setTeXCommand(command.callMBox(""), lineNumber);
}
QProcess *TeXFile::getProcess()
{
    return process;
}
void TeXFile::moveProcessToThread(QThread *thread)
{
    process->moveToThread(thread);
}

void TeXFile::compile(QString compilerPath)
{

    if (QFile(compilerPath).exists() && process->state() == QProcess::NotRunning) {
        QStringList commandArguments ;
        saveFile();
        commandArguments.append("-interaction=nonstopmode");
        commandArguments.append("\"" + file->fileName() + "\"");
        process->start(compilerPath, commandArguments, QIODevice::ReadWrite);
        process->waitForFinished();
        process->close();
        qDebug() << "Document " + getFileName() + " compiled.";
        emit documentCompiled();
    }
}
void TeXFile::compile(QString compilerPath, bool wait)
{
    if (QFile(compilerPath).exists() && process->state() == QProcess::NotRunning)  {
        QStringList commandArguments ;
        saveFile();
        commandArguments.append("-interaction=nonstopmode");
        commandArguments.append(file->fileName());
        process->start(compilerPath, commandArguments, QIODevice::ReadWrite);
        if (wait) {
            process->waitForFinished();
        }
        process->close();
        qDebug() << "Document " + getFileName() + " compiled.";
        emit documentCompiled();
    }
}

void TeXFile::close()
{
    QString path = "./";
    QDir dir(path);
    dir.setNameFilters(QStringList() << getFileName() + ".*");
    dir.setFilter(QDir::Files);
    foreach (QString dirFile, dir.entryList()) {
        dir.remove(dirFile);
    }
    file->close();
}
QString TeXFile::getDirectory()
{
    QFileInfo fileInfo(file->fileName());
    return fileInfo.path();
}
QStringList TeXFile::getFileContent()
{
    return fileContent;
}
QString TeXFile::getFileName()
{
    return _fileName;
}
QString TeXFile::getDocumentType()
{
    return _documentType;
}
QString TeXFile::getDocumentFontSize()
{
    return _documentFontSize;
}
QString TeXFile::getPaperSize()
{
    return _paperSize;
}
QString TeXFile::getDocumentLayout()
{
    return _documentLayout;
}
QString TeXFile::getColumnLayout()
{
    return _columnLayout;
}
QString TeXFile::getDocumentAddress()
{
    return _documentAddress;
}
QString TeXFile::getDocumentTitle()
{
    return _documentTitle;
}
QString TeXFile::getDocumentDate()
{
    return _documentDate;
}
QString TeXFile::getDocumentAuthor()
{
    return _documentAuthor;
}
void TeXFile::setDocumentAddress(QString address)
{
    this->_documentAddress = address;
}

void TeXFile::setDocumentTitle(QString title)
{
    this->_documentTitle = title;
}
void TeXFile::setDocumentDate(QString date)
{
    this->_documentDate = date;
}
void TeXFile::setDocumentAuthor(QString author)
{
    this->_documentAuthor = author;
}
void TeXFile::setDocumentType(QString type)
{
    this->_documentType = type;
}
void TeXFile::setDocumentFontSize(QString fontSize)
{
    this->_documentFontSize = fontSize;
}
void TeXFile::setPaperSize(QString paperSize)
{
    this->_paperSize = paperSize;
}
void TeXFile::setDocumentLayout(QString documentLayout)
{
    this->_documentLayout = documentLayout;
}
void TeXFile::setColumnLayout(QString columnLayout)
{
    this->_columnLayout = columnLayout;
}
void TeXFile::setChapterLayout(QString chapterLayout)
{
    this->_chapterLayout = chapterLayout;
}
int TeXFile::getDocumentTypeIndex()
{
    return _documentTypeIndex;
}
int TeXFile::getDocumentFontSizeIndex()
{
    return _documentFontSizeIndex;
}
int TeXFile::getPaperSizeIndex()
{
    return _paperSizeIndex;
}
int TeXFile::getDocumentLayoutIndex()
{
    return _documentLayoutIndex;
}
int TeXFile::getColumnLayoutIndex()
{
    return _columnLayoutIndex;
}
int TeXFile::getDocumentLanguageIndex()
{
    return _documentLanguageIndex;
}
int TeXFile::getChapterLayoutIndex()
{
    return _chapterLayoutIndex;
}
void TeXFile::setDocumentTypeIndex(int index)
{
    this->_documentTypeIndex = index;
}
void TeXFile::setDocumentFontSizeIndex(int index)
{
    this->_documentFontSizeIndex = index;
}
void TeXFile::setPaperSizeIndex(int index)
{
    this->_paperSizeIndex = index;
}
void TeXFile::setChapterLayoutIndex(int index)
{
    this->_chapterLayoutIndex = index;
}
void TeXFile::setDocumentLayoutIndex(int index)
{
    this->_documentLayoutIndex = index;
}
void TeXFile::setColumnLayoutIndex(int index)
{
    this->_columnLayoutIndex = index;
}
void TeXFile::setDocumentLanguageIndex(int index)
{
    this->_documentLanguageIndex = index;
}
void TeXFile::setAbstract(QString abstract)
{
    int beginDocumentLine = getBeginDocumentCommand();
    _documentAbstract = abstract ;
    setTeXCommand(command.callBegin(ENV_ABSTRACT, abstract), beginDocumentLine + 1);
}
void TeXFile::deleteAbstract()
{
    int abstractLine = getLineNumber(command.callBegin(ENV_ABSTRACT));
    if (abstractLine != -1) {
        fileContent.removeAt(abstractLine);
        _documentAbstract = "";
    }
}
void TeXFile::deleteAddress()
{
    int addressLine = getLineNumber(command.callAddress(getDocumentAddress()));
    if (addressLine != -1) {
        fileContent.removeAt(addressLine);
        _documentAddress = "";
    }
}
void TeXFile::deleteTitle()
{
    int titleLine = getLineNumber(command.callTitle(getDocumentTitle()));
    if (titleLine != -1) {
        fileContent.removeAt(titleLine);
        _documentTitle = "";
    }
}
void TeXFile::deleteAuthor()
{
    int authorLine = getLineNumber(command.callAuthor(getDocumentAuthor()));
    if (authorLine != -1) {
        fileContent.removeAt(authorLine);
        _documentAuthor = "";
    }
}
void TeXFile::deleteDate()
{
    int dateLine = getLineNumber(command.callDate(getDocumentDate()));
    if (dateLine != -1) {
        fileContent.removeAt(dateLine);
        _documentDate = "";
    }
}
QString TeXFile::getDocumentAbstract()
{
    return _documentAbstract;
}
void TeXFile::setDocumentAbstract(QString abstract)
{
    _documentAbstract = abstract;
}
void TeXFile::setAddress(QString address)
{
    int beginDateLine = getLineNumber(CMD_DATE);
    _documentAddress = address ;
    setTeXCommand(command.callAddress(getDocumentAddress()), beginDateLine + 1);
}

void TeXFile::setTitle(QString title)
{
    int beginDocumentLine = getBeginDocumentCommand();
    _documentTitle = title ;
    setTeXCommand(command.callTitle(getDocumentTitle()), beginDocumentLine + 1);
}
void TeXFile::setAuthor(QString author)
{
    int beginTitleLine = getLineNumber(CMD_TITLE);
    _documentAuthor = author ;
    setTeXCommand(command.callAuthor(getDocumentAuthor()), beginTitleLine + 1);
}
void TeXFile::setDate(QString date)
{
    int beginDateLine = getLineNumber(CMD_AUTHOR);
    _documentDate = date ;
    setTeXCommand(command.callDate(getDocumentDate()), beginDateLine + 1);
}
void TeXFile::precompile(QString compilerPath)
{
    if (QFile(compilerPath).exists()) {
        int lineNumber;
        QProcess *process = new QProcess(this);
        QStringList commandArguments ;
        process->setProcessChannelMode(QProcess::MergedChannels);
        commandArguments.append("-ini");
        commandArguments.append("-jobname=\"" + getFileName() + "\"");
        commandArguments.append("&" + compilerPath);
        commandArguments.append("mylatexformat.ltx");
        commandArguments.append("\"" + file->fileName() + "\"");
        process->start(compilerPath, commandArguments, QIODevice::ReadWrite);
        int documentClassLine = getLineNumber(command.callDocumentClass());
        int beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
        setTeXCommand(CMD_ENDOFDUMP, beginDocumentLine);

        for (lineNumber = documentClassLine + 1; lineNumber < beginDocumentLine; lineNumber++) {
            QString line = getFileContent().at(lineNumber);
            replaceTeXCommand("%" + line, lineNumber);
        }
        setTeXCommand("%&" + getFileName() , 0);
        process->close();
        saveFile();
        qDebug() << process->readAll();
        qDebug() << "Precompiled document!";
    }
}
void TeXFile::deprecompile()
{
    deleteTeXCommand(getLineNumber(CMD_ENDOFDUMP));
    if (getFileContent().at(0).contains("%&")) {
        fileContent.removeAt(0);
    }
    int documentClassLine = getLineNumber(command.callDocumentClass());
    int beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
    for (int i = documentClassLine + 1; i < beginDocumentLine; i++) {
        QString line = fileContent.at(i);
        if (line.contains(CMD_USE_PACKAGE)) {
            line = line.remove("%");
        }
        line = line.remove(CMD_ENDOFDUMP);
        replaceTeXCommand(line, i);
    }

    saveFile();

}
void TeXFile::deleteDocumentChapterContent(QString chapterCommand)
{
    int chapterToDeleteLine = getLineNumber(chapterCommand);
    int endDocumentLine = getEndDocumentCommand();
    int lineNumber = chapterToDeleteLine;

    for (lineNumber; lineNumber < endDocumentLine; lineNumber++) {
        chapterToDeleteLine = getLineNumber(chapterCommand);
        endDocumentLine = getEndDocumentCommand();
        if (!fileContent.at(lineNumber).contains(CMD_CHAPTER)) {
            fileContent.removeAt(lineNumber);
        } else {
            fileContent.removeAt(chapterToDeleteLine);
            break;
        }
    }
}
void TeXFile::deleteDocumentSectionContent(QString sectionCommand)
{
    int sectionToDeleteLine = getLineNumber(sectionCommand);
    int endDocumentLine = getEndDocumentCommand();
    int lineNumber = sectionToDeleteLine;
    for (lineNumber; lineNumber < endDocumentLine; lineNumber++) {
        sectionToDeleteLine = getLineNumber(sectionCommand);
        endDocumentLine = getEndDocumentCommand();
        if (!fileContent.at(lineNumber).contains(CMD_SECTION)
            && !fileContent.at(lineNumber).contains(CMD_CHAPTER)) {
            fileContent.removeAt(lineNumber);
        } else {
            fileContent.removeAt(sectionToDeleteLine);
            break;
        }
    }
}
void TeXFile::deleteDocumentSubSectionContent(QString subsectionCommand)
{
    int subsectionToDeleteLine = getLineNumber(subsectionCommand);
    int endDocumentLine = getEndDocumentCommand();
    int lineNumber = subsectionToDeleteLine;
    for (lineNumber; lineNumber < endDocumentLine; lineNumber++) {
        subsectionToDeleteLine = getLineNumber(subsectionCommand);
        endDocumentLine = getEndDocumentCommand();
        if (!fileContent.at(lineNumber).contains(CMD_SUBSECTION)
            && !fileContent.at(lineNumber).contains(CMD_CHAPTER)) {
            fileContent.removeAt(lineNumber);
        } else {
            fileContent.removeAt(subsectionToDeleteLine);
            break;
        }
    }
}
void TeXFile::fixImagePaths()
{
    for (int line = 0; line < fileContent.length(); line++) {
        QString lineString = fileContent.at(line);
        if (lineString.contains(CMD_LOGO)) {
            if (lineString.contains("/")) {
                QString imageName;
                QString imageOptions;
                QRegularExpression re("\\includegraphics.*\\{(.*?)\\}");
                QRegularExpressionMatch match = re.match(lineString);
                if (match.hasMatch()) {
                    imageName = match.captured(1).remove("./");
                    qDebug() << imageName;

                }

                QRegularExpression re2("\\includegraphics\\[(.*?)\\]");
                match = re2.match(lineString);
                if (match.hasMatch()) {
                    imageOptions = match.captured(1);

                }

                replaceTeXCommand(command.callLogo(command.callIncludeGraphics(getDirectory() + "/" + QFileInfo(
                                                                  imageName).fileName(), imageOptions)), line);
                saveFile();
            }

            if (lineString.contains("\\")) {
                QString imageName;
                QString imageOptions;
                QRegularExpression re("\\includegraphics.*\\{(.*?)\\}");
                QRegularExpressionMatch match = re.match(lineString);
                if (match.hasMatch()) {
                    imageName = match.captured(1).remove("./");

                }

                QRegularExpression re2("\\includegraphics\\[(.*?)\\]");
                match = re2.match(lineString);
                if (match.hasMatch()) {
                    imageOptions = match.captured(1);

                }

                replaceTeXCommand(command.callLogo(command.callIncludeGraphics(getDirectory() + "/" + QFileInfo(
                                                                  imageName).fileName(), imageOptions)), line);
                saveFile();
            }
        }


        else if (lineString.contains(CMD_INCLUDE_GRAPHICS)) {
            if (lineString.contains("/")) {
                QString imageName;
                QString imageOptions;
                QRegularExpression re("\\includegraphics.*\\{(.*?)\\}");
                QRegularExpressionMatch match = re.match(lineString);
                if (match.hasMatch()) {
                    imageName = match.captured(1).remove("./");
                    qDebug() << imageName;

                }

                QRegularExpression re2("\\includegraphics\\[(.*?)\\]");
                match = re2.match(lineString);
                if (match.hasMatch()) {
                    imageOptions = match.captured(1);

                }

                replaceTeXCommand(command.callIncludeGraphics(getDirectory() + "/" + QFileInfo(
                                                                  imageName).fileName(), imageOptions), line);
                saveFile();
            }

            if (lineString.contains("\\")) {
                QString imageName;
                QString imageOptions;
                QRegularExpression re("\\includegraphics.*\\{(.*?)\\}");
                QRegularExpressionMatch match = re.match(lineString);
                if (match.hasMatch()) {
                    imageName = match.captured(1).remove("./");

                }

                QRegularExpression re2("\\includegraphics\\[(.*?)\\]");
                match = re2.match(lineString);
                if (match.hasMatch()) {
                    imageOptions = match.captured(1);

                }

                replaceTeXCommand(command.callIncludeGraphics(getDirectory() + "/" + QFileInfo(
                                                                  imageName).fileName(), imageOptions), line);
                saveFile();
            }
        }
    }
}

void TeXFile::deleteEmptyParagraphs()
{
    for (int line = 0; line < fileContent.length(); line++) {

        if (fileContent.at(line).contains(QString(CMD_JUSTIFY) + " " + QString(CMD_LINE_BREAK))) {
            deleteTeXCommand(line);
        }

        if (fileContent.at(line).contains(QString(CMD_JUSTIFY) + QString(CMD_LINE_BREAK))) {
            deleteTeXCommand(line);
        }

        if (fileContent.at(line).compare(QString(CMD_PARAGRAPH_BREAK)) == 0) {
            fileContent.replace(line, CMD_LINE_BREAK);
        }

        if (fileContent.at(line).contains(QString("\\\\\\\\"))) {
            QString newLine  = fileContent.at(line);
            fileContent.replace(line, newLine.replace("\\\\", "\n"));
        }


    }
    saveFile();

}

void TeXFile::deleteDocumentSubSubSectionContent(QString subsubsectionCommand)
{
    int subsubsectionToDeleteLine = getLineNumber(subsubsectionCommand);
    int endDocumentLine = getEndDocumentCommand();
    int lineNumber = subsubsectionToDeleteLine;
    for (lineNumber; lineNumber < endDocumentLine; lineNumber++) {
        subsubsectionToDeleteLine = getLineNumber(subsubsectionCommand);
        endDocumentLine = getEndDocumentCommand();
        if (!fileContent.at(lineNumber).contains(CMD_SUBSUBSECTION)
            && !fileContent.at(lineNumber).contains(CMD_CHAPTER)) {
            fileContent.removeAt(lineNumber);
        } else {
            fileContent.removeAt(subsubsectionToDeleteLine);
            break;
        }
    }
}
void TeXFile::setPaperLayoutIndex(int index)
{
    this->_paperLayoutIndex = index;
}
void TeXFile::setPaperLayout(QString paperLayout)
{
    this->_paperLayout = paperLayout;
}
QString TeXFile::getPaperLayout()
{
    return _paperLayout;
}
void TeXFile::setFileContent(QStringList content)
{
    this->fileContent = content;
}
void TeXFile::deleteTemporaryFiles()
{
    QString path = "./";
    QDir dir(path);
    dir.setNameFilters(QStringList() << getFileName() + ".*");
    dir.setFilter(QDir::Files);
    foreach (QString dirFile, dir.entryList()) {
        if (!dirFile.endsWith(".fmt")) {
            dir.remove(dirFile);
        }
    }
}
void TeXFile::convertToPlainText(QString converterPlainPath)
{
    if (QFile(converterPlainPath).exists()) {
        QProcess *process = new QProcess(this);
        QFile txtFile(getFileName() + ".txt");
        process->setProcessChannelMode(QProcess::MergedChannels);
        QTime elapsedTime;
        elapsedTime.start();
        qDebug() << "Converting to Plain Text the source file named " + file->fileName();
        QStringList commandArguments ;
        commandArguments.append(getDirectory() + "/" + getFileName() + "");
        process->start(converterPlainPath, commandArguments, QProcess::ReadWrite);
        if (wait) {
            process->waitForFinished(5000);

        }
        txtFile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&txtFile);
        out << process->readAll();
        txtFile.close();
        int elapsedMiliSeconds = elapsedTime.elapsed();
        qDebug() << "Converted in " + QString::number(elapsedMiliSeconds) + " miliseconds";
    }
}
void TeXFile::convertToHTML(QString converterHTMLPath)
{
    if (QFile(converterHTMLPath).exists()) {
        QProcess *process = new QProcess(this);
        process->setProcessChannelMode(QProcess::MergedChannels);
        QTime elapsedTime;
        elapsedTime.start();
        process->setProcessChannelMode(QProcess::MergedChannels);
        qDebug() << "Converting to HTML the source file named " + file->fileName();
        QStringList commandArguments ;
        commandArguments.append(getDirectory() + "/" + getFileName()  + ".tex");
        process->start(converterHTMLPath, commandArguments, QProcess::ReadWrite);
        if (wait) {
            process->waitForFinished(5000);

        }
        int elapsedMiliSeconds = elapsedTime.elapsed();
        qDebug() << process->readAll();
        qDebug() << "Converted in " + QString::number(elapsedMiliSeconds) + " miliseconds";
    }
}

void TeXFile::convertToRTF(QString converterRTFPath)
{
    if (QFile(converterRTFPath).exists()) {
        QProcess *process = new QProcess(this);
        process->setProcessChannelMode(QProcess::MergedChannels);
        QTime elapsedTime;
        elapsedTime.start();
        process->setProcessChannelMode(QProcess::MergedChannels);
        qDebug() << "Converting to RTF the source file named " + file->fileName();
        QStringList commandArguments ;
        commandArguments.append(getDirectory() + "/" + getFileName()  + ".tex");
        process->start(converterRTFPath, commandArguments, QProcess::ReadWrite);
        if (wait) {
            process->waitForFinished(5000);

        }
        int elapsedMiliSeconds = elapsedTime.elapsed();
        qDebug() << process->readAll();
        qDebug() << "Converted in " + QString::number(elapsedMiliSeconds) + " miliseconds";
    }
}

QList<QStringList> TeXFile::getFileContentHistory()
{
    return fileContentHistory;
}

void TeXFile::redoFileContentHistory(QString compilerPath)
{

    if (fileContentHistory.isEmpty()) {
        return;
    }

    if (_currentActionIndex < fileContentHistory.count()) {
        _currentActionIndex++;
        setFileContent(fileContentHistory.at(_currentActionIndex));
        file->open(QIODevice::WriteOnly | QFile::Truncate);
        QTextStream out(file);
        for (int i = 0; i < fileContent.length(); i++) {
            out << fileContent.at(i) + "\n";
        }
        file->close();
        compile(compilerPath);
        compile(compilerPath);
    }

}

void TeXFile::undoFileContentHistory(QString compilerPath)
{

    if (fileContentHistory.isEmpty()) {
        return;
    }
    if (_currentActionIndex > 0) {
        _currentActionIndex--;
        setFileContent(fileContentHistory.at(_currentActionIndex));
        file->open(QIODevice::WriteOnly | QFile::Truncate);
        QTextStream out(file);
        for (int i = 0; i < fileContent.length(); i++) {
            out << fileContent.at(i) + "\n";
        }
        file->close();
        compile(compilerPath);
        compile(compilerPath);
    }


}

int TeXFile::getCurrentActionIndex()
{
    return _currentActionIndex;
}

void TeXFile::enableCopyProtect(bool state)
{
    if (state)
    {
        setPackage(PACK_CMAP,FONT_RESETFONTS);

        setPackage(PACK_FANCYVRB);

       int beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));

       setTeXCommand(command.callBegin(ENV_VERBATIM_OUT) + "{OT1.cmap}",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("/CIDInit /ProcSet findresource begin",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("12 dict begin",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("begincmap",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("/CIDSystemInfo",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<< /Registry (TeX)",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("/Ordering (OT1)",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("/Supplement 0",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand(">> def",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("/CMapName /TeX-OT1-0 def",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("/CMapType 2 def",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("1 begincodespacerange",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<00> <7F>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("endcodespacerange",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("8 beginbfrange",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<00> <01> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<09> <0A> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<23> <26> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<28> <3B> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<3F> <5B> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<5D> <5E> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<61> <7A> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<7B> <7C> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("endbfrange",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("40 beginbfchar",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<02> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<03> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<04> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<05> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<06> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<07> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<08> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<0B> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<0C> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<0D> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<0E> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<0F> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<10> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<11> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<12> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<13> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<14> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<15> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<16> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<17> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<18> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<19> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<1A> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<1B> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<1C> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<1D> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<1E> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<1F> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<21> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<22> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<27> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<3C> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<3D> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<3E> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<5C> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<5F> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<60> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<7D> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<7E> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("<7F> <0000>",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("endbfchar",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("endcmap",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("CMapName currentdict /CMap defineresource pop",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("end",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand("end",beginDocumentLine);
       beginDocumentLine = getLineNumber(command.callBegin(ENV_DOCUMENT));
       setTeXCommand(command.callEnd(ENV_VERBATIM_OUT),beginDocumentLine);
       saveFile();

    }
    else
    {
       deleteTeXCommand(command.callBegin(ENV_VERBATIM_OUT) + "{OT1.cmap}");
       deleteTeXCommand("/CIDInit /ProcSet findresource begin");
       deleteTeXCommand("begincmap");
       deleteTeXCommand("/CIDSystemInfo");
       deleteTeXCommand("<< /Registry (TeX)");
       deleteTeXCommand("/Ordering (OT1)");
       deleteTeXCommand("/Supplement 0");
       deleteTeXCommand(">> def");
       deleteTeXCommand("/CMapName /TeX-OT1-0 def");
       deleteTeXCommand("/CMapType 2 def");
       deleteTeXCommand("1 begincodespacerange");
       deleteTeXCommand("<00> <7F>");
       deleteTeXCommand("endcodespacerange");
       deleteTeXCommand("8 beginbfrange");
       deleteTeXCommand("<00> <01> <0000>");
       deleteTeXCommand("<09> <0A> <0000>");
       deleteTeXCommand("<23> <26> <0000>");
       deleteTeXCommand("<28> <3B> <0000>");
       deleteTeXCommand("<3F> <5B> <0000>");
       deleteTeXCommand("<5D> <5E> <0000>");
       deleteTeXCommand("<61> <7A> <0000>");
       deleteTeXCommand("<7B> <7C> <0000>");
       deleteTeXCommand("endbfrange");
       deleteTeXCommand("40 beginbfchar");
       deleteTeXCommand("<02> <0000>");
       deleteTeXCommand("<03> <0000>");
       deleteTeXCommand("<04> <0000>");
       deleteTeXCommand("<05> <0000>");
       deleteTeXCommand("<06> <0000>");
       deleteTeXCommand("<07> <0000>");
       deleteTeXCommand("<08> <0000>");
       deleteTeXCommand("<0B> <0000>");
       deleteTeXCommand("<0C> <0000>");
       deleteTeXCommand("<0D> <0000>");
       deleteTeXCommand("<0E> <0000>");
       deleteTeXCommand("<0F> <0000>");
       deleteTeXCommand("<10> <0000>");
       deleteTeXCommand("<11> <0000>");
       deleteTeXCommand("<12> <0000>");
       deleteTeXCommand("<13> <0000>");
       deleteTeXCommand("<14> <0000>");
       deleteTeXCommand("<15> <0000>");
       deleteTeXCommand("<16> <0000>");
       deleteTeXCommand("<17> <0000>");
       deleteTeXCommand("<18> <0000>");
       deleteTeXCommand("<19> <0000>");
       deleteTeXCommand("<1A> <0000>");
       deleteTeXCommand("<1B> <0000>");
       deleteTeXCommand("<1C> <0000>");
       deleteTeXCommand("<1D> <0000>");
       deleteTeXCommand("<1E> <0000>");
       deleteTeXCommand("<1F> <0000>");
       deleteTeXCommand("<21> <0000>");
       deleteTeXCommand("<22> <0000>");
       deleteTeXCommand("<27> <0000>");
       deleteTeXCommand("<3C> <0000>");
       deleteTeXCommand("<3D> <0000>");
       deleteTeXCommand("<3E> <0000>");
       deleteTeXCommand("<5C> <0000>");
       deleteTeXCommand("<5F> <0000>");
       deleteTeXCommand("<60> <0000>");
       deleteTeXCommand("<7D> <0000>");
       deleteTeXCommand("<7E> <0000>");
       deleteTeXCommand("<7F> <0000>");
       deleteTeXCommand("endbfchar");
       deleteTeXCommand("endcmap");
       deleteTeXCommand("CMapName currentdict /CMap defineresource pop");
       deleteTeXCommand("end");
       deleteTeXCommand("end");
       deleteTeXCommand(command.callEnd(ENV_VERBATIM_OUT));
       saveFile();
    }
}

