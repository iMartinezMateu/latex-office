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
#include "lib/synctex/synctex_parser.h"
#include "lib/synctex/synctex_parser_utils.h"
#include "lib/latex/file.h"
#include "lib/latex/compiler.h"
#include "lib/latex/parser.h"
#include "lib/latex/bibliography.h"
#include <QTextEdit>
#include <QFont>
#include <QMessageBox>
#include <QListWidgetItem>
#include "constants.h"
#include "dialog_modifyimage.h"
#include "dialog_modifyequation.h"
#include "dialog_modifytable.h"
#include "dialog_modifycodeasset.h"
#include "dialog_symbol.h"
#include "dialog_citations.h"
#include "dialog_references.h"
#include "caja.h"
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
    void showPage(int pageNumber, int scaleFactor);
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
      @brief This function hides Caja widget.
      @returns This is a void function.
      */
    void hideTextEdit();
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
      @brief This function fills Puzzle with the current document structure.
      @returns This is a void function.
      */
    void fillList();
    /*************************************************************************************************/
    /**
      @brief This function gets the current document structure.
      @returns The function returns a string list that contains the chapters, sections, subsections and subsubsections of the document.
      */
    QStringList getDocumentStructure();
    /*************************************************************************************************/
    /**
      @brief This function adds a math symbol in the document.
      @param command LaTeX math symbol command.
      @returns This is a void function.
      */
    void addSymbol(QString command);
    /*************************************************************************************************/
    /**
      @brief This function cuts the selected text.
      @returns The function returns a string list that contains the chapters, sections, subsections and subsubsections of the document.
      */
    void cutText();
    /*************************************************************************************************/
    /**
      @brief This function copies the selected text.
      @returns The function returns a string list that contains the chapters, sections, subsections and subsubsections of the document.
      */
    void copyText();
    /*************************************************************************************************/
    /**
      @brief This function pastes some text to the document.
      @returns The function returns a string list that contains the chapters, sections, subsections and subsubsections of the document.
      */
    void pasteText();
    /*************************************************************************************************/
    /**
      @brief This function gets the reference of the text editing zone inside Caja widget.
      @returns The function returns a reference of the text edit zone.
      */
    QTextEdit *getTextEditZone();
    /*************************************************************************************************/
    /**
      @brief This function enables or disables a goal.
      @param cap the amount of words that the user must write to achieve the goal.
      @param warn If true, the program will warn the user when the goal has been achieved.
      @returns The function returns a reference of the text edit zone.
      */
    void enableGoal(int cap, bool warn);
    /*************************************************************************************************/
    /**
      @brief This function gets the goal achievement cap.
      @returns The function returns the amount of words that the user must write to achieve the goal.
      */
    int getGoalCap();
    /*************************************************************************************************/
    /**
      @brief This function disables the current goal.
      @returns This is a void function.
      */
    void disableGoal();
    /*************************************************************************************************/
    /**
      @brief This function gets the amount of words written in a paragrah.
      @returns The function returns the number of words that the user has written in a paragraph.
      */
    int getParagraphWordCount();
    /*************************************************************************************************/
    /**
      @brief This function starts the compiler thread.
      @returns This is a void function.
      */
    void loadThreadPool();
    /*************************************************************************************************/
    /**
      @brief This function hides Puzzle widget.
      @param hide If true, hides the document structure list widget.
      @returns This is a void function.
      */
    void hideDocumentStructureWidget(bool hide);
    /*************************************************************************************************/
    /**
      @brief This function loads a PDF document.
      @param path document file path.
      @param page number of page that will be shown to the user at first.
      @returns This is a void function.
      */
    void loadDocument(QString path, int page);
    /*************************************************************************************************/
    /**
      @brief This function stops the compiler thread.
      @returns This is a void function.
      */
    void stopThreadPool();
    /*End of declaration of public functions*/
signals:
    /*************************************************************************************************/
    /**
      @brief This function emits the Text Attributes Signal when the user selects the text in Caja and stylizes it.
      @returns This is a void function.
      */
    void selectedTextAttributes(int fontSize, QString headingStyle);
    /*************************************************************************************************/
    /**
      @brief This function emits the Text Edit Appeared Signal when Caja is being shown to the user.
      @returns This is a void function.
      */
    void textEditAppeared();
    /*************************************************************************************************/
    /**
      @brief This function emits the Text Edit Disappeared Signal when Caja has just disappeared from the user's view.
      @returns This is a void function.
      */
    void textEditDisappeared();
    /*************************************************************************************************/
    /**
      @brief This function emits the Text Edit Changed Signal when the text stored in Caja has been changed.
      @returns This is a void function.
      */
    void textEditChanged();
public slots:
    void setLineNumber(int lineNumber);
    void refreshCurrentPage();
    void setTextBold();
    void setTextItalics();
    void setTextUnderline();
    void setTextStrikethrough();
    void setTextEmphatize();
    void setTextHyperlink();
    void setTextFootnote();
    void setTextSmallCaps();
    void setTextChapter();
    void setTextSection();
    void setTextSubSection();
    void setTextSubSubSection();
    void setTextParagraph();
    void setTextLeftAlign();
    void setTextCenterAlign();
    void setTextRightAlign();
    void setTextJustify();
    void setTextTiny();
    void setTextSmall();
    void setTextNormal();
    void setTextLarge();
    void setTextXLarge();
    void setTextXXLarge();
    void setTextHuge();
    void setTextXHuge();
    void setNumberedList();
    void setBulletList();
    void setSymbol();
    void setCite();
    void setReference();
    void setColor();

private slots:
    void on_pushButtonNextPage_clicked();
    void on_pushButtonPreviousPage_clicked();
    void on_textEdit_textChanged();
    void on_textEdit_cursorPositionChanged();
    void on_listWidget_itemChanged(QListWidgetItem *item);
    void sortDocumentStructure();
    void on_progressBarWords_valueChanged(int value);
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_listWidget_viewportEntered();

private:
    /*Private variables*/
    Ui::DocumentViewer *ui;
    QString documentPath;
    int currentPage;
    int totalPages;
    int currentScaleFactor;
    Poppler::Document *doc;
    synctex_scanner_t scanner;
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

