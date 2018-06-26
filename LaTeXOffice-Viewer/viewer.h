#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QComboBox>
#include <QFileDialog>
#include <QFile>
#include <QCloseEvent>
#include <QDir>
#include <QPrinter>
#include "lib/latex/file.h"
#include "lib/latex/compiler.h"
#include "lib/latex/bibliography.h"
#include "documentviewer.h"
#include "dialog_compilersettings.h"
#include "dialog_log.h"
#include <JlCompress.h>
#include "constants.h"
#include <QDesktopServices>
#include <QPrintDialog>
#include "dialog_loading.h"
#include <QTranslator>
#include <QDesktopWidget>
#include "dialog_documentunlock.h"
#include "dialog_find.h"
#include "window_slideshow.h"
#include "remotecontrolserver.h"
namespace Ui {
class Viewer;
}

class Viewer : public QMainWindow
{
    Q_OBJECT
protected:
    /*Protected functions*/
    void closeEvent(QCloseEvent *);
    /*End of declaration of protected functions*/

public:
    /*Public functions*/
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit Viewer(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Viewer();
    /*************************************************************************************************/
    /**
      @brief This function fills with items the upper secondary toolbar.
      @returns This is a void function.
      */
    void fillSecondaryToolBar();
    /*************************************************************************************************/
    /**
      @brief This function defines and creates the keyboard shortcuts to some program functions.
      @returns This is a void function.
      */
    void createShortcuts();

    /*************************************************************************************************/
    /**
      @brief This function sets a Hunspell dictionary reference at the program startup .
      @returns This is a void function.
      */
    void setDictionary(QString dict);
    /*************************************************************************************************/
    /**
      @brief This function loads the Hunspell dictionary previously referenced.
      @returns This is a void function.
      */
    void loadDictionary();
    /*************************************************************************************************/
    /**
      @brief This function opens and tries to show a LaTeX Document .
      @param fileName LaTeX document file path with its name and extension.
      @returns This is a void function.
      */
    void openDocument(QString fileName);
    /*************************************************************************************************/
    /**
      @brief This function unpacks a packed document with LaTeX Office.
      @param fileName directory where the document will be unpacked.
      @returns This is a void function.
      */
    void unpackDocument(QString fileName);
    /*************************************************************************************************/
    /**
      @brief This function enables the functions of the program, so the user can interact with them. Usually, the functions are enabled when a document has been loaded succesfully.
      @returns This is a void function.
      */
    void enableFunctions();
    /*************************************************************************************************/
    /**
      @brief This function disables the functions of the program, so the user cannot interact with them. Usually, the functions are enabled when a document has not been loaded .
      @returns This is a void function.
      */
    void disableFunctions();
    /*End of declaration of public functions*/

public slots:
    void refreshPage();
private slots:
    void on_actionOpen_triggered();
    void on_actionClose_triggered();
    void on_actionExit_triggered();
    void on_actionCompiler_Settings_triggered();
    void on_actionPrint_Preview_triggered();
    void on_actionPrint_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionMinimize_window_triggered();
    void on_actionFull_Screen_triggered();
    void on_actionMaximize_triggered();
    void on_actionMinimize_Screen_triggered();
    void on_actionLaTeX_Office_on_the_Web_triggered();
    void on_actionFind_triggered();
    void on_actionRun_Slide_Show_triggered();

    void on_actionLaTeX_Office_Viewer_Help_triggered();

private:
    /*Private variables*/
    Ui::Viewer *ui;
    QComboBox *fontSizeComboBox;
    TeXFile *file;
    bool hasFileChanged;
    TeXCommands command;
    QString oriFileName;
    QString cpyFileName;
    TeXBibliography *bibFile;
    QString pdfCompilerPath;
    QString bibCompilerPath;
    QString currentDictionary;
    RemoteControlServer* remoteControlServer;
    /*End of declaration of private variables*/
};

#endif // VIEWER_H
