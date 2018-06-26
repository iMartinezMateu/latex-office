#ifndef DIALOG_BIBLIOGRAPHY_H
#define DIALOG_BIBLIOGRAPHY_H

#include <QDialog>
#include "lib/latex/bibliography.h"
#include <QToolTip>
#include <QTableWidgetItem>
#include <QDebug>
#include "lib/latex/compiler.h"
#include <constants.h>
#include <QMessageBox>
namespace Ui {
class Dialog_Bibliography;
}
/**
 * The Dialog_Bibliography class represents the functionality and implementation of this dialog. It is used to communicate with the user, so the program can really know what the author wants in this dialog.
 *
 * @author Iván Martínez Mateu
 */
class Dialog_Bibliography : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_Bibliography(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_Bibliography();
    /*************************************************************************************************/
    /**
      @brief This function sets the necessary data so the dialog can work.
      @param bibFilePath bibliography definitions file path.
      @returns This is a void function.
      */
    void setData(QString bibFilePath);
    /*End of declaration of public functions*/

private slots:
    void on_pushButtonArticleReset_clicked();
    void on_pushButtonBookReset_clicked();
    void on_pushButtonBookletReset_clicked();
    void on_pushButtonInbookReset_clicked();
    void on_pushButtonIncollectionReset_clicked();
    void on_pushButtonInproceedingsReset_clicked();
    void on_pushButtonManualsReset_clicked();
    void on_pushButtonThesisReset_clicked();
    void on_pushButtonProceedingsReset_clicked();
    void on_pushButtonReportsReset_clicked();
    void on_lineEditArticleID_textChanged(const QString &arg1);
    void on_lineEditBookID_textChanged(const QString &arg1);
    void on_lineEditBookletID_textChanged(const QString &arg1);
    void on_lineEditInbookIdentificator_textChanged(const QString &arg1);
    void on_lineEditIncollectionIdentificator_textChanged(const QString &arg1);
    void on_lineEditInproceedingsID_textChanged(const QString &arg1);
    void on_lineEditManualsID_textChanged(const QString &arg1);
    void on_lineEditThesisID_textChanged(const QString &arg1);
    void on_lineEditProceedingsIdentificator_textChanged(const QString &arg1);
    void on_lineEditReportsID_textChanged(const QString &arg1);
    void on_pushButtonArticleAddEntry_clicked();
    void on_tableWidgetArticles_itemSelectionChanged();
    void on_pushButtonArticleDelete_clicked();
    void on_buttonBox_accepted();
    void on_pushButtonBookAddEntry_clicked();
    void on_pushButtonBookDelete_clicked();
    void on_tableWidgetBooks_itemSelectionChanged();
    void on_pushButtonBookletAddEntry_clicked();
    void on_pushButtonBookletDelete_clicked();
    void on_tableWidgetBooklets_itemSelectionChanged();
    void on_pushButtonInbookAddEntry_clicked();
    void on_tableWidgetInbooks_itemSelectionChanged();
    void on_pushButtonInbookDelete_clicked();
    void on_pushButtonIncollectionAddEntry_clicked();
    void on_tableWidgetIncollections_itemSelectionChanged();
    void on_pushButtonIncollectionDelete_clicked();
    void on_pushButtonInproceedingsAddEntry_clicked();
    void on_tableWidgetInproceedings_itemSelectionChanged();
    void on_pushButtonInproceedingsDelete_clicked();
    void on_pushButtonManualsAddEntry_clicked();
    void on_tableWidgetManuals_itemSelectionChanged();
    void on_pushButtonManualDelete_clicked();
    void on_pushButtonThesisAddEntry_clicked();
    void on_tableWidgetThesis_itemSelectionChanged();
    void on_pushButtonThesisDelete_clicked();
    void on_pushButtonProceedingsAddEntry_clicked();
    void on_tableWidgetProceedings_itemSelectionChanged();
    void on_pushButtonProceedingsDelete_clicked();
    void on_pushButtonReportsAddEntry_clicked();
    void on_tableWidgetReports_itemSelectionChanged();
    void on_pushButtonReportsDelete_clicked();
    void on_buttonBox_helpRequested();

private:
    /*Private variables*/
    Ui::Dialog_Bibliography *ui;
    TeXBibliography *file;
    QString bibFilePath;
    /*End of declaration of private variables*/
};

#endif // DIALOG_BIBLIOGRAPHY_H
