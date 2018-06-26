#include "dialog_code.h"
#include "ui_dialog_code.h"

Dialog_Code::Dialog_Code(QStringList fileContent, TeXFile *file, DocumentViewer *viewer,
                         QString compilerPath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Code)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Save)->setText(tr("Save"));

    foreach (QString line, fileContent) {
        ui->plainTextEdit->appendPlainText(line);
    }

    this->file = file;
    this->viewer = viewer;
    this->compilerPath = compilerPath;
}

Dialog_Code::~Dialog_Code()
{
    delete ui;
}

void Dialog_Code::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Save) {
        QStringList newFileContent = ui->plainTextEdit->toPlainText().split("\n");
        viewer->stopThreadPool();

        file->setFileContent(newFileContent);

        file->saveFile();
        file->compile(compilerPath);
        file->compile(compilerPath);
        viewer->refresh(viewer->getCurrentPage());
        viewer->loadThreadPool();
        accept();
    }
}
