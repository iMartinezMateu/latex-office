#ifndef DIALOG_CITATIONS_H
#define DIALOG_CITATIONS_H

#include <QDialog>
#include "lib/latex/bibliography.h"
#include "caja.h"
#include "lib/latex/commands.h"
#include "lib/latex/file.h"
#include <constants.h>
#include <QMessageBox>
namespace Ui {
class Dialog_Citations;
}

class Dialog_Citations : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param file current TeX file reference.
      @param bibFile bibliography definitions reference.
      @param lineNumber selected line number.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_Citations(TeXFile *file, TeXBibliography *bibFile, int lineNumber,
                              QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_Citations();
    /*End of declaration of public functions*/

private slots:
    void on_comboBoxCategory_currentIndexChanged(int index);
    void on_buttonBox_accepted();
    void on_buttonBox_helpRequested();

private:
    /*Private variables*/
    Ui::Dialog_Citations *ui;
    TeXBibliography *bibFile;
    QList<QStringList> articlesList;
    QList<QStringList> bookletsList;
    QList<QStringList> booksList;
    QList<QStringList> inbooksList;
    QList<QStringList> incollectionsList;
    QList<QStringList> inproceedingsList;
    QList<QStringList> manualsList;
    QList<QStringList> proceedingsList;
    QList<QStringList> reportsList;
    QList<QStringList> thesisList;
    QStringList articlesIDList;
    QStringList bookletsIDList;
    QStringList booksIDList;
    QStringList inbooksIDList;
    QStringList incollectionsIDList;
    QStringList inproceedingsIDList;
    QStringList manualsIDList;
    QStringList proceedingsIDList;
    QStringList reportsIDList;
    QStringList thesisIDList;
    TeXFile *file;
    Caja *caja;
    TeXCommands *command;
    int lineNumber;
    /*End of declaration of private variables*/
};

#endif // DIALOG_CITATIONS_H
