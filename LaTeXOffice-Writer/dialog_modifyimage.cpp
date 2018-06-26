#include "dialog_modifyimage.h"
#include "ui_dialog_modifyimage.h"

Dialog_ModifyImage::Dialog_ModifyImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_ModifyImage)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    ui->buttonBox->button(QDialogButtonBox::Discard)->setText(tr("Delete"));
}
void Dialog_ModifyImage::setData(TeXFile *file, QString documentPath, QStringList lines,
                                 QString compilerPath)
{
    this->file = file;
    this->lines = lines;
    this->compilerPath = compilerPath;
    foreach (QString line, lines) {
        if (line.contains(CMD_INCLUDE_GRAPHICS)) {
            QRegularExpression re("\\[(.*?)\\]");
            QRegularExpressionMatch match = re.match(line);
            if (match.hasMatch()) {
                QString options = match.captured(1);
                QRegularExpression re3("width=([0-9]*\.[0-9]+)");
                QRegularExpressionMatch match2 = re3.match(options);
                if (match2.hasMatch()) {
                    QString imageScale = match2.captured(1);
                    ui->spinBoxScale->setValue(imageScale.toFloat() * 100);
                }
                QRegularExpression re4("angle=([0-9]*\.[0-9]+)");
                match2 = re4.match(options);
                if (match2.hasMatch()) {
                    QString imageRotation = match2.captured(1);
                    ui->spinBoxRotation->setValue(imageRotation.toInt());
                }
            }
            QRegularExpression re2("\{(.*?)\}");
            match = re2.match(line);
            if (match.hasMatch()) {
                QString path = match.captured(1);
                QPixmap pixmap(path.replace("./", documentPath + "/"));
                ui->lineEditImagePath->setText(path.replace("./", documentPath + "/"));
                ui->imagePlaceHolder->setPixmap(pixmap);
            }
        }
    }
    foreach (QString line, lines) {
        if (line.contains(CMD_CAPTION)) {
            ui->lineEditCaption->setEnabled(true);
            ui->lineEditCaption->setReadOnly(false);
            QRegularExpression re("\{(.*?)\}");
            QRegularExpressionMatch match = re.match(line);
            if (match.hasMatch()) {
                ui->lineEditCaption->setText(match.captured(1));
            }
        }
        if (line.contains(CMD_CENTERING)) {
            ui->comboBoxAlign->setEnabled(true);
        }
        if (line.contains(CMD_LABEL)) {
            ui->lineEditLabel->setEnabled(true);
            ui->lineEditLabel->setReadOnly(false);
            QRegularExpression re("\{(.*?)\}");
            QRegularExpressionMatch match = re.match(line);
            if (match.hasMatch()) {
                ui->lineEditLabel->setText(match.captured(1));
            }
        }
    }
}
Dialog_ModifyImage::~Dialog_ModifyImage()
{
    delete ui;
}
void Dialog_ModifyImage::on_pushButtonBrowse_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("Image Files (*.png *.jpg *.jbig2)"));
    QPixmap pixmap(fileName);
    ui->lineEditImagePath->setText(fileName);
    ui->imagePlaceHolder->setPixmap(pixmap);
}
void Dialog_ModifyImage::on_buttonBox_accepted()
{
    int lineNumber;
    lines.removeDuplicates();
    foreach (QString line, lines) {
        lineNumber = file->getLineNumber(line);

        if (line.contains(CMD_LABEL)) {
            if (ui->lineEditLabel->isEnabled()) {
                file->replaceTeXCommand(command.callLabel("img:"+ui->lineEditLabel->text()), lineNumber);
            }
        }
        if (line.contains(CMD_CENTERING)) {
            if (ui->comboBoxAlign->isEnabled())
                if (ui->comboBoxAlign->currentIndex() == 0) {
                    file->replaceTeXCommand(QString("%%%") + CMD_CENTERING, lineNumber);
                } else {
                    file->replaceTeXCommand(CMD_CENTERING, lineNumber);
                }
        }
        if (line.contains(CMD_CAPTION)) {
            if (ui->lineEditCaption->isEnabled()) {
                file->replaceTeXCommand(command.callCaption(ui->lineEditCaption->text()), lineNumber);
            }
        }
        if (line.contains(CMD_INCLUDE_GRAPHICS)) {
            QString options;
            options = options.append("scale=" + QString::number(ui->spinBoxScale->value() * 0.01, '.',
                                                                2) + ",angle=" + QString::number(ui->spinBoxRotation->value()));
            file->replaceTeXCommand(command.callIncludeGraphics(ui->lineEditImagePath->text(),
                                                                options), lineNumber);
        }
    }
    file->saveFile();
    file->compile(compilerPath);
    file->compile(compilerPath);
}

void Dialog_ModifyImage::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Discard) {
        foreach (QString line, lines) {
            file->deleteTeXCommand(file->getLineNumber(line));
        }
        file->saveFile();
        file->compile(compilerPath);
        file->compile(compilerPath);
        close();
    }
}
