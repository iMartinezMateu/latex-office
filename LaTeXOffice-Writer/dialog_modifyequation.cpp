#include "dialog_modifyequation.h"
#include "ui_dialog_modifyequation.h"

Dialog_ModifyEquation::Dialog_ModifyEquation(TeXFile* file, int selectedLineNumber, QString compilerPath, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dialog_ModifyEquation)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    ui->buttonBox->button(QDialogButtonBox::Discard)->setText(tr("Delete"));
    this->file = file;
    this->selectedLineNumber = selectedLineNumber;
    this->compilerPath = compilerPath;
    setEquationCode();
}

Dialog_ModifyEquation::~Dialog_ModifyEquation()
{
    delete ui;
}

void Dialog_ModifyEquation::setEquationCode()
{
    QStringList fileContent = file->getFileContent();
    QStringList equationCode;

    for (int iterationLineNumber=selectedLineNumber-1; iterationLineNumber>0; iterationLineNumber--)
    {
        QString line = fileContent.at(iterationLineNumber);
        if (line.compare(command->callBegin(ENV_EQUATION)) != 0 && !line.contains(command->callLabel()))
        {
            equationCode.append(line);
        }
        else
        {
            break;
        }
    }
    for(int k = 0; k < (equationCode.size()/2); k++) equationCode.swap(k,equationCode.size()-(1+k)); //Reverse list

    foreach (QString item, equationCode)
    {
        ui->plainTextEdit->appendPlainText(item + "\n");
    }

}

void Dialog_ModifyEquation::on_plainTextEdit_textChanged()
{
    QString htmlContent;
    htmlContent.clear();
    if (!ui->plainTextEdit->toPlainText().isEmpty())
    {
        htmlContent.append("<!DOCTYPE html>");
        htmlContent.append("<html>");
        htmlContent.append("<head>");
        htmlContent.append(" <title>Math preview</title>");
        htmlContent.append("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />");
        htmlContent.append(" <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\" />");
        htmlContent.append( "<script type=\"text/x-mathjax-config\">");
        htmlContent.append("MathJax.Hub.Config({");
        htmlContent.append("tex2jax: {inlineMath: [[\"$\",\"$\"],[\"\\(\",\"\\)\"]]}");
        htmlContent.append("  });");
        htmlContent.append(" </script>");
        htmlContent.append(" <script type=\"text/javascript\" src=\"qrc:/scripts/MathJax.js?config=TeX-AMS-MML_HTMLorMML  \"></script>");
        htmlContent.append(" </head>");
        htmlContent.append("<body>");
        htmlContent.append("<p>");
        htmlContent.append("$" + ui->plainTextEdit->toPlainText() +"$");
        htmlContent.append("</p>");
        htmlContent.append("</body>");
        htmlContent.append("</html>");
    }
    ui->previewView->setHtml(htmlContent);


}

void Dialog_ModifyEquation::on_buttonBox_rejected()
{
    this->close();
}

void Dialog_ModifyEquation::on_actionLabel_triggered()
{
    Dialog_Label *dialog = new Dialog_Label();
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    if (!dialog->getLabel().isEmpty())
        ui->plainTextEdit->textCursor().insertText(dialog->getLabel());
}

void Dialog_ModifyEquation::on_actionSymbol_triggered()
{
    Dialog_Symbol *dialog = new Dialog_Symbol();
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    if (!dialog->getSelectedSymbol().isEmpty())
        ui->plainTextEdit->textCursor().insertText(dialog->getSelectedSymbol());
}

void Dialog_ModifyEquation::on_pushButtonAlg1_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\sqrt{a^2+b^2}");

}

void Dialog_ModifyEquation::on_pushButtonAlg2_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\lim_{x\\to \\infty}");

}

void Dialog_ModifyEquation::on_pushButtonAlg3_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\sqrt{b^2-4*a*c}");
}

void Dialog_ModifyEquation::on_pushButtonAlg4_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\frac{-b\\pm\\sqrt{b^2-4*a*c}}{2*a}");
}

void Dialog_ModifyEquation::on_pushButtonAlg5_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\frac{n!}{r!(n-r)!}");
}

void Dialog_ModifyEquation::on_pushButtonAlg6_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\frac{1}{2}");
}

void Dialog_ModifyEquation::on_pushButtonExportPNG_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("LaTeX Office Writer"), NULL,
                                                    tr("PNG File (*.png)"));
    if (fileName != NULL) {
        ui->previewView->page()->setViewportSize(ui->previewView->page()->mainFrame()->contentsSize());
        QImage *image = new QImage(ui->previewView->page()->mainFrame()->contentsSize(), QImage::Format_ARGB32);
        QPainter *painter = new QPainter(image);

        ui->previewView->page()->mainFrame()->render(painter);

        painter->end();
        image->save(fileName);
        ui->previewView->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
        ui->previewView->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    }

}

void Dialog_ModifyEquation::on_pushButtonExportJPG_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("LaTeX Office Writer"), NULL,
                                                    tr("JPG File (*.jpg)"));
    if (fileName != NULL) {
        ui->previewView->page()->setViewportSize(ui->previewView->page()->mainFrame()->contentsSize());
        QImage *image = new QImage(ui->previewView->page()->mainFrame()->contentsSize(), QImage::Format_ARGB32);
        QPainter *painter = new QPainter(image);

        ui->previewView->page()->mainFrame()->render(painter);

        painter->end();
        image->save(fileName);
        ui->previewView->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
        ui->previewView->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    }

}

void Dialog_ModifyEquation::on_pushButtonExportLOM_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    APP_NAME, NULL,
                                                    tr("LaTeX Office Math File (*.lom)"));
    if (fileName != NULL) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            stream << ui->plainTextEdit->toPlainText() << endl;
            file.close();
        }
    }
}

void Dialog_ModifyEquation::on_pushButtonImportLOM_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(APP_NAME);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText(tr("This will erase the current equation. Do you want to continue?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if (msgBox.exec() == QMessageBox::Yes) {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    APP_NAME, NULL,
                                                    tr("LaTeX Office Math File (*.lom)"));
    if (fileName != NULL) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream in(&file);

            while(!in.atEnd()) {
                QString line = in.readLine();
                ui->plainTextEdit->clear();
                ui->plainTextEdit->appendPlainText(line);
            }
            file.close();
        }
    }
   }
}

void Dialog_ModifyEquation::on_pushButtonDer1_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\frac{dy}{dx}");

}

void Dialog_ModifyEquation::on_pushButtonDer2_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\frac{\\partial y}{\\partial x}");
}

void Dialog_ModifyEquation::on_pushButtonDer3_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\frac{d^2y}{dx^2}");

}

void Dialog_ModifyEquation::on_pushButtonDer4_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\frac{d^2}{dx^2}");
}

void Dialog_ModifyEquation::on_pushButtonDer5_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\frac{d^2}{dxdy}");

}

void Dialog_ModifyEquation::on_pushButtonDer6_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\frac{\\bigtriangleup y}{\\bigtriangleup x}");
}

void Dialog_ModifyEquation::on_pushButtonSta1_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\sum\\limits_{i=1}^n x_i");

}

void Dialog_ModifyEquation::on_pushButtonSta2_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\sum\\limits_{i=1}^n x^2_i");
}

void Dialog_ModifyEquation::on_pushButtonSta3_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\sum\\limits_{i=1}^n x_i y_i");
}

void Dialog_ModifyEquation::on_pushButtonSta4_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\frac{1}{n}");

}

void Dialog_ModifyEquation::on_pushButtonSta5_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\sum\\limits_{i=1}^n (x_i-\\overline{x})^2");
}

void Dialog_ModifyEquation::on_pushButtonSta6_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("x_1, \\ldots , x_n");

}

void Dialog_ModifyEquation::on_pushButtonSta7_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\frac{\\chi - \\mu}{\\sigma}");
}

void Dialog_ModifyEquation::on_pushButtonMat1_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\begin{pmatrix} \n a_{11} & a_{12}  \\\\ \n a_{21} & a_{22} \\\\ \n \\end{pmatrix}");
}

void Dialog_ModifyEquation::on_pushButtonMat2_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\begin{pmatrix} \n a_{11} & a_{12} & a_{13}  \\\\ \n a_{21} & a_{22} & a_{23} \\\\ \n a_{31} & a_{32} & a_{33} \\\\ \n \\end{pmatrix}");
}

void Dialog_ModifyEquation::on_pushButtonMat3_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\begin{pmatrix} \n a_{11} & \\ldots & a_{1n}  \\\\ \\vdots & \\ddots & \\vdots \\\\ \n a_{m1} & \\ldots & a_{mn} \\\\ \n \\end{pmatrix}");
}

void Dialog_ModifyEquation::on_pushButtonMat4_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\begin{pmatrix} \n 1 & 0  \\\\ \n 0 & 1 \\\\ \n \\end{pmatrix}");

}

void Dialog_ModifyEquation::on_pushButtonMat5_3_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\begin{pmatrix} \n 4 & 7  \\\\ \n 2 & 5 \\\\ \n \\end{pmatrix} * \\begin{pmatrix} \n x_1  \\\\ \n x_2  \\\\ \n \\end{pmatrix} = \\begin{pmatrix} \n 1  \\\\ \n 4  \\\\ \n \\end{pmatrix}");
}

void Dialog_ModifyEquation::on_pushButtonMat6_3_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\begin{bmatrix} \n a_{1} & a_{2} & a_{3}  \\\\ \n b_{1} & b_{2} & b_{3} \\\\ \n c_{1} & c_{2} & c_{3} \\\\ \n \\end{bmatrix}");

}

void Dialog_ModifyEquation::on_pushButtonSet1_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\bigcup \\limits_{i=1}^n x_i");
}

void Dialog_ModifyEquation::on_pushButtonSet2_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\bigcap \\limits_{i=1}^n x_i");
}

void Dialog_ModifyEquation::on_pushButtonTri1_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\cos^{-1} \\theta ");
}

void Dialog_ModifyEquation::on_pushButtonTri2_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\sin^{-1} \\theta ");
}

void Dialog_ModifyEquation::on_pushButtonTri3_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" e^{i\\theta} ");
}

void Dialog_ModifyEquation::on_pushButtonTri4_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\frac{\\pi}{2}-\\theta");
}

void Dialog_ModifyEquation::on_pushButtonTri4_3_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\widehat{BAM} = \\tan \\dfrac{BM}{AB}");

}

void Dialog_ModifyEquation::on_pushButtonTri4_4_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\theta = \\arctan (\\frac{a_y}{a_x})");
}

void Dialog_ModifyEquation::on_pushButtonGeo1_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\vec{\\mathbf{AB}}");
}

void Dialog_ModifyEquation::on_pushButtonGeo2_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\overleftrightarrow{\\mathbf{AB}}");
}

void Dialog_ModifyEquation::on_pushButtonGeo3_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\widehat{\\mathbf{AB}}");

}

void Dialog_ModifyEquation::on_pushButtonGeo4_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\bigtriangleup ABC");
}

void Dialog_ModifyEquation::on_pushButtonPhy1_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" \\overrightarrow{F} = m* \\overrightarrow{a}");

}

void Dialog_ModifyEquation::on_pushButtonPhy2_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\oint \\overrightarrow{F} * d \\overrightarrow{s} = 0");

}

void Dialog_ModifyEquation::on_pushButtonPhy3_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\psi (t) = \\hat{\\psi} *e^{i(\\omega t \\pm \\theta)}");
}

void Dialog_ModifyEquation::on_pushButtonPhy4_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText("\\sum \\limits_{i} \\hat{\\psi}_i \\cos(\\alpha_i \\pm \\omega t)");
}

void Dialog_ModifyEquation::on_pushButtonAlg7_2_clicked()
{
    ui->plainTextEdit->textCursor().insertText(" f(n) = \\begin{cases} n/2 & \\quad \\text{if } n \\text{ is even}\\\\ -(n+1)/2 & \\quad \\text{if } n \\text{ is odd}\\\\ \\end{cases} ");
}

void Dialog_ModifyEquation::on_actionAngle_triggered()
{
    ui->plainTextEdit->textCursor().insertText("\\hat{ab}");
}

void Dialog_ModifyEquation::on_actionExp_triggered()
{
    ui->plainTextEdit->textCursor().insertText("a^{b+c}");
}

void Dialog_ModifyEquation::on_actionFraction_triggered()
{
    ui->plainTextEdit->textCursor().insertText("\\frac{a+1}{b-1}");
}

void Dialog_ModifyEquation::on_actionIntegral_triggered()
{
    ui->plainTextEdit->textCursor().insertText("\\int_{a}^{b} x^2 dx");
}

void Dialog_ModifyEquation::on_actionIntegral_Symbol_triggered()
{
    ui->plainTextEdit->textCursor().insertText("\\int x^2 dx");
}

void Dialog_ModifyEquation::on_actionSquare_Root_triggered()
{
    ui->plainTextEdit->textCursor().insertText("\\sqrt{a}");
}

void Dialog_ModifyEquation::on_actionN_Square_Root_triggered()
{
    ui->plainTextEdit->textCursor().insertText("\\sqrt[b]{a}");
}

void Dialog_ModifyEquation::on_actionSubelement_triggered()
{
    ui->plainTextEdit->textCursor().insertText("a_{b+c}");
}

void Dialog_ModifyEquation::on_actionSumatory_triggered()
{
    ui->plainTextEdit->textCursor().insertText("\\sum_{n=-\\infty}^{+\\infty} f(x)");

}

QString Dialog_ModifyEquation::getEquation()
{
    return equation;
}

void Dialog_ModifyEquation::on_buttonBox_accepted()
{
    equation = ui->plainTextEdit->toPlainText().remove(QRegExp("[\\n\\t\\r]"));
    if (file != NULL)
    {

        for (int iterationLineNumber=selectedLineNumber-1; iterationLineNumber>0; iterationLineNumber--)
        {
            QString line = file->getFileContent().at(iterationLineNumber);
            if (line.compare(command->callBegin(ENV_EQUATION)) == 0)
            {
                for (int secondIterationLineNumber= iterationLineNumber; secondIterationLineNumber<file->getFileContent().length(); secondIterationLineNumber++)
                {
                    QString secondIterationLine = file->getFileContent().at(secondIterationLineNumber);
                    if ( secondIterationLine.compare(command->callEnd(ENV_EQUATION))!=0)
                    {
                        file->deleteTeXCommand(secondIterationLineNumber);
                        secondIterationLineNumber--;
                    }
                    else if (secondIterationLine.compare(command->callEnd(ENV_EQUATION))==0)
                    {
                        file->deleteTeXCommand(secondIterationLineNumber);
                        break;
                    }
                }
                file->saveFile();
                file->setTeXCommand(command->callBegin(ENV_EQUATION),iterationLineNumber);

                if (!ui->lineEditLabel->text().isEmpty())
                {
                    file->setTeXCommand(command->callLabel("eq:"+ui->lineEditLabel->text()),iterationLineNumber+1);
                    file->setTeXCommand(getEquation(),iterationLineNumber+2);
                    file->setTeXCommand(command->callEnd(ENV_EQUATION),iterationLineNumber+3);
                }
                else
                {
                    file->setTeXCommand(getEquation(),iterationLineNumber+1);
                    file->setTeXCommand(command->callEnd(ENV_EQUATION),iterationLineNumber+2);
                }
                file->saveFile();
                file->compile(compilerPath);
                file->compile(compilerPath);
                close();
               break;
            }

        }

    }
}


void Dialog_ModifyEquation::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Discard) {
        for (int iterationLineNumber=selectedLineNumber-1; iterationLineNumber>0; iterationLineNumber--)
        {
            QString line = file->getFileContent().at(iterationLineNumber);
            if (line.compare(command->callBegin(ENV_EQUATION)) == 0)
            {
                        for (int secondIterationLineNumber= iterationLineNumber; secondIterationLineNumber<file->getFileContent().length(); secondIterationLineNumber++)
                        {
                            QString secondIterationLine = file->getFileContent().at(secondIterationLineNumber);
                            if ( secondIterationLine.compare(command->callEnd(ENV_EQUATION))!=0)
                            {
                                file->deleteTeXCommand(secondIterationLineNumber);
                                secondIterationLineNumber--;
                            }
                            else if (secondIterationLine.compare(command->callEnd(ENV_EQUATION))==0)
                            {
                                file->deleteTeXCommand(secondIterationLineNumber);
                                break;
                            }
                        }
                file->saveFile();
                file->compile(compilerPath);
                file->compile(compilerPath);
                close();
            }
     }
  }
}
