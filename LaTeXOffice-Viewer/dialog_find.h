#ifndef DIALOG_FIND_H
#define DIALOG_FIND_H

#include <QDialog>

#include "documentviewer.h"

namespace Ui {
class Dialog_Find;
}

class Dialog_Find : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_Find(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_Find();
    /*************************************************************************************************/
    /**
      @brief This function sets the necessary data so the dialog can work.
      @param viewer current document viewer reference.
      @returns This is a void function.
      */
    void setData(DocumentViewer *viewer);
    /*End of declaration of public functions*/

private slots:
    void on_pushButtonSearch_clicked();
    void on_lineEditSearchKey_textChanged(const QString &arg1);

private:
    /*Private variables*/
    Ui::Dialog_Find *ui;
    DocumentViewer *viewer;
    /*End of declaration of private variables*/
};

#endif // DIALOG_FIND_H
