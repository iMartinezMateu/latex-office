#ifndef SLIDESHOWPLACEHOLDER_H
#define SLIDESHOWPLACEHOLDER_H


#include <QLabel>
#include <QMouseEvent>
#include <poppler-qt5.h>
#include <documentslideshow.h>
#include <lib/latex/file.h>
#include <QApplication>
#include <QtMath>
class SlideShowPlaceHolder : public QLabel
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    SlideShowPlaceHolder(QWidget *parent);
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param image the image reference that corresponds to the renderized PDF page.
      @param doc the reference of the PDF document that is going to be renderized by Poppler.
      @param currentPage current page number shown in the widget.
      @param currentScaleFactor current scale factor applied in the render.
      @param scanner scanner reference that will scan the SyncTeX sync file.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    SlideShowPlaceHolder(QImage image, Poppler::Document *doc, int currentPage,
                        int currentScaleFactor, QWidget *parent);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~SlideShowPlaceHolder();

    /*************************************************************************************************/
    /**
      @brief This function calculates a matrix deppending of the screen DPI's, so LaTeXOffice can map correctly the PDF coords in the SyncTeX file and the mouse coords.
      @returns The function returns a matrix that will be used by other functions.
      */
    QMatrix matrix() const;
    /*************************************************************************************************/
    /**
      @brief This function sets the necessary data so the dialog can work.
      @param doc the reference of the PDF document that is going to be renderized by Poppler.
      @param currentPage current page number shown in the widget.
      @param currentScaleFactor current scale factor applied in the render.
      @param scanner scanner reference that will scan the SyncTeX sync file.
      @param path SyncTeX file path.
      @param file LaTeX file reference.
      @param viewer widget reference.
      @param compilerPath PDFLaTeX binary path.
      @returns This is a void function.
      */
    void setData(Poppler::Document *doc, int currentPage, int currentScaleFactor,
                  QString path, TeXFile *file, DocumentSlideShow *viewer, QString compilerPath);
    /*End of declaration of public functions*/

signals:
    void getLineNumber(int line);

private:
    /*Private variables*/
    Poppler::Document *doc;
    int currentScaleFactor;
    int currentPage;
    QPixmap  image;
    QString path;
    TeXFile* file;
    QString compilerPath;
    DocumentSlideShow* viewer;
    /*End of declaration of private variables*/
};

#endif // SlideShowPlaceHolder_H
