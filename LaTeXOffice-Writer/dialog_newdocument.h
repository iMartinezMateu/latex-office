#ifndef DIALOG_NEWDOCUMENT_H
#define DIALOG_NEWDOCUMENT_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QToolTip>
#include <QLocale>
#include <QPushButton>

#include "lib/latex/file.h"
namespace Ui {
class Dialog_NewDocument;
}

class Dialog_NewDocument : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_NewDocument(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_NewDocument();
    /*************************************************************************************************/
    /**
      @brief This function checks the Operating System language, so the program can set automatically the language document according to it.
      @returns This is a void function.
      */
    void checkOSLocale();
    /*************************************************************************************************/
    /**
      @brief This function creates a new document with the data supplied.
      @param documentTypeIndex this is the combobox element index of the selected document type.
      @param documentLanguageIndex this is the combobox element index of the selected document language.
      @param fontSizeIndex this is the combobox element index of the selected font size.
      @param paperLayoutIndex this is the combobox element index of the selected paper layout.
      @param paperSizeIndex this is the combobox element index of the selected paper size.
      @param documentTypesetIndex this is the combobox element index of the selected document typeset.
      @param documentLayoutIndex this is the combobox element index of the selected document layout.
      @param chapterLayoutIndex this is the combobox element index of the selected chapter layout.
      @param documentTitle this is the title of the document.
      @param documentAuthor this is the author of the document.
      @param documentDate this is the date of the document.
      @param documentDirectory this is the path where the document will be stored.
      @returns This is a void function.
      */
    void createDocument(int documentTypeIndex, int documentLanguageIndex, int fontSizeIndex,
                        int paperLayoutIndex,
                        int paperSizeIndex, int documentTypesetIndex, int documentLayoutIndex,
                        int chapterLayoutIndex,
                        QString documentTitle, QString documentAuthor, QString documentDate,
                        QString documentDirectory);
    /*************************************************************************************************/
    /**
      @brief This function returns the document path.
      @returns This function returns the path where the document is stored.
      */
    QString getDocumentPath();
    /*End of declaration of public functions*/

private slots:
    void on_pushButtonBrowseDirectory_clicked();
    void on_buttonBox_accepted();
    void on_lineEditDocumentDirectory_textChanged(const QString &arg1);
    void on_lineEditDocumentTitle_textEdited(const QString &arg1);
    void on_pushButtonBrowseStyleFile_clicked();
    void on_pushButtonBrowseClassFile_clicked();
    void on_pushButtonClearStyleFile_clicked();
    void on_pushButtonClearClassFile_clicked();
    void on_buttonBox_helpRequested();

private:
    /*Private variables*/
    Ui::Dialog_NewDocument *ui;
    TeXCommands *command;
    /*End of declaration of private variables*/

};

#endif // DIALOG_NEWDOCUMENT_H
