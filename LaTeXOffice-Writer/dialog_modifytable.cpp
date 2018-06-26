#include "dialog_modifytable.h"
#include "ui_dialog_modifytable.h"

Dialog_ModifyTable::Dialog_ModifyTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_ModifyTable)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    ui->buttonBox->button(QDialogButtonBox::Discard)->setText(tr("Delete"));
}

Dialog_ModifyTable::~Dialog_ModifyTable()
{
    delete ui;
}

void Dialog_ModifyTable::on_buttonBox_accepted()
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
           tableLine.append(command.callRowColor("C0C0C0") +  " " +QString(CMD_TAB_HORIZ_LINE)+ " "  );
            break;
        case 2: //red
           tableLine.append(command.callRowColor("FF0000") +  " " +QString(CMD_TAB_HORIZ_LINE)+ " "  );
            break;
        case 3: //blue
            tableLine.append(command.callRowColor("33CCFF") + " " +QString(CMD_TAB_HORIZ_LINE)+ " "  );
            break;
        case 4: //green
            tableLine.append(command.callRowColor("33FF33") + " " +QString(CMD_TAB_HORIZ_LINE)+ " "  );
            break;
        case 5: //yellow
            tableLine.append(command.callRowColor("FFFF99") + " " +QString(CMD_TAB_HORIZ_LINE) + " " );
            break;
        case 6: //pink
            tableLine.append(command.callRowColor("FF99CC") +  " " +QString(CMD_TAB_HORIZ_LINE)+ " "  );
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

    lineNumber -= 1;

    file->replaceTeXCommand(beginTableLine, lineNumber);
    foreach (QString line, tableContents) {
        file->replaceTeXCommand(line, lineNumber + offset);
        offset++;
    }
    file->replaceTeXCommand(command.callEnd(ENV_TABULAR), lineNumber + offset);
    offset++;

    if (ui->lineEditReference->text().isEmpty())
    {
        file->replaceTeXCommand("",lineNumber + offset);
        offset++;
    }
    else
    {
        file->replaceTeXCommand(command.callLabel("table:"+ui->lineEditReference->text()),lineNumber + offset);
        offset++;
    }

        if (ui->lineEditCaption->text().isEmpty())
        {
            file->replaceTeXCommand("",lineNumber + offset);
            offset++;
        }
        else
        {
            file->replaceTeXCommand(command.callCaption(ui->lineEditCaption->text()),lineNumber + offset);
            offset++;
        }

    file->setTeXCommand(command.callEnd("table"),lineNumber+offset);
    offset++;
    file->replaceTeXCommand(CMD_PARAGRAPH_BREAK, lineNumber + offset);

    file->saveFile();
    file->compile(compilerPath);
    file->compile(compilerPath);
}

void Dialog_ModifyTable::setData(int lineNumber, TeXFile *file, QString compilerPath,
                                 QStringList tableCommands)
{
    QString rowColorContent;
    this->lineNumber = lineNumber;
    this->file = file;
    this->compilerPath = compilerPath;
    this->tableCommands = tableCommands;
    foreach (QString tableCommand, tableCommands) {
        if (tableCommand.contains(command.callBegin(ENV_TABULAR))) {
            QRegularExpression re("\\\\begin\\{tabular\\}\\{(.*?)\\}");
            QRegularExpressionMatch match = re.match(tableCommand);
            if (match.hasMatch()) {
                QString argument = match.captured(1);
                ui->spinBoxColumns->setValue(argument.count('l') + argument.count('c') +
                                             argument.count('r'));
                ui->tableWidget->setColumnCount(argument.count('l') + argument.count('c') +
                                                argument.count('r'));
            }
        }

        QRegularExpression rowcolorRe("(\\\\rowcolor\\[.*?\\]\\{.*?\\})");
       QRegularExpressionMatch  match = rowcolorRe.match(tableCommand);
        if (match.hasMatch()) {
            QString content = match.captured(1);
            rowColorContent = content;
        }

        if (tableCommand.contains(CMD_TAB_HORIZ_LINE)) {
            ui->tableWidget->setRowCount(tableCommand.count(CMD_TAB_NEW_ROW));
            ui->spinBoxRows->setValue(tableCommand.count(CMD_TAB_NEW_ROW));
            QStringList tableCells = tableCommand.replace(QString(CMD_TAB_NEW_ROW) + " " + QString(
                                                              CMD_TAB_HORIZ_LINE), " &").remove(rowColorContent).remove(CMD_TAB_NEW_ROW).remove(CMD_TAB_HORIZ_LINE).split('&');
            qDebug() << tableCells;
            int positionCell = 0;
            for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
                for (int column = 0; column < ui->tableWidget->columnCount(); column++) {
                    QTableWidgetItem *tableItem = new QTableWidgetItem;
                    tableItem->setText(tableCells.at(positionCell));
                    ui->tableWidget->setItem(row, column, tableItem);
                    if (positionCell < tableCells.count()) {
                        positionCell++;
                    }
                }
            }
        }
    }
}

void Dialog_ModifyTable::on_spinBoxColumns_valueChanged(int arg1)
{
    ui->tableWidget->setColumnCount(arg1);
}

void Dialog_ModifyTable::on_spinBoxRows_valueChanged(int arg1)
{
    ui->tableWidget->setRowCount(arg1);
}

void Dialog_ModifyTable::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Discard) {
        for (int iterationLineNumber=lineNumber;iterationLineNumber>0;iterationLineNumber--)
        {
            if (file->getFileContent().at(iterationLineNumber).contains(command.callBegin("table")))
            {
                for (int secondIterationLineNumber=iterationLineNumber;secondIterationLineNumber<file->getFileContent().length();secondIterationLineNumber++)
                {
                    if (file->getFileContent().at(secondIterationLineNumber).compare(command.callEnd("table"))!=0)
                    {
                        file->deleteTeXCommand(secondIterationLineNumber);
                        secondIterationLineNumber--;
                    }
                    else
                    {
                        file->deleteTeXCommand(secondIterationLineNumber);
                        break;
                    }
                }
                file->saveFile();
                file->compile(compilerPath);
                file->compile(compilerPath);
                hide();
                break;
            }
        }

    }

}
