#include "dialog_compilersettings.h"
#include "ui_dialog_compilersettings.h"

Dialog_CompilerSettings::Dialog_CompilerSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_CompilerSettings)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    showWarning();
    wantPathChange = false;
    ui->lineEditCompilerPath->setText(TeXCompiler::loadPDFCompilerPathSettings());
    ui->lineEditBIBTeXPath->setText(TeXCompiler::loadBIBCompilerPathSettings());
    ui->lineEditHTMLConverterPath->setText(TeXCompiler::loadHTMLConverterPathSettings());
    ui->lineEditRTFConverterPath->setText(TeXCompiler::loadRTFConverterPathSettings());
    ui->lineEditTXTConverterPath->setText(TeXCompiler::loadTXTConverterPathSettings());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    ui->buttonBox->button(QDialogButtonBox::Help)->setText(tr("Help"));
}

Dialog_CompilerSettings::~Dialog_CompilerSettings()
{
    delete ui;
}

void Dialog_CompilerSettings::showWarning()
{
    QMessageBox::warning(this, APP_NAME,
                         tr("WATCH OUT!!!\nChanging compiler settings could bring the absolute loss of the program functionality. Act with precaution from here!"));
}

void Dialog_CompilerSettings::on_pushButtonChangeCompilerPath_clicked()
{
    showWarning();
    ui->pushButtonAutoDetectPDFLaTeX->setEnabled(true);
    ui->pushButtonAutoDetectBIBTeX->setEnabled(true);
    ui->pushButtonHTMLConverter->setEnabled(true);
    ui->pushButtonRTFConverter->setEnabled(true);
    ui->pushButtonTXTConverter->setEnabled(true);
    ui->pushButtonChangeCompilerPath->setEnabled(false);
    ui->lineEditCompilerPath->setEnabled(true);
    ui->lineEditCompilerPath->setReadOnly(false);
    ui->lineEditBIBTeXPath->setReadOnly(false);
    ui->lineEditHTMLConverterPath->setReadOnly(false);
    ui->lineEditRTFConverterPath->setReadOnly(false);
    ui->lineEditTXTConverterPath->setReadOnly(false);
    wantPathChange = true;
}

void Dialog_CompilerSettings::on_buttonBox_accepted()
{
    TeXCompiler::savePDFCompilerPathSettings(ui->lineEditCompilerPath->text());
    TeXCompiler::saveBIBCompilerPathSettings(ui->lineEditBIBTeXPath->text());
    if (!ui->lineEditHTMLConverterPath->text().isEmpty()) {
        TeXCompiler::saveHTMLConverterPathSettings(ui->lineEditHTMLConverterPath->text());
    }
    if (!ui->lineEditRTFConverterPath->text().isEmpty()) {
        TeXCompiler::saveRTFConverterPathSettings(ui->lineEditRTFConverterPath->text());
    }
    if (!ui->lineEditTXTConverterPath->text().isEmpty()) {
        TeXCompiler::saveTXTConverterPathSettings(ui->lineEditTXTConverterPath->text());
    }
    QMessageBox::information(this, APP_NAME,
                             tr("The program must be restarted in order to check the new compiler path. Save your work and quit the application."));
}
void Dialog_CompilerSettings::on_lineEditCompilerPath_textChanged(const QString &arg1)
{
    if (arg1.isEmpty() || ui->lineEditBIBTeXPath->text().isEmpty()) {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    } else {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

void Dialog_CompilerSettings::on_pushButtonAutoDetectPDFLaTeX_clicked()
{
    QString path;

    QMessageBox::information(this, APP_NAME,
                             tr("Please be patient. This process can take a long time to complete ..."),
                             QMessageBox::Ok);
    path = TeXCompiler::searchCompilerBinary();
    if (!path.isEmpty()) {
        ui->lineEditCompilerPath->setText(path);
    } else {
        QMessageBox::critical(this, APP_NAME,
                              tr("LaTeX Office could not detect a valid PDFLaTeX compiler. Check that your LaTeX distribution has been installed correctly and try again."));
    }
}

void Dialog_CompilerSettings::on_lineEditBIBTeXPath_textChanged(const QString &arg1)
{
    if (arg1.isEmpty() || ui->lineEditCompilerPath->text().isEmpty()) {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    } else {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}


void Dialog_CompilerSettings::on_pushButtonAutoDetectBIBTeX_clicked()
{
    QString path;

    QMessageBox::information(this, APP_NAME,
                             tr("Please be patient. This process can take a long time to complete ..."),
                             QMessageBox::Ok);
    path = TeXCompiler::searchBiBTeXBinary();
    if (!path.isEmpty()) {
        ui->lineEditBIBTeXPath->setText(path);
    } else {
        QMessageBox::critical(this, APP_NAME,
                              tr("LaTeX Office could not detect a valid BIBTeX compiler. Check that your LaTeX distribution has been installed correctly and try again."));
    }
}

void Dialog_CompilerSettings::on_pushButtonHTMLConverter_clicked()
{
    QString path;

    QMessageBox::information(this, APP_NAME,
                             tr("Please be patient. This process can take a long time to complete ..."),
                             QMessageBox::Ok);
    path = TeXCompiler::searchHTMLConverterBinary();
    if (!path.isEmpty()) {
        ui->lineEditHTMLConverterPath->setText(path);
    } else {
        QMessageBox::critical(this, APP_NAME,
                              tr("LaTeX Office could not detect a valid HTML converter. Check that your LaTeX distribution has been installed correctly and try again."));
    }
}

void Dialog_CompilerSettings::on_pushButtonTXTConverter_clicked()
{
    QString path;

    QMessageBox::information(this, APP_NAME,
                             tr("Please be patient. This process can take a long time to complete ..."),
                             QMessageBox::Ok);
    path = TeXCompiler::searchTXTConverterBinary();
    if (!path.isEmpty()) {
        ui->lineEditTXTConverterPath->setText(path);
    } else {
        QMessageBox::critical(this, APP_NAME,
                              tr("LaTeX Office could not detect a valid TXT converter. Check that your LaTeX distribution has been installed correctly and try again."));
    }
}

void Dialog_CompilerSettings::on_pushButtonRTFConverter_clicked()
{
    QString path;

    QMessageBox::information(this, APP_NAME,
                             tr("Please be patient. This process can take a long time to complete ..."),
                             QMessageBox::Ok);
    path = TeXCompiler::searchRTFConverterBinary();
    if (!path.isEmpty()) {
        ui->lineEditHTMLConverterPath->setText(path);
    } else {
        QMessageBox::critical(this, APP_NAME,
                              tr("LaTeX Office could not detect a valid RTF converter. Check that your LaTeX distribution has been installed correctly and try again."));
    }
}

void Dialog_CompilerSettings::on_buttonBox_helpRequested()
{
    QMessageBox::information(this, APP_NAME,
                             tr("You can change some paths regarding to the program binaries related to the document compiling process. It is not recommended to change these settings if the program works correctly."));

}
