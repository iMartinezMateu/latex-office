#ifndef DOCUMENTVIEWER_H
#define DOCUMENTVIEWER_H

#include <QWidget>
#include <QDebug>
#include <QPixmap>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <poppler-qt5.h>
#include <QPainter>
#include <QLabel>
#include <QFileInfo>
#include <QList>
#include "lib/latex/file.h"
#include "lib/latex/compiler.h"
#include "lib/latex/parser.h"
#include "lib/latex/bibliography.h"
#include <QTextEdit>
#include <QFont>
#include <QMessageBox>
#include <QListWidgetItem>
#include "constants.h"
#include <QColorDialog>

namespace Ui {

class DocumentViewer;
}

class DocumentViewer : public QWidget
{
    Q_OBJECT

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit DocumentViewer(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~DocumentViewer();
    /*************************************************************************************************/
    /**
      @brief This function loads a PDF document.
      @param path document file path.
      @returns This is a void function.
      */
    void loadDocument(QString path);
    /*************************************************************************************************/
    /**
      @brief This function loads a LaTeX document but it will not read the file content, so it cannot be shown in the viewer.
      @param path document file path.
      @returns This is a void function.
      */
    void loadTeXFile(TeXFile *file);
    /*************************************************************************************************/
    /**
      @brief This function loads a LaTeX bibliography but it will not read the file content, so it cannot be shown in the viewer.
      @param path bibliography file path.
      @returns This is a void function.
      */
    void loadBiBFile(TeXBibliography *file);
    /*************************************************************************************************/
    /**
      @brief This function shows a PDF page in the viewer.
      @param pageNumber PDF page number to be shown
      @param saleFactor factor to adjust the PDF size render.
      @returns This is a void function.
      */
    void showPage(int pageNumber, float scaleFactor);
    /*************************************************************************************************/
    /**
      @brief This function adjusts the viewer to show the previous PDF page of the document.
      @returns This is a void function.
      */
    void showPreviousPage();
    /*************************************************************************************************/
    /**
      @brief This function adjusts the viewer to show the next PDF page of the document.
      @returns This is a void function.
      */
    void showNextPage();

    /*************************************************************************************************/
    /**
      @brief This function increases the view zoom.
      @returns This is a void function.
      */
    void maximizeZoom();

    /*************************************************************************************************/
    /**
      @brief This function decreases the view zoom.
      @returns This is a void function.
      */
    void minimizeZoom();
    /*************************************************************************************************/
    /**
      @brief This function closes the current document from the viewer.
      @returns This is a void function.
      */
    void closeDocument();
    /*************************************************************************************************/
    /**
      @brief This function calculates a matrix deppending of the screen DPI's, so LaTeXOffice can map correctly the PDF coords in the SyncTeX file and the mouse coords.
      @returns The function returns a matrix that will be used by other functions.
      */
    QMatrix matrix() const;
    /*************************************************************************************************/
    /**
      @brief This function returns the PDF scale factor assigned.
      @returns The function returns the PDF scale factor applied to the render made by LaTeX Office.
      */
    qreal scale() const;
    /*************************************************************************************************/
    /**
      @brief This function gets the selected line number.
      @returns The function returns the line number that corresponds with the PDF page element that was clicked by the user.
      */
    int getSelectedLineNumber();
    /*************************************************************************************************/
    /**
      @brief This function refresh the PDF render so the last changes made to the document are shown.
      @returns This is a void function.
      */
    void refresh(int pageNumber);
    /*************************************************************************************************/
    /**
      @brief This function gets the current page.
      @returns The function returns the page number of the current page that the user is reading at that moment.
      */
    int getCurrentPage();
    /*************************************************************************************************/
    /**
      @brief This function gets the PDF renders list.
      @returns The function returns all the document pages that was rendered by LaTeX Office.
      */
    QList<QImage> getImages();
    /*************************************************************************************************/
    /**
      @brief This function gets the total pages of the document.
      @returns The function returns the latest page of the document.
      */
    int getTotalPages();

    /*************************************************************************************************/
    /**
      @brief This function searchs a string in the entire document.
      @param string string to be searched.
      @param caseSensitive If true, the searching process will take care of the string caps.
      @returns This is a void function.
      */
    void searchString(QString string, bool caseSensitive);

    /*************************************************************************************************/
    /**
      @brief This function loads a PDF document.
      @param path document file path.
      @param page number of page that will be shown to the user at first.
      @returns This is a void function.
      */
    void loadDocument(QString path, int page);

public slots:
    void refreshCurrentPage();

private slots:
    void on_pushButtonNextPage_clicked();
    void on_pushButtonPreviousPage_clicked();

    void on_pushButtonMinimizeZoom_clicked();

    void on_pushButtonMaximizeZoom_clicked();

private:
    /*Private variables*/
    Ui::DocumentViewer *ui;
    QString documentPath;
    int currentPage;
    int totalPages;
    float currentScaleFactor;
    Poppler::Document *doc;
    QImage image;
    QList<QImage> images;
    int selectedLineNumber;
    TeXFile *file;
    TeXBibliography *bibFile;
    TeXCommands command;
    QString compilerPath;
    QString bibCompilerPath;
    QStringList documentStructureLines;
    bool warnGoalAchieved;
    int goalCap;
    int paragraphWordCount;
    int initialParagraphWordCount;
    int previousGoalWordCount;
    int goalWordCount;
    QList<QStringList> definitionsList;
    /*End of declaration of private variables*/
};

#endif // DOCUMENTVIEWER_H

