#ifndef DIALOG_REPLACE_H
#define DIALOG_REPLACE_H

#include <QDialog>
#include "documentviewer.h"
#include "lib/latex/compiler.h"

namespace Ui {
class Dialog_Replace;
}

class Dialog_Replace : public QDialog
{
    Q_OBJECT

public:
    /*Public functions*/
    explicit Dialog_Replace(QWidget *parent = 0);
    ~Dialog_Replace();
    void setData(DocumentViewer *viewer, TeXFile * file);
    QVector<int> findStrings(QString oldString, bool caseSensitive);
    /*End of declaration of public functions*/
private slots:
    void on_buttonBox_accepted();

    void on_lineEditSearchKey_textChanged(const QString &arg1);

    void on_lineEditReplace_textChanged(const QString &arg1);

private:
    /*Private variables*/
        Ui::Dialog_Replace *ui;
        DocumentViewer *viewer;
        TeXFile *file;
    /*End of declaration of private variables*/
};

#endif // DIALOG_REPLACE_H
