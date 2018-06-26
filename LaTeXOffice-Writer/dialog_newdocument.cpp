#include "dialog_newdocument.h"
#include "ui_dialog_newdocument.h"
#include "writer.h"

Dialog_NewDocument::Dialog_NewDocument(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_NewDocument)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    checkOSLocale();
    setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    ui->buttonBox->button(QDialogButtonBox::Help)->setText(tr("Help"));
}
Dialog_NewDocument::~Dialog_NewDocument()
{
    delete ui;
}

QString Dialog_NewDocument::getDocumentPath()
{
    return ui->lineEditDocumentDirectory->text();
}

void Dialog_NewDocument::checkOSLocale()
{
    //Detecta el lenguaje instalado y usado en el sistema operativo para elegir
    //de forma automática el idioma del documento. Así, el usuario se evita tener
    //que elegir siempre su idioma cada vez que quiera crear un documento cualquiera.
    //ya que siempre estará elegido el utilizado por su sistema operativo.
    switch (QLocale::system().language()) {
    case 8: //arabic
        ui->comboBoxDocumentLanguage->setCurrentIndex(0);
        break;
    case 20: //bulgarian
        ui->comboBoxDocumentLanguage->setCurrentIndex(1);
        break;
    case 96: //russian
        ui->comboBoxDocumentLanguage->setCurrentIndex(2);
        break;
    case 129: //ukrainian
        ui->comboBoxDocumentLanguage->setCurrentIndex(3);
        break;
    case 25: //chinese
        ui->comboBoxDocumentLanguage->setCurrentIndex(4);
        break;
    case 28: //czech
        ui->comboBoxDocumentLanguage->setCurrentIndex(5);
        break;
    case 31: //english
        ui->comboBoxDocumentLanguage->setCurrentIndex(6);
        break;
    case 36: //finnish
        ui->comboBoxDocumentLanguage->setCurrentIndex(7);
        break;
    case 37: //french
        ui->comboBoxDocumentLanguage->setCurrentIndex(8);
        break;
    case 42: //german
        ui->comboBoxDocumentLanguage->setCurrentIndex(9);
        break;
    case 43: //greek
        ui->comboBoxDocumentLanguage->setCurrentIndex(10);
        break;
    case 51: //icelandic
        ui->comboBoxDocumentLanguage->setCurrentIndex(11);
        break;
    case 34: //faroese
        ui->comboBoxDocumentLanguage->setCurrentIndex(12);
        break;
    case 58: //italian
        ui->comboBoxDocumentLanguage->setCurrentIndex(13);
        break;
    case 66: //korean
        ui->comboBoxDocumentLanguage->setCurrentIndex(14);
        break;
    case 89: //persian
        ui->comboBoxDocumentLanguage->setCurrentIndex(15);
        break;
    case 90: //polish
        ui->comboBoxDocumentLanguage->setCurrentIndex(16);
        break;
    case 91: //portuguese
        ui->comboBoxDocumentLanguage->setCurrentIndex(17);
        break;
    case 108: //slovak
        ui->comboBoxDocumentLanguage->setCurrentIndex(18);
        break;
    case 111: //spanish
        ui->comboBoxDocumentLanguage->setCurrentIndex(19);
        break;
    case 121: //tibetan
        ui->comboBoxDocumentLanguage->setCurrentIndex(20);
        break;

    }
}
void Dialog_NewDocument::on_pushButtonBrowseDirectory_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("LaTeX Office Writer"), "",
                                                    tr("LaTeX File (*.tex)"));
    if (fileName != NULL) {
        if (!fileName.endsWith(".tex")) {
            fileName.append(".tex");
        }
        ui->lineEditDocumentDirectory->setText(fileName);
        if (ui->lineEditDocumentTitle->text().length() > 3     ) {
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        }

    }
}
void Dialog_NewDocument::on_buttonBox_accepted()
{
    int documentTypeIndex = ui->comboBoxDocumentType->currentIndex();
    int documentLanguageIndex = ui->comboBoxDocumentLanguage->currentIndex();
    int fontSizeIndex = ui->comboBoxFontSize->currentIndex();
    int paperLayoutIndex = ui->comboBoxPaperLayout->currentIndex();
    int paperSizeIndex = ui->comboBoxPaperSize->currentIndex();
    int documentTypesetIndex = ui->comboBoxDocumentTypeset->currentIndex();
    int documentLayoutIndex = ui->comboBoxDocumentLayout->currentIndex();
    int chapterLayoutIndex = ui->comboBoxChapterLayout->currentIndex();
    QString documentTitle = ui->lineEditDocumentTitle->text();
    QString documentAuthor = ui->lineEditDocumentAuthor->text();
    QString documentDate = ui->lineEditDocumentDate->text();
    QString documentDirectory = ui->lineEditDocumentDirectory->text();
    if (documentTitle.isEmpty()
        || documentDirectory.isEmpty() ) {
        QMessageBox::critical(this, APP_NAME,
                              tr("There are text fields that are not filled correctly. Please, fill them and try again. "));
    } else {
        createDocument(documentTypeIndex, documentLanguageIndex, fontSizeIndex, paperLayoutIndex,
                       paperSizeIndex,
                       documentTypesetIndex, chapterLayoutIndex, documentLayoutIndex, documentTitle,
                       documentAuthor, documentDate,
                       documentDirectory);
    }
}
void Dialog_NewDocument::on_lineEditDocumentDirectory_textChanged(const QString &arg1)
{
    if (arg1.length() < 3 || ui->lineEditDocumentTitle->text().isEmpty()
        || ui->lineEditDocumentDate->text().isEmpty()
        || ui->lineEditDocumentAuthor->text().isEmpty()) {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    } else {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}
void Dialog_NewDocument::on_lineEditDocumentTitle_textEdited(const QString &arg1)
{
    if (arg1.length() < 3) {
        QToolTip::showText(ui->lineEditDocumentTitle->mapToGlobal(QPoint()),
                           tr("The title can't be too short.\nYou will not be able to create a new document with this title."));
        ui->lineEditDocumentTitle->setStyleSheet("color: #FF0000");

    } else {
        QToolTip::hideText();
        ui->lineEditDocumentTitle->setStyleSheet("color: #000000");
    }
    if (arg1.length() < 3
        || ui->lineEditDocumentTitle->text().isEmpty()
        || ui->lineEditDocumentDirectory->text().isEmpty()) {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    } else {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

void Dialog_NewDocument::createDocument(int documentTypeIndex, int documentLanguageIndex,
                                        int fontSizeIndex, int paperLayoutIndex, int paperSizeIndex, int documentTypesetIndex,
                                        int documentLayoutIndex, int chapterLayoutIndex,
                                        QString documentTitle, QString documentAuthor, QString documentDate,
                                        QString documentDirectory)
{
    QString documentType;
    QString documentFontSize;
    QString paperLayout;
    QString paperSize;
    QString documentLayout;
    QString chapterLayout;
    QString columnLayout;

    if (QFile::exists(documentDirectory)) {
        QFile::remove(documentDirectory);
    }
    TeXFile *newFile = new TeXFile(documentDirectory, false);
    switch (documentTypeIndex) {
    case 0: //book
        documentType = DOC_BOOK;
        break;
    case 1: //article
        documentType = DOC_ARTICLE;
        break;
    case 2: //report
        documentType = DOC_REPORT;
        break;
    case 3: //memoir
        documentType = DOC_MEMOIR;
        break;
    case 4: //letter
        documentType = DOC_LETTER;
        break;
    case 5: //proc
        documentType = DOC_PROC;
        break;
    }
    switch (fontSizeIndex) {
    case 0: //10pt
        documentFontSize = DOC_FONTSIZE_10PT;
        break;
    case 1: //11pt
        documentFontSize = DOC_FONTSIZE_11PT;
        break;
    case 2: //12pt
        documentFontSize = DOC_FONTSIZE_12PT;
        break;
    }
    switch (paperLayoutIndex) {
    case 0: //two side
        paperLayout = DOC_SIDE_2;
        break;
    case 1: //one side
        paperLayout = DOC_SIDE_1;
        break;
    }
    switch (paperSizeIndex) {
    case 0: //a4papper
        paperSize = DOC_PAPER_A4;
        break;
    case 1: //letterpaper
        paperSize = DOC_PAPER_LETTER;
        break;
    case 2: //a5paper
        paperSize = DOC_PAPER_A5;
        break;
    case 3: //b5paper
        paperSize = DOC_PAPER_B5;
        break;
    case 4: //executivepaper
        paperSize = DOC_PAPER_EXECUTIVE;
        break;
    case 5: //legalpaper
        paperSize = DOC_PAPER_LEGAL;
        break;
    }
    switch (documentTypesetIndex) {
    case 0: //onecolumn
        columnLayout = DOC_COLUMN_1;
        break;
    case 1: //twocolumn
        columnLayout = DOC_COLUMN_2;
        break;
    }
    switch (chapterLayoutIndex) {
    case 0: //openany
        chapterLayout = DOC_OPEN_ANY;
        break;
    case 1: //openright
        chapterLayout = DOC_OPEN_RIGHT;
        break;
    }

    switch (documentLayoutIndex) {
    case 0: //vertical
        documentLayout = DOC_PORTRAIT;
        break;
    case 1: //horizontal
        documentLayout = DOC_LANDSCAPE;
        break;
    }
    if (ui->lineEditClassFile->text().isEmpty())
        newFile->setDocumentPreamble(documentType, documentFontSize, paperLayout, paperSize,
                                     documentLayout,
                                     chapterLayout, columnLayout);
    else {
        QFile classFile(ui->lineEditClassFile->text());
        classFile.copy(QFileInfo(documentDirectory).absolutePath() + "/" + QFileInfo(
                           classFile).baseName().append(".cls"));
        newFile->setDocumentPreamble(QFileInfo(ui->lineEditClassFile->text()).baseName());
    }
    newFile->setBeginDocumentCommand();
    newFile->setDocumentTypeIndex(documentTypeIndex);
    newFile->setDocumentFontSizeIndex(fontSizeIndex);
    newFile->setPaperLayoutIndex(paperLayoutIndex);
    newFile->setPaperSizeIndex(paperSizeIndex);
    newFile->setDocumentLayoutIndex(documentLayoutIndex);
    newFile->setColumnLayoutIndex(documentTypesetIndex);
    newFile->setDocumentLanguageIndex(documentLanguageIndex);
    newFile->setDocumentTitle(ui->lineEditDocumentTitle->text());
    newFile->setDocumentAuthor(ui->lineEditDocumentAuthor->text());
    newFile->setDocumentDate(ui->lineEditDocumentDate->text());
    newFile->setTitle(documentTitle);
    newFile->setAuthor(documentAuthor);
    newFile->setDate(documentDate);
    switch (documentLanguageIndex) {
    case 0: //arabic
        newFile->setArabicLanguage();
        break;
    case 1: //bulgarian
        newFile->setBulgarianLanguage();
        break;
    case 2: //russian
        newFile->setRussianLanguage();
        break;
    case 3: //ukrainian
        newFile->setUkrainianLanguage();
        break;
    case 4: //chinese
        newFile->setChineseLanguage();
        break;
    case 5: //czech
        newFile->setCzechLanguage();
        break;
    case 6: //english
        newFile->setEnglishLanguage();
        break;
    case 7: //finnish
        newFile->setFinnishLanguage();
        break;
    case 8: //french
        newFile->setFrenchLanguage();
        break;
    case 9: //german
        newFile->setGermanLanguage();
        break;
    case 10: //greek
        newFile->setGreekLanguage();
        break;
    case 11: //icelandic
        newFile->setIcelandicLanguage();
        break;
    case 12: //faroese
        newFile->setFaroeseLanguage();
        break;
    case 13: //italian
        newFile->setItalianLanguage();
        break;
    case 14: //korean
        newFile->setKoreanLanguage();
        break;
    case 15: //persian
        newFile->setPersianLanguage();
        break;
    case 16: //polish
        newFile->setPolishLanguage();
        break;
    case 17: //portuguese
        newFile->setPortugueseLanguage();
        break;
    case 18: //slovak
        newFile->setSlovakLanguage();
        break;
    case 19: //spanish
        newFile->setSpanishLanguage();
        break;
    case 20: //tibetan
        newFile->setTibetanLanguage();
        break;

    }
    newFile->setPackage(PACK_HYPERREF, "hidelinks");
    newFile->setPackage(PACK_SOUL);
    newFile->setPackage(PACK_MATH);
    newFile->setPackage(PACK_GRFFILE, "space");
    if (!ui->lineEditStyleFile->text().isEmpty()) {
        QFile styleFile(ui->lineEditStyleFile->text());
        styleFile.copy(QFileInfo(documentDirectory).absolutePath() + "/" + QFileInfo(
                           styleFile).baseName().append(".sty"));
        newFile->setPackage(QFileInfo(ui->lineEditClassFile->text()).baseName());
    }

    newFile->setTeXCommand(command->callMakeTitle());
    newFile->setTeXCommand(command->callChapter(tr("My first chapter")));
    newFile->setTeXCommand(command->callSection(tr("My first section")));
    newFile->writePlainText("Lorem ipsum ad his scripta blandit partiendo, eum fastidii accumsan euripidis in, eum liber hendrerit an. Qui ut wisi vocibus suscipiantur, quo dicit ridens inciderint id. Quo mundi lobortis reformidans eu, legimus senserit definiebas an eos. Eu sit tincidunt incorrupte definitionem, vis mutat affert percipit cu, eirmod consectetuer signiferumque eu per. In usu latine equidem dolores. Quo no falli viris intellegam, ut fugit veritus placerat per.");
    newFile->writePlainText("Ius id vidit volumus mandamus, vide veritus democritum te nec, ei eos debet libris consulatu. No mei ferri graeco dicunt, ad cum veri accommodare. Sed at malis omnesque delicata, usu et iusto zzril meliore. Dicunt maiorum eloquentiam cum cu, sit summo dolor essent te. Ne quodsi nusquam legendos has, ea dicit voluptua eloquentiam pro, ad sit quas qualisque. Eos vocibus deserunt quaestio ei.");
    newFile->writePlainText("Blandit incorrupte quaerendum in quo, nibh impedit id vis, vel no nullam semper audiam. Ei populo graeci consulatu mei, has ea stet modus phaedrum. Inani oblique ne has, duo et veritus detraxit. Tota ludus oratio ea mel, offendit persequeris ei vim. Eos dicat oratio partem ut, id cum ignota senserit intellegat. Sit inani ubique graecis ad, quando graecis liberavisse et cum, dicit option eruditi at duo. Homero salutatus suscipiantur eum id, tamquam voluptaria expetendis ad sed, nobis feugiat similique usu ex.");
    newFile->saveFile();
    QMessageBox::information(this, APP_NAME,
                             tr("Document was created in directory ") + documentDirectory);
    qDebug() << "Document was created succesfully";
}

void Dialog_NewDocument::on_pushButtonBrowseStyleFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("LaTeX Office Writer"), "",
                                                    tr("LaTeX Style File (*.sty)"));
    if (fileName != NULL) {
        if (!fileName.endsWith(".sty")) {
            fileName.append(".sty");
        }
        ui->lineEditStyleFile->setText(fileName);
    }
}

void Dialog_NewDocument::on_pushButtonBrowseClassFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("LaTeX Office Writer"), "",
                                                    tr("LaTeX Class File (*.cls)"));
    if (fileName != NULL) {
        if (!fileName.endsWith(".cls")) {
            fileName.append(".cls");
        }
        ui->lineEditClassFile->setText(fileName);
        ui->comboBoxChapterLayout->setEnabled(false);
        ui->comboBoxDocumentLanguage->setEnabled(false);
        ui->comboBoxDocumentLayout->setEnabled(false);
        ui->comboBoxDocumentType->setEnabled(false);
        ui->comboBoxDocumentTypeset->setEnabled(false);
        ui->comboBoxFontSize->setEnabled(false);
        ui->comboBoxPaperLayout->setEnabled(false);
        ui->comboBoxPaperSize->setEnabled(false);

    }
}

void Dialog_NewDocument::on_pushButtonClearStyleFile_clicked()
{
    ui->lineEditStyleFile->clear();
}

void Dialog_NewDocument::on_pushButtonClearClassFile_clicked()
{
    ui->lineEditClassFile->clear();
    ui->comboBoxChapterLayout->setEnabled(true);
    ui->comboBoxDocumentLanguage->setEnabled(true);
    ui->comboBoxDocumentLayout->setEnabled(true);
    ui->comboBoxDocumentType->setEnabled(true);
    ui->comboBoxDocumentTypeset->setEnabled(true);
    ui->comboBoxFontSize->setEnabled(true);
    ui->comboBoxPaperLayout->setEnabled(true);
    ui->comboBoxPaperSize->setEnabled(true);
}


void Dialog_NewDocument::on_buttonBox_helpRequested()
{
    QMessageBox::information(this, APP_NAME,
                             tr("When creating a new document, you can select several options whose effect will be reflected when you export the document to PDF format. Also, you can add a template previously created from this window to the document."));
}
