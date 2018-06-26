#include "dialog_symbol.h"
#include "ui_dialog_symbol.h"

Dialog_Symbol::Dialog_Symbol(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Symbol)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->tableWidget->resizeColumnsToContents();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
}
Dialog_Symbol::~Dialog_Symbol()
{
    delete ui;
}


void Dialog_Symbol::on_lineEditFilter_textChanged(const QString &arg1)
{
    QString filter = arg1;
    ui->comboBoxType->setCurrentIndex(0);
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        bool match = false;
        for (int j = 2; j < ui->tableWidget->columnCount(); ++j) {
            QTableWidgetItem *item = ui->tableWidget->item(i, j);
            if (item->text().contains(filter, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        ui->tableWidget->setRowHidden(i, !match);
    }
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    selectedItem = NULL;
}
void Dialog_Symbol::setSelectedSymbol(QString symbol)
{
    this->selectedSymbol = symbol;
}

QString Dialog_Symbol::getSelectedSymbol()
{
    return selectedSymbol;
}

void Dialog_Symbol::on_buttonBox_accepted()
{
    setSelectedSymbol(ui->tableWidget->selectedItems().at(3)->text());
}
void Dialog_Symbol::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    selectedItem = item;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}
void Dialog_Symbol::on_comboBoxType_currentIndexChanged(int index)
{
    QString filter;
    QString filterES;
    switch (index) {
    case 0:
        filter = "";
        filterES = "";
        break;
    case 1:
        filter = "relation";
        filterES = "relación";
        break;
    case 2:
        filter = "binary";
        filterES = "binario";
        break;
    case 3:
        filter = "logic";
        filterES = "lógica";
        break;
    case 4:
        filter = "delimiters";
        filterES = "delimitadores";
        break;
    case 5:
        filter = "greek";
        filterES = "griegas";
        break;
    case 6:
        filter = "other";
        filterES = "otro";
        break;
    }
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j) {
            QTableWidgetItem *item = ui->tableWidget->item(i, 0);
            if (item->text().contains(filter, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
            if (item->text().contains(filterES, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        ui->tableWidget->setRowHidden(i, !match);
    }
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    selectedItem = NULL;
}
