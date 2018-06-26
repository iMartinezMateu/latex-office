#include "documentplaceholder.h"
DocumentPlaceHolder::DocumentPlaceHolder(QWidget *parent) : QLabel(parent)
{

}

DocumentPlaceHolder::DocumentPlaceHolder(QImage image, Poppler::Document *doc,
                                         int currentPage, int currentScaleFactor, synctex_scanner_t scanner, QWidget *parent)
    : QLabel(parent)
{
    this->doc = doc;
    this->currentPage = currentPage;
    this->currentScaleFactor = currentScaleFactor;
    this->scanner = scanner;
    this->image = QPixmap::fromImage(image);
    setPixmap(this->image);
}

DocumentPlaceHolder::~DocumentPlaceHolder()
{

}
void DocumentPlaceHolder::setData(Poppler::Document *doc, int currentPage,
                                  int currentScaleFactor, synctex_scanner_t scanner, QString path, TeXFile * file, DocumentViewer* viewer, QString compilerPath)
{
    this->doc = doc;
    this->currentPage = currentPage;
    this->currentScaleFactor = currentScaleFactor;
    this->scanner = scanner;
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
void DocumentPlaceHolder::mousePressEvent(QMouseEvent *event)
{

    viewer->stopThreadPool();
        file->readFile();
        file->saveFile();
        file->compile(compilerPath);
        viewer->loadThreadPool();
   scanner = synctex_scanner_new_with_output_file(path.toStdString().c_str(), NULL, 1);
    if (!doc) {
        return;
    }
    QPointF pagePos((event->pos().x() - (width() - pixmap()->width()) / 2.0) /
                    currentScaleFactor / physicalDpiX() * 72.0,
                    (event->pos().y() - (height() - pixmap()->height()) / 2.0) / currentScaleFactor /
                    physicalDpiY() * 72.0);
    if (synctex_edit_query(scanner, currentPage + 1, pagePos.x(), pagePos.y()) > 0) {
        synctex_node_t node;
        while ((node = synctex_next_result(scanner)) != NULL) {
            int lineNumber = synctex_node_line(node);
            emit getLineNumber(lineNumber);
        }
    }
    synctex_scanner_free(scanner);
}

void DocumentPlaceHolder::mouseMoveEvent(QMouseEvent *event)
{
    if (!doc) {
        return;
    }
}
void DocumentPlaceHolder::mouseReleaseEvent(QMouseEvent *)
{
    if (!doc) {
        return;
    }
}
