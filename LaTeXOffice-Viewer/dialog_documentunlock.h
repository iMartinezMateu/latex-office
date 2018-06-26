#ifndef DIALOG_DOCUMENTUNLOCK_H
#define DIALOG_DOCUMENTUNLOCK_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include "lib/latex/commands.h"
#include <QFileInfo>
#include "constants.h"
#include <QTextStream>

namespace Ui {
class Dialog_DocumentUnlock;
}

class Dialog_DocumentUnlock : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param ltexFile a reference to the ciphered document to be unlocked.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_DocumentUnlock(QFile *ltexFile, QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_DocumentUnlock();
    /*************************************************************************************************/
    /**
      @brief This function checks if the file has been unlocked.
      @returns This function will return true if it is unlocked. Otherwise, it will return false.
      */
    bool getUnlockedFile();
    /*End of declaration of public functions*/

private slots:
    void on_lineEditPassword_textChanged(const QString &arg1);
    void on_pushButtonUnlock_clicked();

private:
    /*Private variables*/
    Ui::Dialog_DocumentUnlock *ui;
    bool unlockedFile;
    QFile *ltexFile;
    /*End of private variables*/
};

#endif // DIALOG_DOCUMENTUNLOCK_H
