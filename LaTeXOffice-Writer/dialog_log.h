#ifndef DIALOG_LOG_H
#define DIALOG_LOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QPushButton>

namespace Ui {
class Dialog_Log;
}

class Dialog_Log : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_Log(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_Log();
    /*************************************************************************************************/
    /**
      @brief This function sets the necessary data so the dialog can work.
      @param docLogFile reference to the document log file.
      @param texLogFile reference to the compiling process log file.
      @returns This is a void function.
      */
    void setData(QFile *docLogFile, QFile *texLogFile);
    /*End of declaration of public functions*/

private:
    /*Private variables*/
    Ui::Dialog_Log *ui;
    QFile *docLogFile;
    QFile *texLogFile;
    /*End of declaration of private variables*/
};

#endif // DIALOG_LOG_H
