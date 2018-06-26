#include "dialog_documentpreamble.h"
#include "ui_dialog_documentpreamble.h"

Dialog_DocumentPreamble::Dialog_DocumentPreamble(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_DocumentPreamble)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    ui->buttonBox->button(QDialogButtonBox::Help)->setText(tr("Help"));
}

Dialog_DocumentPreamble::~Dialog_DocumentPreamble()
{
    delete ui;
}

void Dialog_DocumentPreamble::setData(TeXFile *file, DocumentViewer *viewer)
{
    this->file = file;
    this->viewer = viewer;
    ui->lineEditDocumentTitle->setText(file->getDocumentTitle());
    ui->lineEditDocumentDate->setText(file->getDocumentDate());
    ui->lineEditDocumentAuthor->setText(file->getDocumentAuthor());
    titleEdited = false;
    authorEdited = false;
    dateEdited = false;
    if (file->getDocumentAbstract().isEmpty()) {
        ui->radioButtonDisableAbstract->setChecked(true);
        ui->radioButtonEnableAbstract->setChecked(false);
        on_radioButtonDisableAbstract_clicked();
    } else {
        ui->radioButtonEnableAbstract->setChecked(true);
        ui->radioButtonDisableAbstract->setChecked(false);
        on_radioButtonEnableAbstract_clicked();
        ui->plainTextEditDocumentAbstract->setText(file->getDocumentAbstract());
    }
}

void Dialog_DocumentPreamble::on_radioButtonDisableAbstract_clicked()
{
    ui->plainTextEditDocumentAbstract->clear();
    ui->plainTextEditDocumentAbstract->setEnabled(false);
    ui->plainTextEditDocumentAbstract->setReadOnly(true);
}

void Dialog_DocumentPreamble::on_radioButtonEnableAbstract_clicked()
{
    ui->plainTextEditDocumentAbstract->clear();
    ui->plainTextEditDocumentAbstract->setEnabled(true);
    ui->plainTextEditDocumentAbstract->setReadOnly(false);
}

void Dialog_DocumentPreamble::on_buttonBox_accepted()
{
    if (ui->radioButtonEnableAbstract->isChecked()) {
        file->deleteAbstract();
        file->setAbstract(ui->plainTextEditDocumentAbstract->text());
    } else if (ui->radioButtonDisableAbstract->isChecked()) {
        file->deleteAbstract();
    }
    if (titleEdited) {
        file->deleteTitle();
        file->setTitle(ui->lineEditDocumentTitle->text());
    }
    if (dateEdited) {
        file->deleteDate();
        file->setDate(ui->lineEditDocumentDate->text());
    }
    if (authorEdited) {
        file->deleteAuthor();
        file->setAuthor(ui->lineEditDocumentAuthor->text());
    }
    file->saveFile();
    file->compile(TeXCompiler::loadPDFCompilerPathSettings());
    file->compile(TeXCompiler::loadPDFCompilerPathSettings());
    viewer->refresh(viewer->getCurrentPage());
    QMessageBox::information(this, APP_NAME,
                             tr("Document preamble was modified succesfully!"));

}

void Dialog_DocumentPreamble::on_lineEditDocumentTitle_textEdited(const QString &arg1)
{
    if (arg1.length() < 3) {
        QToolTip::showText(ui->lineEditDocumentTitle->mapToGlobal(QPoint()),
                           tr("The title can't be too short.\nYou will not be able to create a new document with this title."));
        ui->lineEditDocumentTitle->setStyleSheet("color: #FF0000");
    } else {
        QToolTip::hideText();
        ui->lineEditDocumentTitle->setStyleSheet("color: #000000");
    }
    if (arg1.isEmpty()) {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    } else {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    titleEdited = true;
}

void Dialog_DocumentPreamble::on_buttonBox_helpRequested()
{
    QMessageBox::information(this, APP_NAME,
                             tr("You can modify the document title or another document setting in this window easily."));

}
