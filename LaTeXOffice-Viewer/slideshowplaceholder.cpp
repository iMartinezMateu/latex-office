#include "slideshowplaceholder.h"


SlideShowPlaceHolder::SlideShowPlaceHolder(QWidget *parent) : QLabel(parent)
{

}

SlideShowPlaceHolder::~SlideShowPlaceHolder()
{

}

SlideShowPlaceHolder::SlideShowPlaceHolder(QImage image, Poppler::Document *doc,
                                         int currentPage, int currentScaleFactor, QWidget *parent)
    : QLabel(parent)
{
    this->doc = doc;
    this->currentPage = currentPage;
    this->currentScaleFactor = currentScaleFactor;
    this->image = QPixmap::fromImage(image);
    setPixmap(this->image);
}

void SlideShowPlaceHolder::setData(Poppler::Document *doc, int currentPage,
                                  int currentScaleFactor, QString path, TeXFile * file, DocumentSlideShow* viewer, QString compilerPath)
{
    this->doc = doc;
    this->currentPage = currentPage;
    this->currentScaleFactor = currentScaleFactor;
    this->path = path;
    this->file = file;
    this->viewer = viewer;
    this->compilerPath = compilerPath;
}
QMatrix SlideShowPlaceHolder::matrix() const
{
    return QMatrix(currentScaleFactor * physicalDpiX() / 72.0, 0,
                   0, currentScaleFactor * physicalDpiY() / 72.0,
                   0, 0);
}


