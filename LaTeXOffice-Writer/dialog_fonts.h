#ifndef DIALOG_FONTS_H
#define DIALOG_FONTS_H

#include <QDialog>
#include <lib/latex/file.h>

namespace Ui {
class Dialog_Fonts;
}

class Dialog_Fonts : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param file current TeX File reference.
      @param compilerPath PDFLaTeX compiler binary reference.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_Fonts(TeXFile *file, QString compilerPath, QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_Fonts();
    /*End of declaration of public functions*/

private slots:
    void on_buttonBox_accepted();

private:
    /*Private variables*/
    Ui::Dialog_Fonts *ui;
    TeXFile* file;
    TeXCommands* command;
    QString compilerPath;
    /*End of declaration of private variables*/
};

#endif // DIALOG_FONTS_H
