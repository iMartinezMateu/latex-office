#include "writer.h"
#include "ui_writer.h"
#include "lib/assistivetechnologies/timemachine.h"

Writer::Writer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Writer)
{
    ui->setupUi(this);
    QDir().mkdir("./dictionaries/");
    QDir().mkdir("./settings/");
    QDir().mkdir("./themes/");
    QDir().mkdir("./data/");
    QDir().mkdir("./data/timemachine/");
    QDir().mkdir("./data/smartkeys/");
    QDir().mkdir("./data/share/");

    QCoreApplication::translate("MAC_APPLICATION_MENU", "Services");
    QCoreApplication::translate("MAC_APPLICATION_MENU", "Hide %1");
    QCoreApplication::translate("MAC_APPLICATION_MENU", "Hide Others");
    QCoreApplication::translate("MAC_APPLICATION_MENU", "Show All");
    QTranslator *qtTranslator = new QTranslator();
    QTranslator *translator = new QTranslator();
    if (qtTranslator->load("qt_" + QLocale::system().name(), ":/languages")) {
        qApp->installTranslator(translator);
    }
    if (translator->load("writer_" + QLocale::system().name(), ":/languages")) {
        qApp->installTranslator(translator);
    }
    ui->retranslateUi(this);

    ui->secondaryToolBar->setVisible(false);
    file = NULL;
    fillSecondaryToolBar();
    loadStatusBar();

    connect(ui->documentViewer, SIGNAL(textEditAppeared()), this,
            SLOT(showSecondaryToolBar()));
    connect(ui->documentViewer, SIGNAL(textEditDisappeared()), this,
            SLOT(hideSecondaryToolBar()));
    connect(ui->documentViewer, SIGNAL(textEditChanged()), this,
            SLOT(showParagraphWordsCount()));
    if (QFile::exists("settings/pdfcompilerpath.los")) {
        TeXCompiler::loadPDFCompilerPathSettings();
    } else {
        QMessageBox firstRunMessageBox(APP_NAME,
                                       tr("It seems that is the first time you run the program. It is necesary to search where is the compiler path. This process can take a long time but it is mandatory..."),
                                       QMessageBox::Question,
                                       QMessageBox::Yes | QMessageBox::Default,
                                       QMessageBox::No | QMessageBox::Escape,  //This makes "Esc" key to Cancel the Dialog
                                       QMessageBox::NoButton,
                                       this);
        firstRunMessageBox.setButtonText(QMessageBox::Yes, tr("Yes"));
        firstRunMessageBox.setButtonText(QMessageBox::No, tr("No"));



        if (firstRunMessageBox.exec() == QMessageBox::Yes) {
            QString pdfPath = TeXCompiler::searchCompilerBinary();
            QString bibPath = TeXCompiler::searchBiBTeXBinary();
            QString txtPath = TeXCompiler::searchTXTConverterBinary();
            QString htmlPath = TeXCompiler::searchHTMLConverterBinary();
            QString rtfPath = TeXCompiler::searchRTFConverterBinary();
            TeXCompiler::savePDFCompilerPathSettings(pdfPath);
            TeXCompiler::saveBIBCompilerPathSettings(bibPath);
            TeXCompiler::saveRTFConverterPathSettings(rtfPath);
            TeXCompiler::saveTXTConverterPathSettings(txtPath);
            TeXCompiler::saveHTMLConverterPathSettings(htmlPath);
            if (pdfPath.isEmpty() || bibPath.isEmpty()) {
                QMessageBox messageBox(APP_NAME,
                                       tr("LaTeX Office was unable to find a valid compiler. Check that your LaTeX distribution is correctly installed and try again. Do you want to type the path manually?"),
                                       QMessageBox::Question,
                                       QMessageBox::Yes | QMessageBox::Default,
                                       QMessageBox::No | QMessageBox::Escape,  //This makes "Esc" key to Cancel the Dialog
                                       QMessageBox::NoButton,
                                       this);
                messageBox.setButtonText(QMessageBox::Yes, tr("Yes"));
                messageBox.setButtonText(QMessageBox::No, tr("No"));


                if (messageBox.exec() == QMessageBox::Yes) {
                    Dialog_CompilerSettings *dialog = new Dialog_CompilerSettings();
                    dialog->exec(); //Blocks input to parent window until current dialog has been finished
                } else {
                    QApplication::quit();
                }
            }
        } else {
            QApplication::quit();
        }
    }



}
void Writer::closeEvent(QCloseEvent *event)
{
    ui->documentViewer->hideTextEdit();

    QMessageBox messageBox(APP_NAME,
                           tr("Do you want to close LaTeX Office Writer? All unsaved changes will be lost! \n"),
                           QMessageBox::Question,
                           QMessageBox::Yes | QMessageBox::Default,
                           QMessageBox::No | QMessageBox::Escape,  //This makes "Esc" key to Cancel the Dialog
                           QMessageBox::NoButton,
                           this);
    messageBox.setButtonText(QMessageBox::Yes, tr("Yes"));
    messageBox.setButtonText(QMessageBox::No, tr("No"));
    if (oriFileName.isEmpty() || oriFileName == NULL) {
        QApplication::closeAllWindows();
        QApplication::exit(1);
    }
    if (messageBox.exec() == QMessageBox::No) {
        event->ignore();
    } else {
        if (!oriFileName.isEmpty()) {
            TimeMachine::stopTimeMachine("data/timemachine/" + file->getFileName().append(".tmf"));
            ui->documentViewer->closeDocument();
            QFile::remove(QFileInfo(oriFileName).absolutePath() + "/" + QFileInfo(
                              oriFileName).baseName().append(".tmp"));
            file->close();
        }
        event->accept();

    }

}

void Writer::showSecondaryToolBar()
{
        ui->secondaryToolBar->setEnabled(true);
        ui->actionCut->setEnabled(true);
        ui->actionCopy->setEnabled(true);
        ui->actionPaste->setEnabled(true);
        ui->actionPicture->setEnabled(true);
        ui->actionTable->setEnabled(true);
        ui->actionCode_Asset->setEnabled(true);
        ui->actionEquation->setEnabled(true);

}
void Writer::hideSecondaryToolBar()
{
        ui->secondaryToolBar->setEnabled(false);
        ui->actionCut->setEnabled(false);
        ui->actionCopy->setEnabled(false);
        ui->actionPaste->setEnabled(false);
        ui->actionPicture->setEnabled(false);
        ui->actionTable->setEnabled(false);
        ui->actionCode_Asset->setEnabled(false);
        ui->actionEquation->setEnabled(false);

}

void Writer::fillSecondaryToolBar()
{
    fontSizeComboBox = new QComboBox;
    fontSizeComboBox->setEnabled(false);
    fontSizeComboBox->addItem(tr("Tiny"));
    fontSizeComboBox->addItem(tr("Small"));
    fontSizeComboBox->addItem(tr("Normal"));
    fontSizeComboBox->addItem(tr("Large"));
    fontSizeComboBox->addItem(tr("Huge"));
    fontSizeComboBox->setCurrentIndex(2);
    ui->secondaryToolBar->addWidget(fontSizeComboBox);
    connect(fontSizeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeSize()));
    ui->secondaryToolBar->addSeparator();
    ui->secondaryToolBar->addAction(ui->actionBold);
    connect(ui->actionBold, SIGNAL(triggered()), ui->documentViewer, SLOT(setTextBold()));
    ui->secondaryToolBar->addAction(ui->actionItalic);
    connect(ui->actionItalic, SIGNAL(triggered()), ui->documentViewer,
            SLOT(setTextItalics()));
    ui->secondaryToolBar->addAction(ui->actionUnderline);
    connect(ui->actionUnderline, SIGNAL(triggered()), ui->documentViewer,
            SLOT(setTextUnderline()));
    ui->secondaryToolBar->addAction(ui->actionStrikeThrough);
    connect(ui->actionStrikeThrough, SIGNAL(triggered()), ui->documentViewer,
            SLOT(setTextStrikethrough()));
    ui->secondaryToolBar->addAction(ui->actionSmall_Caps);
    connect(ui->actionSmall_Caps, SIGNAL(triggered()), ui->documentViewer,
            SLOT(setTextSmallCaps()));
    ui->secondaryToolBar->addAction(ui->actionEmphatize);
    connect(ui->actionEmphatize, SIGNAL(triggered()), ui->documentViewer,
            SLOT(setTextEmphatize()));

    ui->secondaryToolBar->addAction(ui->actionHyperlink);
    connect(ui->actionHyperlink, SIGNAL(triggered()), ui->documentViewer,
            SLOT(setTextHyperlink()));
    ui->secondaryToolBar->addAction(ui->actionFootnote);
    connect(ui->actionFootnote, SIGNAL(triggered()), ui->documentViewer,
            SLOT(setTextFootnote()));
    ui->secondaryToolBar->addSeparator();
    ui->secondaryToolBar->addAction(ui->actionJustify);
    connect(ui->actionJustify, SIGNAL(triggered()), ui->documentViewer,
            SLOT(setTextJustify()));
    ui->secondaryToolBar->addAction(ui->actionCenter_Align);
    connect(ui->actionCenter_Align, SIGNAL(triggered()), ui->documentViewer,
            SLOT(setTextCenterAlign()));
    ui->secondaryToolBar->addAction(ui->actionRight_Align);
    connect(ui->actionRight_Align, SIGNAL(triggered()), ui->documentViewer,
            SLOT(setTextRightAlign()));
    ui->secondaryToolBar->addSeparator();
    ui->secondaryToolBar->addAction(ui->actionItemize_List);
    connect(ui->actionItemize_List, SIGNAL(triggered()), ui->documentViewer,
            SLOT(setBulletList()));
    ui->secondaryToolBar->addAction(ui->actionEnumerate_List);
    connect(ui->actionEnumerate_List, SIGNAL(triggered()), ui->documentViewer,
            SLOT(setNumberedList()));
    ui->secondaryToolBar->addSeparator();
    ui->secondaryToolBar->addAction(ui->actionSymbol);
    ui->secondaryToolBar->addAction(ui->actionCite);
    ui->secondaryToolBar->addAction(ui->actionReference);
    connect(ui->actionSymbol, SIGNAL(triggered()), ui->documentViewer, SLOT(setSymbol()));
    connect(ui->actionCite, SIGNAL(triggered()), ui->documentViewer, SLOT(setCite()));
    connect(ui->actionReference, SIGNAL(triggered()), ui->documentViewer, SLOT(setReference()));
    connect(ui->documentViewer, SIGNAL(selectedTextAttributes(int, QString)), this,
            SLOT(updateTextAttributes(int, QString)));
}
Writer::~Writer()
{
    delete ui;
}

void Writer::updateTextAttributes(int fontSize, QString headingStyle)
{
    switch (fontSize) {
    case 7:
        fontSizeComboBox->setCurrentIndex(0);
        break;
    case 10:
        fontSizeComboBox->setCurrentIndex(1);
        break;
    case 13:
        fontSizeComboBox->setCurrentIndex(2);
        break;
    case 15:
        fontSizeComboBox->setCurrentIndex(3);
        break;
    case 18:
        fontSizeComboBox->setCurrentIndex(4);
        break;
    default:
        fontSizeComboBox->setCurrentIndex(2);
        break;
    }

}

void Writer::changeSize()
{
    switch (fontSizeComboBox->currentIndex()) {
    case 0: //tiny
        ui->documentViewer->setTextTiny();
        break;
    case 1: //small
        ui->documentViewer->setTextSmall();
        break;
    case 2: //normal
        ui->documentViewer->setTextNormal();
        break;
    case 3: //large
        ui->documentViewer->setTextLarge();
        break;
    case 4: //huge
        ui->documentViewer->setTextHuge();
        break;

    }
}
void Writer::showParagraphWordsCount()
{
    if (ui->documentViewer->getParagraphWordCount() > 0) {
        ui->statusBar->showMessage(QString::number(ui->documentViewer->getParagraphWordCount()) +
                                   tr(" words in this paragraph."), 5000);
    }
}

void Writer::openDocument(QString fileName)
{
    ui->documentViewer->hideTextEdit();

    if (!QFile(TeXCompiler::loadPDFCompilerPathSettings()).exists()) {
        QMessageBox::critical(this, APP_NAME,
                              tr("Compiler binary was not found at the configured path. You cannot open a document."),
                              QMessageBox::Ok);
    } else {
        if (file == NULL) {
            if (!fileName.isEmpty()) {

                QFile *newFile = new QFile(fileName);
                if (fileName.endsWith(".ltex")) {
                    Dialog_DocumentUnlock *dialog = new Dialog_DocumentUnlock(newFile);
                    dialog->exec();
                    if (dialog->getUnlockedFile()) {
                        newFile->close();
                        newFile->remove();
                        fileName = QFileInfo(fileName).absolutePath() + "/" + QFileInfo(
                                       fileName).baseName().append(".tex");
                        newFile = new QFile(fileName);
                    } else {
                        return;
                    }
                }
                if (fileName.endsWith(".lop"))
                {
                    unpackDocument(fileName);
                    QStringList nameFilter("*.tex");
                    QDir searchDirectory(QFileInfo(fileName).absolutePath() + "/" + QFileInfo(fileName).baseName());
                    QStringList texFiles = searchDirectory.entryList(nameFilter);

                    fileName = QFileInfo(fileName).absolutePath() + "/" + QFileInfo(fileName).baseName() + "/" + texFiles.at(0);
                }
                if (fileName.endsWith(".tex")) {
                    Dialog_Loading *dialog = new Dialog_Loading();
                    dialog->setProgressBarValue(0);
                    dialog->show();

                    newFile->open(QIODevice::WriteOnly | QIODevice::Append);
                    if (newFile->pos() < 15) {
                        QMessageBox::critical(this, APP_NAME,
                                              tr("The file is currently empty and it cannot be opened with LaTeX Office Writer"),
                                              QMessageBox::Ok);
                    } else {

                        if (QFile(QFileInfo(fileName).absolutePath() + "/" + QFileInfo(
                                      fileName).baseName().append(".tmp")).exists()) {
                            QMessageBox messageBox(APP_NAME,
                                                   tr("An autosave file is available. It seems that the previous document you were editing was not saved correctly. Do you want to recover the last changes comitted to the document?"),
                                                   QMessageBox::Question,
                                                   QMessageBox::Yes | QMessageBox::Default,
                                                   QMessageBox::No | QMessageBox::Escape,  //This makes "Esc" key to Cancel the Dialog
                                                   QMessageBox::NoButton,
                                                   this);

                            messageBox.setButtonText(QMessageBox::Yes, tr("Yes"));
                            messageBox.setButtonText(QMessageBox::No, tr("No"));

                            if (messageBox.exec() == QMessageBox::Yes) {
                                QFile(fileName).copy(QFileInfo(fileName).absolutePath() + "/backup-" + QFileInfo(
                                                         fileName).baseName().append(".tex"));
                                QFile tmpFile(QFileInfo(fileName).absolutePath() + "/" + QFileInfo(
                                                  fileName).baseName().append(".tmp"));
                                QFile(fileName).remove();
                                tmpFile.copy(fileName);
                            }
                        }
                        dialog->setProgressBarValue(10);
                        oriFileName = fileName;

                        QFile cpyFileName(QFileInfo(fileName).absolutePath() + "/" + QFileInfo(
                                              fileName).baseName().append(".tmp"));
                        if (cpyFileName.exists()) {
                            cpyFileName.remove();
                        }
                        QFile(fileName).copy(QFileInfo(fileName).absolutePath() + "/" + QFileInfo(
                                                 fileName).baseName().append(".tmp"));

                        file = new TeXFile(QFileInfo(cpyFileName).absoluteFilePath(), true);

                        if (QFile(QFileInfo(fileName).absolutePath() + "/" + file->getCLSFile()).exists()) {
                            QFile(QFileInfo(fileName).absolutePath() + "/" + file->getCLSFile()).copy(
                                file->getCLSFile());
                        }

                        if (QFile(QFileInfo(fileName).absolutePath() + "/" + file->getSTYFile()).exists()) {
                            QFile(QFileInfo(fileName).absolutePath() + "/" + file->getSTYFile()).copy(
                                file->getSTYFile());
                        }
                        file->deprecompile();
                        dialog->setProgressBarValue(15);
                        if (file->getPackage(PACK_HYPERREF) != -1) {
                            file->deleteTeXCommand(file->getPackage(PACK_HYPERREF));
                            file->saveFile();
                        }
                        dialog->setProgressBarValue(30);
                        if (file->getPackage(PACK_LISTINGS) == -1) {
                            file->setPackage(PACK_LISTINGS);
                            file->saveFile();
                        }
                        if (file->getPackage(PACK_XCOLOR,"table,xcdraw") == -1) {
                            file->setPackage(PACK_XCOLOR,"table,xcdraw");
                            file->saveFile();
                        }
                        if (file->getPackage(PACK_HYPERREF, "hidelinks") == -1) {
                            file->setPackage(PACK_HYPERREF, "hidelinks");
                            file->saveFile();
                        }
                        if (file->getPackage(PACK_GRAPHICX) == -1) {
                            file->setPackage(PACK_GRAPHICX);
                            file->saveFile();
                        }
                        dialog->setProgressBarValue(55);
                        if (file->getPackage(PACK_GRFFILE, "space") == -1) {
                            file->setPackage(PACK_GRFFILE, "space");
                            file->saveFile();
                        }
                        if (file->getPackage(PACK_AMSSYMB) == -1) {
                            file->setPackage(PACK_AMSSYMB);
                            file->saveFile();
                        }
                        if (file->getPackage(PACK_EUROSYM) == -1) {
                            file->setPackage(PACK_EUROSYM);
                            file->saveFile();
                        }
                        if (file->getPackage(PACK_WASYSYM) == -1) {
                            file->setPackage(PACK_WASYSYM);
                            file->saveFile();
                        }

                        if (!file->getFileName().contains(' '))
                            file->precompile(TeXCompiler::loadPDFCompilerPathSettings());
                        {
                            dialog->setProgressBarValue(60);
                        }
                        if (QFile(file->getDirectory() + "/" + file->getFileName() + ".bib").exists()) {
                            bibFile = new TeXBibliography(file->getDirectory() + "/" + file->getFileName() + ".bib");
                            bibFile->saveFile();
                            dialog->setProgressBarValue(65);
                            file->compile(TeXCompiler::loadPDFCompilerPathSettings());
                            bibFile->compile(TeXCompiler::loadBIBCompilerPathSettings());
                        } else {
                            bibFile = new TeXBibliography(file->getDirectory() + "/" + file->getFileName() + ".bib");
                        }
                        file->fixImagePaths();
                        file->compile(TeXCompiler::loadPDFCompilerPathSettings());
                        dialog->setProgressBarValue(85);
                        file->compile(
                            TeXCompiler::loadPDFCompilerPathSettings()); //Compile two times to get table of contents...
                        dialog->setProgressBarValue(100);
                        dialog->accept();
                        if (!QFile(file->getFileName() + ".pdf").exists()) {
                            QMessageBox messageBox(APP_NAME,
                                                   tr("The document you wish to open in LaTeX Office Writer is not fully compatible. Edit it with some plain text editor and try again. Do you want to open the log file?"),
                                                   QMessageBox::Question,
                                                   QMessageBox::Yes | QMessageBox::Default,
                                                   QMessageBox::No | QMessageBox::Escape,  //This makes "Esc" key to Cancel the Dialog
                                                   QMessageBox::NoButton,
                                                   this);
                            messageBox.setButtonText(QMessageBox::Yes, tr("Yes"));
                            messageBox.setButtonText(QMessageBox::No, tr("No"));


                            if (messageBox.exec() == QMessageBox::Yes) {
                                Dialog_Log *dialog = new Dialog_Log();
                                QFile logFile(file->getFileName() + ".log");
                                QFile texLogFile("texput.log");
                                dialog->setData(&logFile, &texLogFile);
                                dialog->exec(); //Blocks input to parent window until current dialog has been finished
                            }
                            ui->documentViewer->closeDocument();
                            file->close();
                            QFile::remove(QFileInfo(oriFileName).absolutePath() + "/" + QFileInfo(
                                              oriFileName).baseName().append(".tmp"));
                            disableFunctions();
                            QWidget::setWindowTitle(APP_NAME);
                            file = NULL;
                            oriFileName = "";
                            return;
                        } else {
                            this->cpyFileName = QFileInfo(cpyFileName).absoluteFilePath();

                            ui->documentViewer->loadTeXFile(file);
                            if (bibFile) {
                                ui->documentViewer->loadBiBFile(bibFile);
                            }
                            enableFunctions();
                            QWidget::setWindowTitle(QString(APP_NAME) + " <" + fileName + ">");
                            ui->documentViewer->loadDocument(QFileInfo(fileName).baseName() + ".pdf");
                            connect(file, SIGNAL(documentCompiled()), this, SLOT(setModifiedStatus()));
                            connect(file, SIGNAL(documentCompiled()), this, SLOT(checkModifiedStatus()));
                            ui->actionUnpackage_Document->setEnabled(false);
                            pdfCompilerPath = TeXCompiler::loadPDFCompilerPathSettings();
                            bibCompilerPath = TeXCompiler::loadBIBCompilerPathSettings();
                            loadDictionary();
                            QDir timeMachineDir("data/timemachine");
                            if (!timeMachineDir.exists()) {
                                timeMachineDir.mkpath(".");
                            }
                            TimeMachine::newTimeMachine("data/timemachine/" + file->getFileName().append(".tmf"),
                                                        file, BACKUP_TIME);
                            if (currentDictionary.isEmpty()) {
                                QMessageBox::critical(this, APP_NAME,
                                                      tr("A dictionary file was not configured. The Spell Check functionality will be disabled until you configure one dictionary."));
                            }
                        }
                    }
                }
            }
        }
    }
}

void Writer::on_actionOpen_triggered()
{
    if (file != NULL) {
        on_actionClose_triggered();
    }
    if (file == NULL) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "",
                                                        tr("TeX File (*.tex *.ltex *.lop)"));
        if (fileName != NULL) {
            openDocument(fileName);
        }
    }
}
void Writer::on_actionClose_triggered()
{
    if (file != NULL) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(APP_NAME);
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setText(
            tr("Do you want to close the current document? All unsaved changes will be lost!"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setButtonText(QMessageBox::Yes, tr("Yes"));
        msgBox.setButtonText(QMessageBox::No, tr("No"));
        msgBox.setDefaultButton(QMessageBox::No);
        if (msgBox.exec() == QMessageBox::Yes) {
            ui->actionUnpackage_Document->setEnabled(true);
            TimeMachine::stopTimeMachine("data/timemachine/" + file->getFileName().append(".tmf"));
            ui->documentViewer->hideTextEdit();
            ui->documentViewer->closeDocument();
            ui->documentViewer->setHidden(true);
            file->close();
            QFile::remove(QFileInfo(oriFileName).absolutePath() + "/" + QFileInfo(
                              oriFileName).baseName().append(".tmp"));
            disableFunctions();
            QWidget::setWindowTitle(APP_NAME);
            file = NULL;
            bibFile = NULL;
            oriFileName = "";
        }
    }
}
void Writer::on_actionExit_triggered()
{
    this->close();
}
void Writer::on_actionSave_triggered()
{
    file->deprecompile();
    file->saveFile();
    file->saveFile(oriFileName);
    hasFileChanged = false;
    checkModifiedStatus();
    ui->documentViewer->hideTextEdit();
}

void Writer::disableStyleFunctions()
{
    ui->actionBold->setEnabled(false);
    ui->actionItalic->setEnabled(false);
    ui->actionUnderline->setEnabled(false);
    ui->actionCenter_Align->setEnabled(false);
    ui->actionRight_Align->setEnabled(false);
    ui->actionJustify->setEnabled(false);
    ui->actionSmall_Caps->setEnabled(false);
    ui->actionStrikeThrough->setEnabled(false);
    fontSizeComboBox->setEnabled(false);
    ui->actionEmphatize->setEnabled(false);
    ui->actionEnumerate_List->setEnabled(false);
    ui->actionItemize_List->setEnabled(false);
    ui->actionHyperlink->setEnabled(false);
    ui->actionFootnote->setEnabled(false);
}

void Writer::enableStyleFunctions()
{
    ui->actionBold->setEnabled(true);
    ui->actionItalic->setEnabled(true);
    ui->actionUnderline->setEnabled(true);
    ui->actionCenter_Align->setEnabled(true);
    ui->actionRight_Align->setEnabled(true);
    ui->actionJustify->setEnabled(true);
    ui->actionSmall_Caps->setEnabled(true);
    ui->actionStrikeThrough->setEnabled(true);
    fontSizeComboBox->setEnabled(true);
    ui->actionEmphatize->setEnabled(true);
    ui->actionEnumerate_List->setEnabled(true);
    ui->actionItemize_List->setEnabled(true);
    ui->actionHyperlink->setEnabled(true);
    ui->actionFootnote->setEnabled(true);
}


void Writer::disableFunctions()
{
    ui->actionClose->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionSave_As->setEnabled(false);
    ui->actionSymbol->setEnabled(false);
    ui->actionCite->setEnabled(false);
    ui->actionDocument_Preamble->setEnabled(false);
    ui->actionPDF_file->setEnabled(false);
    ui->actionFind->setEnabled(false);
    ui->actionBold->setEnabled(false);
    ui->actionItalic->setEnabled(false);
    ui->actionUnderline->setEnabled(false);
    ui->actionCenter_Align->setEnabled(false);
    ui->actionRight_Align->setEnabled(false);
    ui->actionJustify->setEnabled(false);
    ui->actionSmall_Caps->setEnabled(false);
    ui->actionStrikeThrough->setEnabled(false);
    ui->actionBreak->setEnabled(false);
    ui->actionEnumerate_List->setEnabled(false);
    ui->actionItemize_List->setEnabled(false);
    ui->actionEmphatize->setEnabled(false);
    fontSizeComboBox->setEnabled(false);
    ui->actionPackage_Document->setEnabled(false);
    ui->actionChapter->setEnabled(false);
    ui->actionSection->setEnabled(false);
    ui->actionSub_Section->setEnabled(false);
    ui->actionSub_Sub_Section->setEnabled(false);
    ui->actionParagraph->setEnabled(false);
    ui->actionTable_of_Contents->setEnabled(false);
    ui->actionTable_of_Contents->setChecked(false);
    ui->actionBibliography->setEnabled(false);
    ui->actionBibliography->setChecked(false);
    ui->actionList_of_Figures->setEnabled(false);
    ui->actionList_of_Figures->setChecked(false);
    ui->actionList_of_Tables->setEnabled(false);
    ui->actionList_of_Tables->setChecked(false);
    ui->actionPrint_Preview->setEnabled(false);
    ui->actionPrint->setEnabled(false);
    ui->actionHyperlink->setEnabled(false);
    ui->actionPlain_Text->setEnabled(false);
    ui->actionWeb_Archive->setEnabled(false);
    ui->actionRTF_File->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->actionFootnote->setEnabled(false);
    ui->actionBibliography_Manager->setEnabled(false);
    ui->actionSpelling->setEnabled(false);
    ui->actionGoal->setEnabled(false);
    ui->actionTime_Machine->setEnabled(false);
    ui->actionDocument_Lock->setEnabled(false);
    ui->actionHide_Document_Structure_List->setEnabled(false);
    ui->actionHide_Primary_Toolbar->setEnabled(false);
    ui->actionHide_Secondary_Toolbar->setEnabled(false);
    ui->actionShow_LaTeX_Code->setEnabled(false);
    ui->actionCopy_Protect->setEnabled(false);
    ui->actionFonts->setEnabled(false);

}
void Writer::enableFunctions()
{
    ui->actionClose->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionSave_As->setEnabled(true);
    ui->actionSymbol->setEnabled(true);
    ui->actionCite->setEnabled(true);
    ui->actionDocument_Preamble->setEnabled(true);
    ui->actionPDF_file->setEnabled(true);
    ui->actionPlain_Text->setEnabled(true);
    ui->actionWeb_Archive->setEnabled(true);
    ui->actionFind->setEnabled(true);
    ui->actionBreak->setEnabled(true);
    ui->actionBold->setEnabled(true);
    ui->actionItalic->setEnabled(true);
    ui->actionUnderline->setEnabled(true);
    ui->actionCenter_Align->setEnabled(true);
    ui->actionRight_Align->setEnabled(true);
    ui->actionJustify->setEnabled(true);
    ui->actionSmall_Caps->setEnabled(true);
    ui->actionStrikeThrough->setEnabled(true);
    ui->actionEmphatize->setEnabled(true);
    fontSizeComboBox->setEnabled(true);
    ui->actionPackage_Document->setEnabled(true);
    ui->actionChapter->setEnabled(true);
    ui->actionSection->setEnabled(true);
    ui->actionSub_Section->setEnabled(true);
    ui->actionSub_Sub_Section->setEnabled(true);
    ui->actionParagraph->setEnabled(true);
    ui->actionTable_of_Contents->setEnabled(true);
    ui->actionList_of_Figures->setEnabled(true);
    ui->actionList_of_Tables->setEnabled(true);
    ui->actionEnumerate_List->setEnabled(true);
    ui->actionItemize_List->setEnabled(true);
    ui->actionBibliography->setEnabled(true);
    int bibliographyLine = file->getLineNumber(CMD_BIBLIOGRAPHY);
    if (bibliographyLine != -1) {
        ui->actionBibliography->setChecked(true);
    }
    int tableOfContentsLine = file->getLineNumber(command.callTableOfContents());
    if (tableOfContentsLine != -1) {
        ui->actionTable_of_Contents->setChecked(true);
    }
    int listOfFiguresLine = file->getLineNumber(command.callListOfFigures());
    if (listOfFiguresLine != -1) {
        ui->actionList_of_Figures->setChecked(true);
    }
    int listOfTablessLine = file->getLineNumber(command.callListOfTables());
    if (listOfTablessLine != -1) {
        ui->actionList_of_Tables->setChecked(true);
    }
    ui->actionPrint_Preview->setEnabled(true);
    ui->actionPrint->setEnabled(true);
    ui->actionHyperlink->setEnabled(true);
    ui->actionFootnote->setEnabled(true);
    ui->actionRTF_File->setEnabled(true);
    ui->actionBibliography_Manager->setEnabled(true);
    ui->actionGoal->setEnabled(true);
    ui->actionTime_Machine->setEnabled(true);
    ui->actionDocument_Lock->setEnabled(true);
    ui->actionHide_Document_Structure_List->setEnabled(true);
    ui->actionHide_Primary_Toolbar->setEnabled(true);
    ui->actionHide_Secondary_Toolbar->setEnabled(true);
    ui->actionShow_LaTeX_Code->setEnabled(true);
    ui->actionCopy_Protect->setEnabled(true);
    ui->actionFonts->setEnabled(true);

}
void Writer::setModifiedStatus()
{
    hasFileChanged = true;
}
void Writer::checkModifiedStatus()
{
    if (hasFileChanged && !windowTitle().contains(tr("Modified"))) {
        ui->actionRedo->setEnabled(false);
        ui->actionUndo->setEnabled(true);
        QWidget::setWindowTitle(windowTitle().append(" - " + tr("Modified")));
    } else if (!hasFileChanged) {
        ui->actionRedo->setEnabled(false);
        ui->actionUndo->setEnabled(false);
        if (!oriFileName.isEmpty()) {
            QWidget::setWindowTitle(QString(APP_NAME) + " <" + oriFileName + ">");
        }
    }

}
void Writer::loadStatusBar()
{
    ui->actionAbout_LaTeX_Office_Writer->setStatusTip(
        tr("Show some relevant information about the program"));
    ui->actionBold->setStatusTip(tr("Set text to bold"));
    ui->actionBreak->setStatusTip(tr("Add a page break on the selected position"));
    ui->actionCenter_Align->setStatusTip(
        tr("Align text and items to the center of the document"));
    ui->actionClose->setStatusTip(tr("Close the current document"));
    ui->actionCopy->setStatusTip(tr("Copy selected text or item and store it to clipboard"));
    ui->actionCut->setStatusTip(tr("Cut selected text or item and store it to clipboard"));
    ui->actionDocument_Setup->setStatusTip(
        tr("Configure some settings regarding to document layout"));
    ui->actionEmphatize->setStatusTip(tr("Emphatize text"));
    ui->actionEnumerate_List->setStatusTip(
        tr("Add a enumerate list from one to infinite elements"));
    ui->actionEquation->setStatusTip(tr("Add an equation on the selected position"));
    ui->actionExit->setStatusTip(
        tr("Exit LaTeX Office Writer. All unsaved changes will be lost!"));
    ui->actionPDF_file->setStatusTip(tr("Export current document to a PDF file"));
    ui->actionPlain_Text->setStatusTip(tr("Export current document to a plain file"));
    ui->actionWord_Document->setStatusTip(
        tr("Export current document to a propietary compatible file"));
    ui->actionWeb_Archive->setStatusTip(tr("Export current document to a XHTML webpage"));
    ui->actionRTF_File->setStatusTip(tr("Export current document to a RTF file"));
    ui->actionFind->setStatusTip(tr("Find text from current document"));
    ui->actionFootnote->setStatusTip(tr("Add a footnote on the selected position"));
    ui->actionHyperlink->setStatusTip(tr("Add a hyperlink on the selected position"));
    ui->actionItalic->setStatusTip(tr("Set text to italic"));
    ui->actionItemize_List->setStatusTip(
        tr("Add a itemize list from one to infinite elements"));
    ui->actionJustify->setStatusTip(tr("Justify text and items"));
    ui->actionLaTeX_Office_on_the_Web->setStatusTip(
        tr("Open the browser to watch the project webpage"));
    ui->actionLaTeX_Office_Writer_Help->setStatusTip(tr("Open user manual"));
    ui->actionNew->setStatusTip(tr("Create a new document"));
    ui->actionOpen->setStatusTip(tr("Open an existing file"));
    ui->actionPaste->setStatusTip(
        tr("Paste to the selected position the element stored in the clipboard"));
    ui->actionPicture->setStatusTip(tr("Add a picture on the selected position"));
    ui->actionPrint->setStatusTip(tr("Print document"));
    ui->actionPrint_Preview->setStatusTip(tr("Preview the document before printing"));
    ui->actionRedo->setStatusTip(tr("Redo subsequent action"));
    ui->actionRight_Align->setStatusTip(
        tr("Align text and items to the right of the document"));
    ui->actionSave->setStatusTip(tr("Save document"));
    ui->actionSave_As->setStatusTip(tr("Save document to another directory"));
    ui->actionSmall_Caps->setStatusTip(tr("Change text to appear as small caps"));
    ui->actionSpelling->setStatusTip(tr("Check spelling and grammar"));
    ui->actionStrikeThrough->setStatusTip(tr("Strikethrough text"));
    ui->actionSymbol->setStatusTip(tr("Add a symbol on the selected position"));
    ui->actionCite->setStatusTip(tr("Add a cite notation"));
    ui->actionTable->setStatusTip(tr("Add a table on the selected position"));
    ui->actionUnderline->setStatusTip(tr("Underline text"));
    ui->actionUndo->setStatusTip(tr("Undo previous action"));
    ui->actionChapter->setStatusTip(tr("Add a new chapter"));
    ui->actionSection->setStatusTip(tr("Add a new section"));
    ui->actionSub_Section->setStatusTip(tr("Add a new sub section"));
    ui->actionSub_Sub_Section->setStatusTip(tr("Add a new sub subsection"));
    ui->actionPackage_Document->setStatusTip(
        tr("Package the document itself and its auxiliary files and compress them"));
    ui->actionUnpackage_Document->setStatusTip(
        tr("Unpackage a document and place it somewhere"));
    ui->actionParagraph->setStatusTip(tr("Add a new paragraph"));
    ui->actionTable_of_Contents->setStatusTip(
        tr("Enable or disable a table of contents that will be updated automatically when new content is being added."));
    ui->actionList_of_Figures->setStatusTip(
        tr("Enable or disable a list of figures that will be updated automatically when new content is being added."));
    ui->actionList_of_Tables->setStatusTip(
        tr("Enable or disable a list of tables that will be updated automatically when new content is being added."));
    ui->actionBibliography_Manager->setStatusTip(
        tr("Modify the bibliography associated with this document."));
    ui->actionBibliography->setStatusTip(tr("Enable or disable the bibliography view"));
    ui->actionDictionary_Settings->setStatusTip(
        tr("Configure some dictionary paths in order to use the grammar check functionality"));
    ui->actionGoal->setStatusTip(
        tr("Set a goal to motivate yourself, so you can work better"));
    ui->actionDocument_Lock->setStatusTip(
        tr("Lock the document with a password, so unauthorized people cannot read it"));
    ui->actionCode_Asset->setStatusTip(
        tr("Insert pieces of programming language code directly to the document"));
    ui->actionSmartKeys->setStatusTip(
        tr("Type faster using abbreviations that will turn automatically what you wanted to write. "));
    ui->actionTheme_Settings->setStatusTip(tr("Customize the application appearance."));
    ui->actionMinimize_window->setStatusTip(tr("Minimize current window"));
    ui->actionFull_Screen->setStatusTip(tr("Show current window in full screen."));
    ui->actionMaximize->setStatusTip(tr("Maximize current window"));
    ui->actionMinimize_Screen->setStatusTip(tr("Show current window in a minimized screen"));
    ui->actionHide_Document_Structure_List->setStatusTip(
        tr("Hide the document structure list on the left."));
    ui->actionHide_Primary_Toolbar->setStatusTip(tr("Hide the primary toolbar."));
    ui->actionHide_Secondary_Toolbar->setStatusTip(tr("Hide the secondary toolbar."));
    ui->actionShow_LaTeX_Code->setStatusTip(tr("Show current document code."));
    ui->actionFonts->setStatusTip(
        tr("Configure the fonts used by the current document."));
    ui->actionCopy_Protect->setStatusTip("Generates a PDF file with the copy protection enabled.");
}
void Writer::on_actionPDF_file_triggered()
{
    if (hasFileChanged == true) {
        QMessageBox::critical(this, APP_NAME,
                              tr("You must save the document before exporting to PDF!"));
    } else {
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("LaTeX Office Writer"), file->getDirectory(),
                                                        tr("Portable Document File (*.pdf)"));
        if (fileName != NULL) {
            if (!fileName.endsWith(".pdf")) {
                fileName.append(".pdf");
            }
            QFile::copy(file->getFileName() + ".pdf", fileName);
            QMessageBox::information(this, APP_NAME,
                                     tr("PDF file exported to directory ") + fileName);
        }
    }
}
void Writer::on_actionRTF_File_triggered()
{
    QString rtfConverterPath = TeXCompiler::loadRTFConverterPathSettings();
    if (rtfConverterPath.isEmpty()) {
        QMessageBox::critical(this, APP_NAME,
                              tr("You have to configure the converter binary path before exporting."));
        Dialog_CompilerSettings *dialog = new Dialog_CompilerSettings();
        dialog->exec(); //Blocks input to parent window until current dialog has been finished
        return;
    }

    if (hasFileChanged == true) {
        QMessageBox::critical(this, APP_NAME,
                              tr("You must save the document before exporting to RTF!"));
    } else {
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("LaTeX Office Writer"), file->getDirectory(),
                                                        tr("Rich Text File (*.rtf)"));
        if (fileName != NULL) {

            file->convertToRTF(rtfConverterPath);

            if (!fileName.endsWith(".rtf")) {
                fileName.append(".rtf");
            }
            QFile::copy(file->getFileName() + ".rtf", fileName);
            QMessageBox::information(this, APP_NAME,
                                     tr("Rich text file exported to directory ") + fileName);
        }
    }
}

void Writer::on_actionPlain_Text_triggered()
{
    QString txtConverterPath = TeXCompiler::loadTXTConverterPathSettings();
    ui->documentViewer->hideTextEdit();

    if (txtConverterPath.isEmpty()) {
        QMessageBox::critical(this, APP_NAME,
                              tr("You have to configure the converter binary path before exporting."));
        Dialog_CompilerSettings *dialog = new Dialog_CompilerSettings();
        dialog->exec(); //Blocks input to parent window until current dialog has been finished

        return;


    }

    if (hasFileChanged == true) {
        QMessageBox::critical(this, APP_NAME,
                              tr("You must save the document before exporting to plain text!"));
    } else {
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("LaTeX Office Writer"), file->getDirectory(),
                                                        tr("Plain Text File (*.txt)"));
        if (fileName != NULL) {

            file->convertToPlainText(txtConverterPath);

            if (!fileName.endsWith(".txt")) {
                fileName.append(".txt");
            }
            QFile::copy(file->getFileName() + ".txt", fileName);
            QMessageBox::information(this, APP_NAME,
                                     tr("Plain text file exported to directory ") + fileName);
        }

    }
}
void Writer::on_actionWeb_Archive_triggered()
{
    QString htmlConverterPath = TeXCompiler::loadHTMLConverterPathSettings();
    ui->documentViewer->hideTextEdit();

    if (htmlConverterPath.isEmpty()) {
        QMessageBox::critical(this, APP_NAME,
                              tr("You have to configure the converter binary path before exporting."));
        Dialog_CompilerSettings *dialog = new Dialog_CompilerSettings();
        dialog->exec(); //Blocks input to parent window until current dialog has been finished
        return;

    }
    if (hasFileChanged == true) {
        QMessageBox::critical(this, APP_NAME,
                              tr("You must save the document before exporting to a web archive!"));
    } else {
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("LaTeX Office Writer"), file->getDirectory(),
                                                        tr("HTML File (*.html)"));
        if (fileName != NULL) {
            file->convertToHTML(htmlConverterPath);

            if (!fileName.endsWith(".html")) {
                fileName.append(".html");
            }
            QFile::copy(file->getFileName() + ".html", fileName);
            QMessageBox::information(this, APP_NAME,
                                     tr("Web archive exported to directory ") + fileName);
        }
    }
}

void Writer::on_actionNew_triggered()
{
    Dialog_NewDocument *dialog = new Dialog_NewDocument();
    ui->documentViewer->hideTextEdit();

    if (file != NULL) {
        on_actionClose_triggered();
    }
    if (file == NULL) {
        dialog->exec(); //Blocks input to parent window until current dialog has been finished
        if (QFile(dialog->getDocumentPath()).exists()) {
            openDocument(dialog->getDocumentPath());
        }
    }

}
void Writer::on_actionEquation_triggered()
{
    MathEditor *dialog = new MathEditor(file,ui->documentViewer->getSelectedLineNumber());
    ui->documentViewer->hideTextEdit();

    dialog->setWindowModality(
        Qt::WindowModal); //Blocks input to parent window until current dialog has been finished
    dialog->show(); //Blocks input to parent window until current dialog has been finished
    file->saveFile();
    file->compile(pdfCompilerPath);
    file->compile(pdfCompilerPath);
    ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());
}
void Writer::refreshPage()
{
    ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());
}
void Writer::on_actionDocument_Preamble_triggered()
{
    Dialog_DocumentPreamble *dialog = new Dialog_DocumentPreamble();
    dialog->setData(file, ui->documentViewer);
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    connect(dialog, SIGNAL(accepted()), this, SLOT(refreshPage()));
    ui->documentViewer->hideTextEdit();

}
void Writer::on_actionCompiler_Settings_triggered()
{
    Dialog_CompilerSettings *dialog = new Dialog_CompilerSettings();
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    ui->documentViewer->hideTextEdit();

}
void Writer::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("LaTeX Office Writer"), file->getDirectory(),
                                                    tr("LaTeX File (*.tex)"));
    if (fileName != NULL) {
        if (!fileName.endsWith(".tex")) {
            fileName.append(".tex");
        }
        file->deprecompile();
        file->saveFile();
        file->saveFile(fileName);

    }
    ui->documentViewer->hideTextEdit();

}
void Writer::on_actionFind_triggered()
{
    Dialog_Find *dialog = new Dialog_Find();
    dialog->setData(ui->documentViewer);
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionBreak_triggered()
{
    file->setNewPage();
    file->saveFile();
    file->compile(pdfCompilerPath);
    ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionPackage_Document_triggered()
{
    ui->documentViewer->hideTextEdit();

    if (hasFileChanged == true) {
        QMessageBox::critical(this, APP_NAME,
                              tr("You must save the document before packaging it!"));
    } else {
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("LaTeX Office Writer"), file->getDirectory(),
                                                        tr("LaTeX Office Package (*.lop)"));
        if (fileName != NULL) {
            if (!fileName.endsWith(".lop")) {
                fileName.append(".lop");
            }

            QString schemaFileName = "document.xsd";
            QString metaFileName = "META-INF.xml";
            QString bibliographyFileName = file->getFileName() + ".bib";
            QString tableOfContentsFileName = file->getFileName() + ".toc";
            QString listOfFiguresFileName = file->getFileName() + ".lof";
            QString listOfTablesFileName = file->getFileName() + ".lot";
            QString styFileName = file->getFileName() + ".sty";
            QString clsFileName = file->getFileName() + ".cls";
            QFile xsdFile(schemaFileName);
            QFile xmlFile(metaFileName);
            QFile bibFile(bibliographyFileName);
            QFile tocFile(tableOfContentsFileName);
            QFile lofFile(listOfFiguresFileName);
            QFile lotFile(listOfTablesFileName);
            QFile styFile(styFileName);
            QFile clsFile(clsFileName);
            QStringList filesToCompress;
            filesToCompress.append(oriFileName);
            if (xsdFile.open(QIODevice::ReadWrite)) {
                QTextStream stream(&xsdFile);
                stream << "<?xml version=\"1.0\"?>" << endl;
                stream << "<xs:schema xmlns:xs=\"http://www.w3.org/2001/XMLSchema\">" << endl;
                stream << "<xs:element name=\"document\">" << endl;
                stream << "  <xs:complexType>" << endl;
                stream << "    <xs:sequence>" << endl;
                stream << "      <xs:element name=\"name\" type=\"xs:string\"/>" << endl;
                stream << "      <xs:element name=\"latex\" type=\"xs:string\"/>" << endl;
                stream << "      <xs:element name=\"bibliography\" type=\"xs:string\"/>" << endl;
                stream << "      <xs:element name=\"tableOfContents\" type=\"xs:string\"/>" << endl;
                stream << "      <xs:element name=\"listOfFigures\" type=\"xs:string\"/>" << endl;
                stream << "      <xs:element name=\"listOfTables\" type=\"xs:string\"/>" << endl;
                stream << "      <xs:element name=\"styleFile\" type=\"xs:string\"/>" << endl;
                stream << "      <xs:element name=\"classFile\" type=\"xs:string\"/>" << endl;
                stream << "    </xs:sequence>" << endl;
                stream << "  </xs:complexType>" << endl;
                stream << "  </xs:element>" << endl;
                stream << "  </xs:schema>" << endl;
            }
            if (bibFile.exists()) {
                filesToCompress.append(bibliographyFileName);
            } else {
                bibliographyFileName = "";
            }
            if (tocFile.exists()) {
                filesToCompress.append(tableOfContentsFileName);
            } else {
                tableOfContentsFileName = "";
            }
            if (lofFile.exists()) {
                filesToCompress.append(listOfFiguresFileName);
            } else {
                listOfFiguresFileName = "";
            }
            if (lotFile.exists()) {
                filesToCompress.append(listOfTablesFileName);
            } else {
                listOfTablesFileName = "";
            }
            if (styFile.exists()) {
                filesToCompress.append(styFileName);
            } else {
                styFileName = "";
            }
            if (clsFile.exists()) {
                filesToCompress.append(clsFileName);
            } else {
                clsFileName = "";
            }
            if (xmlFile.open(QIODevice::ReadWrite)) {
                QTextStream stream(&xmlFile);


                stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
                stream << "<document xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"document.xsd\">"
                       << endl;
                stream << "<name>" + file->getFileName() + "</name>" << endl;
                stream << "<latex>" + file->getFileName() + ".tex</latex>" << endl;
                stream << "<bibliography>" + bibliographyFileName + "</bibliography>" << endl;
                stream << "<tableOfContents>" + tableOfContentsFileName + "</tableOfContents>" << endl;
                stream << "<listOfFigures>" + listOfFiguresFileName + "</listOfFigures>" << endl;
                stream << "<listOfTables>" + listOfTablesFileName + "</listOfTables>" << endl;
                stream << "<styleFile>" + styFileName + "</styleFile>" << endl;
                stream << "<classFile>" + clsFileName + "</classFile>" << endl;

                stream << "</document>" << endl;
            }

            filesToCompress.append(schemaFileName);
            filesToCompress.append(metaFileName);
            JlCompress::compressFiles(fileName, filesToCompress);
            xsdFile.remove();
            xmlFile.remove();
            QMessageBox::information(this, APP_NAME,
                                     tr("The document was packaged succesfully at ") + fileName);
        }
    }
}
void Writer::unpackDocument(QString fileName)
{
    QStringList filesToUncompress;
    QString documentName;
    QString latexFileName;
    QString bibliographyFileName;
    QString tableOfContentsFileName;
    QString listOfFiguresFileName;
    QString listOfTablesFileName;
    QString styleFileName;
    QString classFileName;
    QString extractionPath;
    ui->documentViewer->hideTextEdit();

    QFile xmlFile(JlCompress::extractFile(fileName, "META-INF.xml"));
    xmlFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&xmlFile);
    QString line = in.readLine();
    while (!line.isNull()) {
        if (line.contains("name")) {
            documentName = line.remove("<name>").remove("</name>");
        }
        if (line.contains("latex")) {
            latexFileName = line.remove("<latex>").remove("</latex>");
            if (!latexFileName.isEmpty()) {
                filesToUncompress.append(latexFileName);
            }
        }
        if (line.contains("bibliography")) {
            bibliographyFileName = line.remove("<bibliography>").remove("</bibliography>");
            if (!bibliographyFileName.isEmpty()) {
                filesToUncompress.append(bibliographyFileName);
            }
        } else if (line.contains("tableOfContents")) {
            tableOfContentsFileName = line.remove("<tableOfContents>").remove("</tableOfContents>");
            filesToUncompress.append(tableOfContentsFileName);
            if (!tableOfContentsFileName.isEmpty()) {
                filesToUncompress.append(tableOfContentsFileName);
            }
        } else if (line.contains("listOfFigures")) {
            listOfFiguresFileName = line.remove("<listOfFigures>").remove("</listOfFigures>");
            if (!listOfFiguresFileName.isEmpty()) {
                filesToUncompress.append(listOfFiguresFileName);
            }
        } else if (line.contains("listOfTables")) {
            listOfTablesFileName = line.remove("<listOfTables>").remove("</listOfTables>");
            if (!listOfTablesFileName.isEmpty()) {
                filesToUncompress.append(listOfTablesFileName);
            }
        } else if (line.contains("styleFile")) {
            styleFileName = line.remove("<styleFile>").remove("</styleFile>");
            if (!styleFileName.isEmpty()) {
                filesToUncompress.append(styleFileName);
            }
        } else if (line.contains("classFile")) {
            classFileName = line.remove("<classFile>").remove("</classFile>");
            if (!classFileName.isEmpty()) {
                filesToUncompress.append(classFileName);
            }
        }
        line = in.readLine();
    }
    extractionPath = QFileInfo(fileName).absolutePath() + "/" + QFileInfo(fileName).baseName() + "/" ;
    xmlFile.remove();
    foreach (QString item, filesToUncompress)
    {
        if (!item.isEmpty())
            JlCompress::extractFile(fileName, item, extractionPath + "/" + item);
    }

    QMessageBox::information(this, APP_NAME,
                             tr("The document was unpackaged succesfully at ") + extractionPath);
}

void Writer::on_actionUnpackage_Document_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("LaTeX Office Package (*.lop)"));
    if (!fileName.isEmpty()) {
        unpackDocument(fileName);
    }
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionChapter_triggered()
{
    Dialog_Chapter *dialog = new Dialog_Chapter();
    dialog->setData(file, ui->documentViewer, pdfCompilerPath);
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionSection_triggered()
{
    Dialog_Section *dialog = new Dialog_Section();
    dialog->setData(file, ui->documentViewer, pdfCompilerPath);
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionSub_Section_triggered()
{
    Dialog_SubSection *dialog = new Dialog_SubSection();
    dialog->setData(file, ui->documentViewer, pdfCompilerPath);
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionSub_Sub_Section_triggered()
{
    Dialog_SubSubSection *dialog = new Dialog_SubSubSection();
    dialog->setData(file, ui->documentViewer, pdfCompilerPath);
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionParagraph_triggered()
{
    Dialog_Paragraph *dialog = new Dialog_Paragraph();
    dialog->setData(file, ui->documentViewer, pdfCompilerPath,
                    ui->documentViewer->getDocumentStructure());
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionTable_of_Contents_triggered()
{
    QStringList newFileContent;
    if (ui->actionTable_of_Contents->isChecked()) {
        if (file->getLineNumber(command.callTableOfContents()) == -1) {
            if (file->getLineNumber(CMD_MAKE_TITLE) != -1) {
                file->setTeXCommand(command.callTableOfContents(),
                                    file->getLineNumber(CMD_MAKE_TITLE) + 1);
            } else {
                file->setTeXCommand(command.callTableOfContents(),
                                    file->getLineNumber(command.callEnd(DOC_PAGE_TITLE)) + 1);
            }
        }
    } else {
        int tableOfContentsLine = file->getLineNumber(command.callTableOfContents());
        if (tableOfContentsLine != -1) {
            newFileContent = file->getFileContent();
            newFileContent.removeAt(tableOfContentsLine);
            file->setFileContent(newFileContent);
        }

    }
    ui->documentViewer->hideTextEdit();

    file->saveFile();
    file->compile(pdfCompilerPath);
    file->compile(
        pdfCompilerPath); //Compilar dos veces para evitar problemas con la tabla de contenidos.
    ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());
}
void Writer::on_actionPrint_Preview_triggered()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(file->getFileName() + ".pdf"));
    ui->documentViewer->hideTextEdit();

}
void Writer::on_actionCut_triggered()
{
    ui->documentViewer->cutText();
}
void Writer::on_actionCopy_triggered()
{
    ui->documentViewer->copyText();
}
void Writer::on_actionPaste_triggered()
{
    ui->documentViewer->pasteText();
}
void Writer::on_actionPicture_triggered()
{
    Dialog_InsertImage *dialog = new Dialog_InsertImage();
    if (file->getPackage(PACK_GRFFILE, "space") == -1) {
        file->deprecompile();
        file->setPackage(PACK_GRFFILE, "space");
        file->saveFile();
    }

    dialog->setData(ui->documentViewer->getSelectedLineNumber(), file, pdfCompilerPath);
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());
    ui->documentViewer->hideTextEdit();
}

void Writer::on_actionTable_triggered()
{
    Dialog_InsertTable *dialog = new Dialog_InsertTable();
    dialog->setData(ui->documentViewer->getSelectedLineNumber(), file, pdfCompilerPath);
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionPrint_triggered()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    dlg->setWindowTitle(QObject::tr("Print Document"));
    dlg->setMinimumSize(640, 480);
    dlg->setMaximumSize(640, 480);
    dlg->setBaseSize(640, 480);
    QList<QImage> images = ui->documentViewer->getImages();

    if (!dlg->exec() == QDialog::Accepted) {
        return;
    } else {
        QPainter painter(&printer);

        for (int page = 0; page < ui->documentViewer->getTotalPages(); page++) {
            painter.drawImage(printer.pageRect(), images.at(page));
            printer.newPage();
        }
    }
    ui->documentViewer->hideTextEdit();

}


void Writer::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, APP_NAME);
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionUndo_triggered()
{
    ui->documentViewer->hideTextEdit();
    if (file->getCurrentActionIndex() == 1) {
        ui->actionUndo->setEnabled(false);
        ui->actionRedo->setEnabled(true);
    } else {
        ui->actionUndo->setEnabled(true);
        ui->actionRedo->setEnabled(true);
    }
    file->undoFileContentHistory(pdfCompilerPath);
    ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());

}

void Writer::on_actionRedo_triggered()
{
    ui->documentViewer->hideTextEdit();
    if (file->getCurrentActionIndex() == file->getFileContentHistory().count() - 2) {
        ui->actionRedo->setEnabled(false);
        ui->actionUndo->setEnabled(true);
    } else {
        ui->actionRedo->setEnabled(true);
    }
    file->redoFileContentHistory(pdfCompilerPath);
    ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());

}

void Writer::on_actionBibliography_Manager_triggered()
{
    Dialog_Bibliography *dialog = new Dialog_Bibliography();
    dialog->setData(file->getDirectory() + "/" + file->getFileName() + ".bib");
    file->compile(pdfCompilerPath);
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    disableFunctions();
    qDebug() << "Compiling bibliography file";
    bibFile = new TeXBibliography(file->getDirectory() + "/" + file->getFileName() + ".bib");
    bibFile->saveFile();
    file->compile(pdfCompilerPath);
    bibFile->compile(bibCompilerPath);
    file->compile(pdfCompilerPath);
    file->compile(pdfCompilerPath);
    enableFunctions();
    ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());
    ui->documentViewer->hideTextEdit();


}

void Writer::on_actionBibliography_triggered()
{
    QStringList newFileContent;
    if (ui->actionBibliography->isChecked()) {
        if (file->getLineNumber(CMD_NOCITE) != -1) {
            file->replaceTeXCommand(command.callNoCite("*"), file->getLineNumber(CMD_NOCITE));
        } else {
            file->setTeXCommand(command.callNoCite("*"), file->getEndDocumentCommand());
        }

        if (file->getLineNumber(CMD_BIBLIOGRAPHY) != -1) {
            file->replaceTeXCommand(QString(CMD_BIBLIOGRAPHY) + "{" + file->getFileName() + "}{}" ,
                                    file->getLineNumber(CMD_BIBLIOGRAPHY));
        } else {
            file->setTeXCommand(QString(CMD_BIBLIOGRAPHY) + "{" + file->getFileName() + "}{}" ,
                                file->getEndDocumentCommand());
        }
        if (file->getLineNumber(CMD_BIBLIOGRAPHYSTYLE) != -1) {
            file->replaceTeXCommand(command.callBibliographyStyle("plain"),
                                    file->getLineNumber(CMD_BIBLIOGRAPHYSTYLE));
        } else {
            file->setTeXCommand(command.callBibliographyStyle("plain"),
                                file->getEndDocumentCommand());
        }

        ui->documentViewer->hideTextEdit();
        file->saveFile();
        bibFile->saveFile();
        file->compile(pdfCompilerPath);
        bibFile->compile(bibCompilerPath);
        file->compile(
            pdfCompilerPath); //Compilar dos veces para evitar problemas con la tabla de contenidos.
        file->compile(
            pdfCompilerPath); //Compilar dos veces para evitar problemas con la tabla de contenidos.
        ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());
    } else {
        int bibliographyLine = file->getLineNumber(CMD_BIBLIOGRAPHY);
        if (bibliographyLine != -1) {
            int bibliographyStyleLine;
            newFileContent = file->getFileContent();
            newFileContent.removeAt(bibliographyLine);
            bibliographyStyleLine = file->getLineNumber(CMD_BIBLIOGRAPHYSTYLE) - 1;
            newFileContent.removeAt(bibliographyStyleLine);
            file->setFileContent(newFileContent);
            file->saveFile();
            file->compile(
                pdfCompilerPath); //Compilar dos veces para evitar problemas con la tabla de contenidos.
            file->compile(
                pdfCompilerPath); //Compilar dos veces para evitar problemas con la tabla de contenidos.
            ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());
        }
    }
}

void Writer::on_actionSpelling_triggered()
{
    QString dictPath = QFileInfo(currentDictionary).absolutePath() + "/" + QFileInfo(
                           currentDictionary).baseName();
    QString userDict = "./dictionaries/userDict.txt";
    SpellChecker *spellChecker = new SpellChecker(dictPath, userDict);
    Dialog_SpellChecker *checkDialog = new Dialog_SpellChecker(file->getFileContent(),
                                                               spellChecker, this);
    ui->documentViewer->hideTextEdit();

    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(QBrush(QColor("#ff6060")));
    highlightFormat.setForeground(QBrush(QColor("#000000")));
    // alternative format
    //highlightFormat.setUnderlineColor(QColor("red"));
    //highlightFormat.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);


    // save the position of the current cursor
    QTextCursor oldCursor = checkDialog->getDocumentZone()->textCursor();

    // create a new cursor to walk through the text
    QTextCursor cursor(checkDialog->getDocumentZone()->document());

    // Don't call cursor.beginEditBlock(), as this prevents the rewdraw after changes to the content
    // cursor.beginEditBlock();
    while (!cursor.atEnd()) {
        QCoreApplication::processEvents();
        cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor, 1);
        QString word = cursor.selectedText();
        // Workaround for better recognition of words
        // punctuation etc. does not belong to words
        while (!word.isEmpty() && word.length() < 4 && !word.at(0).isMark()
               && !word.at(0).isLetter() && cursor.anchor() < cursor.position()) {
            int cursorPos = cursor.position();
            cursor.setPosition(cursor.anchor() + 1, QTextCursor::MoveAnchor);
            cursor.setPosition(cursorPos, QTextCursor::KeepAnchor);
            word = cursor.selectedText();
        }

        if (!word.isEmpty() && word.length() > 4 && !word.contains(CMD_LINE_BREAK)
            && !spellChecker->spell(word)) {
            QTextCursor tmpCursor(cursor);
            tmpCursor.setPosition(cursor.anchor());
            checkDialog->getDocumentZone()->setTextCursor(tmpCursor);
            checkDialog->getDocumentZone()->ensureCursorVisible();

            // highlight the unknown word
            QTextEdit::ExtraSelection es;
            es.cursor = cursor;
            es.format = highlightFormat;

            QList<QTextEdit::ExtraSelection> esList;
            esList << es;
            checkDialog->getDocumentZone()->setExtraSelections(esList);
            QCoreApplication::processEvents();

            // ask the user what to do
            Dialog_SpellChecker::SpellCheckAction spellResult = checkDialog->checkWord(word);

            // reset the word highlight
            esList.clear();
            checkDialog->getDocumentZone()->setExtraSelections(esList);
            QCoreApplication::processEvents();

            if (spellResult == Dialog_SpellChecker::AbortCheck) {
                break;
            }

            switch (spellResult) {
            case Dialog_SpellChecker::ReplaceOnce:
                cursor.insertText(checkDialog->replacement());
                file->setFileContent(checkDialog->getDocumentZone()->toPlainText().split("\n"));
                file->saveFile();
                file->compile(pdfCompilerPath);
                if (bibFile) {
                    bibFile->compile(bibCompilerPath);
                    file->compile(pdfCompilerPath);
                }
                file->compile(pdfCompilerPath);
                ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());
                break;

            default:
                break;
            }
            QCoreApplication::processEvents();
        }
        cursor.movePosition(QTextCursor::NextWord, QTextCursor::MoveAnchor, 1);
    }
    //cursor.endEditBlock();
    checkDialog->getDocumentZone()->setTextCursor(oldCursor);

    QMessageBox::information(
        this,
        APP_NAME,
        tr("The spell check has finished."));
}

void Writer::on_actionGoal_triggered()
{
    Dialog_Goal *dialog = new Dialog_Goal(ui->documentViewer);
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionDictionary_Settings_triggered()
{
    Dialog_DictionarySettings *dialog = new Dialog_DictionarySettings();
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    setDictionary(dialog->getDictionary());
    ui->documentViewer->hideTextEdit();

}
void Writer::setDictionary(QString dict)
{
    currentDictionary = dict;
}
void Writer::loadDictionary()
{
    QFile file("settings/dictionary.los");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString line;
    while (!in.atEnd()) {
        line = in.readLine();
    }
    file.close();
    currentDictionary = line;
    if (!currentDictionary.isEmpty()) {
        ui->actionSpelling->setEnabled(true);
    }
}

void Writer::on_actionDocument_Lock_triggered()
{
    Dialog_DocumentLock *dialog = new Dialog_DocumentLock(file);
    dialog->exec(); //Blocks input to parent window until current dialog has been finished

    if (dialog->getLockedFile()) {
        ui->documentViewer->closeDocument();
        file->close();
        QFile::remove(QFileInfo(oriFileName).absolutePath() + "/" + QFileInfo(
                          oriFileName).baseName().append(".tmp"));
        disableFunctions();
        QWidget::setWindowTitle(APP_NAME);
        file = NULL;
        oriFileName = "";
        ui->documentViewer->setVisible(false);
        ui->documentViewer->hideTextEdit();

    }
}

void Writer::on_actionCode_Asset_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("Source Code File (*.abap *.adb *.ads *.awk *.sh *.bas *.c *.h *.cpp *.ml *.cbl *.cob *.cpy *.csh *.pas *.eaf *.erl *.ex *.f *.for *.ftn *.f90 *.gcl *.gnu *.plt *.gplot *.hs *.lhs *.htm *.html *.java *.lisp *.m *.ml *.mod *.m2 *.def *.MOD *.DEF *.mi *.md *.mu *.ob2 *.m *.pas *.pl *.php *.pl1 *.pro *.pl *.pml *.py *.r *.rb *.rbw *.s *.sas *.sce *.sql *.tcl *.tex *.vb *.xml *.xslt)"));
    ui->documentViewer->hideTextEdit();

    if (!fileName.isEmpty()) {
        if (fileName.endsWith(".abap")) { //Abap
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=ABAP,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".adb")) { //Ada
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Ada,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".ads")) { //Ada
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Ada,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".awk")) { //Awk
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Awk,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".sh")) { //Bash
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=bash,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".bas")) { //Basic
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Basic,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".c")) { //C
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=C,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".h")) { //C, C++
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=C,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".cpp")) { //C++
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=C++,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".ml")) { //Caml
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Caml,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".cbl")) { //Cobol
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Cobol,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".cob")) { //Cobol
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Cobol,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".cpy")) { //Cobol
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Cobol,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".csh")) { //Csh
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=csh,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".pas")) { //Delphi
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Delphi,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".eaf")) { //Elan
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Elan,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".erl")) { //Erlang
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=erlang,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".ex")) { //Euphoria
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Euphoria,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".f")) { //Fortran
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Fortran,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".for")) { //Fortran
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Fortran,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".ftn")) { //Fortran
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Fortran,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".f90")) { //Fortran
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Fortran,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".gcl")) { //Gcl
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=GCL,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".gnu")) { //Gnuplot
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Gnuplot,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".plt")) { //Gnuplot
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Gnuplot,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".gplot")) { //Gnuplot
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Gnuplot,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".hs")) { //Haskell
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Haskell,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".lhs")) { //Haskell
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Haskell,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".html")) { //HTML
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=HTML,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".htm")) { //HTML
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=HTML,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".java")) { //Java
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Java,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".lisp")) { //Lisp
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Lisp,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".m")) { //Matlab, Octave
            QMessageBox msgBox;
            msgBox.setWindowTitle(APP_NAME);
            msgBox.setIcon(QMessageBox::Question);
            msgBox.setText(tr("Is this a Matlab source file or an Octave one?"));
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setButtonText(QMessageBox::Yes, tr("Matlab Source File"));
            msgBox.setButtonText(QMessageBox::No, tr("Octave Source File"));
            msgBox.setDefaultButton(QMessageBox::Yes);

            if (msgBox.exec() == QMessageBox::Yes) {
                file->setTeXCommand(command.callLstInputListing(fileName,
                                                                "language=Matlab,breaklines=true,showstringspaces=false"),
                                    ui->documentViewer->getSelectedLineNumber());
            } else {
                file->setTeXCommand(command.callLstInputListing(fileName,
                                                                "language=Octave,breaklines=true,showstringspaces=false"),
                                    ui->documentViewer->getSelectedLineNumber());
            }
        } else if (fileName.endsWith(".ml")) { //ML
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=ML,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".mod")) { //Modula-2
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Modula-2,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".m2")) { //Modula-2
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Modula-2,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".def")) { //Modula-2
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Modula-2,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".MOD")) { //Modula-2
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Modula-2,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".DEF")) { //Modula-2
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Modula-2,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".mi")) { //Modula-2
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Modula-2,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".md")) { //Modula-2
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Modula-2,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".mu")) { //MuPAD
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=MuPAD,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".ob2")) { //Oberon-2
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Oberon-2,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".pas")) { //Pascal
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Pascal,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".pl")) { //Perl, Prolog
            QMessageBox msgBox;
            msgBox.setWindowTitle(APP_NAME);
            msgBox.setIcon(QMessageBox::Question);
            msgBox.setText(tr("Is this a Perl source file or a Prolog one?"));
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setButtonText(QMessageBox::Yes, tr("Perl Source File"));
            msgBox.setButtonText(QMessageBox::No, tr("Prolog Source File"));
            msgBox.setDefaultButton(QMessageBox::Yes);

            if (msgBox.exec() == QMessageBox::Yes) {
                file->setTeXCommand(command.callLstInputListing(fileName,
                                                                "language=Perl,breaklines=true,showstringspaces=false"),
                                    ui->documentViewer->getSelectedLineNumber());
            } else {
                file->setTeXCommand(command.callLstInputListing(fileName,
                                                                "language=Prolog,breaklines=true,showstringspaces=false"),
                                    ui->documentViewer->getSelectedLineNumber());
            }
        } else if (fileName.endsWith(".php")) { //Php
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=PHP,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".pl1")) { //PL/I
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=PL/I,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".pro")) { //Prolog
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Prolog,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".pml")) { //Promela
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Promela,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".py")) { //Python
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Python,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".r")) { //R
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=R,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".rb")) { //Ruby
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Ruby,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".rbw")) { //Ruby
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Ruby,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".s")) { //S
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=S,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".sas")) { //SAS
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=SAS,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".sce")) { //Scilab
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=Scilab,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".sql")) { //SQL
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=SQL,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".tcl")) { //TCL
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=tcl,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".tex")) { //TeX
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=TeX,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".vb")) { //Visual Basic
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=VBScript,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".xml")) { //XML
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=XML,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        } else if (fileName.endsWith(".xslt")) { //XSLT
            file->setTeXCommand(command.callLstInputListing(fileName,
                                                            "language=XSLT,breaklines=true,showstringspaces=false"),
                                ui->documentViewer->getSelectedLineNumber());
        }
        file->saveFile();
        file->compile(pdfCompilerPath);
        file->compile(pdfCompilerPath);
        ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());
    }
}

void Writer::on_actionSmartKeys_triggered()
{
    Dialog_SmartKeys *dialog = new Dialog_SmartKeys();
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionTime_Machine_triggered()
{
    QList<QDateTime> datesList;
    QList<QStringList> fileBackupsList;
    if (TimeMachine::getBackupsList().isEmpty()) {
        QMessageBox::information(this, APP_NAME,
                                 tr("There are no backups available for this document."));
        return;
    }
    foreach (backup item, TimeMachine::getBackupsList()) {
        datesList.append(item.date);
        fileBackupsList.append(item.fileContent);
    }
    Dialog_TimeMachine *dialog = new Dialog_TimeMachine(file, datesList, fileBackupsList, "data/timemachine/" + file->getFileName().append(".tmf"),
                                                        pdfCompilerPath);
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());
    ui->documentViewer->fillList();
    ui->documentViewer->hideTextEdit();
    ui->documentViewer->refresh(0);
}

void Writer::on_actionTheme_Settings_triggered()
{
    Dialog_ThemeSettings *dialog = new Dialog_ThemeSettings();
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionMinimize_window_triggered()
{
    setWindowState(Qt::WindowMinimized);
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionFull_Screen_triggered()
{
    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height();
    int width = rec.width();
    setWindowState(Qt::WindowMaximized);
    this->setGeometry(this->geometry().x(), this->geometry().y(), width, height);
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionMaximize_triggered()
{
    setWindowState(Qt::WindowMaximized);
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionMinimize_Screen_triggered()
{
    setWindowState(Qt::WindowMaximized);
    this->setGeometry(this->geometry().x(), this->geometry().y(), minimumWidth(),
                      minimumHeight());
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionHide_Primary_Toolbar_triggered()
{
    if (ui->actionHide_Primary_Toolbar->isChecked()) {
        ui->mainToolBar->setHidden(true);
        ui->actionHide_Primary_Toolbar->setChecked(true);
    } else {
        ui->mainToolBar->setHidden(false);
        ui->actionHide_Primary_Toolbar->setChecked(false);
    }
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionHide_Secondary_Toolbar_triggered()
{
    if (ui->actionHide_Secondary_Toolbar->isChecked()) {
        ui->secondaryToolBar->setHidden(true);
        ui->secondaryToolBar->setEnabled(false);
        ui->actionHide_Secondary_Toolbar->setChecked(true);
    } else {
        ui->secondaryToolBar->setHidden(false);
        ui->secondaryToolBar->setEnabled(false);
        ui->actionHide_Secondary_Toolbar->setChecked(false);
    }
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionHide_Document_Structure_List_triggered()
{
    if (ui->actionHide_Document_Structure_List->isChecked()) {
        ui->documentViewer->hideDocumentStructureWidget(true);
        ui->actionHide_Document_Structure_List->setChecked(true);
    } else {
        ui->documentViewer->hideDocumentStructureWidget(false);
        ui->actionHide_Document_Structure_List->setChecked(false);
    }
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionShow_LaTeX_Code_triggered()
{
    Dialog_Code *dialog = new Dialog_Code(file->getFileContent(), file, ui->documentViewer,
                                          pdfCompilerPath);
    dialog->exec();
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionTime_Machine_Settings_triggered()
{
    Dialog_TimeMachineSettings *dialog = new Dialog_TimeMachineSettings();
    dialog->exec();
    ui->documentViewer->hideTextEdit();

}



void Writer::on_actionList_of_Tables_triggered()
{
    QStringList newFileContent;
    if (file->getLineNumber(command.callTableOfContents()) == -1) {
        ui->actionTable_of_Contents->setChecked(true);
        on_actionTable_of_Contents_triggered();
    }
    if (ui->actionList_of_Tables->isChecked()) {
        if (file->getLineNumber(command.callListOfTables()) == -1) {
            if (file->getLineNumber(CMD_TABLE_OF_CONTENTS) != -1) {
                file->setTeXCommand(command.callListOfTables(),
                                    file->getLineNumber(CMD_TABLE_OF_CONTENTS) + 1);
            } else {
                file->setTeXCommand(command.callListOfTables(),
                                    file->getLineNumber(command.callEnd(CMD_TABLE_OF_CONTENTS)) + 1);
            }
        }
    } else {
        int listOfTablesLine = file->getLineNumber(command.callListOfTables());
        if (listOfTablesLine != -1) {
            newFileContent = file->getFileContent();
            newFileContent.removeAt(listOfTablesLine);
            file->setFileContent(newFileContent);
        }

    }
    ui->documentViewer->hideTextEdit();

    file->saveFile();
    file->compile(pdfCompilerPath);
    file->compile(
        pdfCompilerPath); //Compilar dos veces para evitar problemas con la tabla de contenidos.
    ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());

}

void Writer::on_actionList_of_Figures_triggered()
{
    QStringList newFileContent;
    if (file->getLineNumber(command.callTableOfContents()) == -1) {
        ui->actionTable_of_Contents->setChecked(true);
        on_actionTable_of_Contents_triggered();
    }
    if (ui->actionList_of_Figures->isChecked()) {
        if (file->getLineNumber(command.callListOfFigures()) == -1) {
            if (file->getLineNumber(CMD_TABLE_OF_CONTENTS) != -1) {
                file->setTeXCommand(command.callListOfFigures(),
                                    file->getLineNumber(CMD_TABLE_OF_CONTENTS) + 1);
            } else {
                file->setTeXCommand(command.callListOfFigures(),
                                    file->getLineNumber(command.callEnd(CMD_TABLE_OF_CONTENTS)) + 1);
            }
        }
    } else {
        int listOfFiguresLine = file->getLineNumber(command.callListOfFigures());
        if (listOfFiguresLine != -1) {
            newFileContent = file->getFileContent();
            newFileContent.removeAt(listOfFiguresLine);
            file->setFileContent(newFileContent);
        }

    }
    ui->documentViewer->hideTextEdit();

    file->saveFile();
    file->compile(pdfCompilerPath);
    file->compile(
        pdfCompilerPath); //Compilar dos veces para evitar problemas con la tabla de contenidos.
    ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());
}

void Writer::on_actionLaTeX_Office_on_the_Web_triggered()
{
    QString link = "http://www.wordtasticapp.com";
    QDesktopServices::openUrl(QUrl(link));
    ui->documentViewer->hideTextEdit();

}

void Writer::on_actionCopy_Protect_triggered()
{

    QMessageBox copyProtectMessageBox(APP_NAME,
                                   tr("With Copy Protect, the program will generate a PDF file that is protected against not authorized copies, so you will have to supply a path for the protected PDF file. Do you want to continue ?"),
                                   QMessageBox::Question,
                                   QMessageBox::Yes | QMessageBox::Default,
                                   QMessageBox::No | QMessageBox::Escape,  //This makes "Esc" key to Cancel the Dialog
                                   QMessageBox::NoButton,
                                   this);
    copyProtectMessageBox.setButtonText(QMessageBox::Yes, tr("Yes"));
    copyProtectMessageBox.setButtonText(QMessageBox::No, tr("No"));
    ui->documentViewer->hideTextEdit();



    if (copyProtectMessageBox.exec() == QMessageBox::Yes) {

        QFile cpyFileName(QFileInfo(oriFileName).absolutePath() + "/" + QFileInfo(
                              oriFileName).baseName().append("-protected.tex"));
        if (cpyFileName.exists()) {
            cpyFileName.remove();
        }
        QFile(oriFileName).copy(QFileInfo(oriFileName).absolutePath() + "/" + QFileInfo(
                                 oriFileName).baseName().append("-protected.tex"));
        TeXFile* temporalFile = new TeXFile(QFileInfo(oriFileName).absolutePath() + "/" + QFileInfo(
                                                oriFileName).baseName().append("-protected.tex"),true);
        QString savePath = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "",
                                                        tr("PDF File (*.pdf)"));
        if (savePath != NULL) {
            if (!savePath.endsWith(".pdf"))
            {
                savePath.append(".pdf");
            }
            temporalFile->deleteTeXCommand(CMD_ENDOFDUMP);
            temporalFile->enableCopyProtect(true);
            temporalFile->saveFile();
            temporalFile->compile(TeXCompiler::loadPDFCompilerPathSettings());
            temporalFile->compile(TeXCompiler::loadPDFCompilerPathSettings());
            QFile(QFileInfo( oriFileName).baseName().append("-protected.pdf")).rename(savePath);
            QFile(QFileInfo(oriFileName).absolutePath() + "/" + QFileInfo(oriFileName).baseName().append("-protected.tex")).remove();
            temporalFile->close();
        }
    }
}

void Writer::on_actionFonts_triggered()
{
    Dialog_Fonts*  dialog = new Dialog_Fonts(file,TeXCompiler::loadPDFCompilerPathSettings());
    dialog->exec();
    ui->documentViewer->hideTextEdit();

    ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());
}

void Writer::on_actionLaTeX_Office_Writer_Help_triggered()
{
    QFile::copy(":/documents/Manual.pdf","Manual.pdf");
    QDesktopServices::openUrl(QUrl::fromLocalFile("Manual.pdf"));
    ui->documentViewer->hideTextEdit();
}
