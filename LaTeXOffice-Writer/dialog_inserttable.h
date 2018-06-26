#ifndef DIALOG_INSERTTABLE_H
#define DIALOG_INSERTTABLE_H

#include <QDialog>
#include <QPushButton>
#include "lib/latex/file.h"
#include "lib/latex/commands.h"
#include "lib/latex/constants.h"
#include "lib/latex/packages.h"
#include <constants.h>

namespace Ui {
class Dialog_InsertTable;
}

class Dialog_InsertTable : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_InsertTable(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function sets the necessary data so the dialog can work.
      @param lineNumber number of the document's selected line.
      @param file current TeX file reference.
      @param compilerPath current document viewer reference.
      @returns This is a void function.
      */
    void setData(int lineNumber, TeXFile *file, QString compilerPath);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_InsertTable();
    /*End of declaration of public functions*/

private slots:
    void on_spinBoxColumns_valueChanged(int arg1);
    void on_spinBoxRows_valueChanged(int arg1);
    void on_buttonBox_accepted();
    void on_buttonBox_helpRequested();

private:
    /*Private variables*/
    Ui::Dialog_InsertTable *ui;
    int lineNumber;
    TeXFile *file;
    QString compilerPath;
    TeXCommands command;
    /*End of declaration of private variables*/
};

#endif // DIALOG_INSERTTABLE_H
