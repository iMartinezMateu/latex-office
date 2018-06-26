#ifndef DIALOG_CHAPTER_H
#define DIALOG_CHAPTER_H

#include <QDialog>
#include "lib/latex/file.h"
#include "documentviewer.h"
#include <QPushButton>

namespace Ui {
class Dialog_Chapter;
}

class Dialog_Chapter : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_Chapter(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_Chapter();
    /*************************************************************************************************/
    /**
      @brief This function sets the necessary data so the dialog can work.
      @param file current TeX file reference.
      @param viewer document viewer widget reference.
      @param compilerPath PDF compiler binary path.
      @returns This is a void function.
      */
    void setData(TeXFile *file, DocumentViewer *viewer, QString compilerPath);
    /*End of declaration of public functions*/

private slots:
    void on_lineEditChapter_textChanged(const QString &arg1);
    void on_buttonBox_accepted();
    void on_buttonBox_helpRequested();

private:
    /*Private variables*/
    Ui::Dialog_Chapter *ui;
    TeXFile *file;
    TeXCommands *command;
    DocumentViewer *viewer;
    QString compilerPath;
    /*End of declaration of private variables*/
};

#endif // DIALOG_CHAPTER_H
