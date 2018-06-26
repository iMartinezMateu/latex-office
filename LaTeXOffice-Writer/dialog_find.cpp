#include "dialog_find.h"
#include "ui_dialog_find.h"

Dialog_Find::Dialog_Find(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Find)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->buttonBox->button(QDialogButtonBox::Close)->setText(tr("Close"));
}
Dialog_Find::~Dialog_Find()
{
    delete ui;
}
void Dialog_Find::setData(DocumentViewer *viewer)
{
    this->viewer = viewer;
}
void Dialog_Find::on_pushButtonSearch_clicked()
{
    if (ui->radioButtonCaseInsensitive->isChecked()) {
        viewer->searchString(ui->lineEditSearchKey->text(), false);
    } else {
        viewer->searchString(ui->lineEditSearchKey->text(), true);
    }
}

void Dialog_Find::on_lineEditSearchKey_textChanged(const QString &arg1)
{
    if (arg1.length() < 3) {
        ui->pushButtonSearch->setEnabled(false);
    } else {
        ui->pushButtonSearch->setEnabled(true);
    }
}
