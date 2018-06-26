#ifndef DIALOG_TIMEMACHINE_H
#define DIALOG_TIMEMACHINE_H

#include <QDialog>
#include "lib/latex/file.h"
#include <QPushButton>
#include <QMessageBox>
#include "constants.h"


namespace Ui {
class Dialog_TimeMachine;
}

class Dialog_TimeMachine : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param file the current LaTeX file reference.
      @param datesList a list of all generated backups' dates.
      @param fileBackupsList a list of all generated backups' data.
      @param compilerPath the PDFLaTeX binary compiler path.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_TimeMachine(TeXFile *file, QList<QDateTime> datesList,
                                QList<QStringList> fileBackupsList, QString compilerPath, QString timeMachineFilePath, QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_TimeMachine();
    /*End of declaration of public functions*/

private slots:
    void on_calendarWidget_clicked(const QDate &date);
    void on_listWidget_itemSelectionChanged();
    void on_buttonBox_accepted();

private:
    /*Private variables*/
    Ui::Dialog_TimeMachine *ui;
    TeXFile *file;
    QList<QDateTime> datesList;
    QList<QStringList> backupsList;
    QString compilerPath;
    QString timeMachineFilePath;
    /*End of declaration of private variables*/
};

#endif // DIALOG_TIMEMACHINE_H
