#ifndef DIALOG_DOCUMENTLOCK_H
#define DIALOG_DOCUMENTLOCK_H

#include <QDialog>
#include <QMessageBox>
#include "constants.h"
#include "lib/latex/file.h"
namespace Ui {
class Dialog_DocumentLock;
}

class Dialog_DocumentLock : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param file current TeX file reference.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_DocumentLock(TeXFile *file, QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_DocumentLock();
    /*************************************************************************************************/
    /**
      @brief This function checks if the file has been locked.
      @returns This function will return true if it is locked. Otherwise, it will return false.
      */
    bool getLockedFile();
    /*End of declaration of public functions*/

private slots:
    void on_pushButtonLockDocument_clicked();
    void on_lineEditPassword_textChanged(const QString &arg1);
    void on_lineEditVerify_textChanged(const QString &arg1);

private:
    /*Private variables*/
    Ui::Dialog_DocumentLock *ui;
    bool lockedFile;
    TeXFile *file;
    /*End of declaration of private variables*/
};

#endif // DIALOG_DOCUMENTLOCK_H
