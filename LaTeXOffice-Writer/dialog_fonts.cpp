#include "dialog_fonts.h"
#include "ui_dialog_fonts.h"

Dialog_Fonts::Dialog_Fonts(TeXFile* file, QString compilerPath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Fonts)
{
    ui->setupUi(this);
    this->file = file;
    this->compilerPath = compilerPath;
}

Dialog_Fonts::~Dialog_Fonts()
{
    delete ui;
}

void Dialog_Fonts::on_buttonBox_accepted()
{
   int fontIndex = ui->listWidgetFonts->currentRow();
   int fontSizeIndex = ui->comboBoxFontSize->currentIndex();
   int spacingIndex = ui->comboBoxLineSpread->currentIndex();
   int beginDocumentLine = file->getLineNumber(command->callBegin(ENV_DOCUMENT));
   int documentClassLine = file->getLineNumber(CMD_DOCUMENT_CLASS);

   if (file->getLineNumber(CMD_RMDEFAULT) != -1)
   {
        file->deleteTeXCommand(file->getLineNumber(CMD_RMDEFAULT));
   }

   switch (fontIndex)
   {
        case 0: //computer modern roman serif (cmr)
        file->setTeXCommand(command->callRMDefault("cmr"),beginDocumentLine);
        break;
        case 1: //latin modern roman serif (lmr)
        file->setTeXCommand(command->callRMDefault("lmr"),beginDocumentLine);
        break;
        case 2: //bookman serif (pbk)
        file->setTeXCommand(command->callRMDefault("pbk"),beginDocumentLine);
        break;
        case 3: //charter serif (bch)
        file->setTeXCommand(command->callRMDefault("bch"),beginDocumentLine);
        break;
        case 4: //new century schoolbook serif(pnc)
       file->setTeXCommand(command->callRMDefault("pnc"),beginDocumentLine);
        break;
        case 5: //palatino serif(ppl)
       file->setTeXCommand(command->callRMDefault("ppl"),beginDocumentLine);
        break;
        case 6: //times serif(ptm)
       file->setTeXCommand(command->callRMDefault("ptm"),beginDocumentLine);
        break;
        case 7: //computer modern sans serif(cmss)
       file->setTeXCommand(command->callRMDefault("cmss"),beginDocumentLine);
        break;
        case 8: //latin modern sans serif(lmss)
       file->setTeXCommand(command->callRMDefault("lmss"),beginDocumentLine);
        break;
        case 9: //avant grade sans serif(pag)
       file->setTeXCommand(command->callRMDefault("pag"),beginDocumentLine);
        break;
        case 10: //helvetica sans serif(phv)
       file->setTeXCommand(command->callRMDefault("phv"),beginDocumentLine);
        break;
        case 11: //computer modern typewriter(cmtt)
       file->setTeXCommand(command->callRMDefault("cmtt"),beginDocumentLine);
        break;
        case 12: //latin modern typewriter(lmtt)
       file->setTeXCommand(command->callRMDefault("lmtt"),beginDocumentLine);
        break;
        case 13: //courier typewriter(pcr)
       file->setTeXCommand(command->callRMDefault("pcr"),beginDocumentLine);
        break;
   }
    if (documentClassLine != -1)
    {
        QString documentClass = file->getFileContent().at(documentClassLine);
        QString documentFont;
        QRegularExpression documentClassRegularExpresion("(\\d.*?pt)");
        QRegularExpressionMatchIterator iterator = documentClassRegularExpresion.globalMatch(documentClass);
        while (iterator.hasNext()) {
            QRegularExpressionMatch match = iterator.next();
             documentFont = match.captured(1);
        }
           switch (fontSizeIndex)
           {
                case 0: //10 pt
                    file->replaceTeXCommand(documentClass.replace(documentFont,"10pt"),documentClassLine);
                    break;
                case 1: //11 pt
                   file->replaceTeXCommand(documentClass.replace(documentFont,"11pt"),documentClassLine);
                    break;
                case 2: //12 pt
                   file->replaceTeXCommand(documentClass.replace(documentFont,"12pt"),documentClassLine);
                    break;
           }
    }
   if (file->getLineNumber(CMD_LINESPREAD) != -1)
   {
        file->deleteTeXCommand(file->getLineNumber(CMD_LINESPREAD));
   }

   switch (spacingIndex)
   {
        case 0: //one
            file->setTeXCommand(command->callLineSpread("1"),beginDocumentLine);
            break;
        case 1: //one and a half
            file->setTeXCommand(command->callLineSpread("1.3"),beginDocumentLine);
            break;
        case 2: //double
            file->setTeXCommand(command->callLineSpread("1.6"),beginDocumentLine);
            break;

   }

   file->saveFile();
   file->compile(compilerPath);
   file->compile(compilerPath);


}
