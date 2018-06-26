#include "dialog_timemachine.h"
#include "ui_dialog_timemachine.h"
#include "lib/assistivetechnologies/timemachine.h"

Dialog_TimeMachine::Dialog_TimeMachine(TeXFile *file, QList<QDateTime> datesList,
                                       QList<QStringList> fileBackupsList, QString compilerPath, QString timeMachineFilePath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_TimeMachine)
{
    ui->setupUi(this);
    this->file = file;

    ui->calendarWidget->setMinimumDate(QDate(datesList.at(0).date()));
    ui->calendarWidget->setMaximumDate(QDate(datesList.last().date()));

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Restore backup"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));

    this->datesList = datesList;
    this->backupsList = fileBackupsList;

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    this->compilerPath = compilerPath;
    this->timeMachineFilePath = timeMachineFilePath;
}

Dialog_TimeMachine::~Dialog_TimeMachine()
{
    delete ui;
}

void Dialog_TimeMachine::on_calendarWidget_clicked(const QDate &date)
{
    ui->listWidget->clear();
    foreach (QDateTime item, datesList) {
        if (date == item.date()) {
            ui->listWidget->addItem(tr("Backup created at ") + item.time().toString("hh:mm:ss"));
        }
    }
}

void Dialog_TimeMachine::on_listWidget_itemSelectionChanged()
{
    int position = 0;
    QString fileContent;
    if (ui->listWidget->currentItem()->isSelected()) {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        foreach (QDateTime item, datesList) {
            if (ui->calendarWidget->selectedDate() == item.date()) {
                if (ui->listWidget->currentItem()->text().contains(item.time().toString("hh:mm:ss"))) {
                    foreach (QString line, backupsList.at(position)) {
                        fileContent.append(line + "\n");
                    }
                    ui->plainTextEdit->setPlainText(fileContent);
                    break;
                }

            }
            position++;
        }

    } else {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->plainTextEdit->clear();
    }
}

void Dialog_TimeMachine::on_buttonBox_accepted()
{
    int position = 0;
    this->setHidden(false);
    QMessageBox messageBox(APP_NAME,
                           tr("Do you want to recover the backup created at ") +
                           ui->listWidget->currentItem()->text() + tr("?"),
                           QMessageBox::Question,
                           QMessageBox::Yes | QMessageBox::Default,
                           QMessageBox::No | QMessageBox::Escape,  //This makes "Esc" key to Cancel the Dialog
                           QMessageBox::NoButton,
                           this);
    messageBox.setButtonText(QMessageBox::Yes, tr("Yes"));
    messageBox.setButtonText(QMessageBox::No, tr("No"));


    if (messageBox.exec() == QMessageBox::Yes) {

        foreach (QDateTime item, datesList) {
            if (ui->calendarWidget->selectedDate() == item.date()) {
                if (ui->listWidget->currentItem()->text().contains(item.time().toString("hh:mm:ss"))) {
                    TimeMachine::makeBackup(QDateTime().currentDateTime(), file->getFileContent());
                    TimeMachine::saveTimeMachineFile(timeMachineFilePath);
                    file->setFileContent(backupsList.at(position));
                    file->saveFile();
                    file->compile(compilerPath);
                    file->compile(compilerPath);
                    QMessageBox::information(this, APP_NAME, tr("Backup was applied succesfully!"));
                    this->setHidden(true);
                    break;
                }
                position++;
            }
        }
    }
}
