#ifndef DIALOG_COMPILERSETTINGS_H
#define DIALOG_COMPILERSETTINGS_H

#include <QDialog>
#include <QMessageBox>
#include "constants.h"
#include "lib/latex/compiler.h"
namespace Ui {
class Dialog_CompilerSettings;
}

class Dialog_CompilerSettings : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_CompilerSettings(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_CompilerSettings();
    /*End of declaration of public functions*/

private slots:
    void on_pushButtonChangeCompilerPath_clicked();
    void on_buttonBox_accepted();
    void on_lineEditCompilerPath_textChanged(const QString &arg1);
    void on_pushButtonAutoDetectPDFLaTeX_clicked();
    void on_lineEditBIBTeXPath_textChanged(const QString &arg1);
    void on_pushButtonAutoDetectBIBTeX_clicked();
    void on_pushButtonHTMLConverter_clicked();
    void on_pushButtonTXTConverter_clicked();
    void on_pushButtonRTFConverter_clicked();
    void on_buttonBox_helpRequested();

private:
    /*Private variables*/
    Ui::Dialog_CompilerSettings *ui;
    bool wantPathChange;
    /*End of declaration of private variables*/
    /*Private functions*/
    /*************************************************************************************************/
    /**
      @brief This function shows a warning message box to the user, so he can know the risks of touching the compiler paths.
      @returns This is a void function.
      */
    void showWarning();
    /*End of declaration of private functions*/
};

#endif // DIALOG_COMPILERSETTINGS_H
