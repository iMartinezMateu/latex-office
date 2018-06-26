#include "dialog_dictionarysettings.h"
#include "ui_dialog_dictionarysettings.h"

Dialog_DictionarySettings::Dialog_DictionarySettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_DictionarySettings)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    ui->buttonBox->button(QDialogButtonBox::Help)->setText(tr("Help"));
    on_pushButtonSearch_clicked();
}

Dialog_DictionarySettings::~Dialog_DictionarySettings()
{
    delete ui;
}

void Dialog_DictionarySettings::on_pushButtonSearch_clicked()
{
    QDirIterator it("./dictionaries", QStringList() << "*.dic", QDir::Files,
                    QDirIterator::Subdirectories);

    while (it.hasNext()) {
        ui->comboBox->addItem(it.next());
    }
}

QString Dialog_DictionarySettings::getDictionary()
{
    return selectedDictionary;
}

void Dialog_DictionarySettings::on_buttonBox_accepted()
{
    if (ui->comboBox->currentText().isEmpty()) {
        QMessageBox::critical(this, APP_NAME, tr("You have not selected a dictionary."));
    } else {
        selectedDictionary = ui->comboBox->currentText();
        if (!QDir("settings").exists()) {
            QDir().mkdir("settings");
        }
        if (QFile("settings/dictionary.los").exists()) {
            QFile("settings/dictionary.los").remove();
        }
        QString filename = "settings/dictionary.los";
        QFile file(filename);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            stream << selectedDictionary << endl;
        }
        file.close();
    }
}

void Dialog_DictionarySettings::on_pushButtonAdd_clicked()
{
    QString DICfileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                       "",
                                                       tr("Dictionary File (*.dic)"));
    if (DICfileName != NULL) {
        QString AFFfileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                           "",
                                                           tr("Auxiliar Dictionary File (*.aff)"));
        if (AFFfileName != NULL) {
            QFile(DICfileName).copy("./dictionaries/" + QFileInfo(
                                        DICfileName).baseName().append(".dic"));
            QFile(AFFfileName).copy("./dictionaries/" + QFileInfo(
                                        AFFfileName).baseName().append(".aff"));
            QMessageBox::information(this, APP_NAME, tr("Dictionary installed correctly!"));
            on_pushButtonSearch_clicked();
        }
    }
}

void Dialog_DictionarySettings::on_buttonBox_helpRequested()
{
    QMessageBox::information(this, APP_NAME,
                             tr("Selecting a dictionary stored in the hard drive will make the Grammar and Spelling Check functionality available."));

}
