#ifndef TEXBIBLIOGRAPHY_H
#define TEXBIBLIOGRAPHY_H

#include <QObject>
#include <QFile>
#include <QProcess>
#include <QFileInfo>
#include <QTextStream>
#include <QRegularExpressionMatchIterator>
#include <QList>
#include <QDebug>
/**
 * The TeXBibliography class represents the functions that LaTeX Office provide to alter the document bibliography.
 *
 * @author Iván Martínez Mateu
 */
class TeXBibliography : public QObject
{
public:
    /*************************************************************************************************/
    /**
      @brief This is the constructor function that reads the file provided by the unique argument and enables the use of the rest functions declared here.
      @param filePath bibliography file path.
      @returns This is a void function.
      */
    TeXBibliography(QString filePath);
    /*************************************************************************************************/
    /**
      @brief Destroy the object.
      @returns This is a void function.
      */
    ~TeXBibliography();
    /*************************************************************************************************/
    /**
      @brief Creates an article entry in the articles structure list.
      @param id unique identificator for the entry.
      @param author author who wrote the article.
      @param title article's title.
      @param year year when article was published.
      @param journal journal where article was published.
      @param volume article's volume.
      @param number article's number.
      @param pages article's pages.
      @returns This is a void function.
      */
    void createArticleEntry(QString id, QString author, QString title, QString year, QString journal, QString volume, QString number, QString pages);
    /*************************************************************************************************/
    /**
      @brief Creates a book entry in the books structure list.
      @param id unique identificator for the entry.
      @param author author who wrote the book.
      @param title book's title.
      @param year year when book was published.
      @param publisher book's publisher.
      @param volume book's volume.
      @param number book's number.
      @param edition book's edition.
      @returns This is a void function.
      */
    void createBookEntry(QString id, QString author, QString title, QString year, QString publisher, QString volume, QString number, QString edition);
    /*************************************************************************************************/
    /**
      @brief Creates a booklet entry in the booklets structure list.
      @param id unique identificator for the entry.
      @param author author who wrote the booklet.
      @param title booklet's title.
      @param year year when booklet was published.
      @param address booklet's address.
      @param month month when booklet was published.
      @param note booklet's note.
      @param howPublished how the booklet was published.
      @returns This is a void function.
      */
    void createBookletEntry(QString id, QString author, QString title, QString year, QString address, QString month, QString note, QString howPublished);
    /*************************************************************************************************/
    /**
      @brief Creates a inbook entry in the inbooks structure list.
      @param id unique identificator for the entry.
      @param author author who wrote the inbook.
      @param title inbook's title.
      @param year year when inbook was published.
      @param editor inbook's editor.
      @param chapter inbook's chapter.
      @param pages inbook's pages.
      @param publisher inbook's publisher.
      @returns This is a void function.
      */
    void createInbookEntry(QString id, QString author, QString title, QString year, QString editor, QString chapter, QString pages, QString publisher);
    /*************************************************************************************************/
    /**
      @brief Creates a incollection entry in the incollections structure list.
      @param id unique identificator for the entry.
      @param author author who wrote the incollection.
      @param title incollection's title.
      @param year year when incollection was published.
      @param bookTitle book's title where incollection was published.
      @param publisher incollection's publisher.
      @param chapter incollection's chapter.
      @param edition incollection's edition.
      @returns This is a void function.
      */
    void createIncollectionEntry(QString id, QString author, QString title, QString year, QString bookTitle, QString publisher, QString chapter, QString edition);
    /*************************************************************************************************/
    /**
      @brief Creates a inproceeding entry in the inproceedings structure list.
      @param id unique identificator for the entry.
      @param author author who wrote the inproceeding.
      @param title inproceeding's title.
      @param bookTitle book's title where inproceeding was published.
      @param year year when inproceeding was published.
      @param editor inproceeding's editor.
      @param publisher inproceeding's publisher.
      @param organization inproceeding's organization.
      @returns This is a void function.
      */
    void createInproceedingsEntry(QString id, QString author, QString title, QString bookTitle, QString year, QString editor, QString publisher, QString organization);
    /*************************************************************************************************/
    /**
      @brief Creates a manual entry in the manuals structure list.
      @param id unique identificator for the entry.
      @param title manual's title.
      @param author author who wrote the manual.
      @param year year when manual was published.
      @param edition manual's edition.
      @param month month when manual was published.
      @param organization manual's organization.
      @param note manual's note.
      @returns This is a void function.
      */
    void createManualEntry(QString id, QString title, QString author, QString year, QString edition, QString month, QString organization, QString note);
    /*************************************************************************************************/
    /**
      @brief Creates a thesis entry in the thesis structure list.
      @param id unique identificator for the entry.
      @param title thesis' title.
      @param author author who wrote the thesis.
      @param year year when thesis was published.
      @param type thesis' type.
      @param address thesis' address.
      @param month thesis' month.
      @param school thesis' school.
      @returns This is a void function.
      */
    void createThesisEntry(QString id, QString title, QString author, QString year, QString type, QString address, QString month, QString school);
    /*************************************************************************************************/
    /**
      @brief Creates a proceedings entry in the proceedings structure list.
      @param id unique identificator for the entry.
      @param title proceedings' title.
      @param publisher publisher who published the proceeding.
      @param year year when proceeding was published.
      @param editor proceeding's editor.
      @param organization proceeding's organization.
      @param volume proceeding's volume.
      @param number proceeding's number.
      @returns This is a void function.
      */
    void createProceedingsEntry(QString id, QString title, QString publisher, QString year, QString editor, QString organization, QString volume, QString number);
    /*************************************************************************************************/
    /**
      @brief Creates a report entry in the reports structure list.
      @param id unique identificator for the entry.
      @param author author who wrote the report.
      @param title report's title.
      @param institution report's institution.
      @param year year when report was published.
      @param address report's address.
      @param type report's type.
      @param number report's number.
      @returns This is a void function.
      */
    void createReportEntry(QString id,  QString author,QString title, QString institution, QString year, QString address, QString type, QString number);
    /*************************************************************************************************/
    /**
      @brief Saves the data stored in every structure list to a local file.
      @returns This is a void function.
      */
    void saveFile();
    /*************************************************************************************************/
    /**
      @brief Reads the data stored in a file and fills every structure list. This function gets the file reference by calling the constructor function.
      @returns This is a void function.
      */
    void readFile();
    /*************************************************************************************************/
    /**
      @brief Checks if file referenced by the constructor functions really exist or not.
      @returns This is a void function.
      */
    bool existsFile();
    /*************************************************************************************************/
    /**
      @brief Compile the BIBTeX file to generate the bibliography in the document.
      @param compilerPath path where BIBTeX compiler binary can be found.
      @returns This is a void function.
      */
    void compile(QString compilerPath);
    /*************************************************************************************************/
    /**
      @brief Compile the BIBTeX file to generate the bibliography in the document.
      @param compilerPath path where BIBTeX compiler binary can be found.
      @param wait If true, the function will wait until the compiling process is completed.
      @returns This is a void function.
      */
    void compile(QString compilerPath, bool wait);
    /*************************************************************************************************/
    /**
      @brief Deletes an article entry stored in the corresponding list.
      @param id unique entry identificator to be deleted.
      @returns This is a void function.
      */
    void deleteArticleEntry(QString id);
    /*************************************************************************************************/
    /**
      @brief Deletes a book entry stored in the corresponding list.
      @param id unique entry identificator to be deleted.
      @returns This is a void function.
      */
    void deleteBookEntry(QString id);
    /*************************************************************************************************/
    /**
      @brief Deletes a booklet entry stored in the corresponding list.
      @param id unique entry identificator to be deleted.
      @returns This is a void function.
      */
    void deleteBookletEntry(QString id);
    /*************************************************************************************************/
    /**
      @brief Deletes an inbook entry stored in the corresponding list.
      @param id unique entry identificator to be deleted.
      @returns This is a void function.
      */
    void deleteInbookEntry(QString id);
    /*************************************************************************************************/
    /**
      @brief Deletes an incollection entry stored in the corresponding list.
      @param id unique entry identificator to be deleted.
      @returns This is a void function.
      */
    void deleteIncollectionEntry(QString id);
    /*************************************************************************************************/
    /**
      @brief Deletes an inproceeding entry stored in the corresponding list.
      @param id unique entry identificator to be deleted.
      @returns This is a void function.
      */
    void deleteInproceedingsEntry(QString id);
    /*************************************************************************************************/
    /**
      @brief Deletes a manual entry stored in the corresponding list.
      @param id unique entry identificator to be deleted.
      @returns This is a void function.
      */
    void deleteManualEntry(QString id);
    /*************************************************************************************************/
    /**
      @brief Deletes a thesis entry stored in the corresponding list.
      @param id unique entry identificator to be deleted.
      @returns This is a void function.
      */
    void deleteThesisEntry(QString id);
    /*************************************************************************************************/
    /**
      @brief Deletes a proceeding entry stored in the corresponding list.
      @param id unique entry identificator to be deleted.
      @returns This is a void function.
      */
    void deleteProceedingsEntry(QString id);
    /*************************************************************************************************/
    /**
      @brief Deletes a report entry stored in the corresponding list.
      @param id unique entry identificator to be deleted.
      @returns This is a void function.
      */
    void deleteReportEntry(QString id);
    /*************************************************************************************************/
    /**
      @brief Check if the identificator is already chosen by another structure list entry or not.
      @param id unique entry identificator.
      @returns The function will return false if there is not an entry with the ID passed by argument. Otherwise, will return true.
      */
    bool isSelectedIDChosen(QString id);
    /*************************************************************************************************/
    /**
      @brief This function gets the articles' structure list and converts it to a string list, so it can be used by another class.
      @returns Returns a string list containing the articles' structure list.
      */
    QList<QStringList> getArticlesStringList();
    /*************************************************************************************************/
    /**
      @brief This function gets the books' structure list and converts it to a string list, so it can be used by another class.
      @returns Returns a string list containing the books' structure list.
      */
     QList<QStringList> getBooksStringList();
     /*************************************************************************************************/
     /**
       @brief This function gets the booklets' structure list and converts it to a string list, so it can be used by another class.
       @returns Returns a string list containing the booklets' structure list.
       */
     QList<QStringList> getBookletsStringList();
     /*************************************************************************************************/
     /**
       @brief This function gets the inbooks' structure list and converts it to a string list, so it can be used by another class.
       @returns Returns a string list containing the inbooks' structure list.
       */
     QList<QStringList> getInbooksStringList();
     /*************************************************************************************************/
     /**
       @brief This function gets the incollections' structure list and converts it to a string list, so it can be used by another class.
       @returns Returns a string list containing the incollections' structure list.
       */
     QList<QStringList> getIncollectionsStringList();
     /*************************************************************************************************/
     /**
       @brief This function gets the inproceedings' structure list and converts it to a string list, so it can be used by another class.
       @returns Returns a string list containing the inproceedings' structure list.
       */
     QList<QStringList> getInproceedingsStringList();
     /*************************************************************************************************/
     /**
       @brief This function gets the manuals' structure list and converts it to a string list, so it can be used by another class.
       @returns Returns a string list containing the manuals' structure list.
       */
     QList<QStringList> getManualsStringList();
     /*************************************************************************************************/
     /**
       @brief This function gets the thesis' structure list and converts it to a string list, so it can be used by another class.
       @returns Returns a string list containing the thesis' structure list.
       */
     QList<QStringList> getThesisStringList();
     /*************************************************************************************************/
     /**
       @brief This function gets the proceedings' structure list and converts it to a string list, so it can be used by another class.
       @returns Returns a string list containing the proceedings' structure list.
       */
     QList<QStringList> getProceedingsStringList();
     /*************************************************************************************************/
     /**
       @brief This function gets the reports' structure list and converts it to a string list, so it can be used by another class.
       @returns Returns a string list containing the reports' structure list.
       */
     QList<QStringList> getReportsStringList();
     /*************************************************************************************************/
     /**
       @brief This function gets the reference of the process that is called while the bibliography file is being compiled.
       @returns Returns a reference of the compiling process.
       */
     QProcess* getProcess();

private:
     /**
      * @brief This is the Articles' Structure which will store all information regarding to the articles defined in the bibliography.
      */
     struct article {
         QString id;//!<  Unique entry identificator.
         QString author;//!<  Stores the article's author.
         QString title;//!<  Stores the article's title.
         QString year;//!<  Stores the year when the article was published.
         QString journal;//!<  Stores the article's journal.
         QString volume;//!<  Stores the article's volume.
         QString number;//!<  Stores the article's number.
         QString pages;//!<  Stores the article's pages.
     };
     /**
      * @brief This is the Books' Structure which will store all information regarding to the books defined in the bibliography.
      */
     struct book {
         QString id; //!<  Unique entry identificator.
         QString author; //!<  Stores the book's author.
         QString title; //!<  Stores the book's title.
         QString year; //!<  Stores the year when the book was published.
         QString publisher; //!<  Stores who published the book.
         QString volume; //!<  Stores the book's volume.
         QString number; //!<  Stores the book's number.
         QString edition; //!<  Stores the book's edition.
     };
     /**
      * @brief This is the Booklets' Structure which will store all information regarding to the booklets defined in the bibliography.
      */
     struct booklet {
         QString id;//!<  Unique entry identificator.
         QString author;//!<  Stores the booklet's author.
         QString title;//!<  Stores the booklet's title.
         QString year;//!<  Stores the year when the booklet was published.
         QString address;//!<  Stores the booklet's address.
         QString month;//!<  Stores the booklet's month.
         QString note;//!<  Stores the booklet's note.
         QString howPublished; //!<  Stores how the booklet was published.
     };
     /**
      * @brief This is the Inbooks' Structure which will store all information regarding to the inbooks defined in the bibliography.
      */
     struct inbook {
         QString id;//!<  Unique entry identificator.
         QString author;//!<  Stores the inbook's author.
         QString title;//!<  Stores the inbook's title.
         QString year;//!<  Stores the year when the inbook was published.
         QString editor;//!<  Stores the inbook's editor.
         QString chapter;//!<  Stores the inbook's chapter.
         QString pages;//!<  Stores the inbook's pages.
         QString publisher;//!<  Stores who published the inbook.
     };
     /**
      * @brief This is the Incollections' Structure which will store all information regarding to the incollections defined in the bibliography.
      */
     struct incollection {
         QString id;//!<  Unique entry identificator.
         QString author;//!<  Stores the incollection's author.
         QString title;//!<  Stores the incollection's title.
         QString year;//!<  Stores the year when the incollection was published.
         QString bookTitle; //!<  Stores the book's title where the incollection was published.
         QString publisher;//!<  Stores who published the incollection.
         QString chapter;//!<  Stores the incollection's chapter.
         QString edition;//!<  Stores the incollection's edition.
     };
     /**
      * @brief This is the Inproceedings' Structure which will store all information regarding to the inproceedings defined in the bibliography.
      */
     struct inproceedings {
         QString id;//!<  Unique entry identificator.
         QString title;//!<  Stores the inproceedings' author.
         QString bookTitle;//!<  Stores the book's title where the inproceedings was published.
         QString author;//!<  Stores the inproceedings' author.
         QString editor;//!<  Stores the inproceedings' editor.
         QString publisher;//!<  Stores who published the inproceedings.
         QString organization; //!<  Stores the inproceedings' organization.
         QString year;//!<  Stores the year when the inproceedings' was published.
     };
     /**
      * @brief This is the Manuals' Structure which will store all information regarding to the manuals defined in the bibliography.
      */
     struct manual {
         QString id;//!<  Unique entry identificator.
         QString title;//!<  Stores the manual's title.
         QString author;//!<  Stores the manual's author.
         QString year;//!<  Stores the year when the manual was published.
         QString edition;//!<  Stores the manual's edition.
         QString month;//!<  Stores the month when the manual was published.
         QString organization; //!<  Stores the manual's organization.
         QString note;//!<  Stores the manual's note.
     };
     /**
      * @brief This is the Thesis' Structure which will store all information regarding to the thesis defined in the bibliography.
      */
     struct thesis {
         QString id;//!<  Unique entry identificator.
         QString title;//!<  Stores the thesis' title.
         QString school;//!<  Stores the thesis' school.
         QString author;//!<  Stores the thesis' author.
         QString year;//!<  Stores the year when the thesis was published.
         QString type;//!<  Stores the thesis' type.
         QString address;//!<  Stores the thesis' address.
         QString month;//!<  Stores the month when the thesis was published.
     };
     /**
      * @brief This is the Proceedings' Structure which will store all information regarding to the proceedings defined in the bibliography.
      */
     struct proceedings {
         QString id;//!<  Unique entry identificator.
         QString title;//!<  Stores the proceedings' title.
         QString publisher;//!<  Stores who published the proceedings.
         QString year;//!<  Stores the year when the proceedings was published.
         QString editor;//!<  Stores the proceedings' editor.
         QString organization;//!<  Stores the proceedings' organization.
         QString volume;//!<  Stores the proceedings' volume.
         QString number;//!<  Stores the proceedings' number.
     };
     /**
      * @brief This is the Reports' Structure which will store all information regarding to the reports defined in the bibliography.
      */
     struct report {
         QString id;//!<  Unique entry identificator.
         QString author;//!<  Stores the report's author.
         QString title;//!<  Stores the report's title.
         QString institution;//!<  Stores the report's institution.
         QString year;//!<  Stores the year when the report was published.
         QString address;//!<  Stores the report's address.
         QString type;//!<  Stores the report's type.
         QString number;//!<  Stores the report's number.
     };
    QStringList fileContent;//!<  Stores the BIB file content.
    QList<article> articlesList; //!<  Stores an unlimited list of articles.
    QList<book> booksList; //!<  Stores an unlimited list of books.
    QList<booklet> bookletsList;//!<  Stores an unlimited list of booklets.
    QList<inbook> inbooksList;//!<  Stores an unlimited list of inbooks.
    QList<incollection> incollectionsList;//!<  Stores an unlimited list of incollections.
    QList<inproceedings> inproceedingsList;//!<  Stores an unlimited list of inproceedings.
    QList<manual> manualsList;//!<  Stores an unlimited list of manuals.
    QList<thesis> thesisList;//!<  Stores an unlimited list of thesis.
    QList<proceedings> proceedingsList;//!<  Stores an unlimited list of proceedings.
    QList<report> reportsList;//!<  Stores an unlimited list of reports.
    QFile *file = NULL;
    QProcess *process = new QProcess(this);

};

#endif // TEXBIBLIOGRAPHY_H
