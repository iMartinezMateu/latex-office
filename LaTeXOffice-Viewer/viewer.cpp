#include "viewer.h"
#include "ui_viewer.h"

Viewer::Viewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Viewer)
{
    ui->setupUi(this);
    remoteControlServer = new RemoteControlServer();
    remoteControlServer->generatePin();

    QCoreApplication::translate("MAC_APPLICATION_MENU", "Services");
    QCoreApplication::translate("MAC_APPLICATION_MENU", "Hide %1");
    QCoreApplication::translate("MAC_APPLICATION_MENU", "Hide Others");
    QCoreApplication::translate("MAC_APPLICATION_MENU", "Show All");
    QTranslator *qtTranslator = new QTranslator();
    QTranslator *translator = new QTranslator();
    if (qtTranslator->load("qt_" + QLocale::system().name(), ":/languages")) {
        qApp->installTranslator(translator);
    }
    if (translator->load("viewer_" + QLocale::system().name(), ":/languages")) {
        qApp->installTranslator(translator);
    }
    ui->retranslateUi(this);

    file = NULL;

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


        ui->statusBar->showMessage(tr("Remote Control is running on\n\nIP: %1\nport: %2 with the following pin code: %3")
                                   .arg(remoteControlServer->getIPAddress()).arg(remoteControlServer->getPort()).arg(remoteControlServer->getPin()));


}
void Viewer::closeEvent(QCloseEvent *event)
{


    QMessageBox messageBox(APP_NAME,
                           tr("Do you want to close LaTeX Office Viewer?  \n"),
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
            ui->documentViewer->closeDocument();
            QFile::remove(QFileInfo(oriFileName).absolutePath() + "/" + QFileInfo(
                              oriFileName).baseName().append(".tmp"));
            file->close();
        }

        remoteControlServer->close();
        event->accept();

    }

}



Viewer::~Viewer()
{
    delete ui;
}




void Viewer::openDocument(QString fileName)
{


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
                                              tr("The file is currently empty and it cannot be opened with LaTeX Office Viewer"),
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
                        dialog->setProgressBarValue(35);



                        if (!file->getFileName().contains(' '))
                            //file->precompile(TeXCompiler::loadPDFCompilerPathSettings());
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
                        file->saveFile();
                        file->compile(TeXCompiler::loadPDFCompilerPathSettings());
                        dialog->setProgressBarValue(85);
                        file->compile(
                            TeXCompiler::loadPDFCompilerPathSettings()); //Compile two times to get table of contents...
                        dialog->setProgressBarValue(100);
                        dialog->accept();
                        if (!QFile(file->getFileName() + ".pdf").exists()) {
                            QMessageBox messageBox(APP_NAME,
                                                   tr("The document you wish to open in LaTeX Office Viewer is not fully compatible. Edit it with some plain text editor and try again. Do you want to open the log file?"),
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
                            QWidget::setWindowTitle(QString(APP_NAME) + " <" + fileName + ">");
                            ui->documentViewer->loadDocument(QFileInfo(fileName).baseName() + ".pdf");

                            ui->actionUnpackage_Document->setEnabled(false);
                            enableFunctions();
                            pdfCompilerPath = TeXCompiler::loadPDFCompilerPathSettings();
                            bibCompilerPath = TeXCompiler::loadBIBCompilerPathSettings();
                            remoteControlServer->loadDocumentViewer(ui->documentViewer);
                        }
                    }
                }
            }
        }
    }
}

void Viewer::on_actionOpen_triggered()
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
void Viewer::on_actionClose_triggered()
{
    if (file != NULL) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(APP_NAME);
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setText(
            tr("Do you want to close the current document?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setButtonText(QMessageBox::Yes, tr("Yes"));
        msgBox.setButtonText(QMessageBox::No, tr("No"));
        msgBox.setDefaultButton(QMessageBox::No);
        if (msgBox.exec() == QMessageBox::Yes) {
            ui->actionUnpackage_Document->setEnabled(true);

            ui->documentViewer->closeDocument();
            ui->documentViewer->setHidden(true);
            file->close();
            QFile::remove(QFileInfo(oriFileName).absolutePath() + "/" + QFileInfo(
                              oriFileName).baseName().append(".tmp"));
            QWidget::setWindowTitle(APP_NAME);
            file = NULL;
            bibFile = NULL;
            oriFileName = "";
            disableFunctions();
            remoteControlServer->unloadDocumentViewer();
            remoteControlServer->unloadDocumentSlideShow();
        }
    }
}
void Viewer::on_actionExit_triggered()
{
    this->close();
}

void Viewer::on_actionPrint_Preview_triggered()
{

}

void Viewer::refreshPage()
{
    ui->documentViewer->refresh(ui->documentViewer->getCurrentPage());
}

void Viewer::on_actionCompiler_Settings_triggered()
{
    Dialog_CompilerSettings *dialog = new Dialog_CompilerSettings();
    dialog->exec(); //Blocks input to parent window until current dialog has been finished


}

void Viewer::unpackDocument(QString fileName)
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





void Viewer::on_actionPrint_triggered()
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


}


void Viewer::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, APP_NAME);


}

void Viewer::on_actionMinimize_window_triggered()
{
    setWindowState(Qt::WindowMinimized);


}

void Viewer::on_actionFull_Screen_triggered()
{
    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height();
    int width = rec.width();
    setWindowState(Qt::WindowMaximized);
    this->setGeometry(this->geometry().x(), this->geometry().y(), width, height);


}

void Viewer::on_actionMaximize_triggered()
{
    setWindowState(Qt::WindowMaximized);


}

void Viewer::on_actionMinimize_Screen_triggered()
{
    setWindowState(Qt::WindowMaximized);
    this->setGeometry(this->geometry().x(), this->geometry().y(), minimumWidth(),
                      minimumHeight());


}

void Viewer::on_actionLaTeX_Office_on_the_Web_triggered()
{
    QString link = "http://www.abstracteditor.com";
    QDesktopServices::openUrl(QUrl(link));

}

void Viewer::on_actionFind_triggered()
{
    Dialog_Find *dialog = new Dialog_Find();
    dialog->setData(ui->documentViewer);
    dialog->exec(); //Blocks input to parent window until current dialog has been finished
}

void Viewer::enableFunctions()
{
    ui->actionClose->setEnabled(true);
    ui->actionFind->setEnabled(true);
    ui->actionPrint->setEnabled(true);
    ui->actionPrint_Preview->setEnabled(true);
    ui->actionRun_Slide_Show->setEnabled(true);
    ui->actionUnpackage_Document->setEnabled(false);
}

void Viewer::disableFunctions()
{
    ui->actionClose->setEnabled(false);
    ui->actionFind->setEnabled(false);
    ui->actionPrint->setEnabled(false);
    ui->actionPrint_Preview->setEnabled(false);
    ui->actionRun_Slide_Show->setEnabled(false);
    ui->actionUnpackage_Document->setEnabled(true);

}

void Viewer::on_actionRun_Slide_Show_triggered()
{
    Window_SlideShow *dialog = new Window_SlideShow(QFileInfo(oriFileName).baseName() + ".pdf",remoteControlServer);

    dialog->showNormal();
}



void Viewer::on_actionLaTeX_Office_Viewer_Help_triggered()
{
    QFile::copy(":/documents/Manual.pdf","Manual.pdf");
    QDesktopServices::openUrl(QUrl::fromLocalFile("Manual.pdf"));
}
