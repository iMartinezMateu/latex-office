#ifndef DIALOG_SMARTKEYS_H
#define DIALOG_SMARTKEYS_H

#include <QDialog>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QMessageBox>
#include "constants.h"
#include <QDir>
namespace Ui {
class Dialog_SmartKeys;
}

class Dialog_SmartKeys : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_SmartKeys(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_SmartKeys();
    /*End of declaration of public functions*/

private slots:
    void on_pushButtonInsert_clicked();
    void on_pushButtonDelete_clicked();
    void on_buttonBox_accepted();
    void on_tableWidget_itemChanged(QTableWidgetItem *item);
    void on_buttonBox_helpRequested();

private:
    /*Private variables*/
    Ui::Dialog_SmartKeys *ui;
    int rowCount;
    /*End of declaration of private variables*/
};

#endif // DIALOG_SMARTKEYS_H
