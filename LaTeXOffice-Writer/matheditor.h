#ifndef MathEditor_H
#define MathEditor_H

#include <QMainWindow>
#include <QWebFrame>
#include <QWebView>
#include <dialog_symbol.h>
#include <dialog_label.h>
#include <QFileDialog>
#include <QMessageBox>
#include <lib/latex/file.h>
#include <lib/latex/commands.h>

#define DIALOG_NAME "LaTeX Office Math"
namespace Ui {
class MathEditor;
}

class MathEditor : public QMainWindow
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit MathEditor(QWidget *parent = 0);
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param file LaTeX file reference.
      @param selectedLineNumber file line where user clicked.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit MathEditor(TeXFile* file, int selectedLineNumber, QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~MathEditor();
    /*************************************************************************************************/
    /**
      @brief This function returns the equation.
      @returns This function returns the equation LaTeX code.
      */
    QString getEquation();
    /*End of declaration of public functions*/

private slots:
    void on_plainTextEdit_textChanged();
    void on_buttonBox_rejected();
    void on_actionLabel_triggered();
    void on_actionSymbol_triggered();
    void on_pushButtonAlg1_2_clicked();
    void on_pushButtonAlg2_2_clicked();
    void on_pushButtonAlg3_2_clicked();
    void on_pushButtonAlg4_2_clicked();
    void on_pushButtonAlg5_2_clicked();
    void on_pushButtonAlg6_2_clicked();
    void on_pushButtonExportPNG_clicked();
    void on_pushButtonExportJPG_clicked();
    void on_pushButtonExportLOM_clicked();
    void on_pushButtonImportLOM_clicked();
    void on_pushButtonDer1_2_clicked();
    void on_pushButtonDer2_2_clicked();
    void on_pushButtonDer3_2_clicked();
    void on_pushButtonDer4_2_clicked();
    void on_pushButtonDer5_2_clicked();
    void on_pushButtonDer6_2_clicked();
    void on_pushButtonSta1_2_clicked();
    void on_pushButtonSta2_2_clicked();
    void on_pushButtonSta3_2_clicked();
    void on_pushButtonSta4_2_clicked();
    void on_pushButtonSta5_2_clicked();
    void on_pushButtonSta6_2_clicked();
    void on_pushButtonSta7_2_clicked();
    void on_pushButtonMat1_2_clicked();
    void on_pushButtonMat2_2_clicked();
    void on_pushButtonMat3_2_clicked();
    void on_pushButtonMat4_2_clicked();
    void on_pushButtonMat5_3_clicked();
    void on_pushButtonMat6_3_clicked();
    void on_pushButtonSet1_2_clicked();
    void on_pushButtonSet2_2_clicked();
    void on_pushButtonTri1_2_clicked();
    void on_pushButtonTri2_2_clicked();
    void on_pushButtonTri3_2_clicked();
    void on_pushButtonTri4_2_clicked();
    void on_pushButtonTri4_3_clicked();
    void on_pushButtonTri4_4_clicked();
    void on_pushButtonGeo1_2_clicked();
    void on_pushButtonGeo2_2_clicked();
    void on_pushButtonGeo3_2_clicked();
    void on_pushButtonGeo4_2_clicked();
    void on_pushButtonPhy1_2_clicked();
    void on_pushButtonPhy2_2_clicked();
    void on_pushButtonPhy3_2_clicked();
    void on_pushButtonPhy4_2_clicked();
    void on_pushButtonAlg7_2_clicked();
    void on_actionAngle_triggered();
    void on_actionExp_triggered();
    void on_actionFraction_triggered();
    void on_actionIntegral_triggered();
    void on_actionIntegral_Symbol_triggered();
    void on_actionSquare_Root_triggered();
    void on_actionN_Square_Root_triggered();
    void on_actionSubelement_triggered();
    void on_actionSumatory_triggered();
    void on_buttonBox_accepted();

private:
    /*Private variables*/
    Ui::MathEditor *ui;
    QString equation;
    TeXFile * file;
    TeXCommands * command;
    int selectedLineNumber;
    /*End of declaration of private variables*/
};

#endif // MathEditor_H
