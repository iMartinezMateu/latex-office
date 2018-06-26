#include "dialog_themesettings.h"
#include "ui_dialog_themesettings.h"
Dialog_ThemeSettings::Dialog_ThemeSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_ThemeSettings)
{
    ui->setupUi(this);
    on_pushButtonRefresh_clicked();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
}

Dialog_ThemeSettings::~Dialog_ThemeSettings()
{
    delete ui;
}

void Dialog_ThemeSettings::on_listWidget_itemSelectionChanged()
{
    if (!themeList.at(ui->listWidget->currentRow()).isEmpty()) {
        QFile themeFile(themeList.at(ui->listWidget->currentRow()));
        themeFile.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(themeFile.readAll());
        qApp->setStyleSheet(styleSheet);
        ui->pushButtonDelete->setEnabled(true);
    } else {
        qApp->setStyleSheet("");
        ui->pushButtonDelete->setEnabled(false);
    }
    ensurePolished();
}

void Dialog_ThemeSettings::on_pushButtonRefresh_clicked()
{
    ui->listWidget->clear();
    themeList.clear();
    ui->listWidget->addItem("Default Theme");
    themeList.append("");
    QDirIterator themeIterator("./themes", QStringList() << "*.qss", QDir::Files,
                               QDirIterator::Subdirectories);

    while (themeIterator.hasNext()) {
        QString theme = themeIterator.next();
        ui->listWidget->addItem(QFileInfo(theme).baseName());
        themeList.append(theme);
    }

}




void Dialog_ThemeSettings::on_buttonBox_accepted()
{
    QFile file("settings/theme.los");
    if (file.exists()) {
        file.remove();
    }
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << themeList.at(ui->listWidget->currentRow()) << endl;
    }
    file.close();

}


void Dialog_ThemeSettings::on_pushButtonInstall_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("Theme File (*.qss)"));
    if (fileName==NULL)
        return;

    QMessageBox messageBox(APP_NAME,
                           tr("The theme directory is ") + QFileInfo(fileName).absolutePath() +
                           tr(". In order to install a theme, the previous directory will have to be copied to a new path so make sure the directory is correct. Is the directory correct?"),
                           QMessageBox::Question,
                           QMessageBox::Yes | QMessageBox::Default,
                           QMessageBox::No | QMessageBox::Escape,  //This makes "Esc" key to Cancel the Dialog
                           QMessageBox::NoButton,
                           this);
    messageBox.setButtonText(QMessageBox::Yes, tr("Yes"));
    messageBox.setButtonText(QMessageBox::No, tr("No"));

    if (messageBox.exec() == QMessageBox::Yes) {
        installTheme(QFileInfo(fileName).absolutePath(),
                     "./themes/" + QFileInfo(fileName).baseName());
        on_pushButtonRefresh_clicked();


    }
}

bool Dialog_ThemeSettings::installTheme(const QString &srcFilePath,
                                        const QString &tgtFilePath)
{
    QFileInfo srcFileInfo(srcFilePath);
    if (srcFileInfo.isDir()) {
        QDir targetDir(tgtFilePath);
        targetDir.cdUp();
        if (!targetDir.mkdir(QFileInfo(tgtFilePath).fileName())) {
            return false;
        }
        QDir sourceDir(srcFilePath);
        QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs |
                                                    QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
        foreach (const QString &fileName, fileNames) {
            const QString newSrcFilePath
                = srcFilePath + QLatin1Char('/') + fileName;
            const QString newTgtFilePath
                = tgtFilePath + QLatin1Char('/') + fileName;
            if (!installTheme(newSrcFilePath, newTgtFilePath)) {
                return false;
            }
        }
    } else {
        if (!QFile::copy(srcFilePath, tgtFilePath)) {
            return false;
        }
    }
    return true;
}

bool Dialog_ThemeSettings::removeTheme(const QString &dirName)
{
    bool result = true;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
        Q_FOREACH (QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System |
                                                     QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeTheme(info.absoluteFilePath());
            } else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }
    return result;
}

void Dialog_ThemeSettings::on_pushButtonDelete_clicked()
{
    QMessageBox messageBox(APP_NAME,
                           tr("Do you want to delete the selected theme? You cannot undo the action..."),
                           QMessageBox::Question,
                           QMessageBox::Yes | QMessageBox::Default,
                           QMessageBox::No | QMessageBox::Escape,  //This makes "Esc" key to Cancel the Dialog
                           QMessageBox::NoButton,
                           this);
    messageBox.setButtonText(QMessageBox::Yes, tr("Yes"));
    messageBox.setButtonText(QMessageBox::No, tr("No"));



    if (messageBox.exec() == QMessageBox::Yes) {
        removeTheme(QFileInfo(themeList.at(ui->listWidget->currentRow())).absolutePath());
        on_pushButtonRefresh_clicked();
        ui->listWidget->clearSelection();
    }
}
