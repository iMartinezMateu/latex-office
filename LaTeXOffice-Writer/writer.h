#ifndef WRITER_H
#define WRITER_H

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
#include "dialog_newdocument.h"
#include "dialog_documentpreamble.h"
#include "dialog_compilersettings.h"
#include "dialog_find.h"
#include "dialog_chapter.h"
#include "dialog_section.h"
#include "dialog_subsection.h"
#include "dialog_subsubsection.h"
#include "dialog_paragraph.h"
#include "dialog_log.h"
#include "dialog_insertimage.h"
#include "dialog_inserttable.h"
#include "dialog_dictionarysettings.h"
#include "matheditor.h"
#include <JlCompress.h>
#include "constants.h"
#include <QDesktopServices>
#include <QPrintDialog>
#include "dialog_bibliography.h"
#include "dialog_spellchecker.h"
#include "dialog_goal.h"
#include "dialog_documentlock.h"
#include "dialog_documentunlock.h"
#include "dialog_smartkeys.h"
#include "dialog_timemachine.h"
#include "dialog_loading.h"
#include "dialog_themesettings.h"
#include "dialog_code.h"
#include <QTranslator>
#include <QDesktopWidget>
#include "dialog_timemachinesettings.h"
#include "dialog_fonts.h"

namespace Ui {
class Writer;
}

class Writer : public QMainWindow
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
    explicit Writer(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function destroys the dialog reference.
      @returns This is a void function.
      */
    ~Writer();
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
    /*************************************************************************************************/
    /**
      @brief This function enables the style functions of the program, so the user can interact with them to stylize the document text. Usually, the functions are enabled when a document has been loaded succesfully.
      @returns This is a void function.
      */
    void enableStyleFunctions();
    /*************************************************************************************************/
    /**
      @brief This function disables the style functions of the program, so the user cannot interact with them to stylize the document text. Usually, the functions are enabled when a document has not been loaded .
      @returns This is a void function.
      */
    void disableStyleFunctions();
    /*************************************************************************************************/
    /**
      @brief This function loads the program status bar and it defines the description of the main program functions so it can be viewed in the status bar.
      @returns This is a void function.
      */
    void loadStatusBar();
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
    /*End of declaration of public functions*/

public slots:
    void checkModifiedStatus();
    void setModifiedStatus();
    void refreshPage();
    void updateTextAttributes(int fontSize, QString headingStyle);
    void showSecondaryToolBar();
    void hideSecondaryToolBar();
    void showParagraphWordsCount();
private slots:
    void on_actionOpen_triggered();
    void on_actionClose_triggered();
    void on_actionExit_triggered();
    void on_actionSave_triggered();
    void on_actionPDF_file_triggered();
    void on_actionRTF_File_triggered();
    void on_actionPlain_Text_triggered();
    void on_actionWeb_Archive_triggered();
    void on_actionNew_triggered();
    void on_actionEquation_triggered();
    void on_actionDocument_Preamble_triggered();
    void on_actionCompiler_Settings_triggered();
    void on_actionSave_As_triggered();
    void on_actionFind_triggered();
    void changeSize();
    void on_actionBreak_triggered();
    void on_actionPackage_Document_triggered();
    void on_actionUnpackage_Document_triggered();
    void on_actionChapter_triggered();
    void on_actionSection_triggered();
    void on_actionSub_Section_triggered();
    void on_actionSub_Sub_Section_triggered();
    void on_actionParagraph_triggered();
    void on_actionTable_of_Contents_triggered();
    void on_actionPrint_Preview_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionPicture_triggered();
    void on_actionTable_triggered();
    void on_actionPrint_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionBibliography_Manager_triggered();
    void on_actionBibliography_triggered();
    void on_actionSpelling_triggered();
    void on_actionGoal_triggered();
    void on_actionDictionary_Settings_triggered();
    void on_actionDocument_Lock_triggered();
    void on_actionCode_Asset_triggered();
    void on_actionSmartKeys_triggered();
    void on_actionTime_Machine_triggered();
    void on_actionTheme_Settings_triggered();
    void on_actionMinimize_window_triggered();
    void on_actionFull_Screen_triggered();
    void on_actionMaximize_triggered();
    void on_actionMinimize_Screen_triggered();
    void on_actionHide_Primary_Toolbar_triggered();
    void on_actionHide_Secondary_Toolbar_triggered();
    void on_actionHide_Document_Structure_List_triggered();
    void on_actionShow_LaTeX_Code_triggered();
    void on_actionTime_Machine_Settings_triggered();
    void on_actionList_of_Tables_triggered();
    void on_actionList_of_Figures_triggered();
    void on_actionLaTeX_Office_on_the_Web_triggered();
    void on_actionCopy_Protect_triggered();
    void on_actionFonts_triggered();

    void on_actionLaTeX_Office_Writer_Help_triggered();

private:
    /*Private variables*/
    Ui::Writer *ui;
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
    /*End of declaration of private variables*/
};

#endif // WRITER_H
