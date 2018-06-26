#ifndef DIALOG_DICTIONARYSETTINGS_H
#define DIALOG_DICTIONARYSETTINGS_H

#include <QDialog>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include "constants.h"
#include <QMessageBox>
#include <QFileDialog>
namespace Ui {
class Dialog_DictionarySettings;
}

class Dialog_DictionarySettings : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_DictionarySettings(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_DictionarySettings();
    /*************************************************************************************************/
    /**
      @brief This function gets the Hunspell dictionary declared to use.
      @returns The functions returns the selected Hunspell dictionary description.
      */
    QString getDictionary();
    /*End of declaration of public functions*/

private slots:
    void on_pushButtonSearch_clicked();
    void on_buttonBox_accepted();
    void on_pushButtonAdd_clicked();
    void on_buttonBox_helpRequested();

private:
    /*Private variables*/
    Ui::Dialog_DictionarySettings *ui;
    QString selectedDictionary;
    /*End of declaration of private variables*/
};

#endif // DIALOG_DICTIONARYSETTINGS_H
