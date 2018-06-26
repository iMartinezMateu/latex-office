#ifndef DIALOG_CODE_H
#define DIALOG_CODE_H

#include <QDialog>
#include "lib/latex/file.h"
#include <QPushButton>
#include "documentviewer.h"
namespace Ui {
class Dialog_Code;
}

class Dialog_Code : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param fileContent current document content.
      @param file current TeX file reference.
      @param viewer current document viewer widget reference.
      @param compilerPath PDF compiler binary path.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_Code(QStringList fileContent, TeXFile *file, DocumentViewer *viewer,
                         QString compilerPath, QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_Code();
    /*End of declaration of public functions*/

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    /*Private variables*/
    Ui::Dialog_Code *ui;
    TeXFile *file;
    DocumentViewer *viewer;
    QString compilerPath;
    /*End of declaration of private variables*/
};

#endif // DIALOG_CODE_H
