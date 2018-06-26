#include "bibliography.h"

TeXBibliography::TeXBibliography(QString filePath)
{
    file = new QFile(filePath);
    readFile();
}

TeXBibliography::~TeXBibliography()
{

}
bool TeXBibliography::existsFile()
{
    if (!file) {
        return false;
    }
    return QFileInfo(file->fileName()).exists();
}

void TeXBibliography::readFile()
{
    int position = 0;
    articlesList.clear();
    booksList.clear();
    bookletsList.clear();
    inbooksList.clear();
    incollectionsList.clear();
    inproceedingsList.clear();
    manualsList.clear();
    thesisList.clear();
    proceedingsList.clear();
    reportsList.clear();
    file->open(QIODevice::ReadWrite);
    QTextStream in(file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        fileContent.append(line);
    }
    foreach (QString line, fileContent) {
        if (line.contains("@article{")) {
            article newArticle;
            for (int subElement = position; subElement < fileContent.length(); subElement++) {
                if (!fileContent.at(subElement).contains("}")) {
                    QRegularExpression IDregularExpression("{(.*?),");
                    QRegularExpressionMatch match = IDregularExpression.match(fileContent.at(subElement));
                    if (match.hasMatch()) {
                        newArticle.id = match.captured(1);
                    }
                    QRegularExpression re("(.*?) = \"(.*?)\"\,");
                    QRegularExpressionMatchIterator iteration = re.globalMatch(fileContent.at(subElement));
                    while (iteration.hasNext()) {
                        QRegularExpressionMatch match = iteration.next();
                        if (match.captured(1).contains("author")) {
                            newArticle.author = match.captured(2);
                        }
                        if (match.captured(1).contains("title")) {
                            newArticle.title = match.captured(2);
                        }
                        if (match.captured(1).contains("journal")) {
                            newArticle.journal = match.captured(2);
                        }
                        if (match.captured(1).contains("volume")) {
                            newArticle.volume = match.captured(2);
                        }
                        if (match.captured(1).contains("number")) {
                            newArticle.number = match.captured(2);
                        }
                        if (match.captured(1).contains("pages")) {
                            newArticle.pages = match.captured(2);
                        }
                        if (match.captured(1).contains("year")) {
                            newArticle.year = match.captured(2);
                        }
                    }
                } else {
                    articlesList.append(newArticle);
                    break;
                }
            }
        } else if (line.contains("@book{")) {
            book newBook;
            for (int subElement = position; subElement < fileContent.length(); subElement++) {
                if (!fileContent.at(subElement).contains("}")) {
                    QRegularExpression IDregularExpression("{(.*?),");
                    QRegularExpressionMatch match = IDregularExpression.match(fileContent.at(subElement));
                    if (match.hasMatch()) {
                        newBook.id = match.captured(1);
                    }
                    QRegularExpression re("(.*?) = \"(.*?)\"\,");
                    QRegularExpressionMatchIterator iteration = re.globalMatch(fileContent.at(subElement));
                    while (iteration.hasNext()) {
                        QRegularExpressionMatch match = iteration.next();
                        if (match.captured(1).contains("author")) {
                            newBook.author = match.captured(2);
                        }
                        if (match.captured(1).contains("title")) {
                            newBook.title = match.captured(2);
                        }
                        if (match.captured(1).contains("publisher")) {
                            newBook.publisher = match.captured(2);
                        }
                        if (match.captured(1).contains("volume")) {
                            newBook.volume = match.captured(2);
                        }
                        if (match.captured(1).contains("number")) {
                            newBook.number = match.captured(2);
                        }
                        if (match.captured(1).contains("edition")) {
                            newBook.edition = match.captured(2);
                        }
                        if (match.captured(1).contains("year")) {
                            newBook.year = match.captured(2);
                        }
                    }
                } else {
                    booksList.append(newBook);
                    break;
                }
            }

        } else if (line.contains("@booklet{")) {
            booklet newBooklet;
            for (int subElement = position; subElement < fileContent.length(); subElement++) {
                if (!fileContent.at(subElement).contains("}")) {
                    QRegularExpression IDregularExpression("{(.*?),");
                    QRegularExpressionMatch match = IDregularExpression.match(fileContent.at(subElement));
                    if (match.hasMatch()) {
                        newBooklet.id = match.captured(1);
                    }
                    QRegularExpression re("(.*?) = \"(.*?)\"\,");
                    QRegularExpressionMatchIterator iteration = re.globalMatch(fileContent.at(subElement));
                    while (iteration.hasNext()) {
                        QRegularExpressionMatch match = iteration.next();
                        if (match.captured(1).contains("author")) {
                            newBooklet.author = match.captured(2);
                        }
                        if (match.captured(1).contains("title")) {
                            newBooklet.title = match.captured(2);
                        }
                        if (match.captured(1).contains("howpublished")) {
                            newBooklet.howPublished = match.captured(2);
                        }
                        if (match.captured(1).contains("address")) {
                            newBooklet.address = match.captured(2);
                        }
                        if (match.captured(1).contains("year")) {
                            newBooklet.year = match.captured(2);
                        }
                        if (match.captured(1).contains("month")) {
                            newBooklet.month = match.captured(2);
                        }
                        if (match.captured(1).contains("note")) {
                            newBooklet.note = match.captured(2);
                        }
                    }
                } else {
                    bookletsList.append(newBooklet);
                    break;
                }
            }

        } else if (line.contains("@inbook{")) {
            inbook newInbook;
            for (int subElement = position; subElement < fileContent.length(); subElement++) {
                if (!fileContent.at(subElement).contains("}")) {
                    QRegularExpression IDregularExpression("{(.*?),");
                    QRegularExpressionMatch match = IDregularExpression.match(fileContent.at(subElement));
                    if (match.hasMatch()) {
                        newInbook.id = match.captured(1);
                    }
                    QRegularExpression re("(.*?) = \"(.*?)\"\,");
                    QRegularExpressionMatchIterator iteration = re.globalMatch(fileContent.at(subElement));
                    while (iteration.hasNext()) {
                        QRegularExpressionMatch match = iteration.next();
                        if (match.captured(1).contains("author")) {
                            newInbook.author = match.captured(2);
                        }
                        if (match.captured(1).contains("editor")) {
                            newInbook.editor = match.captured(2);
                        }
                        if (match.captured(1).contains("title")) {
                            newInbook.title = match.captured(2);
                        }
                        if (match.captured(1).contains("chapter")) {
                            newInbook.chapter = match.captured(2);
                        }
                        if (match.captured(1).contains("pages")) {
                            newInbook.pages = match.captured(2);
                        }
                        if (match.captured(1).contains("publisher")) {
                            newInbook.publisher = match.captured(2);
                        }
                        if (match.captured(1).contains("year")) {
                            newInbook.year = match.captured(2);
                        }
                    }
                } else {
                    inbooksList.append(newInbook);
                    break;
                }
            }

        } else if (line.contains("@incollection{")) {
            incollection newIncollection;
            for (int subElement = position; subElement < fileContent.length(); subElement++) {
                if (!fileContent.at(subElement).contains("}")) {
                    QRegularExpression IDregularExpression("{(.*?),");
                    QRegularExpressionMatch match = IDregularExpression.match(fileContent.at(subElement));
                    if (match.hasMatch()) {
                        newIncollection.id = match.captured(1);
                    }
                    QRegularExpression re("(.*?) = \"(.*?)\"\,");
                    QRegularExpressionMatchIterator iteration = re.globalMatch(fileContent.at(subElement));
                    while (iteration.hasNext()) {
                        QRegularExpressionMatch match = iteration.next();
                        if (match.captured(1).contains("author")) {
                            newIncollection.author = match.captured(2);
                        }
                        if (match.captured(1).contains("title")) {
                            newIncollection.title = match.captured(2);
                        }
                        if (match.captured(1).contains("booktitle")) {
                            newIncollection.bookTitle = match.captured(2);
                        }
                        if (match.captured(1).contains("publisher")) {
                            newIncollection.publisher = match.captured(2);
                        }
                        if (match.captured(1).contains("chapter")) {
                            newIncollection.chapter = match.captured(2);
                        }
                        if (match.captured(1).contains("edition")) {
                            newIncollection.edition = match.captured(2);
                        }
                        if (match.captured(1).contains("year")) {
                            newIncollection.year = match.captured(2);
                        }
                    }
                } else {
                    incollectionsList.append(newIncollection);
                    break;
                }
            }

        } else if (line.contains("@inproceedings{")) {
            inproceedings newInproceedings;
            for (int subElement = position; subElement < fileContent.length(); subElement++) {
                if (!fileContent.at(subElement).contains("}")) {
                    QRegularExpression IDregularExpression("{(.*?),");
                    QRegularExpressionMatch match = IDregularExpression.match(fileContent.at(subElement));
                    if (match.hasMatch()) {
                        newInproceedings.id = match.captured(1);
                    }
                    QRegularExpression re("(.*?) = \"(.*?)\"\,");
                    QRegularExpressionMatchIterator iteration = re.globalMatch(fileContent.at(subElement));
                    while (iteration.hasNext()) {
                        QRegularExpressionMatch match = iteration.next();
                        if (match.captured(1).contains("author")) {
                            newInproceedings.author = match.captured(2);
                        }
                        if (match.captured(1).contains("title")) {
                            newInproceedings.title = match.captured(2);
                        }
                        if (match.captured(1).contains("booktitle")) {
                            newInproceedings.bookTitle = match.captured(2);
                        }
                        if (match.captured(1).contains("publisher")) {
                            newInproceedings.publisher = match.captured(2);
                        }
                        if (match.captured(1).contains("organization")) {
                            newInproceedings.organization = match.captured(2);
                        }
                        if (match.captured(1).contains("publisher")) {
                            newInproceedings.publisher = match.captured(2);
                        }
                        if (match.captured(1).contains("year")) {
                            newInproceedings.year = match.captured(2);
                        }
                    }
                } else {
                    inproceedingsList.append(newInproceedings);
                    break;
                }
            }

        } else if (line.contains("@manual{")) {
            manual newManual;

            for (int subElement = position; subElement < fileContent.length(); subElement++) {
                if (!fileContent.at(subElement).contains("}")) {
                    QRegularExpression IDregularExpression("{(.*?),");
                    QRegularExpressionMatch match = IDregularExpression.match(fileContent.at(subElement));
                    if (match.hasMatch()) {
                        newManual.id = match.captured(1);
                    }
                    QRegularExpression re("(.*?) = \"(.*?)\"\,");
                    QRegularExpressionMatchIterator iteration = re.globalMatch(fileContent.at(subElement));
                    while (iteration.hasNext()) {
                        QRegularExpressionMatch match = iteration.next();
                        if (match.captured(1).contains("author")) {
                            newManual.author = match.captured(2);
                        }
                        if (match.captured(1).contains("title")) {
                            newManual.title = match.captured(2);
                        }
                        if (match.captured(1).contains("organization")) {
                            newManual.organization = match.captured(2);
                        }
                        if (match.captured(1).contains("edition")) {
                            newManual.edition = match.captured(2);
                        }
                        if (match.captured(1).contains("organization")) {
                            newManual.organization = match.captured(2);
                        }
                        if (match.captured(1).contains("month")) {
                            newManual.month = match.captured(2);
                        }
                        if (match.captured(1).contains("year")) {
                            newManual.year = match.captured(2);
                        }
                    }
                } else {
                    manualsList.append(newManual);
                    break;
                }
            }

        } else if (line.contains("@mastersthesis{")) {
            thesis newThesis;
            for (int subElement = position; subElement < fileContent.length(); subElement++) {
                if (!fileContent.at(subElement).contains("}")) {
                    QRegularExpression IDregularExpression("{(.*?),");
                    QRegularExpressionMatch match = IDregularExpression.match(fileContent.at(subElement));
                    if (match.hasMatch()) {
                        newThesis.id = match.captured(1);
                    }
                    QRegularExpression re("(.*?) = \"(.*?)\"\,");
                    QRegularExpressionMatchIterator iteration = re.globalMatch(fileContent.at(subElement));
                    while (iteration.hasNext()) {
                        QRegularExpressionMatch match = iteration.next();
                        if (match.captured(1).contains("author")) {
                            newThesis.author = match.captured(2);
                        }
                        if (match.captured(1).contains("title")) {
                            newThesis.title = match.captured(2);
                        }
                        if (match.captured(1).contains("school")) {
                            newThesis.school = match.captured(2);
                        }
                        if (match.captured(1).contains("type")) {
                            newThesis.type = match.captured(2);
                        }
                        if (match.captured(1).contains("address")) {
                            newThesis.address = match.captured(2);
                        }
                        if (match.captured(1).contains("month")) {
                            newThesis.month = match.captured(2);
                        }
                        if (match.captured(1).contains("year")) {
                            newThesis.year = match.captured(2);
                        }
                    }
                } else {
                    thesisList.append(newThesis);
                    break;
                }
            }
        } else if (line.contains("@proceedings{")) {
            proceedings newProceeding;
            for (int subElement = position; subElement < fileContent.length(); subElement++) {
                if (!fileContent.at(subElement).contains("}")) {
                    QRegularExpression IDregularExpression("{(.*?),");
                    QRegularExpressionMatch match = IDregularExpression.match(fileContent.at(subElement));
                    if (match.hasMatch()) {
                        newProceeding.id = match.captured(1);
                    }
                    QRegularExpression re("(.*?) = \"(.*?)\"\,");
                    QRegularExpressionMatchIterator iteration = re.globalMatch(fileContent.at(subElement));
                    while (iteration.hasNext()) {
                        QRegularExpressionMatch match = iteration.next();
                        if (match.captured(1).contains("title")) {
                            newProceeding.title = match.captured(2);
                        }
                        if (match.captured(1).contains("editor")) {
                            newProceeding.editor = match.captured(2);
                        }
                        if (match.captured(1).contains("volume")) {
                            newProceeding.volume = match.captured(2);
                        }
                        if (match.captured(1).contains("number")) {
                            newProceeding.number = match.captured(2);
                        }
                        if (match.captured(1).contains("organization")) {
                            newProceeding.organization = match.captured(2);
                        }
                        if (match.captured(1).contains("publisher")) {
                            newProceeding.publisher = match.captured(2);
                        }
                        if (match.captured(1).contains("year")) {
                            newProceeding.year = match.captured(2);
                        }
                    }
                } else {
                    proceedingsList.append(newProceeding);
                    break;
                }
            }

        } else if (line.contains("@techreport{")) {
            report newReport;
            for (int subElement = position; subElement < fileContent.length(); subElement++) {
                if (!fileContent.at(subElement).contains("}")) {
                    QRegularExpression IDregularExpression("{(.*?),");
                    QRegularExpressionMatch match = IDregularExpression.match(fileContent.at(subElement));
                    if (match.hasMatch()) {
                        newReport.id = match.captured(1);
                    }
                    QRegularExpression re("(.*?) = \"(.*?)\"\,");
                    QRegularExpressionMatchIterator iteration = re.globalMatch(fileContent.at(subElement));
                    while (iteration.hasNext()) {
                        QRegularExpressionMatch match = iteration.next();
                        if (match.captured(1).contains("title")) {
                            newReport.title = match.captured(2);
                        }
                        if (match.captured(1).contains("author")) {
                            newReport.author = match.captured(2);
                        }
                        if (match.captured(1).contains("institution")) {
                            newReport.institution = match.captured(2);
                        }
                        if (match.captured(1).contains("type")) {
                            newReport.type = match.captured(2);
                        }
                        if (match.captured(1).contains("number")) {
                            newReport.number = match.captured(2);
                        }
                        if (match.captured(1).contains("address")) {
                            newReport.address = match.captured(2);
                        }
                        if (match.captured(1).contains("year")) {
                            newReport.year = match.captured(2);
                        }
                    }
                } else {
                    reportsList.append(newReport);
                    break;
                }
            }

        }
        position++;
    }

    file->close();
}
QProcess *TeXBibliography::getProcess()
{
    return process;
}

void TeXBibliography::compile(QString compilerPath)
{
    if (QFile(compilerPath).exists())  {
        QStringList commandArguments ;
        commandArguments.append(QFileInfo(file->fileName()).fileName().remove(".bib"));
        process->start(compilerPath, commandArguments, QProcess::ReadWrite);
        process->waitForFinished();
        process->close();
    }
}
void TeXBibliography::compile(QString compilerPath, bool wait)
{
    if (QFile(compilerPath).exists())  {
        QStringList commandArguments ;
        commandArguments.append(QFileInfo(file->fileName()).fileName().remove(".bib"));
        process->start(compilerPath, commandArguments, QProcess::ReadWrite);
        if (wait) {
            process->waitForFinished();
        }
        process->close();
    }
}
void TeXBibliography::saveFile()
{
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(file);
    foreach (article item, articlesList) {
        stream << "@article{" + item.id + ",\n \t author = \" " + item.author +
               "\",\n \t title = \" " + item.title + "\",\n \t journal = \" " + item.journal +
               "\",\n \t volume = \" " + item.volume + "\",\n \t number = \" " + item.number +
               "\",\n \t pages = \" " + item.pages + "\",\n \t year = \" " + item.year + "\",\n }\n\n";
    }
    foreach (book item, booksList) {
        stream << "@book{" + item.id + ",\n \t author = \" " + item.author +
               "\",\n \t title = \" " + item.title + "\",\n \t publisher = \" " + item.publisher +
               "\",\n \t volume = \" " + item.volume + "\",\n \t number = \" " + item.number +
               "\",\n \t edition = \" " + item.edition + "\",\n \t year = \" " + item.year +
               "\",\n }\n\n";
    }
    foreach (booklet item, bookletsList) {
        stream << "@booklet{" + item.id + ",\n \t author = \" " + item.author +
               "\",\n \t title = \" " + item.title + "\",\n \t howpublished = \" " + item.howPublished +
               "\",\n \t address = \" " + item.address + "\",\n \t year = \" " + item.year +
               "\",\n \t month = \" " + item.month + "\",\n \t note = \" " + item.note + "\",\n }\n\n";
    }
    foreach (inbook item, inbooksList) {
        stream << "@inbook{" + item.id + ",\n \t author = \" " + item.author +
               "\",\n \t editor = \" " + item.editor + "\",\n \t title = \" " + item.title +
               "\",\n \t chapter = \" " + item.chapter + "\",\n \t pages = \" " + item.pages +
               "\",\n \t publisher = \" " + item.publisher + "\",\n \t year = \" " + item.year +
               "\",\n }\n\n";
    }
    foreach (incollection item, incollectionsList) {
        stream << "@incollection{" + item.id + ",\n \t author = \" " + item.author +
               "\",\n \t title = \" " + item.title + "\",\n \t booktitle = \" " + item.bookTitle +
               "\",\n \t publisher = \" " + item.publisher + "\",\n \t chapter = \" " + item.chapter +
               "\",\n \t edition = \" " + item.edition + "\",\n \t year = \" " + item.year +
               "\",\n }\n\n";
    }
    foreach (inproceedings item, inproceedingsList) {
        stream << "@inproceedings{" + item.id + ",\n \t author = \" " + item.author +
               "\",\n \t title = \" " + item.title + "\",\n \t booktitle = \" " + item.bookTitle +
               "\",\n \t editor = \" " + item.editor + "\",\n \t organization = \" " + item.organization
               + "\",\n \t publisher = \" " + item.publisher + "\",\n \t year = \" " + item.year +
               "\",\n }\n\n";
    }
    foreach (manual item, manualsList) {
        stream << "@manual{" + item.id + ",\n \t title = \" " + item.title +
               "\",\n \t author = \" " + item.author + "\",\n \t organization = \" " + item.organization
               + "\",\n \t edition = \" " + item.edition + "\",\n \t year = \" " + item.year +
               "\",\n \t month = \" " + item.month + "\",\n \t note = \" " + item.note + "\",\n }\n\n";
    }
    foreach (thesis item , thesisList) {
        stream << "@mastersthesis{" + item.id + ",\n \t author = \" " + item.author +
               "\",\n \t title = \" " + item.title + "\",\n \t school = \" " + item.school +
               "\",\n \t type = \" " + item.type + "\",\n \t address = \" " + item.address +
               "\",\n \t year = \" " + item.year + "\",\n \t month = \" " + item.month + "\",\n }\n\n";
    }
    foreach (proceedings item, proceedingsList) {
        stream << "@proceedings{" + item.id + ",\n \t title = \" " + item.title +
               "\",\n \t editor = \" " + item.editor + "\",\n \t volume = \" " + item.volume +
               "\",\n \t number = \" " + item.number + "\",\n \t organization = \" " + item.organization
               + "\",\n \t publisher = \" " + item.publisher + "\",\n \t year = \" " + item.year +
               "\",\n }\n\n";
    }
    foreach (report item, reportsList) {
        stream << "@techreport{" + item.id + ",\n \t author = \" " + item.author +
               "\",\n \t title = \" " + item.title + "\",\n \t institution = \" " + item.institution +
               "\",\n \t type = \" " + item.type + "\",\n \t number = \" " + item.number +
               "\",\n \t address = \" " + item.address + "\",\n \t year = \" " + item.year +
               "\",\n }\n\n";
    }
    file->copy(QFileInfo(file->fileName()).fileName());
    file->close();
}

void TeXBibliography::createArticleEntry(QString id, QString author, QString title,
                                         QString year, QString journal, QString volume, QString number, QString pages)
{
    article newArticle;
    newArticle.id = id;
    newArticle.author = author;
    newArticle.title = title;
    newArticle.year = year;
    newArticle.journal = journal;
    newArticle.volume = volume;
    newArticle.number = number;
    newArticle.pages = pages;
    articlesList.append(newArticle);
}

void TeXBibliography::createBookEntry(QString id, QString author, QString title,
                                      QString year, QString publisher, QString volume, QString number, QString edition)
{
    book newBook;
    newBook.id = id;
    newBook.author = author;
    newBook.title = title;
    newBook.year = year;
    newBook.publisher = publisher;
    newBook.volume = volume;
    newBook.number = number;
    newBook.edition = edition;
    booksList.append(newBook);
}

void TeXBibliography::createBookletEntry(QString id, QString author, QString title,
                                         QString year, QString address, QString month, QString note, QString howPublished)
{
    booklet newBooklet;
    newBooklet.id = id;
    newBooklet.author = author;
    newBooklet.title = title;
    newBooklet.year = year;
    newBooklet.address = address;
    newBooklet.month = month;
    newBooklet.note = note;
    newBooklet.howPublished = howPublished;
    bookletsList.append(newBooklet);
}

void TeXBibliography::createInbookEntry(QString id, QString author, QString title,
                                        QString year, QString editor, QString chapter, QString pages, QString publisher)
{
    inbook newInbook;
    newInbook.id = id;
    newInbook.author = author;
    newInbook.title = title;
    newInbook.year = year;
    newInbook.editor = editor;
    newInbook.chapter = chapter;
    newInbook.pages = pages;
    newInbook.publisher = publisher;
    inbooksList.append(newInbook);
}

void TeXBibliography::createIncollectionEntry(QString id, QString author, QString title,
                                              QString year, QString bookTitle, QString publisher, QString chapter, QString edition)
{
    incollection newIncollection;
    newIncollection.id = id;
    newIncollection.author = author;
    newIncollection.title = title;
    newIncollection.year = year;
    newIncollection.bookTitle = bookTitle;
    newIncollection.publisher = publisher;
    newIncollection.chapter = chapter;
    newIncollection.edition = edition;
    incollectionsList.append(newIncollection);
}

void TeXBibliography::createInproceedingsEntry(QString id, QString author, QString title,
                                               QString bookTitle, QString year, QString editor, QString publisher, QString organization)
{
    inproceedings newInproceeding;
    newInproceeding.id = id;
    newInproceeding.author = author;
    newInproceeding.title = title;
    newInproceeding.bookTitle = bookTitle;
    newInproceeding.year = year;
    newInproceeding.editor = editor;
    newInproceeding.publisher = publisher;
    newInproceeding.organization = organization;
    inproceedingsList.append(newInproceeding);
}

void TeXBibliography::createManualEntry(QString id, QString title, QString author,
                                        QString year, QString edition, QString month, QString organization, QString note)
{
    manual newManual;
    newManual.id = id;
    newManual.title = title;
    newManual.author = author;
    newManual.year = year;
    newManual.edition = edition;
    newManual.month = month;
    newManual.organization = organization;
    newManual.note = note;
    manualsList.append(newManual);
}

void TeXBibliography::createThesisEntry(QString id, QString title, QString author,
                                        QString year, QString type, QString address, QString month, QString school)
{
    thesis newThesis;
    newThesis.id = id;
    newThesis.title = title;
    newThesis.author = author;
    newThesis.year = year;
    newThesis.type = type;
    newThesis.address = address;
    newThesis.month = month;
    newThesis.school = school;
    thesisList.append(newThesis);
}

void TeXBibliography::createProceedingsEntry(QString id, QString title, QString publisher,
                                             QString year, QString editor, QString organization, QString volume, QString number)
{
    proceedings newProceeding;
    newProceeding.id = id;
    newProceeding.title = title;
    newProceeding.publisher = publisher;
    newProceeding.year = year;
    newProceeding.editor = editor;
    newProceeding.organization = organization;
    newProceeding.volume = volume;
    newProceeding.number = number;
    proceedingsList.append(newProceeding);
}

void TeXBibliography::createReportEntry(QString id,  QString author, QString title,
                                        QString institution, QString year, QString address, QString type, QString number)
{
    report newReport;
    newReport.id = id;
    newReport.author = author;
    newReport.title = title;
    newReport.institution = institution;
    newReport.year = year;
    newReport.address = address;
    newReport.type = type;
    newReport.number = number;
    reportsList.append(newReport);
}

void TeXBibliography::deleteArticleEntry(QString id)
{
    int position = 0;
    foreach (article item, articlesList) {
        if (item.id.compare(id) == 0) {
            articlesList.removeAt(position);
            break;
        }
        position++;
    }
}

void TeXBibliography::deleteBookEntry(QString id)
{
    int position = 0;
    foreach (book item, booksList) {
        if (item.id.compare(id) == 0) {
            booksList.removeAt(position);
            break;
        }
        position++;
    }
}

void TeXBibliography::deleteBookletEntry(QString id)
{
    int position = 0;
    foreach (booklet item, bookletsList) {
        if (item.id.compare(id) == 0) {
            bookletsList.removeAt(position);
            break;
        }
        position++;
    }
}

void TeXBibliography::deleteInbookEntry(QString id)
{
    int position = 0;
    foreach (inbook item, inbooksList) {
        if (item.id.compare(id) == 0) {
            inbooksList.removeAt(position);
            break;
        }
        position++;
    }
}

void TeXBibliography::deleteIncollectionEntry(QString id)
{
    int position = 0;
    foreach (incollection item, incollectionsList) {
        if (item.id.compare(id) == 0) {
            incollectionsList.removeAt(position);
            break;
        }
        position++;
    }
}

void TeXBibliography::deleteInproceedingsEntry(QString id)
{
    int position = 0;
    foreach (inproceedings item, inproceedingsList) {
        if (item.id.compare(id) == 0) {
            inproceedingsList.removeAt(position);
            break;
        }
        position++;

    }
}

void TeXBibliography::deleteManualEntry(QString id)
{
    int position = 0;
    foreach (manual item, manualsList) {
        if (item.id.compare(id) == 0) {
            manualsList.removeAt(position);
            break;
        }
        position++;
    }
}

void TeXBibliography::deleteThesisEntry(QString id)
{
    int position = 0;
    foreach (thesis item, thesisList) {
        if (item.id.compare(id) == 0) {
            thesisList.removeAt(position);
            break;
        }
        position++;
    }
}

void TeXBibliography::deleteProceedingsEntry(QString id)
{
    int position = 0;
    foreach (proceedings item, proceedingsList) {
        if (item.id.compare(id) == 0) {
            proceedingsList.removeAt(position);
            break;
        }
        position++;
    }
}

void TeXBibliography::deleteReportEntry(QString id)
{
    int position = 0;
    foreach (report item, reportsList) {
        if (item.id.compare(id) == 0) {
            reportsList.removeAt(position);
            break;
        }
        position++;
    }
}

bool TeXBibliography::isSelectedIDChosen(QString id)
{
    foreach (article item, articlesList) {
        if (item.id.compare(id) == 0) {
            return false;
        }
    }
    foreach (book item, booksList) {
        if (item.id.compare(id) == 0) {
            return false;
        }
    }
    foreach (booklet item, bookletsList) {
        if (item.id.compare(id) == 0) {
            return false;
        }
    }
    foreach (inbook item, inbooksList) {
        if (item.id.compare(id) == 0) {
            return false;
        }
    }
    foreach (incollection item, incollectionsList) {
        if (item.id.compare(id) == 0) {
            return false;
        }
    }
    foreach (inproceedings item, inproceedingsList) {
        if (item.id.compare(id) == 0) {
            return false;
        }
    }
    foreach (manual item, manualsList) {
        if (item.id.compare(id) == 0) {
            return false;
        }
    }
    foreach (thesis item, thesisList) {
        if (item.id.compare(id) == 0) {
            return false;
        }
    }
    foreach (proceedings item, proceedingsList) {
        if (item.id.compare(id) == 0) {
            return false;
        }
    }
    foreach (report item, reportsList) {
        if (item.id.compare(id) == 0) {
            return false;
        }
    }
    return true;
}


QList<QStringList> TeXBibliography::getArticlesStringList()
{
    QList<QStringList> list;
    QStringList row;
    list.clear();
    foreach (article item, articlesList) {
        row.clear();
        row.append(item.id);
        row.append(item.author);
        row.append(item.title);
        row.append(item.year);
        row.append(item.journal);
        row.append(item.volume);
        row.append(item.number);
        row.append(item.pages);
        list.append(row);
    }
    return list;
}
QList<QStringList> TeXBibliography::getBooksStringList()
{
    QList<QStringList> list;
    QStringList row;
    list.clear();
    foreach (book item, booksList) {
        row.clear();
        row.append(item.id);
        row.append(item.author);
        row.append(item.title);
        row.append(item.year);
        row.append(item.publisher);
        row.append(item.volume);
        row.append(item.number);
        row.append(item.edition);
        list.append(row);
    }
    return list;
}

QList<QStringList> TeXBibliography::getBookletsStringList()
{
    QList<QStringList> list;
    QStringList row;
    list.clear();
    foreach (booklet item, bookletsList) {
        row.clear();
        row.append(item.id);
        row.append(item.author);
        row.append(item.title);
        row.append(item.year);
        row.append(item.address);
        row.append(item.month);
        row.append(item.note);
        row.append(item.howPublished);
        list.append(row);
    }
    return list;
}

QList<QStringList> TeXBibliography::getInbooksStringList()
{
    QList<QStringList> list;
    QStringList row;
    list.clear();
    foreach (inbook item, inbooksList) {
        row.clear();
        row.append(item.id);
        row.append(item.author);
        row.append(item.title);
        row.append(item.year);
        row.append(item.editor);
        row.append(item.chapter);
        row.append(item.pages);
        row.append(item.publisher);
        list.append(row);
    }
    return list;
}

QList<QStringList> TeXBibliography::getIncollectionsStringList()
{
    QList<QStringList> list;
    QStringList row;
    list.clear();
    foreach (incollection item, incollectionsList) {
        row.clear();
        row.append(item.id);
        row.append(item.author);
        row.append(item.title);
        row.append(item.year);
        row.append(item.bookTitle);
        row.append(item.publisher);
        row.append(item.chapter);
        row.append(item.edition);
        list.append(row);
    }
    return list;
}

QList<QStringList> TeXBibliography::getInproceedingsStringList()
{
    QList<QStringList> list;
    QStringList row;
    list.clear();
    foreach (inproceedings item, inproceedingsList) {
        row.clear();
        row.append(item.id);
        row.append(item.title);
        row.append(item.bookTitle);
        row.append(item.author);
        row.append(item.editor);
        row.append(item.publisher);
        row.append(item.organization);
        row.append(item.year);
        list.append(row);
    }
    return list;
}

QList<QStringList> TeXBibliography::getManualsStringList()
{
    QList<QStringList> list;
    QStringList row;
    list.clear();
    foreach (manual item, manualsList) {
        row.clear();
        row.append(item.id);
        row.append(item.title);
        row.append(item.author);
        row.append(item.year);
        row.append(item.edition);
        row.append(item.month);
        row.append(item.organization);
        row.append(item.year);
        list.append(row);
    }
    return list;
}

QList<QStringList> TeXBibliography::getThesisStringList()
{
    QList<QStringList> list;
    QStringList row;
    list.clear();
    foreach (thesis item, thesisList) {
        row.clear();
        row.append(item.id);
        row.append(item.title);
        row.append(item.school);
        row.append(item.author);
        row.append(item.year);
        row.append(item.type);
        row.append(item.address);
        row.append(item.month);
        list.append(row);
    }
    return list;
}

QList<QStringList> TeXBibliography::getProceedingsStringList()
{
    QList<QStringList> list;
    QStringList row;
    list.clear();
    foreach (proceedings item, proceedingsList) {
        row.clear();
        row.append(item.id);
        row.append(item.title);
        row.append(item.publisher);
        row.append(item.year);
        row.append(item.editor);
        row.append(item.organization);
        row.append(item.volume);
        row.append(item.number);
        list.append(row);
    }
    return list;
}

QList<QStringList> TeXBibliography::getReportsStringList()
{
    QList<QStringList> list;
    QStringList row;
    list.clear();
    foreach (report item, reportsList) {
        row.clear();
        row.append(item.id);
        row.append(item.author);
        row.append(item.title);
        row.append(item.institution);
        row.append(item.year);
        row.append(item.address);
        row.append(item.type);
        row.append(item.number);
        list.append(row);
    }
    return list;
}
