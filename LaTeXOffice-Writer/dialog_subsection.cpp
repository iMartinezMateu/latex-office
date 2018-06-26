#include "dialog_subsection.h"
#include "ui_dialog_subsection.h"

Dialog_SubSection::Dialog_SubSection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_SubSection)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    ui->buttonBox->button(QDialogButtonBox::Help)->setText(tr("Help"));

}

Dialog_SubSection::~Dialog_SubSection()
{
    delete ui;
}
void Dialog_SubSection::setData(TeXFile *file, DocumentViewer *viewer,
                                QString compilerPath)
{
    this->file = file;
    this->viewer = viewer;
    this->compilerPath = compilerPath;
}

void Dialog_SubSection::on_lineEditChapter_textChanged(const QString &arg1)
{
    if (arg1.isEmpty()) {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    } else {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

void Dialog_SubSection::on_buttonBox_accepted()
{
    if (file->getLineNumber(command->callSubSection(ui->lineEditChapter->text())) != -1) {
        QMessageBox::critical(this, APP_NAME,
                              tr("You cannot add a section that already exists on the document!"));
        return;
    }
    if (file->getLineNumber(command->callSubSectionNoN(ui->lineEditChapter->text())) != -1) {
        QMessageBox::critical(this, APP_NAME,
                              tr("You cannot add a section that already exists on the document!"));
        return;
    }

    if (ui->checkBoxEnumerate->isChecked()) {
        if (file->getBibliographyLine() != -1) {
            file->setTeXCommand(command->callSubSection(ui->lineEditChapter->text()),
                                file->getBibliographyLine());
        } else {
            file->setTeXCommand(command->callSubSection(ui->lineEditChapter->text()));
        }
    } else {
        if (file->getBibliographyLine() != -1) {
            file->setTeXCommand(command->callSubSectionNoN(ui->lineEditChapter->text()),
                                file->getBibliographyLine());
        } else {
            file->setTeXCommand(command->callSubSectionNoN(ui->lineEditChapter->text()));
        }
    }
    file->writePlainText("Lorem ipsum ad his scripta blandit partiendo, eum fastidii accumsan euripidis in, eum liber hendrerit an. Qui ut wisi vocibus suscipiantur, quo dicit ridens inciderint id. Quo mundi lobortis reformidans eu, legimus senserit definiebas an eos. Eu sit tincidunt incorrupte definitionem, vis mutat affert percipit cu, eirmod consectetuer signiferumque eu per. In usu latine equidem dolores. Quo no falli viris intellegam, ut fugit veritus placerat per.");
    file->saveFile();
    file->compile(compilerPath);
    file->compile(compilerPath);
    viewer->refresh(viewer->getCurrentPage());
    viewer->fillList();

}

void Dialog_SubSection::on_buttonBox_helpRequested()
{
    QMessageBox::information(this, APP_NAME,
                             tr("You can add a new subsection to your document and choose if you want it to be numbered or not."));

}
