#ifndef DIALOG_MODIFYTABLE_H
#define DIALOG_MODIFYTABLE_H

#include <QDialog>
#include "lib/latex/file.h"
#include "lib/latex/commands.h"
#include <QAbstractButton>
#include <QRegularExpressionMatch>
#include <QPushButton>
namespace Ui {
class Dialog_ModifyTable;
}

class Dialog_ModifyTable : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_ModifyTable(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function sets the necessary data so the dialog can work.
      @param lineNumber line number which contains the table.
      @param file current TeX file reference.
      @param compilerPath PDFLaTeX binary compiler path.
      @param tableCommands commands that where used to create the table.
      @returns This is a void function.
      */
    void setData(int lineNumber, TeXFile *file, QString compilerPath,
                 QStringList tableCommands);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_ModifyTable();
    /*End of declaration of public functions*/

private slots:
    void on_buttonBox_accepted();
    void on_spinBoxColumns_valueChanged(int arg1);
    void on_spinBoxRows_valueChanged(int arg1);
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    /*Private variables*/
    Ui::Dialog_ModifyTable *ui;
    int lineNumber;
    TeXFile *file;
    QString compilerPath;
    TeXCommands command;
    QStringList tableCommands;
    /*End of declaration of private variables*/
};

#endif // DIALOG_MODIFYTABLE_H
