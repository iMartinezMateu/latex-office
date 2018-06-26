#ifndef DIALOG_MODIFYCODEASSET_H
#define DIALOG_MODIFYCODEASSET_H

#include <QDialog>
#include "lib/latex/file.h"
#include "lib/latex/commands.h"
#include <QPushButton>
#include <constants.h>

namespace Ui {
class Dialog_ModifyCodeAsset;
}

class Dialog_ModifyCodeAsset : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param line current document's line which contains the code asset.
      @param lineNumber current document's line number selection.
      @param file current LaTeX file reference.
      @param compilerPath PDFLaTeX compiler binary path.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */    explicit Dialog_ModifyCodeAsset(QString line, int lineNumber, TeXFile *file,
                                    QString compilerPath, QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_ModifyCodeAsset();
    /*End of declaration of public functions*/

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_clicked(QAbstractButton *button);
    void on_lineEditCaption_textChanged(const QString &arg1);
    void on_buttonBox_helpRequested();

private:
    /*Private variables*/
    Ui::Dialog_ModifyCodeAsset *ui;
    int lineNumber;
    TeXFile *file;
    TeXCommands *command;
    QString compilerPath;
    /*End of declaration of private variables*/
};

#endif // DIALOG_MODIFYCODEASSET_H
