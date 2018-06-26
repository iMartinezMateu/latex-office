#include "documentviewer.h"
#include "ui_documentviewer.h"
#include "lib/assistivetechnologies/smartkeys.h"
#include "compilerthread.h"
CompilerThread *compilerThread= new CompilerThread();

DocumentViewer::DocumentViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocumentViewer)
{
    ui->setupUi(this);
    this->setHidden(true);
    goalCap = -1;
    currentPage = -1;
    doc = 0;
    currentScaleFactor = 1;
    ui->caja->setHidden(true);
    compilerPath = TeXCompiler::loadPDFCompilerPathSettings();
    bibCompilerPath = TeXCompiler::loadBIBCompilerPathSettings();
    connect(ui->imagePlaceHolder, SIGNAL(getLineNumber(int)), this,
            SLOT(setLineNumber(int)));
    connect(ui->listWidget->model(), SIGNAL(rowsMoved(QModelIndex,int,int,QModelIndex,int)), this, SLOT(sortDocumentStructure()));
    ui->labelGoalCap->setHidden(true);
    ui->labelWords->setHidden(true);
    ui->progressBarWords->setHidden(true);
    previousGoalWordCount=0;
    goalWordCount=0;
    SmartKeys::loadDefinitionsFile("data/smartkeys/definitions.skd");
    definitionsList=SmartKeys::getDefinitionsStringList();
    ui->caja->getTextEdit()->setAcceptRichText(false);
    connect(ui->caja,SIGNAL(cajaTextChanged()),this,SLOT(on_textEdit_textChanged()));
    connect(ui->caja,SIGNAL(boldStyleChanged()),this,SLOT(setTextBold()));
    connect(ui->caja,SIGNAL(italicStyleChanged()),this,SLOT(setTextItalics()));
    connect(ui->caja,SIGNAL(underlineStyleChanged()),this,SLOT(setTextUnderline()));
    connect(ui->caja,SIGNAL(strikethroughStyleChanged()),this,SLOT(setTextStrikethrough()));
    connect(ui->caja,SIGNAL(smallCapsStyleChanged()),this,SLOT(setTextSmallCaps()));
    connect(ui->caja,SIGNAL(hyperlinkStyleChanged()),this,SLOT(setTextHyperlink()));
    connect(ui->caja,SIGNAL(footnoteStyleChanged()),this,SLOT(setTextFootnote()));
    connect(ui->caja,SIGNAL(centerAlignStyleChanged()),this,SLOT(setTextCenterAlign()));
    connect(ui->caja,SIGNAL(rightAlignStyleChanged()),this,SLOT(setTextRightAlign()));
    connect(ui->caja,SIGNAL(justifyStyleChanged()),this,SLOT(setTextJustify()));
    connect(ui->caja,SIGNAL(bulletListAdded()),this,SLOT(setBulletList()));
    connect(ui->caja,SIGNAL(numberedListAdded()),this,SLOT(setNumberedList()));
    connect(ui->caja,SIGNAL(symbolInserted()),this,SLOT(setSymbol()));
    connect(ui->caja,SIGNAL(citeInserted()),this,SLOT(setCite()));
    connect(ui->caja,SIGNAL(referenceInserted()),this,SLOT(setReference()));
}

void DocumentViewer::loadThreadPool()
{
        compilerThread->setData(file, compilerPath,this);
        compilerThread->setRunState(true);
        compilerThread->start();
        connect(compilerThread,SIGNAL(threadCompiled()),this,SLOT(refreshCurrentPage()));
        qDebug() << "Thread started!";
}

void DocumentViewer::stopThreadPool()
{
        compilerThread->setRunState(false);
        compilerThread->exit();
}

QList<QImage> DocumentViewer::getImages()
{
    return images;
}
void DocumentViewer::loadBiBFile(TeXBibliography * file)
{
    bibFile = file;
}
 QTextEdit* DocumentViewer::getTextEditZone()
 {
     return ui->caja->getTextEdit();
 }

void DocumentViewer::fillList()
{
    int selectedRow = ui->listWidget->currentRow();
    ui->listWidget->clear();
    documentStructureLines.clear();
    foreach (QString line, file->getFileContent())
    {
        if (line.contains(CMD_CHAPTER) && !line.contains(CMD_CHAPTERMARK))
        {
            QRegularExpression re("\{(.*?)\}");
            QRegularExpressionMatch match = re.match(line);
            if (match.hasMatch()) {
                QFont font;
                QString string = match.captured(1);
                QListWidgetItem *item = new QListWidgetItem(string);
                font.setBold(true);
                item->setFont(font);
                item->setTextAlignment(Qt::AlignLeft);
                item->setFlags (item->flags () | Qt::ItemIsEditable);
                ui->listWidget->addItem(item);
                documentStructureLines.append(line);
            }
        }
        else if (line.contains(CMD_SECTION))
        {
            QRegularExpression re("\{(.*?)\}");
            QRegularExpressionMatch match = re.match(line);
            if (match.hasMatch()) {
                QFont font;
                QString string = match.captured(1);
                QListWidgetItem *item = new QListWidgetItem(string);
                font.setUnderline(true);
                item->setFont(font);
                item->setTextAlignment(Qt::AlignCenter);
                item->setFlags (item->flags () | Qt::ItemIsEditable);
                ui->listWidget->addItem(item);
                documentStructureLines.append(line);
            }
        }
        else if (line.contains(CMD_SUBSECTION))
        {
            QRegularExpression re("\{(.*?)\}");
            QRegularExpressionMatch match = re.match(line);
            if (match.hasMatch()) {
                QFont font;
                QString string = match.captured(1);
                QListWidgetItem *item = new QListWidgetItem(string);
                font.setItalic(true);
                item->setFont(font);
                item->setTextAlignment(Qt::AlignCenter);
                item->setFlags (item->flags () | Qt::ItemIsEditable);
                ui->listWidget->addItem(item);
                documentStructureLines.append(line);
            }
        }
        else if (line.contains(CMD_SUBSUBSECTION))
        {
            QRegularExpression re("\{(.*?)\}");
            QRegularExpressionMatch match = re.match(line);
            if (match.hasMatch()) {
                QString string = match.captured(1);
                QListWidgetItem *item = new QListWidgetItem(string);
                item->setTextAlignment(Qt::AlignCenter);
                item->setFlags (item->flags () | Qt::ItemIsEditable);
                ui->listWidget->addItem(item);
                documentStructureLines.append(line);
            }
        }
    }
    ui->listWidget->setCurrentRow(selectedRow);

}
void DocumentViewer::addSymbol(QString command)
{
    QString symbolDefinition = "$"+command.simplified() + "$ ";
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LESS) + "$","<");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LESSOREQUAL) + "$","≤");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_MUCHLESS) + "$","≪");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SUBSET) + "$","⊂");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SUBSETOREQUAL) + "$","⊆");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_NOTSUBSETOREQUAL) + "$","⊈");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SQUAREDSUBSET) + "$","⊏");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_PRECEDESOREQUAL) + "$","≼");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_GREATER) + "$",">");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_GREATEROREQUAL) + "$","≥");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_MUCHGREATER) + "$","≫");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SUPERSET) + "$","⊃");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SUPERSETOREQUAL) + "$","⊇");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_NOTSUPERSETOREQUAL) + "$","⊉");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SQUAREDSUPERSET) + "$","⊐");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SQUAREDSUPERSETOREQUAL) + "$","⊒");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SUCCEEDSOREQUAL) + "$","≽");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_EQUAL) + "$","=");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_EQUALWITHADOTABOVEIT) + "$","≐");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_EQUIVALENT) + "$","≡");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_APPROXIMATELYEQUAL) + "$","≈");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_CONGRUENT) + "$","≅");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SIMILAROREQUAL) + "$","≃");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SIMILAR) + "$","∼");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_PROPORTIONAL) + "$","∝");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_NOTEQUAL) + "$","≠");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_PARALLEL) + "$","∥");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_ASYMPTOTICALLYEQUAL) + "$","≃");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SHORTVERTICALBARTOUCHINGAHORIZONTALBAR) + "$","⊢");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_ELEMENTOF) + "$","∈");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SMILE) + "$","⌣");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_MODELS) + "$","⊧");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_PERPENDICULAR) + "$","⊥");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_PRECEDE) + "$","≺");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SPHERICALANGLE) + "$","∢");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_NOTPARALLEL) + "$","∦");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_NORMALSUBGROUPOF) + "$","⋈");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_REVERSEDASH) + "$","⊣");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_CONTAINSASMEMBER) + "$","∋");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_FROWN) + "$","⌢");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_NOTIN) + "$","∉");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_MIDDLE) + "$","∣");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SUCCEEDS) + "$","≻");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_MEASUREDANGLE) + "$","∡");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_PLUSORMINUS) + "$","±");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_MINUSORPLUS) + "$","∓");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_TIMES) + "$","×");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_DIVISOR) + "$","÷");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_ASTERISK) + "$","*");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_DAGGAR) + "$","†");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_DOUBLEDAGGAR) + "$","‡");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_INTERSECTION) + "$","∩");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_UNION) + "$","∪");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_MULTISETUNION) + "$","⊎");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SQUAREINTERSECTION) + "$","⊓");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SQUAREUNION) + "$","⊔");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LOGICALOR) + "$","⋁");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_VOPERATOR) + "$","⋁");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LOGICALAND) + "$","∧");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_WEDGE) + "$","∧");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_DOTMULTIPLICATION) + "$","⋅");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_DIAMONDOPERATOR) + "$","⋄");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_WIDEUPTRIANGLE) + "$","△");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_WIDEDOWNTRIANGLE) + "$","▽");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LEFTPOINTINGTRIANGLE) + "$","◃");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_RIGHTPOINTINGTRIANGLE) + "$","▹");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LARGECIRCLE) + "$","◯");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_BULLET) + "$","•");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_WREATHPRODUCT) + "$","≀");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_CIRCLEDPLUS) + "$","⊕");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_CIRCLEDMINUS) + "$","⊖");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_CIRCLEDTIMES) + "$","⊗");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_CIRCLEDSLASH) + "$","Ø");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_CIRCLEDDOT) + "$","⊙");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_RINGOPERATOR) + "$","∘");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SETMINUS) + "$","∖");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_AMALGAMATION) + "$","∐");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_COPRODUCT) + "$","∐");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_THEREEXISTSATLEASTONE) + "$","∃");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_THEREEXISTSONEANDONLYONE) + "$","∃!");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_THEREISNO) + "$","∄");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_FORALL) + "$","∀");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LOGICALNOT) + "$","¬");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SUBSET) + "$","⊂");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SUPSET) + "$","⊃");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_IN) + "$","∈");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_NOTIN) + "$","∉");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_CONTAINS) + "$","∋");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LOGICALAND) + "$","∧");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LOGICALOR) + "$","∨");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_RIGHTARROW) + "$","→");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LEFTARROW) + "$","←");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_MAPSTO) + "$","↦");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_IMPLIES) + "$","⇒");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_RIGHTARROW_CAPS) + "$","⇒");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LEFTRIGHTARROW) + "$","↔");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_IFF) + "$","⇔");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LEFTRIGHTARROW_CAPS) + "$","⇔");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_TOP) + "$","⊤");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_BOTTOM) + "$","⊥");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_EMPTYSET) + "$","∅");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_NOTHING) + "$","∅");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_VERTICALBAR) + "$","∣");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_OPENBRACE) + "$","{");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_UPARROW) + "$","↑");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_DOWNARROW) + "$","↓");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_DOUBLEVERTICALBAR) + "$","‖");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_CLOSEBRACE) + "$","}");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_UPARROW_CAPS) + "$","↑");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_DOWNARROW_CAPS) + "$","↓");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SLASH) + "$","/");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LEFTANGLEBRACKET) + "$","‹");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LEFTCEIL) + "$","⌈");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LEFTFLOOR) + "$","⌊");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_BACKSLASH) + "$","∖");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_RIGHTANGLEBRACKET) + "$","›");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_RIGHTCEIL) + "$","⌉");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_RIGHTFLOOR) + "$","⌋");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_A) + "$","Α");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_ALPHA) + "$","α");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_B) + "$","Β");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_BETA) + "$","β");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_GAMMA_CAPS) + "$","Γ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_GAMMA) + "$","γ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_DELTA_CAPS) + "$","Δ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_DELTA) + "$","δ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_E) + "$","Ε");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_EPSILON) + "$","ε");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_VAREPSILON) + "$","ϵ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_Z) + "$","Ζ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_ZETA) + "$","ζ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_H) + "$","Η");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_ETA) + "$","η");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_THETA_CAPS) + "$","Θ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_THETA) + "$","θ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_VARTHETA) + "$","ϑ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_I) + "$","Ι");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_IOTA) + "$","ι");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_K) + "$","K");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_KAPPA) + "$","κ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_VARKAPPA) + "$","ϰ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LAMBDA_CAPS) + "$","Λ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_LAMBDA) + "$","λ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_M) + "$","Μ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_MU) + "$","μ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_N) + "$","Ν");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_NU) + "$","ν");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_XI_CAPS) + "$","Ξ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_XI) + "$","ξ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_O) + "$","Ο");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_OMICRON) + "$","ο");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_PI_CAPS) + "$","Π");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_PI) + "$","π");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_VARPI) + "$","ϖ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_P) + "$","P");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_RHO) + "$","ρ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_VARRHO) + "$","ϱ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SIGMA_CAPS) + "$","Σ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_SIGMA) + "$","σ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_VARSIGMA) + "$","ς");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_T) + "$","Τ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_TAU) + "$","τ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_UPSILON_CAPS) + "$","Υ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_UPSILON) + "$","υ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_PHI_CAPS) + "$","Φ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_PHI) + "$","φ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_VARPHI) + "$","ϕ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_X) + "$","Χ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_CHI) + "$","χ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_PSI_CAPS) + "$","Ψ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_PSI) + "$","ψ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_OMEGA_CAPS) + "$","Ω");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_OMEGA) + "$","ω");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_PARTIAL) + "$","∂");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_DERIVATE) + "$","∂");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_ETH) + "$","ð");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_REDUCEDPLANCKCONSTANT) + "$","ℏ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_IMATH) + "$","ı");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_JMATH) + "$","ĵ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_ELL) + "$","ℓ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_REALPART) + "$","ℜ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_IMAGINARYPART) + "$","ℑ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_WEIERSTRASSPOWERSET) + "$","℘");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_NABLA) + "$","∇");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_BOX) + "$","□");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_INFINITY) + "$","∞");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_ALEPH) + "$","ℵ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_BETH) + "$","ℶ");
    symbolDefinition = symbolDefinition.replace( "$" + QString(SYM_GIMEL) + "$","ℷ");
    ui->caja->getTextEdit()->insertPlainText(symbolDefinition.simplified());
}

void DocumentViewer::sortDocumentStructure()
{
    QString rowChanged = ui->listWidget->currentItem()->text();
    QStringList elementsToBeInserted;
    QStringList newDocumentStructureLines;
    int offset=0;

    for (int element=0; element < documentStructureLines.count(); element++)
    {
        if (documentStructureLines.at(element).contains(rowChanged))
        {
            if (element < ui->listWidget->currentRow())
            {
                QMessageBox::critical(this,APP_NAME,tr("That movement is not allowed. If you wish to move some elements of the document structure, then drag and drop from bottom to up."));
                fillList();
                return;
            }
        }
    }

    for (int element=0; element< documentStructureLines.count();element++)
    {

        if (!documentStructureLines.at(element).contains(rowChanged))
        {
            newDocumentStructureLines.append(documentStructureLines.at(element));
        }
        else if (documentStructureLines.at(element).contains(CMD_CHAPTER))
        {
            for (int subElement = element ; subElement < documentStructureLines.count();subElement++)
            {
                if (documentStructureLines.at(subElement).compare(command.callChapter(rowChanged)) == 0)
                {
                    elementsToBeInserted.append(documentStructureLines.at(subElement));
                }
                else if (!documentStructureLines.at(subElement).contains(CMD_CHAPTER))
                {
                    elementsToBeInserted.append(documentStructureLines.at(subElement));
                }
                else if (documentStructureLines.at(subElement).contains(CMD_CHAPTER))
                {
                    break;
                }
            }
        }
        else if (documentStructureLines.at(element).contains(CMD_SECTION))
        {
            for (int subElement = element ; subElement < documentStructureLines.count();subElement++)
            {
                if (documentStructureLines.at(subElement).compare(command.callSection(rowChanged)) == 0)
                {
                    elementsToBeInserted.append(documentStructureLines.at(subElement));
                }
                else if (!documentStructureLines.at(subElement).contains(CMD_SECTION))
                {
                    elementsToBeInserted.append(documentStructureLines.at(subElement));
                }
                else if (documentStructureLines.at(subElement).contains(CMD_SECTION))
                {
                    break;
                }
            }
        }
    }    

    foreach (QString element, elementsToBeInserted)
    {
        newDocumentStructureLines.insert(ui->listWidget->currentRow()+offset,element);
        offset++;
    }
     newDocumentStructureLines.removeDuplicates();
    QString chapterLine = command.callChapter(rowChanged);
    QString sectionLine = command.callSection(rowChanged);
    QString subSectionLine = command.callSubSection(rowChanged);
    QString subsubSectionLine = command.callSubSubSection(rowChanged);
    QStringList chapterContent;
    QStringList sectionContent;
    QStringList subSectionContent;
    QStringList subsubSectionContent;
    QString nextChapter;
    QStringList newFileContent;
    int position;

    for ( position = 0; position < documentStructureLines.count() ; position++)
    {
        if (documentStructureLines.at(position).compare(chapterLine)==0)
        {
            for (int subPosition= position+1; subPosition < documentStructureLines.count() ; subPosition++)
            {
                if (documentStructureLines.at(subPosition).contains(CMD_CHAPTER))
                {
                    nextChapter = documentStructureLines.at(subPosition);
                    break;
                }
            }
        }
        else if (documentStructureLines.at(position).compare(subsubSectionLine)==0)
        {
            foreach (QString line, file->getFileContent())
            {
                if (line.compare(subsubSectionLine)==0)
                {
                    newFileContent = file->getFileContent();

                    subsubSectionContent.append(subsubSectionLine);
                    newFileContent.removeAt(file->getLineNumber(line));
                    for (int subPosition=file->getLineNumber(line)+1;subPosition<file->getEndDocumentCommand();subPosition++)
                    {
                        if (!file->getFileContent().at(subPosition).contains(CMD_SUBSUBSECTION) && !file->getFileContent().at(subPosition).contains(CMD_SUBSECTION) && !file->getFileContent().at(subPosition).contains(CMD_SECTION) && !file->getFileContent().at(subPosition).contains(CMD_CHAPTER) )
                        {
                            subsubSectionContent.append(file->getFileContent().at(subPosition));
                            if (!file->getFileContent().at(subPosition).contains(CMD_SUBSECTION) && !file->getFileContent().at(subPosition).contains(CMD_SECTION) && !file->getFileContent().at(subPosition).contains(CMD_CHAPTER) && !newFileContent.at(subPosition).contains(ENV_DOCUMENT))
                                 newFileContent.removeAt(subPosition);
                        }
                        else
                            break;
                    }
                    QString nextRowItem = ui->listWidget->item(ui->listWidget->currentRow()+1)->text();
                    foreach (QString line, newFileContent)
                    {
                        if (line.contains(nextRowItem))
                        {
                            int offset=0;
                            foreach (QString element, subsubSectionContent)
                            {
                                newFileContent.insert(file->getLineNumber(line)+offset,element);
                                offset++;
                            }
                            break;
                        }
                    }
                }

            }
        }
        else if (documentStructureLines.at(position).compare(subSectionLine)==0)
        {
            foreach (QString line, file->getFileContent())
            {
                if (line.compare(subSectionLine)==0)
                {
                    newFileContent = file->getFileContent();

                    subSectionContent.append(subSectionLine);
                    newFileContent.removeAt(file->getLineNumber(line));
                    for (int subPosition=file->getLineNumber(line)+1;subPosition<file->getEndDocumentCommand();subPosition++)
                    {
                        if (!file->getFileContent().at(subPosition).contains(CMD_SUBSECTION) && !file->getFileContent().at(subPosition).contains(CMD_SECTION) && !file->getFileContent().at(subPosition).contains(CMD_CHAPTER) )
                        {
                            subSectionContent.append(file->getFileContent().at(subPosition));
                            if (!file->getFileContent().at(subPosition).contains(CMD_SECTION) && !file->getFileContent().at(subPosition).contains(CMD_CHAPTER) && !newFileContent.at(subPosition).contains(ENV_DOCUMENT))
                                 newFileContent.removeAt(subPosition);
                        }
                        else
                            break;
                    }
                    QString nextRowItem = ui->listWidget->item(ui->listWidget->currentRow()+1)->text();
                    foreach (QString line, newFileContent)
                    {
                        if (line.contains(nextRowItem))
                        {
                            int offset=0;
                            foreach (QString element, subSectionContent)
                            {
                                newFileContent.insert(file->getLineNumber(line)+offset,element);
                                offset++;
                            }

                            break;
                        }
                    }
                }
            }
        }
        else if (documentStructureLines.at(position).compare(sectionLine)==0)
        {
            foreach (QString line, file->getFileContent())
            {
                if (line.compare(sectionLine)==0)
                {
                    newFileContent = file->getFileContent();
                    sectionContent.append(sectionLine);
                    newFileContent.removeAt(file->getLineNumber(line));
                    for (int subPosition=file->getLineNumber(line)+1;subPosition<file->getEndDocumentCommand();subPosition++)
                    {
                        if (!file->getFileContent().at(subPosition).contains(CMD_SECTION) && !file->getFileContent().at(subPosition).contains(CMD_CHAPTER) )
                        {
                            sectionContent.append(file->getFileContent().at(subPosition));
                            if (!newFileContent.at(subPosition).contains(CMD_CHAPTER) && !newFileContent.at(subPosition).contains(ENV_DOCUMENT))
                                 newFileContent.removeAt(subPosition);
                        }
                        else
                            break;
                    }
                    QString nextRowItem = ui->listWidget->item(ui->listWidget->currentRow()+1)->text();
                    foreach (QString line, newFileContent)
                    {
                        if (line.contains(nextRowItem))
                        {
                            int offset=0;
                            foreach (QString element, sectionContent)
                            {
                                newFileContent.insert(file->getLineNumber(line)+offset,element);
                                offset++;
                            }

                            break;
                        }
                    }
                }
            }
        }
    }

    if (newFileContent.isEmpty())
    {
                if (nextChapter.isEmpty())
                {
                    nextChapter = command.callEnd(ENV_DOCUMENT);
                }
                    for (int lineNumber=0; lineNumber<file->getFileContent().count();lineNumber++)
                    {
                        if (file->getFileContent().at(lineNumber).compare(chapterLine)==0)
                        {
                            for (int subPosition=lineNumber; subPosition < file->getLineNumber(nextChapter); subPosition++ )
                            {
                                chapterContent.append(file->getFileContent().at(subPosition));
                            }
                            break;
                        }
                        newFileContent.append(file->getFileContent().at(lineNumber));
                    }
                    for (int position = 0; position < newDocumentStructureLines.count() ; position++)
                    {
                        if (newDocumentStructureLines.at(position).compare(chapterLine)==0)
                        {
                            for (int subPosition= position+1; subPosition < newDocumentStructureLines.count() ; subPosition++)
                            {
                                if (newDocumentStructureLines.at(subPosition).contains(CMD_CHAPTER))
                                {
                                    nextChapter = newDocumentStructureLines.at(subPosition);
                                    break;
                                }
                            }
                        }
                    }
                   offset=0;
                   int nextChapterLine=0;
                   foreach (QString fileLine, newFileContent)
                   {
                       if (fileLine.compare(nextChapter)==0 )
                       {
                            foreach (QString line, chapterContent)
                            {
                                newFileContent.insert( nextChapterLine+offset ,line);
                                offset++;
                            }
                       }
                       nextChapterLine++;
                   }
                   for (int lineNumber=newFileContent.count();lineNumber<file->getFileContent().count();lineNumber++)
                   {
                       newFileContent.append(file->getFileContent().at(lineNumber));
                   }
    }
    newFileContent.removeDuplicates();
    documentStructureLines = newDocumentStructureLines;
    file->setFileContent(newFileContent);
    file->saveFile();
    file->compile(compilerPath);
    file->compile(compilerPath);
    refresh(getCurrentPage());
}

void DocumentViewer::setSymbol()
{
    Dialog_Symbol *dialog = new Dialog_Symbol();
    if (file->getPackage(PACK_MATH) == -1)
    {
        file->setPackage(PACK_MATH);
        file->saveFile();
    }
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    if (!dialog->getSelectedSymbol().isEmpty())
        addSymbol(dialog->getSelectedSymbol());
}

void DocumentViewer::setCite()
{
    if (!bibFile)
    {
        QMessageBox::critical(this,APP_NAME,tr("There isn't a bibliography associated with this document. You cannot add citations until you associate a bibliography with this document."));
        return;
    }
    if (!bibFile->existsFile())
    {
        QMessageBox::critical(this,APP_NAME,tr("There isn't a bibliography associated with this document. You cannot add citations until you associate a bibliography with this document."));
        return;
    }
    if (file->getLineNumber(CMD_BIBLIOGRAPHY) == -1)
    {
        QMessageBox::critical(this,APP_NAME,tr("There isn't a bibliography associated with this document. You cannot add citations until you associate a bibliography with this document."));
        return;
    }
    Dialog_Citations *dialog = new Dialog_Citations(file,bibFile,selectedLineNumber);
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    file->compile(compilerPath);
    bibFile->saveFile();
    bibFile->compile(bibCompilerPath);
    file->compile(compilerPath);
    file->compile(compilerPath);
    refresh(getCurrentPage());
}

void DocumentViewer::setReference()
{
    Dialog_References *dialog = new Dialog_References(file,selectedLineNumber);
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    file->compile(compilerPath);
    file->compile(compilerPath);
    refresh(getCurrentPage());
}

void DocumentViewer::setLineNumber(int lineNumber)
{
    selectedLineNumber = lineNumber;
    ui->caja->getTextEdit()->setEnabled(false);
    ui->caja->setHidden(true);
    hideTextEdit();
    if (file->getFileContent().at(lineNumber -1).contains(CMD_TAB_HORIZ_LINE))
    {
        QStringList tableCommands;
        for (int element= lineNumber -1;element>0;element--)
        {
            if (file->getFileContent().at(element).contains(command.callBegin(ENV_TABULAR)))
            {
                for (int subElement= element; subElement < file->getEndDocumentCommand();subElement++)
                {
                    if (!file->getFileContent().at(subElement).contains(command.callEnd(ENV_TABULAR)))
                    {
                        tableCommands.append( file->getFileContent().at(subElement));
                    }
                    else
                    {
                        tableCommands.append(file->getFileContent().at(subElement));
                        break;
                    }
                }
            }
        }
        Dialog_ModifyTable *dialog = new Dialog_ModifyTable();
        dialog->setData(lineNumber-1, file,compilerPath, tableCommands);
        dialog->exec();
        refresh(getCurrentPage());
        hideTextEdit();
    }
    else if (file->getFileContent().at(lineNumber-1).contains(CMD_LSTINPUTLISTING))
    {
        Dialog_ModifyCodeAsset *dialog = new Dialog_ModifyCodeAsset(file->getFileContent().at(lineNumber-1),lineNumber-1,file,compilerPath);
        dialog->exec(); //Blocks input to parent window until current dialog has been finished
        refresh(getCurrentPage());
        hideTextEdit();
    }
    else if (file->getFileContent().at(lineNumber-1).contains(command.callEnd(ENV_EQUATION)))
    {
        Dialog_ModifyEquation *dialog = new Dialog_ModifyEquation(file,lineNumber-1,compilerPath);
        dialog->show(); //Blocks input to parent window until current dialog has been finished
        refresh(getCurrentPage());
    }
    else if (file->getFileContent().at(lineNumber - 1).contains(command.callIncludeGraphics())) {
        QStringList lines;
        for (int subElement=lineNumber-1;subElement>=0;subElement--)
        {
            if (subElement==0)
            {
                lines.append(file->getFileContent().at(lineNumber - 1));
                break;
            }
            if (file->getFileContent().at(subElement).contains(command.callBegin(ENV_FIGURE)))
            {
                int figureElement=subElement;
                foreach (QString(file->getFileContent().at(figureElement)), file->getFileContent())
                {
                    if (!file->getFileContent().at(figureElement).contains(command.callEnd(ENV_FIGURE)))
                    {
                        lines.append(file->getFileContent().at(figureElement));
                    }
                    else
                    {
                        break;
                    }
                    figureElement++;
                }
            }
            if (file->getFileContent().at(subElement).contains(command.callEnd(ENV_FIGURE)))
            {
                lines.append(file->getFileContent().at(lineNumber - 1));
                break;
            }
        }
        if (file->getPackage(PACK_GRFFILE,"space") == -1)
        {
            file->deprecompile();
            file->setPackage(PACK_GRFFILE,"space");
            file->saveFile();
        }
        Dialog_ModifyImage *dialog = new Dialog_ModifyImage();
        dialog->setData(file, file->getDirectory(), lines,compilerPath);
        dialog->exec();
        refresh(getCurrentPage());
    }
     else if (!file->getFileContent().at(lineNumber-1).contains(CMD_VFILL) && !file->getFileContent().at(lineNumber -1).contains("%&" + file->getFileName()) &&!file->getFileContent().at(lineNumber -1).contains(CMD_USE_PACKAGE) &&  !file->getFileContent().at(lineNumber -1).contains(CMD_BIBLIOGRAPHY) && !file->getFileContent().at(lineNumber-1).contains(CMD_PAGESTYLE) && !file->getFileContent().at(lineNumber-1).contains(CMD_BIBLIOGRAPHYSTYLE) && !file->getFileContent().at(lineNumber - 1).contains(command.callBegin(ENV_DOCUMENT)) && !file->getFileContent().at(lineNumber - 1).contains(command.callEnd(ENV_DOCUMENT)) && !file->getFileContent().at(lineNumber - 1).contains(command.callCaption()) && !file->getFileContent().at(lineNumber - 1).contains(command.callLabel()) && !file->getFileContent().at(lineNumber - 1).contains(command.callBegin(DOC_PAGE_TITLE)) && !file->getFileContent().at(lineNumber - 1).contains(command.callTableOfContents()) && !file->getFileContent().at(lineNumber - 1).contains(command.callDocumentClass()) && !file->getFileContent().at(lineNumber - 1).contains(command.callMakeTitle()) && !file->getFileContent().at(lineNumber - 1).contains(CMD_CHAPTER) && !file->getFileContent().at(lineNumber-1).contains(CMD_SECTION) &&  !file->getFileContent().at(lineNumber - 1).isEmpty() && !file->getFileContent().at(lineNumber - 1).contains(CMD_SUBSECTION) && !file->getFileContent().at(lineNumber - 1).contains(CMD_SUBSUBSECTION) ) {
        if (file->getFileContent().at(lineNumber-1).at(0)=='%')
        {
            if (!file->getFileContent().at(lineNumber-1).contains("%justify%"))
            {
                return;
            }
        }
        ui->caja->getTextEdit()->setEnabled(false);
        if (!ui->caja->getTextEdit()->toPlainText().isEmpty()) {
            ui->caja->getTextEdit()->clear();
        }
        ui->caja->getTextEdit()->setText(file->getFileContent().at(lineNumber - 1));
        compilerThread->setRunState(true);
        emit textEditAppeared();
        loadThreadPool();
        QString textContent = ui->caja->getTextEdit()->toPlainText();
        ui->caja->getTextEdit()->setHtml(toHTML(textContent));
        if (!ui->progressBarWords->isHidden())
            ui->progressBarWords->setValue(previousGoalWordCount);
        initialParagraphWordCount = ui->caja->getTextEdit()->toPlainText().split(QRegExp("(\\s|\\n|\\r)+")
                                                          , QString::SkipEmptyParts).count();
        ui->caja->getTextEdit()->setEnabled(true);
        ui->caja->setHidden(false);
    }
}

void DocumentViewer::setTextBold()
{
    QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    if( cursor.charFormat().fontWeight() == QFont::Bold  )
        fmt.setFontWeight( QFont::Normal);
    else
    {
       fmt.setFontWeight( QFont::Bold);
    }
    cursor.mergeCharFormat( fmt );
    ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void DocumentViewer::setTextItalics()
{
        QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
        QTextCharFormat fmt;
        if (!cursor.hasSelection())
            cursor.select(QTextCursor::WordUnderCursor);
        if( cursor.charFormat().fontItalic() )
            fmt.setFontItalic(false);
        else
        {
           fmt.setFontItalic(true);
        }
        cursor.mergeCharFormat( fmt );

        ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void DocumentViewer::setTextUnderline()
{
    QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    if( cursor.charFormat().fontUnderline() )
        fmt.setFontUnderline(false);
    else
    {
       fmt.setFontUnderline(true);
    }
    cursor.mergeCharFormat( fmt );
    ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void DocumentViewer::setTextStrikethrough()
{
    QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    if( cursor.charFormat().fontStrikeOut())
        fmt.setFontStrikeOut(false);
    else
    {
       fmt.setFontStrikeOut(true);
    }
    cursor.mergeCharFormat( fmt );
    ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void DocumentViewer::setTextEmphatize()
{
    QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    if( cursor.charFormat().fontWeight() == QFont::StyleOblique  )
    {
        fmt.setFontStretch(100);
        fmt.setFontWeight( QFont::Normal);
        fmt.setFontItalic(false);
    }
    else
    {
       fmt.setFontStretch(125);
       fmt.setFontWeight( QFont::StyleOblique);
       fmt.setFontItalic(true);
    }
    cursor.mergeCharFormat( fmt );
    ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void DocumentViewer::setTextSmallCaps()
{
    QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    if( cursor.charFormat().fontCapitalization() == QFont::SmallCaps )
            fmt.setFontCapitalization(QFont::MixedCase);
    else
    {
            fmt.setFontCapitalization(QFont::SmallCaps);
    }
    cursor.mergeCharFormat( fmt );
    ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void DocumentViewer::setTextHyperlink()
{
    QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    if( cursor.charFormat().anchorHref().isEmpty() )
    {
            fmt.setAnchor(true);
            fmt.setAnchorHref(ui->caja->getTextEdit()->textCursor().selectedText());
    }
    else
    {
            fmt.setAnchorHref("");
            fmt.setAnchor(false);
            fmt.setFontUnderline(false);
    }
    cursor.mergeCharFormat( fmt );
    ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
    ui->caja->getTextEdit()->setHtml(toHTML(file->getFileContent().at(selectedLineNumber-1)));
    ui->caja->getTextEdit()->setTextCursor(cursor);
}

void DocumentViewer::setTextFootnote()
{
    QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    if( cursor.charFormat().verticalAlignment() == QTextCharFormat::AlignSubScript )
    {
        fmt.setVerticalAlignment(QTextCharFormat::AlignNormal);
    }
    else
    {
        fmt.setVerticalAlignment(QTextCharFormat::AlignSubScript);
    }
    cursor.mergeCharFormat( fmt );
    ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void DocumentViewer::setTextChapter()
{
    if (ui->caja->getTextEdit())
    {
        QString oldText = ui->caja->getTextEdit()->toPlainText();
        ui->caja->getTextEdit()->setHtml("<h1>"+ oldText + "</h1>");
    }
}

void DocumentViewer::setTextSection()
{
    if (ui->caja->getTextEdit())
    {
        QString oldText = ui->caja->getTextEdit()->toPlainText();
        ui->caja->getTextEdit()->setHtml("<h2>"+ oldText + "</h2>");
    }
}

void DocumentViewer::setTextSubSection()
{
    if (ui->caja->getTextEdit())
    {
        QString oldText = ui->caja->getTextEdit()->toPlainText();
        ui->caja->getTextEdit()->setHtml("<h3>"+ oldText + "</h3>");
    }
}

void DocumentViewer::setTextSubSubSection()
{
    if (ui->caja->getTextEdit())
    {
        QString oldText = ui->caja->getTextEdit()->toPlainText();
        ui->caja->getTextEdit()->setHtml("<h4>"+ oldText + "</h4>");
    }
}

void DocumentViewer::setTextParagraph()
{
    if (ui->caja->getTextEdit())
    {
        QString oldText = ui->caja->getTextEdit()->toPlainText();
        ui->caja->getTextEdit()->setHtml("<p>"+ oldText + "</p>");
    }
}

void DocumentViewer::setTextLeftAlign()
{
    ui->caja->getTextEdit()->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    file->saveFile();
}

void DocumentViewer::setTextCenterAlign()
{
    ui->caja->getTextEdit()->setAlignment(Qt::AlignHCenter);
    file->saveFile();
}

void DocumentViewer::setTextRightAlign()
{
    ui->caja->getTextEdit()->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    file->saveFile();
}

void DocumentViewer::setTextJustify()
{
    ui->caja->getTextEdit()->setAlignment(Qt::AlignJustify);
    file->saveFile();
}
void DocumentViewer::cutText()
{
    ui->caja->getTextEdit()->cut();
}

void DocumentViewer::copyText()
{
    ui->caja->getTextEdit()->copy();
}

void DocumentViewer::pasteText()
{
    ui->caja->getTextEdit()->paste();
}

void DocumentViewer::setNumberedList()
{
    QTextCursor cursor = ui->caja->getTextEdit()->cursorForPosition(ui->caja->getTextEdit()->cursor().pos());
    QTextListFormat listFormat;
    listFormat.setStyle(QTextListFormat::ListDecimal);
    cursor.insertList(listFormat);
    cursor.insertText(" ");
}

void DocumentViewer::setBulletList()
{
       QTextCursor cursor = ui->caja->getTextEdit()->cursorForPosition(ui->caja->getTextEdit()->cursor().pos());
       QTextListFormat listFormat;
       listFormat.setStyle(QTextListFormat::ListDisc);
       cursor.insertList(listFormat);
       cursor.insertText(" ");
}

void DocumentViewer::refreshCurrentPage()
{
    QFile pdfFile(documentPath);

    if (!pdfFile.open(QIODevice::ReadOnly))
    {
        return;
    }
            closeDocument();
            loadDocument(documentPath,getCurrentPage());
            showPage(getCurrentPage(), currentScaleFactor);
            compilerThread->setRunState(true);

        pdfFile.close();
}

void DocumentViewer::refresh(int pageNumber)
{
    QFile pdfFile(documentPath);
    if (!pdfFile.open(QIODevice::ReadOnly))
    {
        return;
    }
    closeDocument();
    loadDocument(documentPath, pageNumber);
    showPage(pageNumber, currentScaleFactor);
    compilerThread->setRunState(true);
    pdfFile.close();
}
void DocumentViewer::loadTeXFile(TeXFile *file)
{
    this->file = file;
}
int DocumentViewer::getCurrentPage()
{
    return currentPage;
}
int DocumentViewer::getSelectedLineNumber()
{
    return selectedLineNumber;
}
DocumentViewer::~DocumentViewer()
{
    delete ui;
}
QMatrix DocumentViewer::matrix() const
{
    return QMatrix(currentScaleFactor * physicalDpiX() / 72.0, 0,
                   0, currentScaleFactor * physicalDpiY() / 72.0,
                   0, 0);
}
void DocumentViewer::loadDocument(QString path)
{
    qDebug() << "Loading document in path " + path;
    documentPath = path;
    doc = Poppler::Document::load(path);
    if (doc != NULL) {
        scanner = synctex_scanner_new_with_output_file(path.toStdString().c_str(), NULL, 1);
        currentPage = 0;
        currentScaleFactor = 1;
        totalPages = doc->numPages();
        doc->setRenderHint(Poppler::Document::TextAntialiasing);
        images.clear();
        for (int page=0;page<totalPages;page++)
        {
            images.append(doc->page(page)->renderToImage(
                              currentScaleFactor * physicalDpiX(),
                              currentScaleFactor * physicalDpiY()));
        }
        showPage(currentPage, currentScaleFactor);
        this->setHidden(false);
        fillList();
        qDebug() << "Document loaded";
    } else {
        qDebug() << "Error trying to load document. That's all I know...";
    }
}

void DocumentViewer::loadDocument(QString path, int page)
{
    qDebug() << "Loading document in path " + path;

    documentPath = path;
    doc = Poppler::Document::load(path);
    if (doc != NULL) {
        scanner = synctex_scanner_new_with_output_file(path.toStdString().c_str(), NULL, 1);
        currentPage = page;
        currentScaleFactor = 1;
        totalPages = doc->numPages();
        doc->setRenderHint(Poppler::Document::TextAntialiasing);
        images.clear();
        for (int page=0;page<totalPages;page++)
        {
            images.append(doc->page(page)->renderToImage(
                              currentScaleFactor * physicalDpiX(),
                              currentScaleFactor * physicalDpiY()));
        }
        showPage(currentPage, currentScaleFactor);
        this->setHidden(false);
        fillList();
        qDebug() << "Document loaded";
    } else {
        qDebug() << "Error trying to load document. That's all I know...";
    }
}

int DocumentViewer::getTotalPages()
{
    return totalPages;
}

void DocumentViewer::showPage(int pageNumber, int scaleFactor)
{
    if (pageNumber >= 0 && pageNumber < totalPages) {
        currentPage = pageNumber;
        currentScaleFactor = scaleFactor;
        ui->imagePlaceHolder->setData(doc, currentPage, currentScaleFactor, scanner,documentPath,file,this,compilerPath);

        ui->imagePlaceHolder->setPixmap(QPixmap::fromImage(images.at(currentPage)));
        ui->lineEditPage->setText(QString::number(currentPage + 1) + "/" + QString::number(
                                      totalPages));

        qDebug() << "Displaying page number" + pageNumber;
    }
}

void DocumentViewer::searchString(QString string, bool caseSensitive)
{
      QList< QRectF> searchRect;
      QString searchString;
      int page;
      int initialPage = currentPage;
      /*A causa de limitaciones en la libreria, se precisa que la cadena de búsqueda no tenga acentos...*/
      searchString = string.replace("á","a");
      searchString = string.replace("é","e");
      searchString = string.replace("í","i");
      searchString = string.replace("ó","o");
      searchString = string.replace("ú","u");
      for ( page=0; page<totalPages; page++)
      {
          showPage(page,currentScaleFactor);
          if (caseSensitive == true)
          {
               searchRect = (doc->page(page)->search(searchString, Poppler::Page::CaseSensitive,Poppler::Page::Rotate0));
          }
          else
          {
              searchRect = (doc->page(page)->search(searchString, Poppler::Page::CaseInsensitive,Poppler::Page::Rotate0));
          }
          if (!searchRect.isEmpty())
          {
              QMessageBox messageBox(APP_NAME,
                              tr("The following string \"") + string + tr("\" was found in page ") + QString::number(page+1) + tr(". Do you want to stop the search?"),
                              QMessageBox::Question,
                              QMessageBox::Yes | QMessageBox::Default,
                              QMessageBox::No | QMessageBox::Escape,  //This makes "Esc" key to Cancel the Dialog
                              QMessageBox::NoButton,
                              this);
              messageBox.setButtonText( QMessageBox::Yes, tr("Yes") );
              messageBox.setButtonText( QMessageBox::No, tr("No") );
              if (messageBox.exec() == QMessageBox::Yes)
                  break;
          }
      }
      if (searchRect.isEmpty())
      {
          showPage(initialPage,currentScaleFactor);
          QMessageBox::information(this,APP_NAME,"The following string \"" + string + "\" could not be found on the document!");
      }
}

void DocumentViewer::showPreviousPage()
{
    showPage(currentPage - 1, currentScaleFactor);
    hideTextEdit();
}

void DocumentViewer::hideTextEdit()
{
    stopThreadPool();
    previousGoalWordCount = goalWordCount;

    if (!ui->caja->isHidden())
    {
        ui->caja->getTextEdit()->setEnabled(false);
        ui->caja->setHidden(true);
        emit textEditDisappeared();
        if (!ui->caja->getTextEdit()->toPlainText().isEmpty()) {
            ui->caja->getTextEdit()->clear();
        }
    }
}

void DocumentViewer::showNextPage()
{
    showPage(currentPage + 1, currentScaleFactor);
    hideTextEdit();
}

void DocumentViewer::on_pushButtonNextPage_clicked()
{
    showNextPage();
}

void DocumentViewer::on_pushButtonPreviousPage_clicked()
{
    showPreviousPage();
}

void DocumentViewer::closeDocument()
{
    stopThreadPool();
    if (doc)
        delete doc;
}

qreal DocumentViewer::scale() const
{
    return currentScaleFactor;
}

void DocumentViewer::on_textEdit_textChanged()
{
    if (ui->caja->getTextEdit()->isEnabled()) {
        SmartKeys::loadDefinitionsFile("data/smartkeys/definitions.skd");
        definitionsList=SmartKeys::getDefinitionsStringList();
        foreach (QStringList item,definitionsList)
        {
            if (ui->caja->getTextEdit()->textCursor().position()>0)
                if (ui->caja->getTextEdit()->toPlainText().split(QRegExp("(\\s|\\n|\\r)+")
                                                     , QString::SkipEmptyParts).last().compare(item.at(1))==0)
                {
                    QTextCursor c = ui->caja->getTextEdit()->textCursor();
                    c.setPosition(c.position() - item.at(1).length());
                    c.setPosition(c.position() + item.at(1).length(), QTextCursor::KeepAnchor);
                    ui->caja->getTextEdit()->setTextCursor(c);
                    c.removeSelectedText();
                    c.insertText(item.at(2));
                    c.atEnd();
                }
        }
        file->replaceTeXCommand(fromHTML(ui->caja->getTextEdit()->toHtml().append(CMD_PARAGRAPH_BREAK)), getSelectedLineNumber() - 1);
        paragraphWordCount = ui->caja->getTextEdit()->toPlainText().split(QRegExp("(\\s|\\n|\\r)+")
                                                          , QString::SkipEmptyParts).count();
        goalWordCount = previousGoalWordCount +  paragraphWordCount;
        ui->progressBarWords->setValue(goalWordCount);

        file->saveFile();
        emit textEditChanged();
    }
}

int DocumentViewer::getParagraphWordCount()
{
    return paragraphWordCount;
}

void DocumentViewer::setTextTiny()
{
    QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    cursor.select(QTextCursor::Document);
    //if (!cursor.hasSelection())
    //    cursor.select(QTextCursor::WordUnderCursor);

    fmt.setFontPointSize(7.33);
    cursor.mergeCharFormat( fmt );
    ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void DocumentViewer::setTextSmall()
{
    QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    cursor.select(QTextCursor::Document);
    //if (!cursor.hasSelection())
    //    cursor.select(QTextCursor::WordUnderCursor);

    fmt.setFontPointSize(10);
    cursor.mergeCharFormat( fmt );
    ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void DocumentViewer::setTextNormal()
{
    QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    cursor.select(QTextCursor::Document);
    //if (!cursor.hasSelection())
    //    cursor.select(QTextCursor::WordUnderCursor);

    fmt.setFontPointSize(12.5);
    cursor.mergeCharFormat( fmt );
    ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void DocumentViewer::setTextLarge()
{
    QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    cursor.select(QTextCursor::Document);
    //if (!cursor.hasSelection())
    //    cursor.select(QTextCursor::WordUnderCursor);

    fmt.setFontPointSize(15);
    cursor.mergeCharFormat( fmt );
    ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void DocumentViewer::setTextXLarge()
{
    QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    cursor.select(QTextCursor::Document);
    //if (!cursor.hasSelection())
    //    cursor.select(QTextCursor::WordUnderCursor);

    fmt.setFontPointSize(18);
    cursor.mergeCharFormat( fmt );
    ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void DocumentViewer::setTextXXLarge()
{
    QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    cursor.select(QTextCursor::Document);
    //if (!cursor.hasSelection())
    //    cursor.select(QTextCursor::WordUnderCursor);

    fmt.setFontPointSize(21);
    cursor.mergeCharFormat( fmt );
    ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void DocumentViewer::setTextHuge()
{
    QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    cursor.select(QTextCursor::Document);
    //if (!cursor.hasSelection())
    //    cursor.select(QTextCursor::WordUnderCursor);

    fmt.setFontPointSize(24);
    cursor.mergeCharFormat( fmt );
    ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void DocumentViewer::setTextXHuge()
{
    QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    cursor.select(QTextCursor::Document);
    //if (!cursor.hasSelection())
    //    cursor.select(QTextCursor::WordUnderCursor);
    fmt.setFontPointSize(28);
    cursor.mergeCharFormat( fmt );
    ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void DocumentViewer::on_textEdit_cursorPositionChanged()
{
    QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
    qreal fontSize;
    QString headingStyle;
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    fontSize = cursor.charFormat().fontPointSize();
    if (ui->caja->getTextEdit()->toHtml().contains("font-size:xx-large; font-weight:600;"))
        headingStyle = "chapter";
    else if (ui->caja->getTextEdit()->toHtml().contains("font-size:x-large; font-weight:600;"))
        headingStyle = "section";
    else if (ui->caja->getTextEdit()->toHtml().contains("font-size:large; font-weight:600;"))
        headingStyle = "subsection";
    else if (ui->caja->getTextEdit()->toHtml().contains("font-size:medium; font-weight:600;"))
        headingStyle = "subsubsection";
    else
        headingStyle = "paragraph";
    emit selectedTextAttributes(fontSize,headingStyle);
}

void DocumentViewer::on_listWidget_itemChanged(QListWidgetItem *item)
{
    if  (item->text().length() == 0)
    {
        int row = ui->listWidget->row(item);
        QMessageBox messageBox(APP_NAME,
                        tr("Do you want to delete the selected document part? You will not be able to undo the change."),
                        QMessageBox::Question,
                        QMessageBox::Yes | QMessageBox::Default,
                        QMessageBox::No | QMessageBox::Escape,  //This makes "Esc" key to Cancel the Dialog
                        QMessageBox::NoButton,
                        this);
        messageBox.setButtonText( QMessageBox::Yes, tr("Yes") );
        messageBox.setButtonText( QMessageBox::No, tr("No") );

        if (messageBox.exec() == QMessageBox::Yes)
        {
            if (documentStructureLines.at(row).contains(CMD_CHAPTER_NONUMBERING))
            {
                file->deleteDocumentChapterContent(documentStructureLines.at(row));
            }
            else if (documentStructureLines.at(row).contains(CMD_SECTION_NONUMBERING))
            {
                file->deleteDocumentSectionContent(documentStructureLines.at(row));
            }
            else if (documentStructureLines.at(row).contains(CMD_SUBSECTION_NONUMBERING))
            {
                file->deleteDocumentSubSectionContent(documentStructureLines.at(row));
            }
            else if (documentStructureLines.at(row).contains(CMD_SUBSUBSECTION_NONUMBERING))
            {
                file->deleteDocumentSubSubSectionContent(documentStructureLines.at(row));
            }
            else if (documentStructureLines.at(row).contains(CMD_CHAPTER))
            {
                file->deleteDocumentChapterContent(documentStructureLines.at(row));
            }
            else if (documentStructureLines.at(row).contains(CMD_SECTION))
            {
                file->deleteDocumentSectionContent(documentStructureLines.at(row));
            }
            else if (documentStructureLines.at(row).contains(CMD_SUBSECTION))
            {
                file->deleteDocumentSubSectionContent(documentStructureLines.at(row));
            }
            else if (documentStructureLines.at(row).contains(CMD_SUBSUBSECTION))
            {
                file->deleteDocumentSubSubSectionContent(documentStructureLines.at(row));
            }

            file->saveFile();
            file->compile(compilerPath);
            file->compile(compilerPath);
            refresh(getCurrentPage());
        }
        else
        {
          fillList();
        }
    }
    else if (item->text().length() > 0 && item->text().length() < 2)
    {
        QMessageBox::critical(this,APP_NAME,tr("The entered string length is too short. The change will not be applied."));
        fillList();
    }
    else
    {
        int row = ui->listWidget->row(item);
        int lineNumber=0;
        foreach (QString line, file->getFileContent())
        {
            if (line.contains(documentStructureLines.at(row)))
            {
                if (documentStructureLines.at(row).contains(CMD_CHAPTER_NONUMBERING))
                {
                    if (file->getLineNumber(command.callChapterNoN(item->text()))!=-1)
                    {
                        QMessageBox::critical(this,APP_NAME,tr("You cannot add a chapter that already exists on the document!"));
                        fillList();
                        return;
                    }
                    file->replaceTeXCommand(command.callChapterNoN(item->text()),lineNumber);
                }
                else if (documentStructureLines.at(row).contains(CMD_SECTION_NONUMBERING))
                {
                    if (file->getLineNumber(command.callSectionNoN(item->text()))!=-1)
                    {
                        QMessageBox::critical(this,APP_NAME,tr("You cannot add a section that already exists on the document!"));
                        fillList();
                        return;
                    }
                    file->replaceTeXCommand(command.callSectionNoN(item->text()),lineNumber);
                }
                else if (documentStructureLines.at(row).contains(CMD_SUBSECTION_NONUMBERING))
                {
                    if (file->getLineNumber(command.callSubSectionNoN(item->text()))!=-1)
                    {
                        QMessageBox::critical(this,APP_NAME,tr("You cannot add a subsection that already exists on the document!"));
                        fillList();
                        return;
                    }
                    file->replaceTeXCommand(command.callSubSectionNoN(item->text()),lineNumber);
                }
                else if (documentStructureLines.at(row).contains(CMD_SUBSUBSECTION_NONUMBERING))
                {
                    if (file->getLineNumber(command.callSubSubSectionNoN(item->text()))!=-1)
                    {
                        QMessageBox::critical(this,APP_NAME,tr("You cannot add a subsubsection that already exists on the document!"));
                        fillList();
                        return;
                    }
                    file->replaceTeXCommand(command.callSubSubSectionNoN(item->text()),lineNumber);
                }
                else if (documentStructureLines.at(row).contains(CMD_CHAPTER))
                {
                    if (file->getLineNumber(command.callChapter(item->text()))!=-1)
                    {
                        QMessageBox::critical(this,APP_NAME,tr("You cannot add a chapter that already exists on the document!"));
                        fillList();
                        return;
                    }
                    file->replaceTeXCommand(command.callChapter(item->text()),lineNumber);
                }
                else if (documentStructureLines.at(row).contains(CMD_SECTION))
                {
                    if (file->getLineNumber(command.callSection(item->text()))!=-1)
                    {
                        QMessageBox::critical(this,APP_NAME,tr("You cannot add a section that already exists on the document!"));
                        fillList();
                        return;
                    }
                    file->replaceTeXCommand(command.callSection(item->text()),lineNumber);
                }
                else if (documentStructureLines.at(row).contains(CMD_SUBSECTION))
                {
                    if (file->getLineNumber(command.callSubSection(item->text()))!=-1)
                    {
                        QMessageBox::critical(this,APP_NAME,tr("You cannot add a subsection that already exists on the document!"));
                        fillList();
                        return;
                    }
                    file->replaceTeXCommand(command.callSubSection(item->text()),lineNumber);
                }
                else if (documentStructureLines.at(row).contains(CMD_SUBSUBSECTION))
                {
                    if (file->getLineNumber(command.callSubSubSection(item->text()))!=-1)
                    {
                        QMessageBox::critical(this,APP_NAME,tr("You cannot add a subsubsection that already exists on the document!"));
                        fillList();
                        return;
                    }
                    file->replaceTeXCommand(command.callSubSubSection(item->text()),lineNumber);
                }
            }
            lineNumber++;
        }
        file->saveFile();
        file->compile(compilerPath);
        file->compile(compilerPath);
        refresh(getCurrentPage());
    }
}

void DocumentViewer::enableGoal(int cap, bool warn)
{
    ui->progressBarWords->setValue(0);
    ui->progressBarWords->setMaximum(cap);
    ui->progressBarWords->setMinimum(0);
    ui->labelGoalCap->setText(QString::number(cap) + tr(" words"));
    ui->labelWords->setText(QString::number(0));
    warnGoalAchieved = warn;
    ui->labelGoalCap->setHidden(false);
    ui->labelWords->setHidden(false);
    ui->progressBarWords->setHidden(false);
    goalCap = cap;
}

void DocumentViewer::disableGoal()
{
    ui->labelGoalCap->setHidden(true);
    ui->labelWords->setHidden(true);
    ui->progressBarWords->setHidden(true);
    goalCap = -1;
}

int DocumentViewer::getGoalCap()
{
    return goalCap;
}

QStringList DocumentViewer::getDocumentStructure()
{
    return documentStructureLines;
}

void DocumentViewer::on_progressBarWords_valueChanged(int value)
{
    ui->labelWords->setText(QString::number(ui->progressBarWords->value()));
    if (value == goalCap)
    {
        ui->progressBarWords->setStyleSheet("QProgressBar { width:75px; } QProgressBar::chunk { background-color: green; }");
        if (warnGoalAchieved)
        {
            QMessageBox::information(this,APP_NAME,tr("You have reached the goal. Congratulations!"));
            disableGoal();
        }
    }
    else
        ui->progressBarWords->setStyleSheet("QProgressBar { width:75px; } QProgressBar::chunk { }");
}

void DocumentViewer::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString path =  file->getDirectory()+"/"+file->getFileName().append(".tmp");

    if(synctex_display_query(scanner,path.toStdString().c_str(),file->getLineNumber(documentStructureLines.at(ui->listWidget->currentRow())),-1)>0) {
             synctex_node_t node;
             while((node = synctex_next_result(scanner))) {
                 if (documentStructureLines.at(ui->listWidget->currentRow()).contains(CMD_CHAPTER))
                    showPage(synctex_node_page(node),currentScaleFactor);
                 else
                     showPage(synctex_node_page(node)-1,currentScaleFactor);
                 break;
             }
         }
}
void DocumentViewer::hideDocumentStructureWidget(bool hide)
{
    ui->listWidget->setHidden(hide);
}

void DocumentViewer::setColor()
{
    QColorDialog *colorDialog = new QColorDialog(this);

        QColor selectedColor = colorDialog->getColor();
        QTextCursor cursor = ui->caja->getTextEdit()->textCursor();
        QTextCharFormat fmt;
        if (!cursor.hasSelection())
            cursor.select(QTextCursor::WordUnderCursor);

         fmt.setForeground(selectedColor);
        cursor.mergeCharFormat( fmt );
        ui->caja->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void DocumentViewer::on_listWidget_viewportEntered()
{
    hideTextEdit();
}
