#ifndef DIALOG_INSERTIMAGE_H
#define DIALOG_INSERTIMAGE_H

#include <QDialog>
#include <QFileDialog>
#include <lib/latex/file.h>
#include <lib/latex/commands.h>
#include <constants.h>
namespace Ui {
class Dialog_InsertImage;
}

class Dialog_InsertImage : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_InsertImage(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_InsertImage();
    /*************************************************************************************************/
    /**
      @brief This function sets the necessary data so the dialog can work.
      @param lineNumber number of the document's selected line.
      @param file current TeX file reference.
      @param compilerPath current document viewer reference.
      @returns This is a void function.
      */
    void setData(int lineNumber, TeXFile *file, QString compilerPath);
    /*End of declaration of public functions*/

private slots:
    void on_pushButtonBrowse_clicked();
    void on_lineEditImagePath_textChanged(const QString &arg1);
    void on_buttonBox_accepted();
    void on_buttonBox_helpRequested();

private:
    /*Private variables*/
    Ui::Dialog_InsertImage *ui;
    int lineNumber;
    TeXFile *file;
    TeXCommands command;
    QString compilerPath;
    /*End of declaration of private variables*/
};

#endif // DIALOG_INSERTIMAGE_H
