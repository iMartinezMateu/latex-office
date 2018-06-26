#include "dialog_timemachinesettings.h"
#include "ui_dialog_timemachinesettings.h"

Dialog_TimeMachineSettings::Dialog_TimeMachineSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_TimeMachineSettings)
{
    ui->setupUi(this);
    QFile file("settings/timemachineinterval.los");

    if (file.exists()) {
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
        }
        file.close();
        ui->spinBox->setValue(line.toInt() / 24 / 4);
    }
}

Dialog_TimeMachineSettings::~Dialog_TimeMachineSettings()
{
    delete ui;
}

void Dialog_TimeMachineSettings::on_spinBox_valueChanged(int arg1)
{
    int maxCopies = 4 * 24 *
                    arg1; //4 copias que se hacen en 1 hora (cada 15 min), * 24 h que tiene un dia * los dias elegidos por el usuario;

    float minimumSpace = (maxCopies * 25) /
                         1024; //El número máximo de copias * un tamaño medio por documento de 25 KB / 1MB=1024KB

    ui->labelSpace->setText("<b>" + QString::number(minimumSpace) + " MB </b>");
}

void Dialog_TimeMachineSettings::on_buttonBox_accepted()
{
    if (!QDir("settings").exists()) {
        QDir().mkdir("settings");
    }
    if (QFile("settings/timemachineinterval.los").exists()) {
        QFile("settings/timemachineinterval.los").remove();
    }
    QString filename = "settings/timemachineinterval.los";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << 4 * 24 * ui->spinBox->value() << endl;
    }
}
