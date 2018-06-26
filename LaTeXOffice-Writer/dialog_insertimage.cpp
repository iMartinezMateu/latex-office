#include "dialog_insertimage.h"
#include "ui_dialog_insertimage.h"

Dialog_InsertImage::Dialog_InsertImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_InsertImage)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    ui->buttonBox->button(QDialogButtonBox::Help)->setText(tr("Help"));

}

Dialog_InsertImage::~Dialog_InsertImage()
{
    delete ui;
}
void Dialog_InsertImage::on_pushButtonBrowse_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("Image Files (*.png *.jpg *.jbig2 *.pdf)"));
    QPixmap pixmap(fileName);
    ui->lineEditImagePath->setText(fileName);
    ui->imagePlaceHolder->setPixmap(pixmap);
}
void Dialog_InsertImage::setData(int lineNumber, TeXFile *file, QString compilerPath)
{
    this->lineNumber = lineNumber;
    this->file = file;
    this->compilerPath = compilerPath;
}
void Dialog_InsertImage::on_lineEditImagePath_textChanged(const QString &arg1)
{
    if (arg1.isEmpty()) {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    } else {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }

}
void Dialog_InsertImage::on_buttonBox_accepted()
{
    QString options;
    int offset = 1;
    file->setTeXCommand(command.callBegin(ENV_FIGURE) + "[h]", lineNumber);
    options = options.append("scale=" + QString::number(ui->spinBoxScale->value() * 0.01, '.',
                                                        2) + ",angle=" + QString::number(ui->spinBoxRotation->value()));
    if (ui->comboBoxAlign->currentIndex() == 1) {
        file->setTeXCommand(CMD_CENTERING, lineNumber + offset);
        offset++;
    }
    file->setTeXCommand(command.callIncludeGraphics(
                            ui->lineEditImagePath->text().remove(".pdf"), options), lineNumber + offset);
    offset++;
    if (!ui->lineEditCaption->text().isEmpty()) {
        file->setTeXCommand(command.callCaption() + " " + ui->lineEditCaption->text(),
                            lineNumber + offset);
        offset++;
    }

    if (!ui->lineEditLabel->text().isEmpty()) {
        file->setTeXCommand(command.callLabel(" img:" + ui->lineEditLabel->text()),
                            lineNumber + offset);
        offset++;
    }

    file->setTeXCommand(command.callEnd(ENV_FIGURE), lineNumber + offset);
    file->saveFile();
    file->compile(compilerPath);
    file->compile(compilerPath);
}

void Dialog_InsertImage::on_buttonBox_helpRequested()
{
    QMessageBox::information(this, APP_NAME,
                             tr("You can insert an image after the paragraph you previously clicked and tweak its options."));

}
