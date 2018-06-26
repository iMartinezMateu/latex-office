#include "caja.h"
#include "ui_caja.h"
#include <QDebug>


Caja::Caja(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Caja)
{
    ui->setupUi(this);
    ui->retranslateUi(this);

    connect(ui->comboBoxSize, SIGNAL(currentIndexChanged(int)), this, SLOT(changeSize()));
}

void Caja::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslate();
    } else
        QWidget::changeEvent(event);
}

void Caja::retranslate()
{
    ui->tabWidget->setTabText(0,tr("Edit Mode"));
    ui->tabWidget->setTabText(1,tr("Review Mode"));
    ui->comboBoxSize->setItemText(0,tr("Tiny"));
    ui->comboBoxSize->setItemText(1,tr("Small"));
    ui->comboBoxSize->setItemText(2,tr("Normal"));
    ui->comboBoxSize->setItemText(3,tr("Large"));
    ui->comboBoxSize->setItemText(4,tr("Huge"));
    ui->labelStrikethroughRatio->setText(tr("<html><head/><body><p><span style=\" font-weight:600;\">Strikethrough</span></p></body></html>"));
    ui->labelSmallCapsRatio->setText(tr("<html><head/><body><p><span style=\" font-weight:600;\">Small Caps</span></p></body></html>"));
    ui->labelUnderlineRatio->setText(tr("<html><head/><body><p><span style=\" font-weight:600;\">Underline</span></p></body></html>"));
    ui->labelItalicsRatio->setText(tr("<html><head/><body><p><span style=\" font-weight:600;\">Italics</span></p></body></html>"));
    ui->labelBoldRatio->setText(tr("<html><head/><body><p><span style=\" font-weight:600;\">Bold</span></p></body></html>"));
}

void Caja::setTextTiny()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt;
    cursor.select(QTextCursor::Document);
    //if (!cursor.hasSelection())
    //    cursor.select(QTextCursor::WordUnderCursor);

    fmt.setFontPointSize(7.33);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void Caja::setTextSmall()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt;
    cursor.select(QTextCursor::Document);
    //if (!cursor.hasSelection())
    //    cursor.select(QTextCursor::WordUnderCursor);

    fmt.setFontPointSize(10);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void Caja::setTextNormal()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt;
    cursor.select(QTextCursor::Document);
    //if (!cursor.hasSelection())
    //    cursor.select(QTextCursor::WordUnderCursor);

    fmt.setFontPointSize(12.5);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void Caja::setTextLarge()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt;
    cursor.select(QTextCursor::Document);
    //if (!cursor.hasSelection())
    //    cursor.select(QTextCursor::WordUnderCursor);

    fmt.setFontPointSize(15);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void Caja::setTextHuge()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt;
    cursor.select(QTextCursor::Document);
    //if (!cursor.hasSelection())
    //    cursor.select(QTextCursor::WordUnderCursor);

    fmt.setFontPointSize(24);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void Caja::changeSize()
{
    switch (ui->comboBoxSize->currentIndex()) {
    case 0: //tiny
        setTextTiny();
        break;
    case 1: //small
        setTextSmall();
        break;
    case 2: //normal
        setTextNormal();
        break;
    case 3: //large
        setTextLarge();
        break;
    case 4: //huge
        setTextHuge();
        break;

    }
}

Caja::~Caja()
{
    delete ui;
}


QTextEdit *Caja::getTextEdit()
{
    return ui->textEdit;
}

void Caja::on_toolButtonBold_clicked()
{
    emit boldStyleChanged();
}

void Caja::on_toolButtonItalic_clicked()
{
    emit italicStyleChanged();
}

void Caja::on_toolButtonUnderline_clicked()
{
    emit underlineStyleChanged();
}

void Caja::on_toolButtonStrikethrough_clicked()
{
    emit strikethroughStyleChanged();
}

void Caja::on_toolButtonSmallCaps_clicked()
{
    emit smallCapsStyleChanged();
}

void Caja::on_toolButtonEmphatize_clicked()
{
    emit emphatizeStyleChanged();
}

void Caja::on_toolButtonHyperlink_clicked()
{
    emit hyperlinkStyleChanged();
}

void Caja::on_toolButton_Footnote_clicked()
{
    emit footnoteStyleChanged();
}

void Caja::on_toolButtonLeftAlign_clicked()
{
    emit leftAlignStyleChanged();
}

void Caja::on_toolButtonCenterAlign_clicked()
{
    emit centerAlignStyleChanged();
}

void Caja::on_toolButtonRightAlign_clicked()
{
    emit rightAlignStyleChanged();
}

void Caja::on_toolButtonJustify_clicked()
{
    emit justifyStyleChanged();
}

void Caja::on_toolButtonItemize_clicked()
{
    emit bulletListAdded();
}

void Caja::on_toolButtonEnumerate_clicked()
{
    emit numberedListAdded();
}

void Caja::on_toolButtonSymbol_clicked()
{
    emit symbolInserted();
}

void Caja::on_toolButtonCite_clicked()
{
    emit citeInserted();
}

void Caja::on_textEdit_textChanged()
{
    QVector<double> ratios;
    ratios.clear();
    int totalParagraphWordCount = ui->textEdit->toPlainText().split(QRegExp("(\\s|\\n|\\r)+")
                                                                    , QString::SkipEmptyParts).count();
    int boldParagraphWordCount = 0;
    int italicParagraphWordCount = 0;
    int underlineParagraphWordCount = 0;
    int smallCapsParagraphWordCount = 0;
    int strikethroughParagraphWordCount = 0;
    double boldRatio = 0;
    double italicRatio = 0;
    double underlineRatio = 0;
    double smallCapsRatio = 0;
    double strikethroughRatio = 0;
    QRegularExpression
    boldRegularExpression("<span style=\" font-weight:600;\">(.*?)<\\/span>");
    QRegularExpressionMatch match = boldRegularExpression.match(ui->textEdit->toHtml());
    boldParagraphWordCount = match.captured(1).split(QRegExp("(\\s|\\n|\\r)+") ,
                                                     QString::SkipEmptyParts).count();

    QRegularExpression
    italicRegularExpression("<span style=\" font-style:italic;\">(.*?)<\\/span>");
    match = italicRegularExpression.match(ui->textEdit->toHtml());
    italicParagraphWordCount = match.captured(1).split(QRegExp("(\\s|\\n|\\r)+") ,
                                                       QString::SkipEmptyParts).count();

    QRegularExpression
    underlineRegularExpression("<span style=\" text-decoration:underline\">(.*?)<\\/span>");
    match = underlineRegularExpression.match(ui->textEdit->toHtml());
    underlineParagraphWordCount = match.captured(1).split(QRegExp("(\\s|\\n|\\r)+") ,
                                                          QString::SkipEmptyParts).count();

    QRegularExpression
    smallCapsRegularExpression("<span style=\" font-variant:small-caps;\">(.*?)<\\/span>");
    match = smallCapsRegularExpression.match(ui->textEdit->toHtml());
    smallCapsParagraphWordCount = match.captured(1).split(QRegExp("(\\s|\\n|\\r)+") ,
                                                          QString::SkipEmptyParts).count();

    QRegularExpression
    strikethroughRegularExpression("<span style=\" text-decoration: line-through;\">(.*?)<\\/span>");
    match = strikethroughRegularExpression.match(ui->textEdit->toHtml());
    strikethroughParagraphWordCount = match.captured(1).split(QRegExp("(\\s|\\n|\\r)+") ,
                                                              QString::SkipEmptyParts).count();

    boldRatio = ((double)boldParagraphWordCount / (double)totalParagraphWordCount) * 100;
    italicRatio = ((double)italicParagraphWordCount / (double)totalParagraphWordCount) * 100;
    underlineRatio = ((double)underlineParagraphWordCount / (double)totalParagraphWordCount) *
                     100;
    smallCapsRatio = ((double)smallCapsParagraphWordCount / (double)totalParagraphWordCount) *
                     100;
    strikethroughRatio = ((double)strikethroughParagraphWordCount /
                          (double)totalParagraphWordCount) * 100;
    ratios.append(boldRatio);
    ratios.append(italicRatio);
    ratios.append(underlineRatio);
    ratios.append(smallCapsRatio);
    ratios.append(strikethroughRatio);
    qSort(ratios); //Ordena todos los ratios del vector, apareciendo el menor ratio en la primera posición del vector y el mayor ratio en la última posición.

    if (ratios.at(4) == boldRatio) {
        if (ratios.at(4) - ratios.at(3) > 45) {
            ui->labelWarning->setText(
                tr("The bold ratio is too high!. Please, consider reducing the amount of bold words..."));
            ui->labelBoldRatio->setStyleSheet("QLabel { color: red; }");
            ui->labelBoldRatioValue->setStyleSheet("QLabel { color:red; }");
        } else {
            ui->labelWarning->clear();
            ui->labelBoldRatio->setStyleSheet("QLabel { color: black; }");
            ui->labelBoldRatioValue->setStyleSheet("QLabel { color:black; }");
        }
    } else if (ratios.at(4) == italicRatio) {
        if (ratios.at(4) - ratios.at(3) > 45) {
            ui->labelWarning->setText(
                tr("The italic ratio is too high!. Please, consider reducing the amount of italic words..."));
            ui->labelItalicsRatio->setStyleSheet("QLabel { color: red; }");
            ui->labelItalicsRatioValue->setStyleSheet("QLabel { color:red; }");
        } else {
            ui->labelWarning->clear();
            ui->labelItalicsRatio->setStyleSheet("QLabel { color: black; }");
            ui->labelItalicsRatioValue->setStyleSheet("QLabel { color:black; }");
        }
    } else if (ratios.at(4) == underlineRatio) {
        if (ratios.at(4) - ratios.at(3) > 45) {
            ui->labelWarning->setText(
                tr("The underline ratio is too high!. Please, consider reducing the amount of underlined words..."));
            ui->labelUnderlineRatio->setStyleSheet("QLabel { color: red; }");
            ui->labelUnderlineRatioValue->setStyleSheet("QLabel { color:red; }");
        } else {
            ui->labelWarning->clear();
            ui->labelUnderlineRatio->setStyleSheet("QLabel { color: black; }");
            ui->labelUnderlineRatioValue->setStyleSheet("QLabel { color:black; }");
        }
    } else if (ratios.at(4) == smallCapsRatio) {
        if (ratios.at(4) - ratios.at(3) > 45) {
            ui->labelWarning->setText(
                tr("The small caps ratio is too high!. Please, consider reducing the amount of small caps words..."));
            ui->labelSmallCapsRatio->setStyleSheet("QLabel { color: red; }");
            ui->labelSmallCapsRatioValue->setStyleSheet("QLabel { color:red; }");
        } else {
            ui->labelWarning->clear();
            ui->labelSmallCapsRatio->setStyleSheet("QLabel { color: black; }");
            ui->labelSmallCapsRatioValue->setStyleSheet("QLabel { color:black; }");
        }
    } else if (ratios.at(4) == strikethroughRatio) {
        if (ratios.at(4) - ratios.at(3) > 45) {
            ui->labelWarning->setText(
                tr("The strikethrough ratio is too high!. Please, consider reducing the amount of strikethrough words..."));
            ui->labelStrikethroughRatio->setStyleSheet("QLabel { color: red; }");
            ui->labelStrikethroughRatioValue->setStyleSheet("QLabel { color:red; }");
        } else {
            ui->labelWarning->clear();
            ui->labelStrikethroughRatio->setStyleSheet("QLabel { color: black; }");
            ui->labelStrikethroughRatioValue->setStyleSheet("QLabel { color:black; }");
        }
    }
    ui->labelBoldRatioValue->setText(QString::number(boldRatio, 'f', 2) + " %");
    ui->labelItalicsRatioValue->setText(QString::number(italicRatio, 'f', 2) + " %");
    ui->labelUnderlineRatioValue->setText(QString::number(underlineRatio, 'f', 2) + " %");
    ui->labelSmallCapsRatioValue->setText(QString::number(smallCapsRatio, 'f', 2) + " %");
    ui->labelStrikethroughRatioValue->setText(QString::number(strikethroughRatio, 'f',
                                                              2) + " %");
    ratios.clear();
    emit cajaTextChanged();
}

void Caja::on_toolButtonReference_clicked()
{
       emit referenceInserted();
}
