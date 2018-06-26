#ifndef DIALOG_DOCUMENTPREAMBLE_H
#define DIALOG_DOCUMENTPREAMBLE_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QToolTip>

#include "lib/latex/file.h"
#include "constants.h"
#include "lib/latex/compiler.h"
#include "documentviewer.h"

namespace Ui {
class Dialog_DocumentPreamble;
}

class Dialog_DocumentPreamble : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_DocumentPreamble(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_DocumentPreamble();
    /*************************************************************************************************/
    /**
      @brief This function sets the necessary data so the dialog can work.
      @param file current TeX file reference.
      @param viewer current document viewer reference.
      @returns This is a void function.
      */
    void setData(TeXFile *file, DocumentViewer *viewer);
    /*End of declaration of public functions*/

private slots:
    void on_radioButtonDisableAbstract_clicked();
    void on_radioButtonEnableAbstract_clicked();
    void on_buttonBox_accepted();
    void on_lineEditDocumentTitle_textEdited(const QString &arg1);
    void on_buttonBox_helpRequested();

private:
    /*Private functions*/
    Ui::Dialog_DocumentPreamble *ui;
    TeXFile *file;
    DocumentViewer *viewer;
    TeXCommands command;
    bool titleEdited;
    bool authorEdited;
    bool dateEdited;
    /*End of declaration of private functions*/
};

#endif // DIALOG_DOCUMENTPREAMBLE_H
