#ifndef DIALOG_TIMEMACHINESETTINGS_H
#define DIALOG_TIMEMACHINESETTINGS_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QDir>

namespace Ui {
class Dialog_TimeMachineSettings;
}

class Dialog_TimeMachineSettings : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_TimeMachineSettings(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_TimeMachineSettings();
    /*End of declaration of public functions*/

private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_buttonBox_accepted();

private:
    /*Private variables*/
    Ui::Dialog_TimeMachineSettings *ui;
    /*End of declaration of private variables*/
};

#endif // DIALOG_TIMEMACHINESETTINGS_H
