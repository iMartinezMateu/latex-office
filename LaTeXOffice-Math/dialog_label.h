#ifndef DIALOG_LABEL_H
#define DIALOG_LABEL_H

#include <QDialog>
#include "lib/latex/commands.h"

namespace Ui {
class Dialog_Label;
}

class Dialog_Label : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Label(QWidget *parent = 0);
    ~Dialog_Label();
    QString getLabel();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog_Label *ui;
    QString label;
};

#endif // DIALOG_LABEL_H
