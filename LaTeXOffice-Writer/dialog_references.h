#ifndef DIALOG_REFERENCES_H
#define DIALOG_REFERENCES_H

#include <QDialog>
#include <lib/latex/file.h>
#include <lib/latex/commands.h>
#include <constants.h>
namespace Ui {
class Dialog_References;
}

class Dialog_References : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param file LaTeX currrent file reference.
      @param lineNumber number of the selected document line.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_References(TeXFile *file, int lineNumber, QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_References();
    /*End of declaration of public functions*/

private slots:
    void on_buttonBox_accepted();
    void on_lineEditFilter_textChanged(const QString &arg1);

    void on_buttonBox_helpRequested();

private:
    /*Private functions*/
    /*************************************************************************************************/
    /**
      @brief This function scans the document references stored in the document.
      @returns This is a void function.
      */
    void scanDocumentReferences();
    /*End of declaration of private functions*/
    /*Private variables*/
    QStringList referencesList;
    Ui::Dialog_References *ui;
    TeXFile *file;
    int lineNumber;
    TeXCommands *command;
    /*End of declaration of private variables*/
};

#endif // DIALOG_REFERENCES_H
