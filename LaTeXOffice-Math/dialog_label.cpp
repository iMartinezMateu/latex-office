#include "dialog_label.h"
#include "ui_dialog_label.h"

Dialog_Label::Dialog_Label(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Label)
{
    ui->setupUi(this);
}

Dialog_Label::~Dialog_Label()
{
    delete ui;
}

QString Dialog_Label::getLabel()
{
    TeXCommands command;
    if (label.isEmpty())
        return "";
    if (ui->radioButtonPlain->isChecked())
        return command.callText(label);
    if (ui->radioButtonBold->isChecked())
        return command.callTextBold(label);


}

void Dialog_Label::on_buttonBox_accepted()
{
    this->label = ui->lineEdit->text();
}
