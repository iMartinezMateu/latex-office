#include "documentslideshow.h"
#include "ui_documentslideshow.h"

DocumentSlideShow::DocumentSlideShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocumentSlideShow)
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


QList<QImage> DocumentSlideShow::getImages()
{
    return images;
}
void DocumentSlideShow::loadBiBFile(TeXBibliography * file)
{
    bibFile = file;
}

void DocumentSlideShow::refreshCurrentPage()
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

void DocumentSlideShow::refresh(int pageNumber)
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
void DocumentSlideShow::loadTeXFile(TeXFile *file)
{
    this->file = file;
}
int DocumentSlideShow::getCurrentPage()
{
    return currentPage;
}
int DocumentSlideShow::getSelectedLineNumber()
{
    return selectedLineNumber;
}
DocumentSlideShow::~DocumentSlideShow()
{
    delete ui;
}
QMatrix DocumentSlideShow::matrix() const
{
    return QMatrix(currentScaleFactor * physicalDpiX() / 72.0, 0,
                   0, currentScaleFactor * physicalDpiY() / 72.0,
                   0, 0);
}
void DocumentSlideShow::loadDocument(QString path)
{
    qDebug() << "Loading document in path " + path;
    documentPath = path;
    doc = Poppler::Document::load(path);
    if (doc != NULL) {
        currentPage = 0;
        currentScaleFactor = 2;
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

void DocumentSlideShow::loadDocument(QString path, int page)
{
    qDebug() << "Loading document in path " + path;

    documentPath = path;
    doc = Poppler::Document::load(path);
    if (doc != NULL) {
        currentPage = page;
        currentScaleFactor = 2;
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

int DocumentSlideShow::getTotalPages()
{
    return totalPages;
}

void DocumentSlideShow::showPage(int pageNumber, float scaleFactor)
{
    if (pageNumber >= 0 && pageNumber < totalPages) {
        currentPage = pageNumber;
        currentScaleFactor = scaleFactor;
        ui->imagePlaceHolder->setData(doc, currentPage, currentScaleFactor,documentPath,file,this,compilerPath);
        ui->imagePlaceHolder->setPixmap(QPixmap::fromImage(images.at(currentPage)));

        qDebug() << "Displaying page number" + pageNumber;
    }
}


void DocumentSlideShow::showPreviousPage()
{
    showPage(currentPage - 1, currentScaleFactor);
}

void DocumentSlideShow::showNextPage()
{
    showPage(currentPage + 1, currentScaleFactor);
}

void DocumentSlideShow::maximizeZoom()
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

void DocumentSlideShow::minimizeZoom()
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

qreal DocumentSlideShow::scale() const
{
    return currentScaleFactor;
}

void DocumentSlideShow::closeDocument()
{
    delete doc;
}
