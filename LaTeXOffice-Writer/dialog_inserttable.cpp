#include "dialog_inserttable.h"
#include "ui_dialog_inserttable.h"

Dialog_InsertTable::Dialog_InsertTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_InsertTable)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    ui->buttonBox->button(QDialogButtonBox::Help)->setText(tr("Help"));
}

Dialog_InsertTable::~Dialog_InsertTable()
{
    delete ui;
}


void Dialog_InsertTable::on_spinBoxColumns_valueChanged(int arg1)
{
    ui->tableWidget->setColumnCount(arg1);
}

void Dialog_InsertTable::on_spinBoxRows_valueChanged(int arg1)
{
    ui->tableWidget->setRowCount(arg1);
}
void Dialog_InsertTable::setData(int lineNumber, TeXFile *file, QString compilerPath)
{
    this->lineNumber = lineNumber;
    this->file = file;
    this->compilerPath = compilerPath;
}

void Dialog_InsertTable::on_buttonBox_accepted()
{
    QStringList tableContents;
    QString tableLine;
    QString beginTableLine;
    int offset = 1;

    if (ui->tableWidget->rowCount()==0)
        return;

    if (ui->tableWidget->columnCount()==0)
        return;
    beginTableLine.append("\n\n");
    switch (ui->comboBoxPosition->currentIndex())
    {
        case 0: //here
        beginTableLine.append(command.callBegin("table")+"[h]");
        break;
        case 1: //top
        beginTableLine.append(command.callBegin("table")+"[t]");
        break;
        case 2: //bottom
        beginTableLine.append(command.callBegin("table")+"[b]");
        break;
    }

    beginTableLine.append(CMD_CENTERING);
    beginTableLine.append(command.callBegin(ENV_TABULAR) + "{");
    tableLine.append(QString(CMD_TAB_HORIZ_LINE) + " ");
    for (int column = 1; column < ui->tableWidget->columnCount(); column++) {
        beginTableLine.append("| l ");

    }
    switch(ui->comboBoxColor->currentIndex())
    {
        case 0: //white
           tableLine.append(command.callRowColor("FFFFFF") + " " +QString(CMD_TAB_HORIZ_LINE)+ " "  );
           break;
        case 1: //gray
           tableLine.append(command.callRowColor("C0C0C0") + " " +QString(CMD_TAB_HORIZ_LINE)+ " "  );
            break;
        case 2: //red
           tableLine.append(command.callRowColor("FF0000") + " " +QString(CMD_TAB_HORIZ_LINE)+ " "  );
            break;
        case 3: //blue
            tableLine.append(command.callRowColor("33CCFF") +" " +QString(CMD_TAB_HORIZ_LINE)+ " "  );
            break;
        case 4: //green
            tableLine.append(command.callRowColor("33FF33") + " " +QString(CMD_TAB_HORIZ_LINE)+ " "  );
            break;
        case 5: //yellow
            tableLine.append(command.callRowColor("FFFF99") + " " +QString(CMD_TAB_HORIZ_LINE)+ " "  );
            break;
        case 6: //pink
            tableLine.append(command.callRowColor("FF99CC") + " " +QString(CMD_TAB_HORIZ_LINE)+ " "  );
            break;
    }

    for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
        for (int column = 0; column < ui->tableWidget->columnCount(); column++) {
            if (column + 1 == ui->tableWidget->columnCount()) {
                tableLine.append(ui->tableWidget->model()->data(ui->tableWidget->model()->index(row,
                                                                                                column)).toString() + "\\\\");
            } else {
                tableLine.append(ui->tableWidget->model()->data(ui->tableWidget->model()->index(row,
                                                                                                column)).toString() + " & ");
            }
        }
        tableLine.append(" " + QString(CMD_TAB_HORIZ_LINE) + " ");
    }
    tableContents.append(tableLine);
    beginTableLine.append("| l |");
    beginTableLine.append("}");



    file->setTeXCommand(beginTableLine, lineNumber);
    foreach (QString line, tableContents) {
        file->setTeXCommand(line, lineNumber + offset);
        offset++;
    }

    file->setTeXCommand(command.callEnd(ENV_TABULAR), lineNumber + offset);
    offset++;
    if (!ui->lineEditReference->text().isEmpty())
    {
        file->setTeXCommand(command.callLabel("table:"+ui->lineEditReference->text()),lineNumber + offset);
        offset++;

    }
    if (!ui->lineEditCaption->text().isEmpty())
    {
        file->setTeXCommand(command.callCaption(ui->lineEditCaption->text()),lineNumber + offset);
        offset++;

    }
    file->setTeXCommand(command.callEnd("table"),lineNumber+offset);
    offset++;
    file->setTeXCommand(CMD_PARAGRAPH_BREAK, lineNumber + offset);
    offset++;

    file->saveFile();
    file->compile(compilerPath);
    file->compile(compilerPath);

}

void Dialog_InsertTable::on_buttonBox_helpRequested()
{
    QMessageBox::information(this, APP_NAME,
                             tr("You can insert a table after the paragraph you previously clicked and tweak its options."));

}
