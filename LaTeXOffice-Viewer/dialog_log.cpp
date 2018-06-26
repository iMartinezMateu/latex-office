#include "dialog_log.h"
#include "ui_dialog_log.h"

Dialog_Log::Dialog_Log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Log)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
}

void Dialog_Log::setData(QFile *docLogFile, QFile *texLogFile)
{
    this->docLogFile = docLogFile;
    this->texLogFile = texLogFile;
    docLogFile->open(QIODevice::ReadOnly);
    QTextStream inDocLog(docLogFile);

    while (!inDocLog.atEnd()) {
        QString line = inDocLog.readLine();
        ui->logViewer->appendPlainText(line);
    }
    docLogFile->close();

    texLogFile->open(QIODevice::ReadOnly);
    QTextStream inTeXLog(texLogFile);

    while (!inTeXLog.atEnd()) {
        QString line = inTeXLog.readLine();
        ui->logViewer->appendPlainText(line);
    }
    texLogFile->close();
}

Dialog_Log::~Dialog_Log()
{
    delete ui;
}
