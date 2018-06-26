#include "dialog_citations.h"
#include "ui_dialog_citations.h"

Dialog_Citations::Dialog_Citations(TeXFile *file, TeXBibliography *bibFile,
                                   int lineNumber, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Citations)
{
    ui->setupUi(this);
    this->bibFile = bibFile;
    bibFile->readFile();
    ui->listWidget->clear();
    articlesList.clear();
    articlesIDList.clear();
    bookletsList.clear();
    bookletsIDList.clear();
    booksList.clear();
    booksIDList.clear();
    inbooksList.clear();
    inbooksIDList.clear();
    incollectionsList.clear();
    incollectionsIDList.clear();
    inproceedingsList.clear();
    inproceedingsIDList.clear();
    manualsList.clear();
    manualsIDList.clear();
    thesisList.clear();
    thesisIDList.clear();
    proceedingsList.clear();
    proceedingsIDList.clear();
    reportsList.clear();
    reportsIDList.clear();
    this->articlesList = bibFile->getArticlesStringList();
    this->bookletsList = bibFile->getBookletsStringList();
    this->booksList = bibFile->getBooksStringList();
    this->inbooksList = bibFile->getInbooksStringList();
    this->incollectionsList = bibFile->getIncollectionsStringList();
    this->inproceedingsList = bibFile->getInproceedingsStringList();
    this->manualsList = bibFile->getManualsStringList();
    this->thesisList = bibFile->getThesisStringList();
    this->proceedingsList = bibFile->getProceedingsStringList();
    this->reportsList = bibFile->getReportsStringList();
    foreach (QStringList article, articlesList) {
        this->articlesIDList.append(article.at(0));
    }
    foreach (QStringList booklet, bookletsList) {
        this->bookletsIDList.append(booklet.at(0));
    }
    foreach (QStringList book, booksList) {
        this->booksIDList.append(book.at(0));
    }
    foreach (QStringList inbook, inbooksList) {
        this->inbooksIDList.append(inbook.at(0));
    }
    foreach (QStringList incollection, incollectionsList) {
        this->incollectionsIDList.append(incollection.at(0));
    }
    foreach (QStringList inproceeding, inproceedingsList) {
        this->inproceedingsIDList.append(inproceeding.at(0));
    }
    foreach (QStringList manual, manualsList) {
        this->manualsIDList.append(manual.at(0));
    }
    foreach (QStringList thesis, thesisList) {
        this->thesisIDList.append(thesis.at(0));
    }
    foreach (QStringList proceeding, proceedingsList) {
        this->proceedingsIDList.append(proceeding.at(0));
    }
    foreach (QStringList report, reportsList) {
        this->reportsIDList.append(report.at(0));
    }
    on_comboBoxCategory_currentIndexChanged(ui->comboBoxCategory->currentIndex());
    this->lineNumber = lineNumber;
    this->file = file;
}

Dialog_Citations::~Dialog_Citations()
{
    delete ui;
}

void Dialog_Citations::on_comboBoxCategory_currentIndexChanged(int index)
{
    ui->listWidget->clear();
    articlesIDList.removeDuplicates();
    booksIDList.removeDuplicates();
    bookletsIDList.removeDuplicates();
    inbooksIDList.removeDuplicates();
    incollectionsIDList.removeDuplicates();
    inproceedingsIDList.removeDuplicates();
    manualsIDList.removeDuplicates();
    thesisIDList.removeDuplicates();
    proceedingsIDList.removeDuplicates();
    reportsIDList.removeDuplicates();
    switch (index) {
    case 0: //all categories
        ui->listWidget->addItems(articlesIDList);
        ui->listWidget->addItems(booksIDList);
        ui->listWidget->addItems(bookletsIDList);
        ui->listWidget->addItems(inbooksIDList);
        ui->listWidget->addItems(incollectionsIDList);
        ui->listWidget->addItems(inproceedingsIDList);
        ui->listWidget->addItems(manualsIDList);
        ui->listWidget->addItems(thesisIDList);
        ui->listWidget->addItems(proceedingsIDList);
        ui->listWidget->addItems(reportsIDList);
        break;
    case 1: //article
        ui->listWidget->addItems(articlesIDList);
        break;
    case 2: //book
        ui->listWidget->addItems(booksIDList);
        break;
    case 3: //booklet
        ui->listWidget->addItems(bookletsIDList);
        break;
    case 4: //inbook
        ui->listWidget->addItems(inbooksIDList);
        break;
    case 5: //incollection
        ui->listWidget->addItems(incollectionsIDList);
        break;
    case 6: //inproceedings
        ui->listWidget->addItems(inproceedingsIDList);
        break;
    case 7: //manual
        ui->listWidget->addItems(manualsIDList);
        break;
    case 8: //thesis
        ui->listWidget->addItems(thesisIDList);
        break;
    case 9: //proceedings
        ui->listWidget->addItems(proceedingsIDList);
        break;
    case 10: //report
        ui->listWidget->addItems(reportsIDList);
        break;
    }
}

void Dialog_Citations::on_buttonBox_accepted()
{
    if (!ui->listWidget->currentItem()->text().isEmpty()) {
        QString line = file->getFileContent().at(lineNumber - 1);
        file->replaceTeXCommand(line.append(command->callCite(
                                                ui->listWidget->currentItem()->text())), lineNumber - 1);
        file->saveFile();
     }
}

void Dialog_Citations::on_buttonBox_helpRequested()
{
    QMessageBox::information(this, APP_NAME,
                             tr("You can select an available entry created with the Bibliography Manager and reference it on the document."));
}
