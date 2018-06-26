#include "documentplaceholder.h"
DocumentPlaceHolder::DocumentPlaceHolder(QWidget *parent) : QLabel(parent)
{

}

DocumentPlaceHolder::DocumentPlaceHolder(QImage image, Poppler::Document *doc,
                                         int currentPage, int currentScaleFactor, QWidget *parent)
    : QLabel(parent)
{
    this->doc = doc;
    this->currentPage = currentPage;
    this->currentScaleFactor = currentScaleFactor;
    this->image = QPixmap::fromImage(image);
    setPixmap(this->image);
}

DocumentPlaceHolder::~DocumentPlaceHolder()
{

}
void DocumentPlaceHolder::setData(Poppler::Document *doc, int currentPage,
                                  int currentScaleFactor, QString path, TeXFile * file, DocumentViewer* viewer, QString compilerPath)
{
    this->doc = doc;
    this->currentPage = currentPage;
    this->currentScaleFactor = currentScaleFactor;
    this->path = path;
    this->file = file;
    this->viewer = viewer;
    this->compilerPath = compilerPath;
}
QMatrix DocumentPlaceHolder::matrix() const
{
    return QMatrix(currentScaleFactor * physicalDpiX() / 72.0, 0,
                   0, currentScaleFactor * physicalDpiY() / 72.0,
                   0, 0);
}


