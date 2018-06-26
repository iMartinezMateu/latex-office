#ifndef DIALOG_SYMBOL_H
#define DIALOG_SYMBOL_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QPushButton>

namespace Ui {
class Dialog_Symbol;
}

class Dialog_Symbol : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Dialog_Symbol(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Dialog_Symbol();
    /*************************************************************************************************/
    /**
      @brief This function gets the selected symbol reference.
      @returns The function returns the LaTeX command of the symbol selected.
      */
    QString getSelectedSymbol();
    /*************************************************************************************************/
    /**
      @brief This function sets a symbol to be selected in the list.
      @param symbol symbol to be selected.
      @returns This is a void function.
      */
    void setSelectedSymbol(QString symbol);
    /*End of definition of public functions*/

private slots:
    void on_lineEditFilter_textChanged(const QString &arg1);
    void on_buttonBox_accepted();
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void on_comboBoxType_currentIndexChanged(int index);


private:
    /*Private variables*/
    Ui::Dialog_Symbol *ui;
    QTableWidgetItem *selectedItem;
    QString selectedSymbol;
    /*End of definition of private variables*/
};

#endif // DIALOG_SYMBOL_H
