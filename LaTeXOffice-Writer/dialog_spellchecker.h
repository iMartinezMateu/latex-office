#ifndef DIALOG_SPELLCHECKER_H
#define DIALOG_SPELLCHECKER_H

#include <QDialog>
#include <QMessageBox>
#include "constants.h"
#include <QPushButton>
#include "lib/spellchecker.h"
#include <QTextEdit>
namespace Ui {
class Dialog_SpellChecker;
}

class Dialog_SpellChecker : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param fileContent current document content.
      @param spellChecker a Hunspell SpellChecker valid reference.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_SpellChecker(QStringList fileContent, SpellChecker *spellChecker,
                                 QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_SpellChecker();

    enum SpellCheckAction {AbortCheck, IgnoreOnce, IgnoreAll, ReplaceOnce, ReplaceAll, AddToDict};//!<  Declare the actions that the Spell Checker can do if a wrong word has been detected.
    /*************************************************************************************************/
    /**
      @brief This function replaces the selected word.
      @returns This function returns the new word.
      */
    QString replacement();
    /*************************************************************************************************/
    /**
      @brief This function gets the reference of the document zone.
      @returns This function returns the reference of the UI widget that shows the document content.
      */
    QTextEdit *getDocumentZone();
    /*End of declaration of public functions*/

public slots:
    /*************************************************************************************************/
    /**
      @brief This function checks the word given .
      @returns This function returns the reference of the UI widget that shows the document content.
      */
    SpellCheckAction checkWord(QString word);

protected slots:
    void ignoreOnce();
    void ignoreAll();
    void replaceOnce();
    void replaceAll();
    void addToDict();

private:
    /*Private variables*/
    Ui::Dialog_SpellChecker *ui;
    SpellChecker *_spellChecker;
    QString _unknownWord;
    SpellCheckAction _returnCode;
    /*End of declaration of private variables*/
};

#endif // DIALOG_SPELLCHECKER_H
