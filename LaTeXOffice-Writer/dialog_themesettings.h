#ifndef DIALOG_THEMESETTINGS_H
#define DIALOG_THEMESETTINGS_H

#include <QDialog>
#include <QMessageBox>
#include <QDirIterator>
#include <QFileInfo>
#include <QFile>
#include <QApplication>
#include <QTextStream>
#include "constants.h"
#include <QFileDialog>

namespace Ui {
class Dialog_ThemeSettings;
}

class Dialog_ThemeSettings : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_ThemeSettings(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_ThemeSettings();
    /*************************************************************************************************/
    /**
      @brief This function installs a theme that will be able to be used by LaTeX Office. This moves the theme to the internal path where LaTeX Office scans the available themes.
      @param srcFilePath theme path declared by the user .
      @param tgtFilePath new path where the theme is going to be moved.
      @returns This function returns true if the install process has been completed sucessfully. Otherwise, it will return false.
      */
    bool installTheme(const QString &srcFilePath,
                      const QString &tgtFilePath);
    /*************************************************************************************************/
    /**
      @brief This function deletes a theme installed by LaTeXOffice.
      @param dirName theme internal path.
      @returns This function returns true if the unistall process has been completed sucessfully. Otherwise, it will return false.
      */
    bool removeTheme(const QString &dirName);
    /*End of declaration of public functions*/

private slots:
    void on_listWidget_itemSelectionChanged();
    void on_pushButtonRefresh_clicked();
    void on_buttonBox_accepted();
    void on_pushButtonInstall_clicked();
    void on_pushButtonDelete_clicked();

private:
    /*Private variables*/
    Ui::Dialog_ThemeSettings *ui;
    QStringList themeList;
    /*End of declaration of private variables*/

};

#endif // DIALOG_THEMESETTINGS_H
