#ifndef FILE_H
#define FILE_H

#include <QObject>
#include <QStringList>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QVector>
#include <QProcess>
#include <QFileInfo>
#include <QDir>
#include <QTime>
#include <QRegularExpression>

#include "commands.h"
#include "constants.h"
#include "packages.h"

#define MAX_UNDO_REDO_ACTIONS 30
/**
 * The TeXFile class represents all the operations that LaTeX Office can do to a LaTeX file.
 *
 * @author Iván Martínez Mateu
 */
class TeXFile : public QObject
{
    Q_OBJECT
public:
    /*Public functions*/
    /*************************************************************************************************/
    /**
      @brief This is the constructor function that reads the file provided by the unique argument and enables the use of the rest functions declared here.
      @param filePath document file path.
      @param mustReadFile force reading the supplied file (true) or not.
      @returns This is a void function.
      */
        explicit TeXFile(QString filePath, bool mustReadFile);
    /*************************************************************************************************/
    /**
      @brief Destroy a TeXFile instance.
      @returns This is a void function.
      */
        ~TeXFile();
    /*************************************************************************************************/
    /**
      @brief This is the function that reads and stores the file content to fast-access memory (RAM).
      @returns This is a void function.
      */
        void readFile();
        /*************************************************************************************************/
        /**
          @brief This is the function that reads and saves the file content stored in fast-access memory (RAM) to the file supplied with the constructor function.
          @returns This is a void function.
          */
        void saveFile();
        /*************************************************************************************************/
        /**
          @brief This is the function that reads and saves the file content stored in fast-access memory (RAM) to the file supplied.
          @param filePath path where the file must be saved.
          @returns This is a void function.
          */
        void saveFile(QString filePath);
        /*************************************************************************************************/
        /**
          @brief While the compiling process has finished, LaTeX generates some auxiliary files that are not needed if the document will be compiled again. This function deletes this auxiliary files without touching the document.
          @returns This is a void function.
          */
        void deleteTemporaryFiles();
        /*************************************************************************************************/
        /**
          @brief This function searches a string or a line into the file content stored in RAM.
          @param searchString string or line to search.
          @returns This function will return the line number where is the search string. Neither, it will return -1.
          */
        int getLineNumber(QString searchString);
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX line which declares the document beginning.
          @returns This is a void function.
          */
        void setBeginDocumentCommand();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX line which declares the document ending.
          @returns This is a void function.
          */
        void setEndDocumentCommand();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the document's beginning line.
          @returns This function will return the line number where is the search string. Neither, it will return -1.
          */
        int getBeginDocumentCommand();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the document's ending line.
          @returns This function will return the line number where is the search string. Neither, it will return -1.
          */
        int getEndDocumentCommand();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setArabicLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line number. Neither, it will return -1.
          */
        int removeArabicLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line number where is the declared language declaration. Neither, it will return -1.
          */
        int getArabicLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setBulgarianLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line numbers. Neither, it will return -1.
          */
        QVector<int> removeBulgarianLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        QVector<int> getBulgarianLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setRussianLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line numbers. Neither, it will return -1.
          */
        QVector<int> removeRussianLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        QVector<int> getRussianLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setUkrainianLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line numbers. Neither, it will return -1.
          */
        QVector<int> removeUkrainianLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        QVector<int> getUkrainianLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setChineseLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line number. Neither, it will return -1.
          */
        int removeChineseLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        int getChineseLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setCzechLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line number. Neither, it will return -1.
          */
        int removeCzechLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        int getCzechLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setFinnishLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line number. Neither, it will return -1.
          */
        int removeFinnishLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        int getFinnishLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setFrenchLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line number. Neither, it will return -1.
          */
        int removeFrenchLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        int getFrenchLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setGermanLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line number. Neither, it will return -1.
          */
        int removeGermanLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        int getGermanLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setGreekLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line numbers. Neither, it will return -1.
          */
        QVector<int> removeGreekLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        QVector<int> getGreekLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setIcelandicLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line numbers. Neither, it will return -1.
          */
        QVector<int> removeIcelandicLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        QVector<int> getIcelandicLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setFaroeseLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line numbers. Neither, it will return -1.
          */
        QVector<int> removeFaroeseLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        QVector<int> getFaroeseLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setItalianLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line numbers. Neither, it will return -1.
          */
        int removeItalianLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        int getItalianLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setKoreanLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line numbers. Neither, it will return -1.
          */
        int removeKoreanLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        int getKoreanLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setPersianLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line numbers. Neither, it will return -1.
          */
        int removePersianLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        int getPersianLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setPolishLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line numbers. Neither, it will return -1.
          */
        QVector<int> removePolishLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        QVector<int> getPolishLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setPortugueseLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line numbers. Neither, it will return -1.
          */
        int removePortugueseLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        int getPortugueseLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setSlovakLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line numbers. Neither, it will return -1.
          */
        QVector<int> removeSlovakLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        QVector<int> getSlovakLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setSpanishLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line numbers. Neither, it will return -1.
          */
        QVector<int> removeSpanishLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        QVector<int> getSpanishLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setTibetanLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line numbers. Neither, it will return -1.
          */
        int removeTibetanLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        int getTibetanLanguage();
        /*************************************************************************************************/
        /**
          @brief This function adds the corresponding LaTeX lines so the document can use the declared language.
          @returns This is a void function.
          */
        void setEnglishLanguage();
        /*************************************************************************************************/
        /**
          @brief This function removes the corresponding LaTeX lines which declares the use of a particular document language.
          @returns This function will return the deleted line numbers. Neither, it will return -1.
          */
        int removeEnglishLanguage();
        /*************************************************************************************************/
        /**
          @brief This function searches where is the declared language declaration line.
          @returns This function will return the line numbers where is the declared language declaration. Neither, it will return -1.
          */
        int getEnglishLanguage();
        /*************************************************************************************************/
        /**
          @brief This function sets the main font to be used in the document.
          @param fontName font name reference to be used in the document.
          @returns This is a void function.
          */
        void setMainFont(QString fontName);
        /*************************************************************************************************/
        /**
          @brief This function searchs if the font introduced by argument is being used in the document.
          @param fontName font name reference.
          @returns This function will return the line number where is the main font declared. Neither, it will return -1.
          */
        int getMainFont(QString fontName);
        /*************************************************************************************************/
        /**
          @brief This function deletes the main font line.
          @returns This is a void function.
          */
        void deleteMainFont();
        /*************************************************************************************************/
        /**
          @brief This function add the corresponding lines so the document can use the declared package.
          @param packageName package name reference.
          @returns This is a void function.
          */
        void setPackage(QString packageName);
        /*************************************************************************************************/
        /**
          @brief This function add the corresponding lines so the document can use the declared package.
          @param packageName package name reference.
          @param packageOptions options to be supplied in order to make the package work correctly.
          @returns This is a void function.
          */
        void setPackage(QString packageName, QString packageOptions);
        /*************************************************************************************************/
        /**
          @brief This function searchs the package line declaration in the document.
          @param packageName package name reference to be found.
          @returns This function will return the line number where is the package declared. Neither, it will return -1.
          */
        int getPackage(QString packageName);
        /*************************************************************************************************/
        /**
          @brief This function searchs the package line declaration in the document.
          @param packageName package name reference to be found.
          @param packageOptions options needed by the package to be found.
          @returns This function will return the line number where is the package declared. Neither, it will return -1.
          */
        int getPackage(QString packageName, QString packageOptions);
        /*************************************************************************************************/
        /**
          @brief This function adds a LaTeX command between the document beginning and ending. The ordering of the commands are made automatically.
          @param command LaTeX command to be added.
          @returns This is a void function.
          */
        void setTeXCommand(QString command);
        /*************************************************************************************************/
        /**
          @brief This function adds a LaTeX command in the indicated line number. The ordering of the commands are made automatically.
          @param command LaTeX command to be added.
          @param lineNumber line Number to be included the new command.
          @returns This is a void function.
          */
        void setTeXCommand(QString command, int lineNumber);
        /*************************************************************************************************/
        /**
          @brief This function adds the LaTeX document preamble directly.
          @param classFile LaTeX class file to be added.
          @returns This is a void function.
          */
        void setDocumentPreamble(QString classFile);
        /*************************************************************************************************/
        /**
          @brief This function adds the LaTeX document preamble directly.
          @param documentType LaTeX document type.
          @param documentFontSize LaTeX document font size.
          @param paperLayout LaTeX document paper layout.
          @param paperSize LaTeX document paper size.
          @param documentLayout LaTeX document layout.
          @param chapterLayout LaTeX chapter layout.
          @param columnLayout LaTeX column layout.
          @returns This is a void function.
          */
        void setDocumentPreamble(QString documentType, QString documentFontSize,
                                 QString paperLayout, QString paperSize, QString documentLayout, QString chapterLayout, QString columnLayout);
        /*************************************************************************************************/
        /**
          @brief This function adds an abstract to the document.
          @param abstract abstract text content.
          @returns This is a void function.
          */
        void setAbstract(QString abstract);
        /*************************************************************************************************/
        /**
          @brief This function deletes the abstract to the document.
          @returns This is a void function.
          */
        void deleteAbstract();
        /*************************************************************************************************/
        /**
          @brief This function get the LaTeX line number where the document preamble is declared.
          @returns This function will return the line number where is the preamble declared. Neither, it will return -1.
          */
        int getDocumentPreamble();
        /*************************************************************************************************/
        /**
          @brief This function clear all the document content stored in volatile memory.
          @returns This is a void function.
          */
        void clearCommands();
        /*************************************************************************************************/
        /**
          @brief This function writes plain text that will be shown in the document like a new paragraph.
          @param content text that will be written to the document.
          @returns This is a void function.
          */
        void writePlainText(QString content);
        /*************************************************************************************************/
        /**
          @brief This function writes plain text that will be shown in the document like a new paragraph.
          @param content text that will be written to the document.
          @param lineNumber line where the text will be put.
          @returns This is a void function.
          */
        void writePlainText(QString content, int lineNumber);
        /*************************************************************************************************/
        /**
          @brief This function creates a new empty line in the document.
          @returns This is a void function.
          */
        void setNewLine();
        /*************************************************************************************************/
        /**
          @brief This function creates a new empty line in the document.
          @param lineNumber document position where the empty line will be added.
          @returns This is a void function.
          */
        void setNewLine(int lineNumber);
        /*************************************************************************************************/
        /**
          @brief This function creates a new paragraph command in the document.
          @returns This is a void function.
          */
        void setNewParagraph();
        /*************************************************************************************************/
        /**
          @brief This function creates a new paragraph command in the document.
          @param lineNumber document position where the paragraph command will be added.
          @returns This is a void function.
          */
        void setNewParagraph(int lineNumber);
        /*************************************************************************************************/
        /**
          @brief This function creates a new page command in the document.
          @returns This is a void function.
          */
        void setNewPage();
        /*************************************************************************************************/
        /**
          @brief This function creates a new page command in the document.
          @param lineNumber document position where the new page command will be added.
          @returns This is a void function.
          */
        void setNewPage(int lineNumber);
        /*************************************************************************************************/
        /**
          @brief Compile the LaTeX file to generate the document's PDF output.
          @param compilerPath path where PDFLaTeX compiler binary can be found.
          @returns This is a void function.
          */
        void compile(QString compilerPath);
        /*************************************************************************************************/
        /**
          @brief Compile the LaTeX file to generate the document's PDF output.
          @param compilerPath path where PDFLaTeX compiler binary can be found.
          @param wait If true, the function will wait until the compiling process is completed.
          @returns This is a void function.
          */
        void compile(QString compilerPath, bool wait);
        /*************************************************************************************************/
        /**
          @brief This function gets the directory where the LaTeX document is stored.
          @returns This function returns the document path.
          */
        QString getDirectory();
        /*************************************************************************************************/
        /**
          @brief This function finishes the document editing and deletes the temporary files.
          @returns This is a void function.
          */
        void close();
        /*************************************************************************************************/
        /**
          @brief This function gets the document content.
          @returns This function returns the LaTeX commands stored in the document as a string list.
          */
        QStringList getFileContent();
        /*************************************************************************************************/
        /**
          @brief This function gets the document name.
          @returns This function returns the LaTeX document name.
          */
        QString getFileName();
        /*************************************************************************************************/
        /**
          @brief This function gets the document type.
          @returns This function returns the LaTeX document type.
          */
        QString getDocumentType();
        /*************************************************************************************************/
        /**
          @brief This function gets the document font size.
          @returns This function returns the font size used in the document.
          */
        QString getDocumentFontSize();
        /*************************************************************************************************/
        /**
          @brief This function gets the document chapter layout.
          @returns This function returns the chapter layout used in the document.
          */
        QString getChapterLayout();
        /*************************************************************************************************/
        /**
          @brief This function gets the document paper layout.
          @returns This function returns the paper layout used in the document.
          */
        QString getPaperLayout();
        /*************************************************************************************************/
        /**
          @brief This function gets the document paper size.
          @returns This function returns the paper size used in the document.
          */
        QString getPaperSize();
        /*************************************************************************************************/
        /**
          @brief This function gets the document layout.
          @returns This function returns the general layout used in the document.
          */
        QString getDocumentLayout();
        /*************************************************************************************************/
        /**
          @brief This function gets the document column layout.
          @returns This function returns the column layout used in the document.
          */
        QString getColumnLayout();
        /*************************************************************************************************/
        /**
          @brief This function gets the document title.
          @returns This function returns the title used in the document.
          */
        QString getDocumentTitle();
        /*************************************************************************************************/
        /**
          @brief This function gets the document date.
          @returns This function returns the date used in the document.
          */
        QString getDocumentDate();
        /*************************************************************************************************/
        /**
          @brief This function gets the document author.
          @returns This function returns the author used in the document.
          */
        QString getDocumentAuthor();
        /*************************************************************************************************/
        /**
          @brief This function gets the document abstract.
          @returns This function returns the abstract used in the document.
          */
        QString getDocumentAbstract();
        /*************************************************************************************************/
        /**
          @brief This function gets the document address.
          @returns This function returns the address used in the document.
          */
        QString getDocumentAddress();
        /*************************************************************************************************/
        /**
          @brief This function gets the document type index (number) so UI elements can understand better the user's choice.
          @returns This function returns the type index used in the document.
          */
        int getDocumentTypeIndex();
        /*************************************************************************************************/
        /**
          @brief This function gets the document font size index (number) so UI elements can understand better the user's choice.
          @returns This function returns the font size index used in the document.
          */
        int getDocumentFontSizeIndex();
        /*************************************************************************************************/
        /**
          @brief This function gets the chapter layout index (number) so UI elements can understand better the user's choice.
          @returns This function returns the chapter layout index used in the document.
          */
        int getChapterLayoutIndex();
        /*************************************************************************************************/
        /**
          @brief This function gets the paper layout index (number) so UI elements can understand better the user's choice.
          @returns This function returns the paper layout index used in the document.
          */
        int getPaperLayoutIndex();
        /*************************************************************************************************/
        /**
          @brief This function gets the chapter size index (number) so UI elements can understand better the user's choice.
          @returns This function returns the chapter size index used in the document.
          */
        int getPaperSizeIndex();
        /*************************************************************************************************/
        /**
          @brief This function gets the document layout index (number) so UI elements can understand better the user's choice.
          @returns This function returns the document layout index used in the document.
          */
        int getDocumentLayoutIndex();
        /*************************************************************************************************/
        /**
          @brief This function gets the column layout index (number) so UI elements can understand better the user's choice.
          @returns This function returns the column layout index used in the document.
          */
        int getColumnLayoutIndex();
        /*************************************************************************************************/
        /**
          @brief This function gets the document language index (number) so UI elements can understand better the user's choice.
          @returns This function returns the document language index used in the document.
          */
        int getDocumentLanguageIndex();
        /*************************************************************************************************/
        /**
          @brief This function sets the document title and puts the corresponding LaTeX command.
          @param title text content for the document title.
          @returns This is a void function.
          */
        void setDocumentTitle(QString title);
        /*************************************************************************************************/
        /**
          @brief This function sets the document date and puts the corresponding LaTeX command.
          @param date text content for the document date.
          @returns This is a void function.
          */
        void setDocumentDate(QString date);
        /*************************************************************************************************/
        /**
          @brief This function sets the document author and puts the corresponding LaTeX command.
          @param author text content for the document author.
          @returns This is a void function.
          */
        void setDocumentAuthor(QString author);
        /*************************************************************************************************/
        /**
          @brief This function sets the document type and puts the corresponding LaTeX command.
          @param type text content for the document type.
          @returns This is a void function.
          */
        void setDocumentType(QString type);
        /*************************************************************************************************/
        /**
          @brief This function sets the document address and puts the corresponding LaTeX command.
          @param address text content for the document address.
          @returns This is a void function.
          */
        void setDocumentAddress(QString address);
        /*************************************************************************************************/
        /**
          @brief This function sets the font size and puts the corresponding LaTeX command.
          @param fontSize main font size to be used.
          @returns This is a void function.
          */
        void setDocumentFontSize(QString fontSize);
        /*************************************************************************************************/
        /**
          @brief This function sets the paper layout and puts the corresponding LaTeX command.
          @param paperLayout paper layout to be used.
          @returns This is a void function.
          */
        void setPaperLayout(QString paperLayout);
        /*************************************************************************************************/
        /**
          @brief This function sets the chapter layout and puts the corresponding LaTeX command.
          @param chapterLayout chapter layout to be used.
          @returns This is a void function.
          */
        void setChapterLayout(QString chapterLayout);
        /*************************************************************************************************/
        /**
          @brief This function sets the paper size and puts the corresponding LaTeX command.
          @param paperSize paper size to be used.
          @returns This is a void function.
          */
        void setPaperSize(QString paperSize);
        /*************************************************************************************************/
        /**
          @brief This function sets the document layout and puts the corresponding LaTeX command.
          @param documentLayout document layout to be used.
          @returns This is a void function.
          */
        void setDocumentLayout(QString documentLayout);
        /*************************************************************************************************/
        /**
          @brief This function sets the column layout and puts the corresponding LaTeX command.
          @param columnLayout column layout to be used.
          @returns This is a void function.
          */
        void setColumnLayout(QString columnLayout);
        /*************************************************************************************************/
        /**
          @brief This function sets the document type index.
          @param index document type index to be used.
          @returns This is a void function.
          */
        void setDocumentTypeIndex(int index);
        /*************************************************************************************************/
        /**
          @brief This function sets the document font size index.
          @param index document font size index to be used.
          @returns This is a void function.
          */
        void setDocumentFontSizeIndex(int index);
        /*************************************************************************************************/
        /**
          @brief This function sets the paper layout index.
          @param index paper layout index to be used.
          @returns This is a void function.
          */
        void setPaperLayoutIndex(int index);
        /*************************************************************************************************/
        /**
          @brief This function sets the chapter layout index.
          @param index chapter layout index to be used.
          @returns This is a void function.
          */
        void setChapterLayoutIndex(int index);
        /*************************************************************************************************/
        /**
          @brief This function sets the paper size index.
          @param index paper size index to be used.
          @returns This is a void function.
          */
        void setPaperSizeIndex(int index);
        /*************************************************************************************************/
        /**
          @brief This function sets the document layout index.
          @param index document layout index to be used.
          @returns This is a void function.
          */
        void setDocumentLayoutIndex(int index);
        /*************************************************************************************************/
        /**
          @brief This function sets the column layout index.
          @param index column layout index to be used.
          @returns This is a void function.
          */
        void setColumnLayoutIndex(int index);
        /*************************************************************************************************/
        /**
          @brief This function sets the document language index.
          @param index document language index to be used.
          @returns This is a void function.
          */
        void setDocumentLanguageIndex(int index);
        /*************************************************************************************************/
        /**
          @brief This function sets the document abstract.
          @param abstract text content for the document abstract.
          @returns This is a void function.
          */
        void setDocumentAbstract(QString abstract);
        /*************************************************************************************************/
        /**
          @brief This function deletes the document title.
          @returns This is a void function.
          */
        void deleteTitle();
        /*************************************************************************************************/
        /**
          @brief This function deletes the document author.
          @returns This is a void function.
          */
        void deleteAuthor();
        /*************************************************************************************************/
        /**
          @brief This function deletes the document date.
          @returns This is a void function.
          */
        void deleteDate();
        /*************************************************************************************************/
        /**
          @brief This function deletes the document address.
          @returns This is a void function.
          */
        void deleteAddress();
        /*************************************************************************************************/
        /**
          @brief This function sets the document title.
          @param title text content for the title.
          @returns This is a void function.
          */
        void setTitle(QString title);
        /*************************************************************************************************/
        /**
          @brief This function sets the document author.
          @param author text content for the author.
          @returns This is a void function.
          */
        void setAuthor(QString author);
        /*************************************************************************************************/
        /**
          @brief This function sets the document date.
          @param date text content for the date.
          @returns This is a void function.
          */
        void setDate(QString date);
        /*************************************************************************************************/
        /**
          @brief This function sets the document address.
          @param address text content for the address.
          @returns This is a void function.
          */
        void setAddress(QString address);
        /*************************************************************************************************/
        /**
          @brief This function starts precompiling the document, so next compiling process will take less time to generate the PDF output.
          @param compilerPath PDFLaTeX binary path.
          @returns This is a void function.
          */
        void precompile(QString compilerPath);
        /*************************************************************************************************/
        /**
          @brief This function replaces the command stored in a line number with another.
          @param newCommand  new LaTeX command to add.
          @param lineNumberToReplace LaTeX file line number to replace.
          @returns This is a void function.
          */
        void replaceTeXCommand(QString newCommand, int lineNumberToReplace);
        /*************************************************************************************************/
        /**
          @brief This function deprecompiles the document, so next compiling process will take more time to generate the PDF output but it can be compiled outside LaTeX Office environment.
          @param compilerPath PDFLaTeX binary path.
          @returns This is a void function.
          */
        void deprecompile();
        /*************************************************************************************************/
        /**
          @brief This function deletes the entire text content of a chapter.
          @param chapterCommand the chapter to be deleted, for example "\\chapter{foo}".
          @returns This is a void function.
          */
        void deleteDocumentChapterContent(QString chapterCommand);
        /*************************************************************************************************/
        /**
          @brief This function deletes the entire text content of a section.
          @param sectionCommand the section to be deleted, for example "\\section{foo}".
          @returns This is a void function.
          */
        void deleteDocumentSectionContent(QString sectionCommand);
        /*************************************************************************************************/
        /**
          @brief This function deletes the entire text content of a subsection.
          @param subsectionCommand the subsection to be deleted, for example "\\subsection{foo}".
          @returns This is a void function.
          */
        void deleteDocumentSubSectionContent(QString subsectionCommand);
        /*************************************************************************************************/
        /**
          @brief This function deletes the entire text content of a subsubsection.
          @param subsubsectionCommand the subsubsection to be deleted, for example "\\subsubsection{foo}".
          @returns This is a void function.
          */
        void deleteDocumentSubSubSectionContent(QString subsubsectionCommand);
        /*************************************************************************************************/
        /**
          @brief This function replaces the entire file content stored in RAM to a new content.
          @param content new file content.
          @returns This is a void function.
          */
        void setFileContent(QStringList content);
        /*************************************************************************************************/
        /**
          @brief This function deletes a LaTeX command stored in the document.
          @param lineNumberToDelete document line to be deleted.
          @returns This is a void function.
          */
        void deleteTeXCommand(int lineNumberToDelete);
        /*************************************************************************************************/
        /**
          @brief This function deletes a LaTeX command stored in the document.
          @param lineToDelete The exact LaTeX command line to be deleted.
          @returns This is a void function.
          */
        void deleteTeXCommand(QString lineToDelete);
        /*************************************************************************************************/
        /**
          @brief This function calls a converter to generate a similar plain text output of the document.
          @param converterPlainPath converter binary path.
          @returns This is a void function.
          */
        void convertToPlainText(QString converterPlainPath);
        /*************************************************************************************************/
        /**
          @brief This function calls a converter to generate a similar HTML output of the document.
          @param converterHTMLPath converter binary path.
          @returns This is a void function.
          */
        void convertToHTML(QString converterHTMLPath);
        /*************************************************************************************************/
        /**
          @brief This function calls a converter to generate a similar RTF output of the document.
          @param converterRTFPath converter binary path.
          @returns This is a void function.
          */
        void convertToRTF(QString converterRTFPath);
        /*************************************************************************************************/
        /**
          @brief This function gets the latest changes made to the document.
          @returns This function returns a string list reference of the different versions of the document.
          */
        QList<QStringList> getFileContentHistory();
        /*************************************************************************************************/
        /**
          @brief This function redo one change made to the document and then, the document gets compiled.
          @param compilerPath PDFLaTeX binary compiler path.
          @returns This is a void function.
          */
        void redoFileContentHistory(QString compilerPath);
        /*************************************************************************************************/
        /**
          @brief This function undo one change made to the document and then, the document gets compiled.
          @param compilerPath PDFLaTeX binary compiler path.
          @returns This is a void function.
          */
        void undoFileContentHistory(QString compilerPath);
        /*************************************************************************************************/
        /**
          @brief This function gets the pointer position. This pointer tell us what change is before the document actual state and after it, so it is important to make the undo/redo work properly.
          @returns This function returns the undo/redo list pointer position.
          */
        int getCurrentActionIndex();
        /*************************************************************************************************/
        /**
          @brief This function deletes every empty paragraph that can cause troubles to the compilation process.
          @returns This is a void function.
          */
        void deleteEmptyParagraphs();
        /*************************************************************************************************/
        /**
          @brief This function gets the position where the bibliography declaration is in the document.
          @returns This functions returns the line number where the bibliography declaration is in the document.
          */
        int getBibliographyLine();
        /*************************************************************************************************/
        /**
          @brief This function gets the reference of the process that is called while the document file is being compiled.
          @returns Returns a reference of the compiling process.
          */
        QProcess* getProcess();
        /*************************************************************************************************/
        /**
          @brief This function gets the reference of the process that is called while the document file is being compiled and moves forcibly to another thread .
          @param thread thread reference on whhich the process will be moved to.
          @returns This is a void function.
          */
        void moveProcessToThread(QThread* thread);
        /*************************************************************************************************/
        /**
          @brief This function gets the path where the class file is.
          @returns This function returns the path where the defined CLS file is in the preamble of the document.
          */
        QString getCLSFile();
        /*************************************************************************************************/
        /**
          @brief This function gets the path where the style file is.
          @returns This function returns the path where the defined STY file is in the preamble of the document.
          */
        QString getSTYFile();
        /*************************************************************************************************/
        /**
          @brief This function fixes every image path so they can be shown correctly in the document.
          @returns This is a void function.
          */
        void fixImagePaths();
        /*************************************************************************************************/
        /**
          @brief This function enables the copy protect technology.
          @param state If true, then enables the copy protect. Otherwise, disables it.
          @returns This is a void function.
          */
        void enableCopyProtect(bool state);


    /*End of declaration of public functions*/

signals:
        /*************************************************************************************************/
        /**
          @brief This signal is emitted when the compiling process has finished correctly.
          @returns This is a void function.
          */
    void documentCompiled();

private:
    /*Private variables*/
        QFile *file;
        TeXCommands command;
        QString _fileName;
        QStringList fileContent;
        QList<QStringList> fileContentHistory;
        QString _documentType;
        QString _documentFontSize;
        QString _paperLayout;
        QString _paperSize;
        QString _documentLayout;
        QString _chapterLayout;
        QString _columnLayout;
        QString _documentTitle;
        QString _documentDate;
        QString _documentAuthor;
        QString _documentAbstract;
        QString _documentAddress;
        int _documentTypeIndex;
        int _documentFontSizeIndex;
        int _paperLayoutIndex;
        int _paperSizeIndex;
        int _documentLayoutIndex;
        int _chapterLayoutIndex;
        int _columnLayoutIndex;
        int _documentLanguageIndex;
        int _currentActionIndex = 0;
        QProcess *process = new QProcess(this);

    /*End of declaration of private variables*/
};

#endif // FILE_H
