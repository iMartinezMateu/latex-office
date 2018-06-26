#ifndef DIALOG_GOAL_H
#define DIALOG_GOAL_H

#include <QDialog>
#include <QPushButton>
#include "documentviewer.h"

namespace Ui {
class Dialog_Goal;
}

class Dialog_Goal : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param viewer current document viewer widget reference.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_Goal(DocumentViewer *viewer, QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_Goal();
    /*End of declaration of public functions*/

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    /*Private variables*/
    Ui::Dialog_Goal *ui;
    DocumentViewer *viewer;
    /*End of declaration of private variables*/
};

#endif // DIALOG_GOAL_H
