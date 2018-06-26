#include "dialog_paragraph.h"
#include "ui_dialog_paragraph.h"

Dialog_Paragraph::Dialog_Paragraph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Paragraph)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));

}

Dialog_Paragraph::~Dialog_Paragraph()
{
    delete ui;
}

void Dialog_Paragraph::setData(TeXFile *file, DocumentViewer *viewer,
                               QString compilerPath, QStringList documentStructureList)
{
    int chapterNumbering = 1;
    this->file = file;
    this->viewer = viewer;
    this->compilerPath = compilerPath;
    this->documentStructureList = documentStructureList;
    QRegularExpression chapterRegularExpresion("\\\\chapter\{(.*?)\}");
    QRegularExpression sectionRegularExpresion("\\\\section\{(.*?)\}");
    QRegularExpression subSectionRegularExpresion("\\\\subsection\{(.*?)\}");
    QRegularExpression subSubSectionRegularExpresion("\\\\subsubsection\{(.*?)\}");

    foreach (QString line, documentStructureList) {
        QRegularExpressionMatch match = chapterRegularExpresion.match(line);
        if (match.hasMatch()) {
            ui->comboBoxDocumentStructure->addItem(QString::number(chapterNumbering) + ". " +
                                                   match.captured(1));
            chapterNumbering++;
        }
        match = sectionRegularExpresion.match(line);
        if (match.hasMatch()) {
            ui->comboBoxDocumentStructure->addItem("        " + match.captured(1));
        }
        match = subSectionRegularExpresion.match(line);
        if (match.hasMatch()) {
            ui->comboBoxDocumentStructure->addItem("              " + match.captured(1));
        }
        match = subSubSectionRegularExpresion.match(line);
        if (match.hasMatch()) {
            ui->comboBoxDocumentStructure->addItem("                  " + match.captured(1));
        }
    }

}

void Dialog_Paragraph::on_buttonBox_accepted()
{
    QString selectedStructureLine = documentStructureList.at(
                                        ui->comboBoxDocumentStructure->currentIndex());
    int lineNumber = file->getLineNumber(selectedStructureLine);

    for (lineNumber; lineNumber < file->getEndDocumentCommand(); lineNumber++) {
        if (file->getFileContent().at(lineNumber).compare(selectedStructureLine) == 0) {
            for (int subElement = lineNumber; subElement < file->getEndDocumentCommand();
                 subElement++) {
                if (ui->comboBoxDocumentStructure->currentIndex() + 1 <
                    ui->comboBoxDocumentStructure->count())
                    if (file->getFileContent().at(subElement).compare(documentStructureList.at(
                                                                          ui->comboBoxDocumentStructure->currentIndex() + 1)) == 0) {
                        file->writePlainText("Lorem ipsum ad his scripta blandit partiendo, eum fastidii accumsan euripidis in, eum liber hendrerit an. Qui ut wisi vocibus suscipiantur, quo dicit ridens inciderint id. Quo mundi lobortis reformidans eu, legimus senserit definiebas an eos. Eu sit tincidunt incorrupte definitionem, vis mutat affert percipit cu, eirmod consectetuer signiferumque eu per. In usu latine equidem dolores. Quo no falli viris intellegam, ut fugit veritus placerat per.",
                                             subElement);
                        break;
                    }
                if (ui->comboBoxDocumentStructure->currentIndex() + 1 ==
                    ui->comboBoxDocumentStructure->count())
                    if (file->getFileContent().at(subElement).compare(documentStructureList.at(
                                                                          ui->comboBoxDocumentStructure->currentIndex())) == 0) {
                        if (file->getBibliographyLine() != -1) {
                            file->writePlainText("Lorem ipsum ad his scripta blandit partiendo, eum fastidii accumsan euripidis in, eum liber hendrerit an. Qui ut wisi vocibus suscipiantur, quo dicit ridens inciderint id. Quo mundi lobortis reformidans eu, legimus senserit definiebas an eos. Eu sit tincidunt incorrupte definitionem, vis mutat affert percipit cu, eirmod consectetuer signiferumque eu per. In usu latine equidem dolores. Quo no falli viris intellegam, ut fugit veritus placerat per.",
                                                 file->getBibliographyLine());
                        } else {
                            file->writePlainText("Lorem ipsum ad his scripta blandit partiendo, eum fastidii accumsan euripidis in, eum liber hendrerit an. Qui ut wisi vocibus suscipiantur, quo dicit ridens inciderint id. Quo mundi lobortis reformidans eu, legimus senserit definiebas an eos. Eu sit tincidunt incorrupte definitionem, vis mutat affert percipit cu, eirmod consectetuer signiferumque eu per. In usu latine equidem dolores. Quo no falli viris intellegam, ut fugit veritus placerat per.",
                                                 file->getEndDocumentCommand());
                        }
                        break;
                    }
            }
            break;
        }
    }
    file->saveFile();
    file->compile(compilerPath);
    file->compile(compilerPath);
    viewer->refresh(viewer->getCurrentPage());
    viewer->fillList();
}
