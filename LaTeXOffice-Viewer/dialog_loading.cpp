#include "dialog_loading.h"
#include "ui_dialog_loading.h"

Dialog_Loading::Dialog_Loading(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Loading)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags | Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint |
                   Qt::WindowTitleHint);

}

void Dialog_Loading::setProgressBarValue(int value)
{
    ui->progressBar->setValue(value);
    qApp->processEvents(); //refresh UI
}

Dialog_Loading::~Dialog_Loading()
{
    delete ui;
}
