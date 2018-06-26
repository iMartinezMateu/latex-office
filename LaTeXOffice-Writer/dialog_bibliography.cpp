#include "dialog_bibliography.h"
#include "ui_dialog_bibliography.h"

Dialog_Bibliography::Dialog_Bibliography(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Bibliography)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    ui->buttonBox->button(QDialogButtonBox::Help)->setText(tr("Help"));
}
void Dialog_Bibliography::setData(QString bibFilePath)
{
    this->bibFilePath = bibFilePath;
    file = new TeXBibliography(bibFilePath);
    foreach (QStringList row, file->getArticlesStringList()) {
        ui->tableWidgetArticles->insertRow(ui->tableWidgetArticles->rowCount());
        for (int column = 0; column < ui->tableWidgetArticles->columnCount(); column++) {
            ui->tableWidgetArticles->setItem(ui->tableWidgetArticles->rowCount() - 1, column,
                                             new QTableWidgetItem(row.at(column)));
        }
    }
    foreach (QStringList row, file->getBookletsStringList()) {
        ui->tableWidgetBooklets->insertRow(ui->tableWidgetBooklets->rowCount());
        for (int column = 0; column < ui->tableWidgetBooklets->columnCount(); column++) {
            ui->tableWidgetBooklets->setItem(ui->tableWidgetBooklets->rowCount() - 1, column,
                                             new QTableWidgetItem(row.at(column)));
        }
    }
    foreach (QStringList row, file->getBooksStringList()) {
        ui->tableWidgetBooks->insertRow(ui->tableWidgetBooks->rowCount());
        for (int column = 0; column < ui->tableWidgetBooks->columnCount(); column++) {
            ui->tableWidgetBooks->setItem(ui->tableWidgetBooks->rowCount() - 1, column,
                                          new QTableWidgetItem(row.at(column)));
        }
    }
    foreach (QStringList row, file->getInbooksStringList()) {
        ui->tableWidgetInbooks->insertRow(ui->tableWidgetInbooks->rowCount());
        for (int column = 0; column < ui->tableWidgetInbooks->columnCount(); column++) {
            ui->tableWidgetInbooks->setItem(ui->tableWidgetInbooks->rowCount() - 1, column,
                                            new QTableWidgetItem(row.at(column)));
        }
    }
    foreach (QStringList row, file->getIncollectionsStringList()) {
        ui->tableWidgetIncollections->insertRow(ui->tableWidgetIncollections->rowCount());
        for (int column = 0; column < ui->tableWidgetIncollections->columnCount(); column++) {
            ui->tableWidgetIncollections->setItem(ui->tableWidgetIncollections->rowCount() - 1,
                                                  column, new QTableWidgetItem(row.at(column)));
        }
    }
    foreach (QStringList row, file->getInproceedingsStringList()) {
        ui->tableWidgetInproceedings->insertRow(ui->tableWidgetInproceedings->rowCount());
        for (int column = 0; column < ui->tableWidgetInproceedings->columnCount(); column++) {
            ui->tableWidgetInproceedings->setItem(ui->tableWidgetInproceedings->rowCount() - 1,
                                                  column, new QTableWidgetItem(row.at(column)));
        }
    }
    foreach (QStringList row, file->getManualsStringList()) {
        ui->tableWidgetManuals->insertRow(ui->tableWidgetManuals->rowCount());
        for (int column = 0; column < ui->tableWidgetManuals->columnCount(); column++) {
            ui->tableWidgetManuals->setItem(ui->tableWidgetManuals->rowCount() - 1, column,
                                            new QTableWidgetItem(row.at(column)));
        }
    }
    foreach (QStringList row, file->getProceedingsStringList()) {
        ui->tableWidgetProceedings->insertRow(ui->tableWidgetProceedings->rowCount());
        for (int column = 0; column < ui->tableWidgetProceedings->columnCount(); column++) {
            ui->tableWidgetProceedings->setItem(ui->tableWidgetProceedings->rowCount() - 1, column,
                                                new QTableWidgetItem(row.at(column)));
        }
    }
    foreach (QStringList row, file->getReportsStringList()) {
        ui->tableWidgetReports->insertRow(ui->tableWidgetReports->rowCount());
        for (int column = 0; column < ui->tableWidgetReports->columnCount(); column++) {
            ui->tableWidgetReports->setItem(ui->tableWidgetReports->rowCount() - 1, column,
                                            new QTableWidgetItem(row.at(column)));
        }
    }
    foreach (QStringList row, file->getThesisStringList()) {
        ui->tableWidgetThesis->insertRow(ui->tableWidgetThesis->rowCount());
        for (int column = 0; column < ui->tableWidgetThesis->columnCount(); column++) {
            ui->tableWidgetThesis->setItem(ui->tableWidgetThesis->rowCount() - 1, column,
                                           new QTableWidgetItem(row.at(column)));
        }
    }
}

Dialog_Bibliography::~Dialog_Bibliography()
{
    delete ui;
}

void Dialog_Bibliography::on_pushButtonArticleReset_clicked()
{
    ui->lineEditArticleAuthor->clear();
    ui->lineEditArticleID->clear();
    ui->lineEditArticleJournal->clear();
    ui->lineEditArticleNumber->clear();
    ui->lineEditArticlePages->clear();
    ui->lineEditArticleTitle->clear();
    ui->lineEditArticleVolume->clear();
    ui->lineEditArticleYear->clear();
}

void Dialog_Bibliography::on_pushButtonBookReset_clicked()
{
    ui->lineEditBookAuthor->clear();
    ui->lineEditBookEdition->clear();
    ui->lineEditBookID->clear();
    ui->lineEditBookNumber->clear();
    ui->lineEditBookPublisher->clear();
    ui->lineEditBookTitle->clear();
    ui->lineEditBookVolume->clear();
    ui->lineEditBookYear->clear();
}

void Dialog_Bibliography::on_pushButtonBookletReset_clicked()
{
    ui->lineEditBookletAddress->clear();
    ui->lineEditBookletAuthor->clear();
    ui->lineEditBookletHowPublished->clear();
    ui->lineEditBookletID->clear();
    ui->lineEditBookletMonth->clear();
    ui->lineEditBookletNote->clear();
    ui->lineEditBookletTitle->clear();
    ui->lineEditBookletYear->clear();
}

void Dialog_Bibliography::on_pushButtonInbookReset_clicked()
{
    ui->lineEditInbookAddress->clear();
    ui->lineEditInbookAuthor->clear();
    ui->lineEditInbookChapter->clear();
    ui->lineEditInbookIdentificator->clear();
    ui->lineEditInbookPages->clear();
    ui->lineEditInbookPublisher->clear();
    ui->lineEditInbookTitle->clear();
    ui->lineEditInbookYear->clear();
}

void Dialog_Bibliography::on_pushButtonIncollectionReset_clicked()
{
    ui->lineEditIncollectionAuthor->clear();
    ui->lineEditIncollectionBookTitle->clear();
    ui->lineEditIncollectionChapter->clear();
    ui->lineEditIncollectionEdition->clear();
    ui->lineEditIncollectionIdentificator->clear();
    ui->lineEditIncollectionPublisher->clear();
    ui->lineEditIncollectionTitle->clear();
    ui->lineEditIncollectionYear->clear();
}

void Dialog_Bibliography::on_pushButtonInproceedingsReset_clicked()
{
    ui->lineEditInproceedingsAuthor->clear();
    ui->lineEditInproceedingsBookTitle->clear();
    ui->lineEditInproceedingsEditor->clear();
    ui->lineEditInproceedingsID->clear();
    ui->lineEditInproceedingsOrganization->clear();
    ui->lineEditInproceedingsPublisher->clear();
    ui->lineEditInproceedingsTitle->clear();
    ui->lineEditInproceedingsYear->clear();
}

void Dialog_Bibliography::on_pushButtonManualsReset_clicked()
{
    ui->lineEditManualsAuthor->clear();
    ui->lineEditManualsEdition->clear();
    ui->lineEditManualsID->clear();
    ui->lineEditManualsMonth->clear();
    ui->lineEditManualsNote->clear();
    ui->lineEditManualsOrganization->clear();
    ui->lineEditManualsTitle->clear();
    ui->lineEditManualsYear->clear();
}

void Dialog_Bibliography::on_pushButtonThesisReset_clicked()
{
    ui->lineEditThesisAddress->clear();
    ui->lineEditThesisAuthor->clear();
    ui->lineEditThesisID->clear();
    ui->lineEditThesisMonth->clear();
    ui->lineEditThesisSchool->clear();
    ui->lineEditThesisTitle->clear();
    ui->lineEditThesisType->clear();
    ui->lineEditThesisYear->clear();
}

void Dialog_Bibliography::on_pushButtonProceedingsReset_clicked()
{
    ui->lineEditProceedingsEditor->clear();
    ui->lineEditProceedingsIdentificator->clear();
    ui->lineEditProceedingsNumber->clear();
    ui->lineEditProceedingsOrganization->clear();
    ui->lineEditProceedingsPublisher->clear();
    ui->lineEditProceedingsTitle->clear();
    ui->lineEditProceedingsVolume->clear();
    ui->lineEditProceedingsYear->clear();
}

void Dialog_Bibliography::on_pushButtonReportsReset_clicked()
{
    ui->lineEditReportsAddress->clear();
    ui->lineEditReportsID->clear();
    ui->lineEditReportsInstitution->clear();
    ui->lineEditReportsAuthor->clear();
    ui->lineEditReportsNumber->clear();
    ui->lineEditReportsTitle->clear();
    ui->lineEditReportsType->clear();
    ui->lineEditReportsYear->clear();
}

void Dialog_Bibliography::on_lineEditArticleID_textChanged(const QString &arg1)
{
    if (arg1.contains(" ")) {
        ui->lineEditArticleID->setText(arg1.trimmed());
    }
    if (!file->isSelectedIDChosen(arg1) || arg1.length() < 5) {
        QToolTip::showText(ui->lineEditArticleID->mapToGlobal(QPoint()),
                           tr("  This identifier is already occupied or is too short. You must choose another."));
        ui->lineEditArticleID->setStyleSheet("color: #FF0000");
        ui->pushButtonArticleAddEntry->setEnabled(false);
    } else {
        ui->lineEditArticleID->setStyleSheet("color: #000000");
        ui->pushButtonArticleAddEntry->setEnabled(true);
    }
}

void Dialog_Bibliography::on_lineEditBookID_textChanged(const QString &arg1)
{
    if (arg1.contains(" ")) {
        ui->lineEditBookID->setText(arg1.trimmed());
    }
    if (!file->isSelectedIDChosen(arg1) || arg1.length() < 5) {
        QToolTip::showText(ui->lineEditBookID->mapToGlobal(QPoint()),
                           tr("  This identifier is already occupied or is too short. You must choose another."));
        ui->lineEditBookID->setStyleSheet("color: #FF0000");
        ui->pushButtonBookAddEntry->setEnabled(false);
    } else {
        ui->lineEditBookID->setStyleSheet("color: #000000");
        ui->pushButtonBookAddEntry->setEnabled(true);
    }
}

void Dialog_Bibliography::on_lineEditBookletID_textChanged(const QString &arg1)
{
    if (arg1.contains(" ")) {
        ui->lineEditBookletID->setText(arg1.trimmed());
    }
    if (!file->isSelectedIDChosen(arg1) || arg1.length() < 5) {
        QToolTip::showText(ui->lineEditBookletID->mapToGlobal(QPoint()),
                           tr("  This identifier is already occupied or is too short. You must choose another."));
        ui->lineEditBookletID->setStyleSheet("color: #FF0000");
        ui->pushButtonBookletAddEntry->setEnabled(false);
    } else {
        ui->lineEditBookletID->setStyleSheet("color: #000000");
        ui->pushButtonBookletAddEntry->setEnabled(true);
    }
}

void Dialog_Bibliography::on_lineEditInbookIdentificator_textChanged(const QString &arg1)
{
    if (arg1.contains(" ")) {
        ui->lineEditInbookIdentificator->setText(arg1.trimmed());
    }
    if (!file->isSelectedIDChosen(arg1) || arg1.length() < 5) {
        QToolTip::showText(ui->lineEditInbookIdentificator->mapToGlobal(QPoint()),
                           tr("  This identifier is already occupied or is too short. You must choose another."));
        ui->lineEditInbookIdentificator->setStyleSheet("color: #FF0000");
        ui->pushButtonInbookAddEntry->setEnabled(false);
    } else {
        ui->lineEditInbookIdentificator->setStyleSheet("color: #000000");
        ui->pushButtonInbookAddEntry->setEnabled(true);
    }
}

void Dialog_Bibliography::on_lineEditIncollectionIdentificator_textChanged(
    const QString &arg1)
{
    if (arg1.contains(" ")) {
        ui->lineEditIncollectionIdentificator->setText(arg1.trimmed());
    }
    if (!file->isSelectedIDChosen(arg1) || arg1.length() < 5) {
        QToolTip::showText(ui->lineEditIncollectionIdentificator->mapToGlobal(QPoint()),
                           tr("  This identifier is already occupied or is too short. You must choose another."));
        ui->lineEditIncollectionIdentificator->setStyleSheet("color: #FF0000");
        ui->pushButtonIncollectionAddEntry->setEnabled(false);
    } else {
        ui->lineEditIncollectionIdentificator->setStyleSheet("color: #000000");
        ui->pushButtonIncollectionAddEntry->setEnabled(true);
    }
}

void Dialog_Bibliography::on_lineEditInproceedingsID_textChanged(const QString &arg1)
{
    if (arg1.contains(" ")) {
        ui->lineEditInproceedingsID->setText(arg1.trimmed());
    }
    if (!file->isSelectedIDChosen(arg1) || arg1.length() < 5) {
        QToolTip::showText(ui->lineEditInproceedingsID->mapToGlobal(QPoint()),
                           tr("  This identifier is already occupied or is too short. You must choose another."));
        ui->lineEditInproceedingsID->setStyleSheet("color: #FF0000");
        ui->pushButtonInproceedingsAddEntry->setEnabled(false);
    } else {
        ui->lineEditInproceedingsID->setStyleSheet("color: #000000");
        ui->pushButtonInproceedingsAddEntry->setEnabled(true);
    }
}

void Dialog_Bibliography::on_lineEditManualsID_textChanged(const QString &arg1)
{
    if (arg1.contains(" ")) {
        ui->lineEditManualsID->setText(arg1.trimmed());
    }
    if (!file->isSelectedIDChosen(arg1) || arg1.length() < 5) {
        QToolTip::showText(ui->lineEditManualsID->mapToGlobal(QPoint()),
                           tr("  This identifier is already occupied or is too short. You must choose another."));
        ui->lineEditManualsID->setStyleSheet("color: #FF0000");
        ui->pushButtonManualsAddEntry->setEnabled(false);
    } else {
        ui->lineEditManualsID->setStyleSheet("color: #000000");
        ui->pushButtonManualsAddEntry->setEnabled(true);
    }
}

void Dialog_Bibliography::on_lineEditThesisID_textChanged(const QString &arg1)
{
    if (arg1.contains(" ")) {
        ui->lineEditThesisID->setText(arg1.trimmed());
    }
    if (!file->isSelectedIDChosen(arg1) || arg1.length() < 5) {
        QToolTip::showText(ui->lineEditThesisID->mapToGlobal(QPoint()),
                           tr("  This identifier is already occupied or is too short. You must choose another."));
        ui->lineEditThesisID->setStyleSheet("color: #FF0000");
        ui->pushButtonThesisAddEntry->setEnabled(false);
    } else {
        ui->lineEditThesisID->setStyleSheet("color: #000000");
        ui->pushButtonThesisAddEntry->setEnabled(true);
    }
}

void Dialog_Bibliography::on_lineEditProceedingsIdentificator_textChanged(
    const QString &arg1)
{
    if (arg1.contains(" ")) {
        ui->lineEditProceedingsIdentificator->setText(arg1.trimmed());
    }
    if (!file->isSelectedIDChosen(arg1) || arg1.length() < 5) {
        QToolTip::showText(ui->lineEditProceedingsIdentificator->mapToGlobal(QPoint()),
                           tr("  This identifier is already occupied or is too short. You must choose another."));
        ui->lineEditProceedingsIdentificator->setStyleSheet("color: #FF0000");
        ui->pushButtonProceedingsAddEntry->setEnabled(false);
    } else {
        ui->lineEditProceedingsIdentificator->setStyleSheet("color: #000000");
        ui->pushButtonProceedingsAddEntry->setEnabled(true);
    }
}

void Dialog_Bibliography::on_lineEditReportsID_textChanged(const QString &arg1)
{
    if (arg1.contains(" ")) {
        ui->lineEditReportsID->setText(arg1.trimmed());
    }
    if (!file->isSelectedIDChosen(arg1) || arg1.length() < 5) {
        QToolTip::showText(ui->lineEditReportsID->mapToGlobal(QPoint()),
                           tr("  This identifier is already occupied or is too short. You must choose another."));
        ui->lineEditReportsID->setStyleSheet("color: #FF0000");
        ui->pushButtonReportsAddEntry->setEnabled(false);
    } else {
        ui->lineEditReportsID->setStyleSheet("color: #000000");
        ui->pushButtonReportsAddEntry->setEnabled(true);
    }
}

void Dialog_Bibliography::on_pushButtonArticleAddEntry_clicked()
{
    file->createArticleEntry(ui->lineEditArticleID->text(), ui->lineEditArticleAuthor->text(),
                             ui->lineEditArticleTitle->text(), ui->lineEditArticleYear->text(),
                             ui->lineEditArticleJournal->text(), ui->lineEditArticleVolume->text(),
                             ui->lineEditArticleNumber->text(), ui->lineEditArticlePages->text());
    ui->tableWidgetArticles->insertRow(ui->tableWidgetArticles->rowCount());
    ui->tableWidgetArticles->setItem(ui->tableWidgetArticles->rowCount() - 1, 0,
                                     new QTableWidgetItem(ui->lineEditArticleID->text()));
    ui->tableWidgetArticles->setItem(ui->tableWidgetArticles->rowCount() - 1, 1,
                                     new QTableWidgetItem(ui->lineEditArticleAuthor->text()));
    ui->tableWidgetArticles->setItem(ui->tableWidgetArticles->rowCount() - 1, 2,
                                     new QTableWidgetItem(ui->lineEditArticleTitle->text()));
    ui->tableWidgetArticles->setItem(ui->tableWidgetArticles->rowCount() - 1, 3,
                                     new QTableWidgetItem(ui->lineEditArticleYear->text()));
    ui->tableWidgetArticles->setItem(ui->tableWidgetArticles->rowCount() - 1, 4,
                                     new QTableWidgetItem(ui->lineEditArticleJournal->text()));
    ui->tableWidgetArticles->setItem(ui->tableWidgetArticles->rowCount() - 1, 5,
                                     new QTableWidgetItem(ui->lineEditArticleVolume->text()));
    ui->tableWidgetArticles->setItem(ui->tableWidgetArticles->rowCount() - 1, 6,
                                     new QTableWidgetItem(ui->lineEditArticleNumber->text()));
    ui->tableWidgetArticles->setItem(ui->tableWidgetArticles->rowCount() - 1, 7,
                                     new QTableWidgetItem(ui->lineEditArticlePages->text()));
    ui->lineEditArticleAuthor->clear();
    ui->lineEditArticleID->clear();
    ui->lineEditArticleJournal->clear();
    ui->lineEditArticleNumber->clear();
    ui->lineEditArticlePages->clear();
    ui->lineEditArticleTitle->clear();
    ui->lineEditArticleVolume->clear();
    ui->lineEditArticleYear->clear();

}


void Dialog_Bibliography::on_tableWidgetArticles_itemSelectionChanged()
{
    if (ui->tableWidgetArticles->currentItem()->isSelected()) {
        ui->pushButtonArticleDelete->setEnabled(true);
    } else {
        ui->pushButtonArticleDelete->setEnabled(false);
    }
}

void Dialog_Bibliography::on_pushButtonArticleDelete_clicked()
{
    ui->tableWidgetArticles->clearSelection();
    file->deleteArticleEntry(ui->tableWidgetArticles->item(
                                 ui->tableWidgetArticles->currentRow(), 0)->text());
    ui->tableWidgetArticles->removeRow(ui->tableWidgetArticles->currentRow());
}

void Dialog_Bibliography::on_buttonBox_accepted()
{
    file->saveFile();
    file->compile(TeXCompiler::loadBIBCompilerPathSettings());
}

void Dialog_Bibliography::on_pushButtonBookAddEntry_clicked()
{
    file->createBookEntry(ui->lineEditBookID->text(), ui->lineEditBookAuthor->text(),
                          ui->lineEditBookTitle->text(), ui->lineEditBookYear->text(),
                          ui->lineEditBookPublisher->text(), ui->lineEditBookVolume->text(),
                          ui->lineEditBookNumber->text(), ui->lineEditBookEdition->text());
    ui->tableWidgetBooks->insertRow(ui->tableWidgetBooks->rowCount());
    ui->tableWidgetBooks->setItem(ui->tableWidgetBooks->rowCount() - 1, 0,
                                  new QTableWidgetItem(ui->lineEditBookID->text()));
    ui->tableWidgetBooks->setItem(ui->tableWidgetBooks->rowCount() - 1, 1,
                                  new QTableWidgetItem(ui->lineEditBookAuthor->text()));
    ui->tableWidgetBooks->setItem(ui->tableWidgetBooks->rowCount() - 1, 2,
                                  new QTableWidgetItem(ui->lineEditBookTitle->text()));
    ui->tableWidgetBooks->setItem(ui->tableWidgetBooks->rowCount() - 1, 3,
                                  new QTableWidgetItem(ui->lineEditBookYear->text()));
    ui->tableWidgetBooks->setItem(ui->tableWidgetBooks->rowCount() - 1, 4,
                                  new QTableWidgetItem(ui->lineEditBookPublisher->text()));
    ui->tableWidgetBooks->setItem(ui->tableWidgetBooks->rowCount() - 1, 5,
                                  new QTableWidgetItem(ui->lineEditBookVolume->text()));
    ui->tableWidgetBooks->setItem(ui->tableWidgetBooks->rowCount() - 1, 6,
                                  new QTableWidgetItem(ui->lineEditBookNumber->text()));
    ui->tableWidgetBooks->setItem(ui->tableWidgetBooks->rowCount() - 1, 7,
                                  new QTableWidgetItem(ui->lineEditBookEdition->text()));
    ui->lineEditBookID->clear();
    ui->lineEditBookAuthor->clear();
    ui->lineEditBookTitle->clear();
    ui->lineEditBookYear->clear();
    ui->lineEditBookPublisher->clear();
    ui->lineEditBookVolume->clear();
    ui->lineEditBookNumber->clear();
    ui->lineEditBookEdition->clear();
}

void Dialog_Bibliography::on_pushButtonBookDelete_clicked()
{
    ui->tableWidgetBooks->clearSelection();
    file->deleteBookEntry(ui->tableWidgetBooks->item(ui->tableWidgetBooks->currentRow(),
                                                     0)->text());
    ui->tableWidgetBooks->removeRow(ui->tableWidgetBooks->currentRow());
}

void Dialog_Bibliography::on_tableWidgetBooks_itemSelectionChanged()
{
    if (ui->tableWidgetBooks->currentItem()->isSelected()) {
        ui->pushButtonBookDelete->setEnabled(true);
    } else {
        ui->pushButtonBookDelete->setEnabled(false);
    }
}

void Dialog_Bibliography::on_pushButtonBookletAddEntry_clicked()
{
    file->createBookletEntry(ui->lineEditBookletID->text(), ui->lineEditBookletAuthor->text(),
                             ui->lineEditBookletTitle->text(), ui->lineEditBookletYear->text(),
                             ui->lineEditBookletAddress->text(), ui->lineEditBookletMonth->text(),
                             ui->lineEditBookletNote->text(), ui->lineEditBookletHowPublished->text());
    ui->tableWidgetBooklets->insertRow(ui->tableWidgetBooklets->rowCount());
    ui->tableWidgetBooklets->setItem(ui->tableWidgetBooklets->rowCount() - 1, 0,
                                     new QTableWidgetItem(ui->lineEditBookletID->text()));
    ui->tableWidgetBooklets->setItem(ui->tableWidgetBooklets->rowCount() - 1, 1,
                                     new QTableWidgetItem(ui->lineEditBookletAuthor->text()));
    ui->tableWidgetBooklets->setItem(ui->tableWidgetBooklets->rowCount() - 1, 2,
                                     new QTableWidgetItem(ui->lineEditBookletTitle->text()));
    ui->tableWidgetBooklets->setItem(ui->tableWidgetBooklets->rowCount() - 1, 3,
                                     new QTableWidgetItem(ui->lineEditBookletYear->text()));
    ui->tableWidgetBooklets->setItem(ui->tableWidgetBooklets->rowCount() - 1, 4,
                                     new QTableWidgetItem(ui->lineEditBookletAddress->text()));
    ui->tableWidgetBooklets->setItem(ui->tableWidgetBooklets->rowCount() - 1, 5,
                                     new QTableWidgetItem(ui->lineEditBookletMonth->text()));
    ui->tableWidgetBooklets->setItem(ui->tableWidgetBooklets->rowCount() - 1, 6,
                                     new QTableWidgetItem(ui->lineEditBookletNote->text()));
    ui->tableWidgetBooklets->setItem(ui->tableWidgetBooklets->rowCount() - 1, 7,
                                     new QTableWidgetItem(ui->lineEditBookletHowPublished->text()));
    ui->lineEditBookletID->clear();
    ui->lineEditBookletAuthor->clear();
    ui->lineEditBookletTitle->clear();
    ui->lineEditBookletYear->clear();
    ui->lineEditBookletAddress->clear();
    ui->lineEditBookletMonth->clear();
    ui->lineEditBookletNote->clear();
    ui->lineEditBookletHowPublished->clear();
}

void Dialog_Bibliography::on_pushButtonBookletDelete_clicked()
{
    ui->tableWidgetBooklets->clearSelection();
    file->deleteBookletEntry(ui->tableWidgetBooklets->item(
                                 ui->tableWidgetBooklets->currentRow(), 0)->text());
    ui->tableWidgetBooklets->removeRow(ui->tableWidgetBooklets->currentRow());
}

void Dialog_Bibliography::on_tableWidgetBooklets_itemSelectionChanged()
{
    if (ui->tableWidgetBooklets->currentItem()->isSelected()) {
        ui->pushButtonBookletDelete->setEnabled(true);
    } else {
        ui->pushButtonBookletDelete->setEnabled(false);
    }
}

void Dialog_Bibliography::on_pushButtonInbookAddEntry_clicked()
{
    file->createInbookEntry(ui->lineEditInbookIdentificator->text(),
                            ui->lineEditInbookAuthor->text(), ui->lineEditInbookTitle->text(),
                            ui->lineEditInbookYear->text(), ui->lineEditInbookAddress->text(),
                            ui->lineEditInbookChapter->text(), ui->lineEditInbookPages->text(),
                            ui->lineEditInbookPublisher->text());
    ui->tableWidgetInbooks->insertRow(ui->tableWidgetInbooks->rowCount());
    ui->tableWidgetInbooks->setItem(ui->tableWidgetInbooks->rowCount() - 1, 0,
                                    new QTableWidgetItem(ui->lineEditInbookIdentificator->text()));
    ui->tableWidgetInbooks->setItem(ui->tableWidgetInbooks->rowCount() - 1, 1,
                                    new QTableWidgetItem(ui->lineEditInbookAuthor->text()));
    ui->tableWidgetInbooks->setItem(ui->tableWidgetInbooks->rowCount() - 1, 2,
                                    new QTableWidgetItem(ui->lineEditInbookTitle->text()));
    ui->tableWidgetInbooks->setItem(ui->tableWidgetInbooks->rowCount() - 1, 3,
                                    new QTableWidgetItem(ui->lineEditInbookYear->text()));
    ui->tableWidgetInbooks->setItem(ui->tableWidgetInbooks->rowCount() - 1, 4,
                                    new QTableWidgetItem(ui->lineEditInbookAddress->text()));
    ui->tableWidgetInbooks->setItem(ui->tableWidgetInbooks->rowCount() - 1, 5,
                                    new QTableWidgetItem(ui->lineEditInbookChapter->text()));
    ui->tableWidgetInbooks->setItem(ui->tableWidgetInbooks->rowCount() - 1, 6,
                                    new QTableWidgetItem(ui->lineEditInbookPages->text()));
    ui->tableWidgetInbooks->setItem(ui->tableWidgetInbooks->rowCount() - 1, 7,
                                    new QTableWidgetItem(ui->lineEditInbookPublisher->text()));
    ui->lineEditInbookIdentificator->clear();
    ui->lineEditInbookAuthor->clear();
    ui->lineEditInbookTitle->clear();
    ui->lineEditInbookYear->clear();
    ui->lineEditInbookAddress->clear();
    ui->lineEditInbookChapter->clear();
    ui->lineEditInbookPages->clear();
    ui->lineEditInbookPublisher->clear();
}

void Dialog_Bibliography::on_tableWidgetInbooks_itemSelectionChanged()
{
    if (ui->tableWidgetInbooks->currentItem()->isSelected()) {
        ui->pushButtonInbookDelete->setEnabled(true);
    } else {
        ui->pushButtonInbookDelete->setEnabled(false);
    }
}

void Dialog_Bibliography::on_pushButtonInbookDelete_clicked()
{
    ui->tableWidgetInbooks->clearSelection();
    file->deleteInbookEntry(ui->tableWidgetInbooks->item(ui->tableWidgetInbooks->currentRow(),
                                                         0)->text());
    ui->tableWidgetInbooks->removeRow(ui->tableWidgetInbooks->currentRow());
}

void Dialog_Bibliography::on_pushButtonIncollectionAddEntry_clicked()
{
    file->createIncollectionEntry(ui->lineEditIncollectionIdentificator->text(),
                                  ui->lineEditIncollectionAuthor->text(), ui->lineEditIncollectionTitle->text(),
                                  ui->lineEditIncollectionYear->text(), ui->lineEditIncollectionBookTitle->text(),
                                  ui->lineEditIncollectionPublisher->text(), ui->lineEditIncollectionChapter->text(),
                                  ui->lineEditIncollectionEdition->text());
    ui->tableWidgetIncollections->insertRow(ui->tableWidgetIncollections->rowCount());
    ui->tableWidgetIncollections->setItem(ui->tableWidgetIncollections->rowCount() - 1, 0,
                                          new QTableWidgetItem(ui->lineEditIncollectionIdentificator->text()));
    ui->tableWidgetIncollections->setItem(ui->tableWidgetIncollections->rowCount() - 1, 1,
                                          new QTableWidgetItem(ui->lineEditIncollectionAuthor->text()));
    ui->tableWidgetIncollections->setItem(ui->tableWidgetIncollections->rowCount() - 1, 2,
                                          new QTableWidgetItem(ui->lineEditIncollectionTitle->text()));
    ui->tableWidgetIncollections->setItem(ui->tableWidgetIncollections->rowCount() - 1, 3,
                                          new QTableWidgetItem(ui->lineEditIncollectionYear->text()));
    ui->tableWidgetIncollections->setItem(ui->tableWidgetIncollections->rowCount() - 1, 4,
                                          new QTableWidgetItem(ui->lineEditIncollectionBookTitle->text()));
    ui->tableWidgetIncollections->setItem(ui->tableWidgetIncollections->rowCount() - 1, 5,
                                          new QTableWidgetItem(ui->lineEditIncollectionPublisher->text()));
    ui->tableWidgetIncollections->setItem(ui->tableWidgetIncollections->rowCount() - 1, 6,
                                          new QTableWidgetItem(ui->lineEditIncollectionChapter->text()));
    ui->tableWidgetIncollections->setItem(ui->tableWidgetIncollections->rowCount() - 1, 7,
                                          new QTableWidgetItem(ui->lineEditIncollectionEdition->text()));
    ui->lineEditIncollectionIdentificator->clear();
    ui->lineEditIncollectionAuthor->clear();
    ui->lineEditIncollectionTitle->clear();
    ui->lineEditIncollectionYear->clear();
    ui->lineEditIncollectionBookTitle->clear();
    ui->lineEditIncollectionPublisher->clear();
    ui->lineEditIncollectionChapter->clear();
    ui->lineEditIncollectionEdition->clear();
}

void Dialog_Bibliography::on_tableWidgetIncollections_itemSelectionChanged()
{
    if (ui->tableWidgetIncollections->currentItem()->isSelected()) {
        ui->pushButtonIncollectionDelete->setEnabled(true);
    } else {
        ui->pushButtonIncollectionDelete->setEnabled(false);
    }
}

void Dialog_Bibliography::on_pushButtonIncollectionDelete_clicked()
{
    ui->tableWidgetIncollections->clearSelection();
    file->deleteIncollectionEntry(ui->tableWidgetIncollections->item(
                                      ui->tableWidgetIncollections->currentRow(), 0)->text());
    ui->tableWidgetIncollections->removeRow(ui->tableWidgetIncollections->currentRow());
}

void Dialog_Bibliography::on_pushButtonInproceedingsAddEntry_clicked()
{
    file->createInproceedingsEntry(ui->lineEditInproceedingsID->text(),
                                   ui->lineEditInproceedingsAuthor->text(), ui->lineEditInproceedingsTitle->text(),
                                   ui->lineEditInproceedingsBookTitle->text(), ui->lineEditInproceedingsYear->text(),
                                   ui->lineEditInproceedingsEditor->text(), ui->lineEditInproceedingsPublisher->text(),
                                   ui->lineEditInproceedingsOrganization->text());
    ui->tableWidgetInproceedings->insertRow(ui->tableWidgetInproceedings->rowCount());
    ui->tableWidgetInproceedings->setItem(ui->tableWidgetInproceedings->rowCount() - 1, 0,
                                          new QTableWidgetItem(ui->lineEditInproceedingsID->text()));
    ui->tableWidgetInproceedings->setItem(ui->tableWidgetInproceedings->rowCount() - 1, 1,
                                          new QTableWidgetItem(ui->lineEditInproceedingsAuthor->text()));
    ui->tableWidgetInproceedings->setItem(ui->tableWidgetInproceedings->rowCount() - 1, 2,
                                          new QTableWidgetItem(ui->lineEditInproceedingsTitle->text()));
    ui->tableWidgetInproceedings->setItem(ui->tableWidgetInproceedings->rowCount() - 1, 3,
                                          new QTableWidgetItem(ui->lineEditInproceedingsBookTitle->text()));
    ui->tableWidgetInproceedings->setItem(ui->tableWidgetInproceedings->rowCount() - 1, 4,
                                          new QTableWidgetItem(ui->lineEditInproceedingsYear->text()));
    ui->tableWidgetInproceedings->setItem(ui->tableWidgetInproceedings->rowCount() - 1, 5,
                                          new QTableWidgetItem(ui->lineEditInproceedingsEditor->text()));
    ui->tableWidgetInproceedings->setItem(ui->tableWidgetInproceedings->rowCount() - 1, 6,
                                          new QTableWidgetItem(ui->lineEditInproceedingsPublisher->text()));
    ui->tableWidgetInproceedings->setItem(ui->tableWidgetInproceedings->rowCount() - 1, 7,
                                          new QTableWidgetItem(ui->lineEditInproceedingsOrganization->text()));
    ui->lineEditInproceedingsID->clear();
    ui->lineEditInproceedingsAuthor->clear();
    ui->lineEditInproceedingsTitle->clear();
    ui->lineEditInproceedingsBookTitle->clear();
    ui->lineEditInproceedingsYear->clear();
    ui->lineEditInproceedingsEditor->clear();
    ui->lineEditInproceedingsPublisher->clear();
    ui->lineEditInproceedingsOrganization->clear();
}

void Dialog_Bibliography::on_tableWidgetInproceedings_itemSelectionChanged()
{
    if (ui->tableWidgetInproceedings->currentItem()->isSelected()) {
        ui->pushButtonInproceedingsDelete->setEnabled(true);
    } else {
        ui->pushButtonInproceedingsDelete->setEnabled(false);
    }
}

void Dialog_Bibliography::on_pushButtonInproceedingsDelete_clicked()
{
    ui->tableWidgetInproceedings->clearSelection();
    file->deleteInproceedingsEntry(ui->tableWidgetInproceedings->item(
                                       ui->tableWidgetInproceedings->currentRow(), 0)->text());
    ui->tableWidgetInproceedings->removeRow(ui->tableWidgetInproceedings->currentRow());
}

void Dialog_Bibliography::on_pushButtonManualsAddEntry_clicked()
{
    file->createManualEntry(ui->lineEditManualsID->text(), ui->lineEditManualsTitle->text(),
                            ui->lineEditManualsAuthor->text(), ui->lineEditManualsYear->text(),
                            ui->lineEditManualsEdition->text(), ui->lineEditManualsMonth->text(),
                            ui->lineEditManualsOrganization->text(), ui->lineEditManualsNote->text());
    ui->tableWidgetManuals->insertRow(ui->tableWidgetManuals->rowCount());
    ui->tableWidgetManuals->setItem(ui->tableWidgetManuals->rowCount() - 1, 0,
                                    new QTableWidgetItem(ui->lineEditManualsID->text()));
    ui->tableWidgetManuals->setItem(ui->tableWidgetManuals->rowCount() - 1, 1,
                                    new QTableWidgetItem(ui->lineEditManualsTitle->text()));
    ui->tableWidgetManuals->setItem(ui->tableWidgetManuals->rowCount() - 1, 2,
                                    new QTableWidgetItem(ui->lineEditManualsAuthor->text()));
    ui->tableWidgetManuals->setItem(ui->tableWidgetManuals->rowCount() - 1, 3,
                                    new QTableWidgetItem(ui->lineEditManualsYear->text()));
    ui->tableWidgetManuals->setItem(ui->tableWidgetManuals->rowCount() - 1, 4,
                                    new QTableWidgetItem(ui->lineEditManualsEdition->text()));
    ui->tableWidgetManuals->setItem(ui->tableWidgetManuals->rowCount() - 1, 5,
                                    new QTableWidgetItem(ui->lineEditManualsMonth->text()));
    ui->tableWidgetManuals->setItem(ui->tableWidgetManuals->rowCount() - 1, 6,
                                    new QTableWidgetItem(ui->lineEditManualsOrganization->text()));
    ui->tableWidgetManuals->setItem(ui->tableWidgetManuals->rowCount() - 1, 7,
                                    new QTableWidgetItem(ui->lineEditManualsNote->text()));
    ui->lineEditManualsID->clear();
    ui->lineEditManualsTitle->clear();
    ui->lineEditManualsAuthor->clear();
    ui->lineEditManualsYear->clear();
    ui->lineEditManualsEdition->clear();
    ui->lineEditManualsMonth->clear();
    ui->lineEditManualsOrganization->clear();
    ui->lineEditManualsNote->clear();
}

void Dialog_Bibliography::on_tableWidgetManuals_itemSelectionChanged()
{
    if (ui->tableWidgetManuals->currentItem()->isSelected()) {
        ui->pushButtonManualDelete->setEnabled(true);
    } else {
        ui->pushButtonManualDelete->setEnabled(false);
    }
}

void Dialog_Bibliography::on_pushButtonManualDelete_clicked()
{
    ui->tableWidgetManuals->clearSelection();
    file->deleteManualEntry(ui->tableWidgetManuals->item(ui->tableWidgetManuals->currentRow(),
                                                         0)->text());
    ui->tableWidgetManuals->removeRow(ui->tableWidgetManuals->currentRow());
}

void Dialog_Bibliography::on_pushButtonThesisAddEntry_clicked()
{
    file->createThesisEntry(ui->lineEditThesisID->text(), ui->lineEditThesisTitle->text(),
                            ui->lineEditThesisAuthor->text(), ui->lineEditThesisYear->text(),
                            ui->lineEditThesisType->text(), ui->lineEditThesisAddress->text(),
                            ui->lineEditThesisMonth->text(), ui->lineEditThesisSchool->text());
    ui->tableWidgetThesis->insertRow(ui->tableWidgetThesis->rowCount());
    ui->tableWidgetThesis->setItem(ui->tableWidgetThesis->rowCount() - 1, 0,
                                   new QTableWidgetItem(ui->lineEditThesisID->text()));
    ui->tableWidgetThesis->setItem(ui->tableWidgetThesis->rowCount() - 1, 1,
                                   new QTableWidgetItem(ui->lineEditThesisTitle->text()));
    ui->tableWidgetThesis->setItem(ui->tableWidgetThesis->rowCount() - 1, 2,
                                   new QTableWidgetItem(ui->lineEditThesisAuthor->text()));
    ui->tableWidgetThesis->setItem(ui->tableWidgetThesis->rowCount() - 1, 3,
                                   new QTableWidgetItem(ui->lineEditThesisYear->text()));
    ui->tableWidgetThesis->setItem(ui->tableWidgetThesis->rowCount() - 1, 4,
                                   new QTableWidgetItem(ui->lineEditThesisType->text()));
    ui->tableWidgetThesis->setItem(ui->tableWidgetThesis->rowCount() - 1, 5,
                                   new QTableWidgetItem(ui->lineEditThesisAddress->text()));
    ui->tableWidgetThesis->setItem(ui->tableWidgetThesis->rowCount() - 1, 6,
                                   new QTableWidgetItem(ui->lineEditThesisMonth->text()));
    ui->tableWidgetThesis->setItem(ui->tableWidgetThesis->rowCount() - 1, 7,
                                   new QTableWidgetItem(ui->lineEditThesisSchool->text()));
    ui->lineEditThesisID->clear();
    ui->lineEditThesisTitle->clear();
    ui->lineEditThesisAuthor->clear();
    ui->lineEditThesisYear->clear();
    ui->lineEditThesisType->clear();
    ui->lineEditThesisAddress->clear();
    ui->lineEditThesisMonth->clear();
    ui->lineEditThesisSchool->clear();
}

void Dialog_Bibliography::on_tableWidgetThesis_itemSelectionChanged()
{
    if (ui->tableWidgetThesis->currentItem()->isSelected()) {
        ui->pushButtonThesisDelete->setEnabled(true);
    } else {
        ui->pushButtonThesisDelete->setEnabled(false);
    }
}

void Dialog_Bibliography::on_pushButtonThesisDelete_clicked()
{
    ui->tableWidgetThesis->clearSelection();
    file->deleteThesisEntry(ui->tableWidgetThesis->item(ui->tableWidgetThesis->currentRow(),
                                                        0)->text());
    ui->tableWidgetThesis->removeRow(ui->tableWidgetThesis->currentRow());
}

void Dialog_Bibliography::on_pushButtonProceedingsAddEntry_clicked()
{
    file->createProceedingsEntry(ui->lineEditProceedingsIdentificator->text(),
                                 ui->lineEditProceedingsTitle->text(), ui->lineEditProceedingsPublisher->text(),
                                 ui->lineEditProceedingsYear->text(), ui->lineEditProceedingsEditor->text(),
                                 ui->lineEditProceedingsOrganization->text(), ui->lineEditProceedingsVolume->text(),
                                 ui->lineEditProceedingsNumber->text());
    ui->tableWidgetProceedings->insertRow(ui->tableWidgetProceedings->rowCount());
    ui->tableWidgetProceedings->setItem(ui->tableWidgetProceedings->rowCount() - 1, 0,
                                        new QTableWidgetItem(ui->lineEditProceedingsIdentificator->text()));
    ui->tableWidgetProceedings->setItem(ui->tableWidgetProceedings->rowCount() - 1, 1,
                                        new QTableWidgetItem(ui->lineEditProceedingsTitle->text()));
    ui->tableWidgetProceedings->setItem(ui->tableWidgetProceedings->rowCount() - 1, 2,
                                        new QTableWidgetItem(ui->lineEditProceedingsPublisher->text()));
    ui->tableWidgetProceedings->setItem(ui->tableWidgetProceedings->rowCount() - 1, 3,
                                        new QTableWidgetItem(ui->lineEditProceedingsYear->text()));
    ui->tableWidgetProceedings->setItem(ui->tableWidgetProceedings->rowCount() - 1, 4,
                                        new QTableWidgetItem(ui->lineEditProceedingsEditor->text()));
    ui->tableWidgetProceedings->setItem(ui->tableWidgetProceedings->rowCount() - 1, 5,
                                        new QTableWidgetItem(ui->lineEditProceedingsOrganization->text()));
    ui->tableWidgetProceedings->setItem(ui->tableWidgetProceedings->rowCount() - 1, 6,
                                        new QTableWidgetItem(ui->lineEditProceedingsVolume->text()));
    ui->tableWidgetProceedings->setItem(ui->tableWidgetProceedings->rowCount() - 1, 7,
                                        new QTableWidgetItem(ui->lineEditProceedingsNumber->text()));
    ui->lineEditProceedingsIdentificator->clear();
    ui->lineEditProceedingsTitle->clear();
    ui->lineEditProceedingsPublisher->clear();
    ui->lineEditProceedingsYear->clear();
    ui->lineEditProceedingsEditor->clear();
    ui->lineEditProceedingsOrganization->clear();
    ui->lineEditProceedingsVolume->clear();
    ui->lineEditProceedingsNumber->clear();
}

void Dialog_Bibliography::on_tableWidgetProceedings_itemSelectionChanged()
{
    if (ui->tableWidgetProceedings->currentItem()->isSelected()) {
        ui->pushButtonProceedingsDelete->setEnabled(true);
    } else {
        ui->pushButtonProceedingsDelete->setEnabled(false);
    }
}

void Dialog_Bibliography::on_pushButtonProceedingsDelete_clicked()
{
    ui->tableWidgetProceedings->clearSelection();
    file->deleteProceedingsEntry(ui->tableWidgetProceedings->item(
                                     ui->tableWidgetProceedings->currentRow(), 0)->text());
    ui->tableWidgetProceedings->removeRow(ui->tableWidgetProceedings->currentRow());
}

void Dialog_Bibliography::on_pushButtonReportsAddEntry_clicked()
{
    file->createReportEntry(ui->lineEditReportsID->text(), ui->lineEditReportsAuthor->text(),
                            ui->lineEditReportsTitle->text(), ui->lineEditReportsInstitution->text(),
                            ui->lineEditReportsYear->text(), ui->lineEditReportsAddress->text(),
                            ui->lineEditReportsType->text(), ui->lineEditReportsNumber->text());
    ui->tableWidgetReports->insertRow(ui->tableWidgetReports->rowCount());
    ui->tableWidgetReports->setItem(ui->tableWidgetReports->rowCount() - 1, 0,
                                    new QTableWidgetItem(ui->lineEditReportsID->text()));
    ui->tableWidgetReports->setItem(ui->tableWidgetReports->rowCount() - 1, 1,
                                    new QTableWidgetItem(ui->lineEditReportsAuthor->text()));
    ui->tableWidgetReports->setItem(ui->tableWidgetReports->rowCount() - 1, 2,
                                    new QTableWidgetItem(ui->lineEditReportsTitle->text()));
    ui->tableWidgetReports->setItem(ui->tableWidgetReports->rowCount() - 1, 3,
                                    new QTableWidgetItem(ui->lineEditReportsInstitution->text()));
    ui->tableWidgetReports->setItem(ui->tableWidgetReports->rowCount() - 1, 4,
                                    new QTableWidgetItem(ui->lineEditReportsYear->text()));
    ui->tableWidgetReports->setItem(ui->tableWidgetReports->rowCount() - 1, 5,
                                    new QTableWidgetItem(ui->lineEditReportsAddress->text()));
    ui->tableWidgetReports->setItem(ui->tableWidgetReports->rowCount() - 1, 6,
                                    new QTableWidgetItem(ui->lineEditReportsType->text()));
    ui->tableWidgetReports->setItem(ui->tableWidgetReports->rowCount() - 1, 7,
                                    new QTableWidgetItem(ui->lineEditReportsNumber->text()));
    ui->lineEditReportsID->clear();
    ui->lineEditReportsAuthor->clear();
    ui->lineEditReportsTitle->clear();
    ui->lineEditReportsInstitution->clear();
    ui->lineEditReportsYear->clear();
    ui->lineEditReportsAddress->clear();
    ui->lineEditReportsType->clear();
    ui->lineEditReportsNumber->clear();
}

void Dialog_Bibliography::on_tableWidgetReports_itemSelectionChanged()
{
    if (ui->tableWidgetReports->currentItem()->isSelected()) {
        ui->pushButtonReportsDelete->setEnabled(true);
    } else {
        ui->pushButtonReportsDelete->setEnabled(false);
    }
}

void Dialog_Bibliography::on_pushButtonReportsDelete_clicked()
{
    ui->tableWidgetReports->clearSelection();
    file->deleteReportEntry(ui->tableWidgetReports->item(ui->tableWidgetReports->currentRow(),
                                                         0)->text());
    ui->tableWidgetReports->removeRow(ui->tableWidgetReports->currentRow());
}

void Dialog_Bibliography::on_buttonBox_helpRequested()
{
    QMessageBox::information(this, APP_NAME,
                             tr("You can edit the bibliography of your document simply through the interface provided. Once you have completed all the information requested to create a new entry, remember to click the provided button to save the changes."));
}
