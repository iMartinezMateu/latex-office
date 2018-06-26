#include "dialog_smartkeys.h"
#include "ui_dialog_smartkeys.h"
#include "lib/assistivetechnologies/smartkeys.h"
#include <QDebug>
Dialog_SmartKeys::Dialog_SmartKeys(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_SmartKeys)
{
    QList<QStringList> definitionsList;
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Help)->setText(tr("Help"));

    QDir smartKeysDir("data/smartkeys");
    if (!smartKeysDir.exists()) {
        smartKeysDir.mkpath(".");
    }

    SmartKeys::loadDefinitionsFile("data/smartkeys/definitions.skd");
    definitionsList = SmartKeys::getDefinitionsStringList();

    foreach (QStringList item, definitionsList) {
        QTableWidgetItem *replaceItem = new QTableWidgetItem(item.at(1));
        QTableWidgetItem *forItem = new QTableWidgetItem(item.at(2));
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, replaceItem);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, forItem);
    }
    rowCount = ui->tableWidget->rowCount();
}

Dialog_SmartKeys::~Dialog_SmartKeys()
{
    delete ui;
}

void Dialog_SmartKeys::on_pushButtonInsert_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}

void Dialog_SmartKeys::on_pushButtonDelete_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

void Dialog_SmartKeys::on_buttonBox_accepted()
{
    for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
        for (int column = 0 ; column < ui->tableWidget->columnCount(); column++) {
            if (!ui->tableWidget->item(row, column)) {
                setHidden(false);
                QMessageBox::information(this, APP_NAME,
                                         tr("There are empty items that cannot be added to SmartKeys. Please, correct them and try again"));
                return;
            }
        }
    }

    SmartKeys::clearDefinitions();
    for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
        SmartKeys::createDefinition(row, ui->tableWidget->item(row, 0)->text(),
                                    ui->tableWidget->item(row, 1)->text());
    }
    QDir smartKeysDir("data/smartkeys");
    if (!smartKeysDir.exists()) {
        smartKeysDir.mkpath(".");
    }
    SmartKeys::saveDefinitionsFile("data/smartkeys/definitions.skd");
    accept();

}



void Dialog_SmartKeys::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if (ui->tableWidget->rowCount() == 0)
        return;

    if (item->text().length() < 2) {
        if (ui->tableWidget->currentItem()->column() == 0) {
            QMessageBox::information(this, APP_NAME,
                                     tr("The item that you have introduced in the first column is too short. Please, try writing another one that is at least 3 characters long."));
            ui->tableWidget->removeRow(ui->tableWidget->currentRow());
        } else {
            QMessageBox::information(this, APP_NAME,
                                     tr("The item that you have introduced in the last column is too short. Please, try writing another one that is at least 3 characters long."));
            ui->tableWidget->removeRow(ui->tableWidget->currentRow());
        }
    } else {
        if (item) {
            item->setText(item->text().remove(QRegExp(
                                                  QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]"))));
        }
    }

    for (int row = 0; row < rowCount; row++) {
        if (row != ui->tableWidget->currentRow())
            if (ui->tableWidget->item(row,
                                      0)->text().compare(ui->tableWidget->currentItem()->text()) == 0) {
                qDebug() << ui->tableWidget->currentItem()->text();
                qDebug() << ui->tableWidget->item(row, 0)->text();
                QMessageBox::information(this, APP_NAME,
                                         tr("The item that you have introduced is already on the list. Please, try writing a different one."));
                ui->tableWidget->removeRow(ui->tableWidget->currentRow());
                break;
            }
    }
}

void Dialog_SmartKeys::on_buttonBox_helpRequested()
{
    QMessageBox::information(this, APP_NAME,
                             tr("With SmartKeys, the program will be smart enough to replace the word you previously typed in Caja and then, it will be replaced by another word that you have indicated here."));
}
