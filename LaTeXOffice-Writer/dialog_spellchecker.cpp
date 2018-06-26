#include "dialog_spellchecker.h"
#include "ui_dialog_spellchecker.h"

Dialog_SpellChecker::Dialog_SpellChecker(QStringList fileContent,
                                         SpellChecker *spellChecker, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_SpellChecker)
{
    ui->setupUi(this);
    _spellChecker = spellChecker;
    ui->textEditDocument->clear();
    foreach (QString line, fileContent) {
        ui->textEditDocument->append(line);
    }
    connect(ui->listWidget, SIGNAL(currentTextChanged(QString)), ui->lineEditReplaceWith,
            SLOT(setText(QString)));
    connect(ui->pushButtonAddToDictionary, SIGNAL(clicked()), this, SLOT(addToDict()));
    connect(ui->pushButtonReplaceOnce, SIGNAL(clicked()), this, SLOT(replaceOnce()));
    connect(ui->pushButtonReplaceAll, SIGNAL(clicked()), this, SLOT(replaceAll()));
    connect(ui->pushButtonIgnoreOnce, SIGNAL(clicked()), this, SLOT(ignoreOnce()));
    connect(ui->pushButtonIgnoreAll, SIGNAL(clicked()), this, SLOT(ignoreAll()));
    connect(ui->buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

Dialog_SpellChecker::~Dialog_SpellChecker()
{
    delete ui;
}

QTextEdit *Dialog_SpellChecker::getDocumentZone()
{
    return ui->textEditDocument;
}

Dialog_SpellChecker::SpellCheckAction Dialog_SpellChecker::checkWord(QString word)
{
    _unknownWord = word;
    ui->labelUnknownWord->setText(QString("<b>%1</b>").arg(_unknownWord));

    ui->lineEditReplaceWith->clear();

    QStringList suggestions = _spellChecker->suggest(word);
    ui->listWidget->clear();
    ui->listWidget->addItems(suggestions);

    if (suggestions.count() > 0) {
        ui->listWidget->setCurrentRow(0, QItemSelectionModel::Select);
    }

    _returnCode = AbortCheck;
    if (!QDialog::isActiveWindow()) {
        QDialog::exec();
    }
    return _returnCode;
}


QString Dialog_SpellChecker::replacement()
{
    return ui->lineEditReplaceWith->text();
}


void Dialog_SpellChecker::ignoreOnce()
{
    _returnCode = IgnoreOnce;
    accept();
}


void Dialog_SpellChecker::ignoreAll()
{
    _spellChecker->ignoreWord(_unknownWord);
    _returnCode = IgnoreAll;
    accept();
}


void Dialog_SpellChecker::replaceOnce()
{
    _returnCode = ReplaceOnce;
    accept();
}


void Dialog_SpellChecker::replaceAll()
{
    _returnCode = ReplaceAll;
    accept();
}


void Dialog_SpellChecker::addToDict()
{
    _spellChecker->addToUserWordlist(_unknownWord);
    _returnCode = AddToDict;
    accept();
}
