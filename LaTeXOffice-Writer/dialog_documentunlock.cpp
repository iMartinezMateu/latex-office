#include "dialog_documentunlock.h"
#include "ui_dialog_documentunlock.h"
#include "lib/assistivetechnologies/documentlock.h"

Dialog_DocumentUnlock::Dialog_DocumentUnlock(QFile *ltexFile, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_DocumentUnlock)
{
    ui->setupUi(this);
    unlockedFile = false;
    this->ltexFile = ltexFile;
}

Dialog_DocumentUnlock::~Dialog_DocumentUnlock()
{
    delete ui;
}
bool Dialog_DocumentUnlock::getUnlockedFile()
{
    return unlockedFile;
}

void Dialog_DocumentUnlock::on_lineEditPassword_textChanged(const QString &arg1)
{
    if (arg1.isEmpty()) {
        ui->pushButtonUnlock->setEnabled(false);
    } else {
        ui->pushButtonUnlock->setEnabled(true);
    }
}

void Dialog_DocumentUnlock::on_pushButtonUnlock_clicked()
{
    ltexFile->open(QIODevice::ReadOnly);

    QTextStream in(ltexFile);
    while (!in.atEnd()) {
        QString lockedDocumentContent = in.readLine();
        QString unlockedDocumentContent = DocumentLock::unlockFile(lockedDocumentContent,
                                                                   ui->lineEditPassword->text());
        if (!unlockedDocumentContent.contains(CMD_DOCUMENT_CLASS)) {
            QMessageBox::critical(this, APP_NAME,
                                  tr("The password is wrong. Please, type the correct password and try again."));
            ui->lineEditPassword->clear();
            unlockedFile = false;
            ltexFile->close();
        } else {
            QFile texFile(QFileInfo(ltexFile->fileName()).absolutePath() + "/" + QFileInfo(
                              ltexFile->fileName()).baseName().append(".tex"));
            if (texFile.open(QIODevice::ReadWrite)) {
                QTextStream stream(&texFile);
                foreach (QString line, unlockedDocumentContent.split("\n")) {
                    stream << line << endl;
                }
            }
            unlockedFile = true;
            ltexFile->close();
            texFile.close();
            accept();
        }

    }

}
