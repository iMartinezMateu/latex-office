#ifndef COMMANDS
#define COMMANDS

#include <QObject>
#include <QStringList>

/**
 * The TeXCommands class represents the commands that LaTeX Office supports and provides some functions in order to call these commands properly, abstracting the LaTeX syntax.
 *
 * @author Iván Martínez Mateu
 */
class TeXCommands : public QObject
{

#define CMD_TODAY  "\\today"
#define CMD_TEX_LOGO  "\\TeX"
#define CMD_LATEX_LOGO "\\LaTeX"
#define CMD_LATEXE_LOGO "\\LaTeXe"
#define CMD_LINE_BREAK "\n"
#define CMD_PARAGRAPH_BREAK "\n\n"
#define CMD_NEW_LINE "\\newline"
#define CMD_NEW_PAGE "\\newpage"
#define CMD_TITLE "\\title"
#define CMD_MAKE_TITLE "\\maketitle"
#define CMD_TABLE_OF_CONTENTS "\\tableofcontents"
#define CMD_LIST_OF_FIGURES "\\listoffigures"
#define CMD_LIST_OF_TABLES "\\listoftables"
#define CMD_LOW_DOTS "\\ldots"
#define CMD_LOW_SLOPPY "\\sloppy"
#define CMD_FRENCH_SPACING "\\frenchspacing"
#define CMD_PARAGRAPH "\\par"
#define CMD_PART "\\part"
#define CMD_APPENDIX "\\appendix"
#define CMD_FRONT_MATTER "\\frontmatter"
#define CMD_BACK_MATTER "\\backmatter"
#define CMD_MAIN_MATTER "\\mainmatter"
#define CMD_ITEM "\\item"
#define CMD_TAB_NEW_ROW "\\\\"
#define CMD_TAB_NEW_LINE "\\newline"
#define CMD_TAB_HORIZ_LINE "\\hline"
#define CMD_TAB_CLINE "\\cline"
#define CMD_TAB_COL_SEP "\\setlength{\\tabcolsep}"
#define CMD_TAB_ARRAY_STRETCH "\\renewcommand{\\arraystretch}"
#define CMD_TAB_MULTI_COLUMN "\\multicolumn"
#define CMD_CLEAR_PAGE "\\clearpage"
#define CMD_CLEAR_PAGE_DOUBLE "\\cleardoublepage" // In a two sided printing style, makes the next page a right-hand (odd-numbered) page, producing a blank page if necessary.
#define CMD_PROTECT "\\protect"
#define CMD_LEFT_ALIGN "\\flushleft"
#define CMD_CENTERING "\\centering"
#define CMD_RIGHT_ALIGN "\\flushright"
#define CMD_JUSTIFY "\\justify"
#define CMD_CHAPTER "\\chapter"
#define CMD_SECTION "\\section"
#define CMD_SUBSECTION "\\subsection"
#define CMD_SUBSUBSECTION "\\subsubsection"
#define CMD_CHAPTER_NONUMBERING "\\chapter*"
#define CMD_SECTION_NONUMBERING "\\section*"
#define CMD_SUBSECTION_NONUMBERING "\\subsection*"
#define CMD_SUBSUBSECTION_NONUMBERING "\\subsubsection*"
#define CMD_BOLD "\\textbf"
#define CMD_UNDERLINE "\\underline"
#define CMD_ITALIC "\\textit"
#define CMD_SMALL_CAPS "\\textsc"
#define CMD_COLOR "\\textcolor"
#define CMD_EMPHATIZE "\\emph"
#define CMD_STRIKETHROUGH_SOUT "\\sout" //Requires "ulem" package to be used in document!
#define CMD_STRIKETHROUGH_ST "\\st" //Requires "soul" package to be used in document!
#define CMD_BEGIN "\\begin"
#define CMD_END "\\end"
#define CMD_USE_PACKAGE "\\usepackage"
#define CMD_DOCUMENT_CLASS "\\documentclass"
#define CMD_AUTHOR "\\author"
#define CMD_DATE "\\date"
#define CMD_SETMAINFONT "\\setmainfont"
#define CMD_TEXTWIDTH "\\textwidth"
#define CMD_VFILL "\\vfill"
#define CMD_HUGE "\\huge{"
#define CMD_BFSERIES "\\bfseries"
#define CMD_INCLUDE_GRAPHICS "\\includegraphics"
#define CMD_LABEL "\\label"
#define CMD_CAPTION "\\caption"
#define CMD_ENDOFDUMP "\\endofdump"
#define CMD_THISPAGESTYLE "\\thispagestyle"
#define CMD_MBOX "\\mbox"
#define CMD_FOOTNOTE "\\footnote"
#define CMD_TINY "\\tiny{"
#define CMD_SCRIPTSIZE "\\scriptsize{"
#define CMD_FOOTNOTESIZE "\\footnotesize{"
#define CMD_SMALL "\\small{"
#define CMD_NORMALSIZE "\\normalsize{"
#define CMD_LARGE "\\large{"
#define CMD_XLARGE "\\xlarge{"
#define CMD_XXLARGE "\\xxlarge{"
#define CMD_XHUGE "\\xhuge{"
#define CMD_URL "\\url"
#define CMD_BIBLIOGRAPHY "\\bibliography"
#define CMD_BIBLIOGRAPHYSTYLE "\\bibliographystyle"
#define CMD_CITE "\\cite"
#define CMD_NOCITE "\\nocite"
#define CMD_LSTINPUTLISTING "\\lstinputlisting"
#define CMD_PAGESTYLE "\\pagestyle"
#define CMD_ADDRESS "\\address"
#define CMD_REFERENCE "\\ref"
#define CMD_EQREFERENCE "\\eqref"
#define CMD_RMDEFAULT "\\renewcommand{\\rmdefault}"
#define CMD_LINESPREAD "\\linespread"
#define CMD_HTML_COLOR "{\\color[HTML]"
#define CMD_TEXT "\\text"
#define CMD_ROWCOLOR "\\rowcolor[HTML]"
#define CMD_LOGO "\\logo"
#define CMD_CHAPTERMARK "\\chaptermark"

private:
    /*Private functions*/
    /*************************************************************************************************/
    /**
      @brief This private function calls a LaTeX Command with its proper syntax.
      @param command LaTeX Command Constant.
      @returns Returns a LaTeX Command like this: \LaTeX.
      */
        QString call(QString command);
        /*************************************************************************************************/
        /**
          @brief This private function calls a LaTeX Command with its proper syntax.
          @param command LaTeX Command Constant.
          @param argument LaTeX Command necessary argument
          @returns Returns a LaTeX Command like this: \textbf{Hello world!}.
          */
        QString call(QString command, QString argument);
        /*************************************************************************************************/
        /**
          @brief This private function calls a LaTeX Command with its proper syntax.
          @param command LaTeX Command Constant.
          @param argument LaTeX Command necessary argument list
          @returns Returns a LaTeX Command with multiple argument like this: \usepackage{pslatex,palatino,avant,graphicx,color}.
          */
        QString call(QString command, QStringList argument);
        /*************************************************************************************************/
        /**
          @brief This private function calls a LaTeX Command with its proper syntax.
          @param command LaTeX Command Constant.
          @param options LaTeX Command necessary options.
          @param argument LaTeX Command necessary argument list
          @returns Returns a LaTeX Command with multiple argument like this: \documentclass[11pt,a4paper,oneside]{report}.
          */
        QString call(QString command, QString options, QString argument);
    /*End of declaration of private functions*/

public:
    /*Public functions*/
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\today as a string.
          */
        QString callToday();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\TeX as a string.
          */
        QString callTeX();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\LaTeX as a string.
          */
        QString callLaTeX();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\LaTeXe as a string.
          */
        QString callLaTeXe();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\linebreak as a string.
          */
        QString callLineBreak();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\newline as a string.
          */
        QString callNewLine();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\newpage as a string.
          */
        QString callNewPage();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param titleText title's text that will be shown on the document.
          @returns Returns the LaTeX Command \\title{foo} as a string.
          */
        QString callTitle(QString titleText);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\maketitle as a string.
          */
        QString callMakeTitle();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\tableofcontents as a string.
          */
        QString callTableOfContents();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\listoffigures as a string.
          */
        QString callListOfFigures();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\listoftables as a string.
          */
        QString callListOfTables();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\ldots as a string.
          */
        QString callLowDots();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\sloppy as a string.
          */
        QString callLowSloppy();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\frenchspacing as a string.
          */
        QString callFrenchSpacing();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\par as a string.
          */
        QString callParagraph();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param partText part's text that will be shown on the document.
          @returns Returns the LaTeX Command \\part{foo} as a string.
          */
        QString callPart(QString partText);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\appendix as a string.
          */
        QString callAppendix();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\frontmatter as a string.
          */
        QString callFrontMatter();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\backmatter as a string.
          */
        QString callBackMatter();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\mainmatter as a string.
          */
        QString callMainMatter();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\item as a string.
          */
        QString callItem();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\\\ as a string.
          */
        QString callNewRowTab();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\newline as a string.
          */
        QString callNewLineTab();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param doHorizontalLine make a horizontal line (true) or not (false).
          @returns Returns the LaTeX Command \\newline or \\hline as a string.
          */
        QString callNewLineTab(bool doHorizontalLine);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param firstColumnNumber column number where the line will start.
          @param secondColumnNumber  column number where the line will end.
          @returns Returns the LaTeX Command \\cline{foo-foo2} as a string.
          */
        QString callNewPartialHorizontalLineTab(int firstColumnNumber, int secondColumnNumber) ;
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param separation column spacing value.
          @returns Returns the LaTeX Command \\setlength[10pt]{\\tabcolsep} as a string.
          */
        QString callColumnSeparatorTab(int separation);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param spacing row separation value.
          @returns Returns the LaTeX Command \\setlength[10pt]{\\arraystretch} as a string.
          */
        QString callRowSpaceTab(float spacing);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param quantity column quantity.
          @param type column type.
          @param name column name.
          @returns Returns the LaTeX Command \\multicolumn{2}{c}{Multi-column} as a string.
          */
        QString callMultiColumnTab(int quantity, QString type, QString name);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\clearpage as a string.
          */
        QString callClearPage();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\cleardobulepage as a string.
          */
        QString callClearPageDouble();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\protect as a string.
          */
        QString callProtect();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\flushleft{foo} as a string.
          */
        QString callLeftAlign(QString text);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param text text to be aligned.
          @returns Returns the LaTeX Command \\centering{foo} as a string.
          */
        QString callCentering(QString text);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param text text to be aligned.
          @returns Returns the LaTeX Command \\flushright{foo} as a string.
          */
        QString callRightAlign(QString text);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\justify as a string.
          */
        QString callJustify();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param chapterText chapter's text that will be shown on the document.
          @returns Returns the LaTeX Command \\chapter{foo} as a string.
          */
        QString callChapter(QString chapterText);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param sectionText section's text that will be shown on the document.
          @returns Returns the LaTeX Command \\section{foo} as a string.
          */
        QString callSection(QString sectionText) ;
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param subSectionText subsection's text that will be shown on the document.
          @returns Returns the LaTeX Command \\subsection{foo} as a string.
          */
        QString callSubSection(QString subSectionText) ;
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param subSubSectionText subsubsection's text that will be shown on the document.
          @returns Returns the LaTeX Command \\subsubsection{foo} as a string.
          */
        QString callSubSubSection(QString subSubSectionText);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param chapterText chapter's text that will be shown on the document (non-numbered).
          @returns Returns the LaTeX Command \\chapter*{foo} as a string.
          */
        QString callChapterNoN(QString chapterText);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param sectionText section's text that will be shown on the document (non-numbered).
          @returns Returns the LaTeX Command \\section*{foo} as a string.
          */
        QString callSectionNoN(QString sectionText) ;
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param subSectionText subsection's text that will be shown on the document (non-numbered).
          @returns Returns the LaTeX Command \\subsection*{foo} as a string.
          */
        QString callSubSectionNoN(QString subSectionText) ;
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param subSubSection subsubsection's text that will be shown on the document (non-numbered).
          @returns Returns the LaTeX Command \\subsubsection*{foo} as a string.
          */
        QString callSubSubSectionNoN(QString subSubSectionText);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param boldText text that is going to be stylized.
          @returns Returns the LaTeX Command \\textbf{foo} as a string.
          */
        QString callTextBold(QString boldText);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param underlineText text that is going to be stylized.
          @returns Returns the LaTeX Command \\underline{foo} as a string.
          */
        QString callTextUnderline(QString underlineText);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param italicText text that is going to be stylized.
          @returns Returns the LaTeX Command \\textit{foo} as a string.
          */
        QString callTextItalic(QString italicText);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param smallCaps text that is going to be stylized.
          @returns Returns the LaTeX Command \\textsc{foo} as a string.
          */
        QString callTextSmallCaps(QString smallCapsText);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param color color string (for example, red). Check LaTeX books for more details on this.
          @param coloredText text that is going to be stylized.
          @returns Returns the LaTeX Command \\textcolor{blue}{foo} as a string.
          */
        QString callTextColor(QString color, QString coloredText);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param emphatizeString text that is going to be emphatized.
          @returns Returns the LaTeX Command \\emph{foo} as a string.
          */
        QString callTextEmphatize(QString emphatizeString);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param strikethroughString text that is going to be stylized.
          @returns Returns the LaTeX Command \\sout{foo} as a string.
          */
        QString callTextStrikethrough(QString strikethroughString);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param strikethroughString text that is going to be stylized.
          @returns Returns the LaTeX Command \\st{foo} as a string.
          */
        QString callTextAlternativeStrikethrough(QString strikethroughString);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param environment environment to use.
          @returns Returns the LaTeX Command \\begin{itemize} as a string.
          */
        QString callBegin(QString environment);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param environment environment to use.
          @param options necessary options to supply to the environment.
          @returns Returns the LaTeX Command \\begin{table}[h] as a string.
          */
        QString callBegin(QString environment, QString options) ;
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param environment environment to use.
          @returns Returns the LaTeX Command \\end{itemize} as a string.
          */
        QString callEnd(QString environment) ;
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\documentclass as a string.
          */
        QString callDocumentClass();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param documentClass LaTeX document class
          @returns Returns the LaTeX Command \\documentclass{article} as a string.
          */
        QString callDocumentClass(QString documentClass);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param documentClass LaTeX document class
          @param documentClassOptions LaTeX document class necessary options
          @returns Returns the LaTeX Command \\documentclass[openany]{article} as a string.
          */
        QString callDocumentClass(QString documentClass, QString documentClassOptions);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param packageName the package reference to use on the document
          @returns Returns the LaTeX Command \\usepackage{color} as a string.
          */
        QString callUsePackage(QString packageName) ;
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param packageName the package reference to use on the document
          @param options supply the necessary options so the package can work correctly
          @returns Returns the LaTeX Command \\usepackage[latin1]{inputenc} as a string.
          */
        QString callUsePackage(QString packageName, QString options);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param author Author name
          @returns Returns the LaTeX Command \\author{Mister Foo} as a string.
          */
        QString callAuthor(QString author);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param date Document Date
          @returns Returns the LaTeX Command \\date{22 June 2015} as a string.
          */
        QString callDate(QString date);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\setmainfont as a string.
          */
        QString callSetMainFont();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param font font name
          @returns Returns the LaTeX Command \\setmainfont{foo} as a string.
          */
        QString callSetMainFont(QString font);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\bfseries as a string.
          */
        QString callBFSeries();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\textwidth as a string.
          */
        QString callTextWidth();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\vfill as a string.
          */
        QString callVFill();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\includegraphics as a string.
          */
        QString callIncludeGraphics();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param path image file path.
          @param options supply the necessary options to alter the figure.
          @returns Returns the LaTeX Command \\includegraphics[size=1\\textwidth]{foo.png} as a string.
          */
        QString callIncludeGraphics(QString path, QString options);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\caption as a string.
          */
        QString callCaption();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param text caption text content.
          @returns Returns the LaTeX Command \\caption{foo} as a string.
          */
        QString callCaption(QString text);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\label as a string.
          */
        QString callLabel();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param text label text content.
          @returns Returns the LaTeX Command \\label{foo} as a string.
          */
        QString callLabel(QString text);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\endofdump as a string.
          */
        QString callEndOfDump();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param style page style reference.
          @returns Returns the LaTeX Command \\thispagestyle{plain} as a string.
          */
        QString callThisPageStyle(QString style);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param text text that will be inside the box.
          @returns Returns the LaTeX Command \\mbox{foo} as a string.
          */
        QString callMBox(QString text);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param text footnote text content.
          @returns Returns the LaTeX Command \\footnote{foo} as a string.
          */
        QString callFootNote(QString text);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param url webpage address.
          @returns Returns the LaTeX Command \\url{foo.com} as a string.
          */
        QString callUrl(QString url);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\tiny as a string.
          */
        QString callTiny();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\scriptsize as a string.
          */
        QString callScriptSize();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\footnotesize as a string.
          */
        QString callFootNoteSize();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\small as a string.
          */
        QString callSmall();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\normal as a string.
          */
        QString callNormalSize();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\large as a string.
          */
        QString callLargeSize();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\Large as a string.
          */
        QString callXLargeSize();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\LARGE as a string.
          */
        QString callXXLargeSize();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\huge as a string.
          */
        QString callHugeSize();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @returns Returns the LaTeX Command \\Huge as a string.
          */
        QString callXHugeSize();
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param filePath BIB bibliography file path.
          @returns Returns the LaTeX Command \\bibliography{foo} as a string.
          */
        QString callBibliography(QString filePath);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param style BIB bibliography style reference.
          @returns Returns the LaTeX Command \\bibliographystyle{plain} as a string.
          */
        QString callBibliographyStyle(QString style);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param item reference to item.
          @returns Returns the LaTeX Command \\cite{foo} as a string.
          */
        QString callCite(QString item);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param item reference to item.
          @returns Returns the LaTeX Command \\nocite{*} as a string.
          */
        QString callNoCite(QString item);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param options supply the necessary options so the source code listing can work correctly.
          @param path source file path.
          @returns Returns the LaTeX Command \\nocite{*} as a string.
          */
        QString callLstInputListing(QString options, QString path);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param style document style reference
          @returns Returns the LaTeX Command \\pagestyle{plain} as a string.
          */
        QString callPageStyle(QString style);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param address document address.
          @returns Returns the LaTeX Command \\address{foo} as a string.
          */
        QString callAddress(QString address);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param item reference to item.
          @returns Returns the LaTeX Command \\ref{foo} as a string.
          */
        QString callReference(QString item);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param item reference to item.
          @returns Returns the LaTeX Command \\eqref{foo} as a string.
          */
        QString callEqReference(QString item);

        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param item reference to font.
          @returns Returns the LaTeX Command \\renewcommand{\\rmdefault}{foo} as a string.
          */
        QString callRMDefault(QString item);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param item reference to font.
          @returns Returns the LaTeX Command \\linespread{1} as a string.
          */
        QString callLineSpread(QString item);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param color hex reference (HTML).
          @returns Returns the LaTeX Command \\color{HTML}{foo} as a string.
          */
        QString callHTMLColor(QString color);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param string text content.
          @returns Returns the LaTeX Command \\text{foo} as a string.
          */
        QString callText(QString string);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param code HTML color hex code.
          @returns Returns the LaTeX Command \\rowcolor[HTML]{C0C0C0} as a string.
          */
        QString callRowColor(QString code);
        /*************************************************************************************************/
        /**
          @brief This public function calls the indicated LaTeX command and adds the properly sintax needed so the LaTeX compiler can understand it .
          @param code a "include graphics" LaTeX code.
          @returns Returns the LaTeX Command \\logo{foo} as a string.
          */
        QString callLogo(QString code);
    /*End of declaration of public functions*/
};
#endif // COMMANDS
