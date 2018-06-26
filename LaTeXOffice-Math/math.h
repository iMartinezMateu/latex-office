#ifndef MATH_H
#define MATH_H

#include <QMainWindow>
#include <QFileDialog>
#include <QWebFrame>
#include <QMessageBox>
#include "dialog_label.h"
#include "dialog_symbol.h"
#include <QDesktopServices>
#define APP_NAME "LaTeX Office Math"

namespace Ui {
class Math;
}

class Math : public QMainWindow
{
    Q_OBJECT

public:
    explicit Math(QWidget *parent = 0);
    ~Math();
private slots:
    void on_plainTextEdit_textChanged();
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
    void on_pushButtonClose_clicked();

    void on_actionLaTeX_Office_Math_Help_triggered();

private:
    Ui::Math *ui;
};

#endif // MATH_H
