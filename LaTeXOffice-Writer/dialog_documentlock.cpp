#include "dialog_documentlock.h"
#include "ui_dialog_documentlock.h"
#include "lib/assistivetechnologies/documentlock.h"

Dialog_DocumentLock::Dialog_DocumentLock(TeXFile *file, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_DocumentLock)
{
    ui->setupUi(this);
    lockedFile = false;
    this->file = file;
}

Dialog_DocumentLock::~Dialog_DocumentLock()
{
    delete ui;
}

void Dialog_DocumentLock::on_pushButtonLockDocument_clicked()
{
    QString fileContent;
    QString lockedFileContent;
    QString lockedFileName = file->getDirectory() + "/" + file->getFileName().append(".ltex");
    QMessageBox messageBox(APP_NAME,
                           tr("Note that if you forget the password, you will not be able to reopen the document. Are you sure you want to apply the password to the document?"),
                           QMessageBox::Question,
                           QMessageBox::Yes | QMessageBox::Default,
                           QMessageBox::No | QMessageBox::Escape,  //This makes "Esc" key to Cancel the Dialog
                           QMessageBox::NoButton,
                           this);
    messageBox.setButtonText(QMessageBox::Yes, tr("Yes"));
    messageBox.setButtonText(QMessageBox::No, tr("No"));


    if (messageBox.exec() == QMessageBox::Yes) {
        QMessageBox secondaryMessageBox(APP_NAME,
                                        tr("After encrypting the document, LaTeX Office will close it so you can not make changes until you open it again and enter the password. Are you sure you want to continue with the process?"),
                                        QMessageBox::Question,
                                        QMessageBox::Yes | QMessageBox::Default,
                                        QMessageBox::No | QMessageBox::Escape,  //This makes "Esc" key to Cancel the Dialog
                                        QMessageBox::NoButton,
                                        this);
        secondaryMessageBox.setButtonText(QMessageBox::Yes, tr("Yes"));
        secondaryMessageBox.setButtonText(QMessageBox::No, tr("No"));
        if (secondaryMessageBox.exec() == QMessageBox::Yes) {
            lockedFile = true;
            foreach (QString line, file->getFileContent()) {
                fileContent.append(line + "\n");
            }
            lockedFileContent = DocumentLock::lockFile(fileContent, ui->lineEditPassword->text());
            QFile lockedFile(lockedFileName);
            if (lockedFile.open(QIODevice::ReadWrite)) {
                QTextStream stream(&lockedFile);
                foreach (QString line, lockedFileContent.split("\n")) {
                    stream << line << endl;
                }
            }
            QFile::remove(file->getDirectory() + "/" + file->getFileName().append(".tex"));
            QMessageBox::information(this, APP_NAME,
                                     tr("Document was locked succesfully! To unlock it, you just have to open the locked TeX File (.ltex) inside LaTeX Office"));
            accept();
        }
    }
}

void Dialog_DocumentLock::on_lineEditPassword_textChanged(const QString &arg1)
{
    if (arg1.length() < 8) {
        ui->labelHint->setStyleSheet("QLabel { color : red; }");
        ui->labelHint->setText(
            tr("Password is not very secure. Please, type a new one that has at least 8 characters."));
    } else {
        ui->labelHint->setStyleSheet("QLabel { color : green; }");
        ui->labelHint->setText(
            tr("Password has at least 8 characters, so it is considered as secure."));
    }
}

bool Dialog_DocumentLock::getLockedFile()
{
    return lockedFile;
}

void Dialog_DocumentLock::on_lineEditVerify_textChanged(const QString &arg1)
{
    if (arg1.isEmpty()) {
        ui->labelHint->setStyleSheet("QLabel { color : red; }");
        ui->labelHint->setText(tr("Password can not be empty!"));
        ui->pushButtonLockDocument->setEnabled(false);
    } else {
        if (arg1.compare(ui->lineEditPassword->text()) != 0) {
            ui->labelHint->setStyleSheet("QLabel { color : red; }");
            ui->labelHint->setText(tr("Passwords does not match!"));
            ui->pushButtonLockDocument->setEnabled(false);
        } else {
            ui->pushButtonLockDocument->setEnabled(true);
            ui->labelHint->setStyleSheet("QLabel { color : green; }");
            ui->labelHint->setText(tr("Passwords does match!"));
        }
    }
}
