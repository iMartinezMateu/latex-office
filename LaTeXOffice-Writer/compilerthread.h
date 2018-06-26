#ifndef COMPILERTHREAD_H
#define COMPILERTHREAD_H

#include <QThread>
#include "lib/latex/bibliography.h"
#include "lib/latex/file.h"
#include "documentviewer.h"
#include <QTimer>
#include "constants.h"
#include <QProcess>
/**
 * The CompilerThread class represents the LaTeX Office core. The program will be able to compile the document in background using the multithreading paradigm.
 *
 * @author Iván Martínez Mateu
 */
class CompilerThread : public QThread
{
    Q_OBJECT
public:
    /*Public functions*/
    /*************************************************************************************************/
    /**
      @brief This function loads some data that the compiler thread needs to operate correctly.
      @param file TeX file reference that will be compiled.
      @param compilerPath the compiler binary path.
      @param viewer a reference to the Document Viewer widget, so the changes made to the document can be reflected on the UI.
      @returns This is a void function.
      */
    void setData(TeXFile *file, QString compilerPath, DocumentViewer *viewer);
    /*************************************************************************************************/
    /**
      @brief This function defines the thread state.
      @param state the boolean value defines wether the thread should be running (true) or it must wait to other event to start again (false).
      @returns This is a void function.
      */
    void setRunState(bool state);
    /*************************************************************************************************/
    /**
      @brief This function contains the commands that are going to be executed by the thread when it's running.
      @returns This is a void function.
      */
    void run();
    /*End of declaration of public functions*/
private:
    /*Private variables*/
    QString compilerPath;
    QString bibCompilerPath;
    TeXFile *file;
    TeXBibliography *bibFile;
    int currentPage;
    bool runState;
    DocumentViewer *viewer;
    QTime *chrono = new QTime();
    /*End of declaration of private variables*/
signals:
    void threadCompiled();
};
#endif
