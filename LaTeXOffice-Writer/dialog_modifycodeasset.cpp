#include "dialog_modifycodeasset.h"
#include "ui_dialog_modifycodeasset.h"

Dialog_ModifyCodeAsset::Dialog_ModifyCodeAsset(QString line, int lineNumber,
                                               TeXFile *file, QString compilerPath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_ModifyCodeAsset)
{
    setWindowFlags(Qt::WindowStaysOnTopHint);
    int sourceFileLineNumber = 0;
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    ui->buttonBox->button(QDialogButtonBox::Help)->setText(tr("Help"));
    ui->buttonBox->button(QDialogButtonBox::Discard)->setText(tr("Delete"));
    QRegularExpression re("firstline=(.*?)[,\\]]");
    QRegularExpressionMatch match = re.match(line);
    if (match.hasMatch()) {
        ui->spinBoxFirstLine->setValue(match.captured(1).toInt());
    }

    QRegularExpression re2("\{(.*?)\}");
    match = re2.match(line);
    if (match.hasMatch()) {
        ui->lineEditSourceCode->setText(match.captured(1));
    }
    QRegularExpression re3("lastline=(.*?)[,\\]]");
    match = re3.match(line);
    if (match.hasMatch()) {
        ui->spinBoxLastLine->setValue(match.captured(1).toInt());
    }
    QRegularExpression re4("caption=(.*?)[,\\]]");
    match = re4.match(line);
    if (match.hasMatch()) {
        ui->lineEditCaption->setText(match.captured(1));
    }
    QRegularExpression re5("language=(.*?)[,\\]]");
    match = re5.match(line);
    if (match.hasMatch()) {
        ui->lineEditLanguage->setText(match.captured(1));
    }
    this->lineNumber = lineNumber;
    this->file = file;
    this->compilerPath = compilerPath;
    QFile sourceFile(ui->lineEditSourceCode->text());
    sourceFile.open(QIODevice::ReadOnly);
    QTextStream in(&sourceFile);
    while (!in.atEnd()) {
        sourceFileLineNumber++;
        in.readLine();
    }
    sourceFile.close();
    ui->spinBoxLastLine->setValue(sourceFileLineNumber);
    ui->spinBoxLastLine->setMaximum(sourceFileLineNumber);
    ui->spinBoxFirstLine->setMaximum(sourceFileLineNumber);
    if (ui->lineEditCaption->text().isEmpty()) {
        ui->radioButtonBottom->setEnabled(false);
        ui->radioButtonTop->setEnabled(false);
    } else {
        ui->radioButtonBottom->setEnabled(true);
        ui->radioButtonTop->setEnabled(true);
    }
}

Dialog_ModifyCodeAsset::~Dialog_ModifyCodeAsset()
{
    delete ui;
}

void Dialog_ModifyCodeAsset::on_buttonBox_accepted()
{
    if (!ui->lineEditCaption->text().isEmpty()) {
        if (ui->radioButtonBottom->isChecked()) {
            file->replaceTeXCommand(command->callLstInputListing(ui->lineEditSourceCode->text(),
                                                                 "language=" + ui->lineEditLanguage->text() + ", caption=" + ui->lineEditCaption->text() +
                                                                 ", firstline=" + QString::number(ui->spinBoxFirstLine->value()) + ", lastline=" +
                                                                 QString::number(ui->spinBoxLastLine->value()) +
                                                                 ",captionpos=b,breaklines=true,showstringspaces=false"), lineNumber);
        } else {
            file->replaceTeXCommand(command->callLstInputListing(ui->lineEditSourceCode->text(),
                                                                 "language=" + ui->lineEditLanguage->text() + ", caption=" + ui->lineEditCaption->text() +
                                                                 ", firstline=" + QString::number(ui->spinBoxFirstLine->value()) + ", lastline=" +
                                                                 QString::number(ui->spinBoxLastLine->value()) +
                                                                 ",breaklines=true,showstringspaces=false"), lineNumber);
        }
    } else {
        file->replaceTeXCommand(command->callLstInputListing(ui->lineEditSourceCode->text(),
                                                             "language=" + ui->lineEditLanguage->text() + ", firstline=" + QString::number(
                                                                 ui->spinBoxFirstLine->value()) + ", lastline=" + QString::number(
                                                                 ui->spinBoxLastLine->value()) + ",breaklines=true,showstringspaces=false"), lineNumber);
    }
    file->saveFile();
    file->compile(compilerPath);
    file->compile(compilerPath);
    close();
}

void Dialog_ModifyCodeAsset::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Discard) {
        file->deleteTeXCommand(lineNumber);
        file->saveFile();
        file->compile(compilerPath);
        file->compile(compilerPath);
        close();
    }
}

void Dialog_ModifyCodeAsset::on_lineEditCaption_textChanged(const QString &arg1)
{
    if (arg1.isEmpty()) {
        ui->radioButtonBottom->setEnabled(false);
        ui->radioButtonTop->setEnabled(false);
    } else {
        ui->radioButtonBottom->setEnabled(true);
        ui->radioButtonTop->setEnabled(true);
    }
}

void Dialog_ModifyCodeAsset::on_buttonBox_helpRequested()
{
    QMessageBox::information(this, APP_NAME,
                             tr("You can modify the selected code asset and limit the amount of lines of code that will appear in the document. ."));
}
