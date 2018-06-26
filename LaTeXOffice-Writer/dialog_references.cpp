#include "dialog_references.h"
#include "ui_dialog_references.h"

Dialog_References::Dialog_References(TeXFile *file, int lineNumber, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_References)
{
    ui->setupUi(this);
    this->file = file;
    this->lineNumber = lineNumber;

    scanDocumentReferences();
}

Dialog_References::~Dialog_References()
{
    delete ui;
}

void Dialog_References::scanDocumentReferences()
{
    QStringList fileContent = file->getFileContent();

    ui->listWidget->clear();
    for (int lineNumber=0; lineNumber<fileContent.length(); lineNumber++)
    {
        if (fileContent.at(lineNumber).contains(CMD_LABEL))
        {
            QString reference = fileContent.at(lineNumber);
            QString referenceContent;
            referencesList.append(referenceContent);
            QRegularExpression labelRegularExpresion("\\\\label\{(.*?)\}");
            QRegularExpressionMatchIterator iterator = labelRegularExpresion.globalMatch(reference);
            while (iterator.hasNext()) {
                QRegularExpressionMatch match = iterator.next();
                referenceContent = match.captured(1);
                ui->listWidget->addItem(referenceContent);
            }

        }
    }

}

void Dialog_References::on_buttonBox_accepted()
{
    if (!ui->listWidget->currentItem()->text().isEmpty()) {
        QString line = file->getFileContent().at(lineNumber - 1);
        if (ui->listWidget->currentItem()->text().contains("eq:"))
        {
            file->replaceTeXCommand(line.append(command->callEqReference(
                                                    ui->listWidget->currentItem()->text())), lineNumber - 1);
        }
        else
        {
            file->replaceTeXCommand(line.append(command->callReference(
                                                    ui->listWidget->currentItem()->text())), lineNumber - 1);
        }
        file->saveFile();

    }
}

void Dialog_References::on_lineEditFilter_textChanged(const QString &arg1)
{
    QString filterText = arg1;

    for( int i = 0; i < ui->listWidget->count(); i++ )
    {
        QListWidgetItem* current = ui->listWidget->item( i );
        if(!current->text().contains( filterText ) )
        {
            current->setHidden(true);
        }
        else
        {
            current->setHidden(false);
        }
    }
}

void Dialog_References::on_buttonBox_helpRequested()
{
    QMessageBox::information(this, APP_NAME,
                             tr("You can select an available document element like a table or an image and reference it."));
}
