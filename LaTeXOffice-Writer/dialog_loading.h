#ifndef DIALOG_LOADING_H
#define DIALOG_LOADING_H

#include <QDialog>
#include <QApplication>

namespace Ui {
class Dialog_Loading;
}

class Dialog_Loading : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_Loading(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_Loading();
    /*************************************************************************************************/
    /**
      @brief This function sets the necessary data so the dialog can work.
      @param value set the progress bar value. This value can be from 0 to 100.
      @returns This is a void function.
      */
    void setProgressBarValue(int value);
    /*End of declaration of public functions*/

private:
    /*Private variables*/
    Ui::Dialog_Loading *ui;
    /*End of private variables*/
};

#endif // DIALOG_LOADING_H
