#ifndef DIALOG_MODIFYIMAGE_H
#define DIALOG_MODIFYIMAGE_H

#include <QDialog>
#include <QFileDialog>
#include "lib/latex/commands.h"
#include "lib/latex/file.h"
#include "lib/latex/constants.h"
#include <QRegularExpressionMatch>

namespace Ui {
class Dialog_ModifyImage;
}

class Dialog_ModifyImage : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_ModifyImage(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_ModifyImage();
    /*************************************************************************************************/
    /**
      @brief This function sets the necessary data so the dialog can work.
      @param file current TeX file reference.
      @param documentPath current document path.
      @param lines content of lines which contains the image.
      @param compilerPath PDFLaTeX binary compiler path.
      @returns This is a void function.
      */
    void setData(TeXFile *file, QString documentPath, QStringList lines,
                 QString compilerPath);
    /*End of declaration of public functions*/

private slots:
    void on_pushButtonBrowse_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    /*Private variables*/
    Ui::Dialog_ModifyImage *ui;
    TeXFile *file;
    QStringList lines;
    TeXCommands command;
    QString compilerPath;
    /*End of declaration of private variables*/
};

#endif // DIALOG_MODIFYIMAGE_H
