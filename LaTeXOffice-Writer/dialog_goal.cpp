#include "dialog_goal.h"
#include "ui_dialog_goal.h"

Dialog_Goal::Dialog_Goal(DocumentViewer *viewer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Goal)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    ui->buttonBox->button(QDialogButtonBox::Discard)->setText(tr("Delete"));
    this->viewer = viewer;
    if (viewer->getGoalCap() != -1) {
        ui->spinBoxWords->setValue(viewer->getGoalCap());
    }
}

Dialog_Goal::~Dialog_Goal()
{
    delete ui;
}

void Dialog_Goal::on_buttonBox_accepted()
{
    viewer->enableGoal(ui->spinBoxWords->value(), ui->checkBoxSound->isChecked());
    QMessageBox::information(this, APP_NAME,
                             tr("You have just started a new goal. Cheer up!"));
}

void Dialog_Goal::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Discard) {
        viewer->disableGoal();
        QMessageBox::information(this, APP_NAME, tr("Goal was removed succesfully!"));
        close();
    }
}
