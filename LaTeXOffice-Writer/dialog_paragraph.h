#ifndef DIALOG_PARAGRAPH_H
#define DIALOG_PARAGRAPH_H

#include <QDialog>
#include "lib/latex/file.h"
#include "documentviewer.h"
#include <QPushButton>

namespace Ui {
class Dialog_Paragraph;
}

class Dialog_Paragraph : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /*************************************************************************************************/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_Paragraph(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_Paragraph();
    /*************************************************************************************************/
    /**
      @brief This function sets the necessary data so the dialog can work.
      @param file current TeX file reference.
      @param viewer document viewer widget reference.
      @param compilerPath PDF compiler binary path.
      @param documentStructureList current document structure list
      @returns This is a void function.
      */
    void setData(TeXFile *file, DocumentViewer *viewer, QString compilerPath,
                 QStringList documentStructureList);
    /*End of declaration of public functions*/

private slots:
    void on_buttonBox_accepted();

private:
    /*Private variables*/
    Ui::Dialog_Paragraph *ui;
    TeXFile *file;
    DocumentViewer *viewer;
    QString compilerPath;
    QStringList documentStructureList;
    /*End of declaration of private variables*/
};

#endif // DIALOG_PARAGRAPH_H
