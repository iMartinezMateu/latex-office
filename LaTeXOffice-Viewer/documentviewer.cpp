#include "documentviewer.h"
#include "ui_documentviewer.h"


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
    compilerPath = TeXCompiler::loadPDFCompilerPathSettings();
    bibCompilerPath = TeXCompiler::loadBIBCompilerPathSettings();

}

QList<QImage> DocumentViewer::getImages()
{
    return images;
}
void DocumentViewer::loadBiBFile(TeXBibliography * file)
{
    bibFile = file;
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
        qDebug() << "Document loaded";
    } else {
        qDebug() << "Error trying to load document. That's all I know...";
    }
}

int DocumentViewer::getTotalPages()
{
    return totalPages;
}

void DocumentViewer::showPage(int pageNumber, float scaleFactor)
{
    if (pageNumber >= 0 && pageNumber < totalPages) {
        currentPage = pageNumber;
        currentScaleFactor = scaleFactor;
        ui->imagePlaceHolder->setData(doc, currentPage, currentScaleFactor,documentPath,file,this,compilerPath);

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
}

void DocumentViewer::showNextPage()
{
    showPage(currentPage + 1, currentScaleFactor);
}

void DocumentViewer::maximizeZoom()
{
    if (currentScaleFactor < 4)
    {
        this->currentScaleFactor = currentScaleFactor +  0.25;
        images.clear();
        for (int page=0;page<totalPages;page++)
        {
            images.append(doc->page(page)->renderToImage(
                              currentScaleFactor * physicalDpiX(),
                              currentScaleFactor * physicalDpiY()));
            if (page==currentPage)
                showPage(currentPage, currentScaleFactor);
        }
    }
}

void DocumentViewer::minimizeZoom()
{
    if (currentScaleFactor > 1)
    {
        this->currentScaleFactor = currentScaleFactor - 0.25;
        images.clear();
        for (int page=0;page<totalPages;page++)
        {
            images.append(doc->page(page)->renderToImage(
                              currentScaleFactor * physicalDpiX(),
                              currentScaleFactor * physicalDpiY()));
            if (page==currentPage)
                showPage(currentPage, currentScaleFactor);
        }
    }
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
    delete doc;
}

qreal DocumentViewer::scale() const
{
    return currentScaleFactor;
}

void DocumentViewer::on_pushButtonMinimizeZoom_clicked()
{
    minimizeZoom();
}

void DocumentViewer::on_pushButtonMaximizeZoom_clicked()
{
    maximizeZoom();
}
