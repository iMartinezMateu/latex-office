
#include "commands.h"


QString TeXCommands::call(QString command)
{
    return command;
}

QString TeXCommands::call(QString command, QString argument)
{
    QString arg = "{" + argument + "}";
    return command + arg;
}

QString TeXCommands::call(QString command, QStringList argument)
{
    QString args = "" ;
    foreach (QString a, argument) {
        args.append("{" + a + "}");
    }
    return command + args;
}

QString TeXCommands::call(QString command, QString options, QString argument)
{
    QString opt = "[" + options + "]";
    QString arg = "{" + argument + "}";
    return command + opt + arg;
}

QString TeXCommands::callToday()
{
    return call(CMD_TODAY);
}

QString TeXCommands::callTeX()
{
    return call(CMD_TEX_LOGO);
}

QString TeXCommands::callLaTeX()
{
    return call(CMD_LATEX_LOGO);
}

QString TeXCommands::callLaTeXe()
{
    return call(CMD_LATEXE_LOGO);
}

QString TeXCommands::callLineBreak()
{
    return call(CMD_LINE_BREAK);
}

QString TeXCommands::callNewLine()
{
    return call(CMD_NEW_LINE);
}


QString TeXCommands::callNewPage()
{
    return call(CMD_NEW_PAGE);
}

QString TeXCommands::callTitle(QString titleText)
{
    return call(CMD_TITLE, titleText);
}

QString TeXCommands::callMakeTitle()
{
    return call(CMD_MAKE_TITLE);
}

QString TeXCommands::callTableOfContents()
{
    return call(CMD_TABLE_OF_CONTENTS);
}

QString TeXCommands::callListOfFigures()
{
    return call(CMD_LIST_OF_FIGURES);
}

QString TeXCommands::callListOfTables()
{
    return call(CMD_LIST_OF_TABLES);
}

QString TeXCommands::callLowDots()
{
    return call(CMD_LOW_DOTS);
}

QString TeXCommands::callLowSloppy()
{
    return call(CMD_LOW_SLOPPY);
}

QString TeXCommands::callFrenchSpacing()
{
    return call(CMD_FRENCH_SPACING);
}

QString TeXCommands::callParagraph()
{
    return call(CMD_PARAGRAPH);
}

QString TeXCommands::callPart(QString partText)
{
    return call(CMD_PART, partText);
}

QString TeXCommands::callAppendix()
{
    return call(CMD_APPENDIX);
}

QString TeXCommands::callFrontMatter()
{
    return call(CMD_FRONT_MATTER);
}

QString TeXCommands::callBackMatter()
{
    return call(CMD_BACK_MATTER);
}

QString TeXCommands::callMainMatter()
{
    return call(CMD_MAIN_MATTER);
}

QString TeXCommands::callItem()
{
    return call(CMD_ITEM);
}

QString TeXCommands::callNewRowTab()
{
    return call(CMD_TAB_NEW_ROW);
}

QString TeXCommands::callNewLineTab()
{
    return call(CMD_TAB_NEW_LINE);
}

QString TeXCommands::callNewLineTab(bool doHorizontalLine)
{
    if (doHorizontalLine) {
        return call(CMD_TAB_HORIZ_LINE);
    } else {
        return call(CMD_TAB_NEW_LINE);
    }
}

QString TeXCommands::callNewPartialHorizontalLineTab(int firstColumnNumber,
                                                     int secondColumnNumber) //Create a partial horizontal line between column i and column j.
{
    return call(CMD_TAB_CLINE, firstColumnNumber + "-" + secondColumnNumber);
}

QString TeXCommands::callColumnSeparatorTab(int separation)
{
    return call(CMD_TAB_COL_SEP, separation + "pt");
}

QString TeXCommands::callRowSpaceTab(float spacing)
{
    return call(CMD_TAB_ARRAY_STRETCH, QString::number(spacing));
}

QString TeXCommands::callMultiColumnTab(int quantity, QString type, QString name)
{
    QStringList args;
    args.append(QString::number(quantity));
    args.append(type);
    args.append(name);

    return call(CMD_TAB_MULTI_COLUMN, args);
}

QString TeXCommands::callClearPage()
{
    return call(CMD_CLEAR_PAGE);
}

QString TeXCommands::callClearPageDouble()
{
    return call(CMD_CLEAR_PAGE_DOUBLE);
}

QString TeXCommands::callProtect()
{
    return call(CMD_PROTECT);
}

QString TeXCommands::callLeftAlign(QString text)
{
    return call(CMD_LEFT_ALIGN, text);
}

QString TeXCommands::callCentering(QString text)
{
    return call(CMD_CENTERING, text);
}

QString TeXCommands::callRightAlign(QString text)
{
    return call(CMD_RIGHT_ALIGN, text);
}

QString TeXCommands::callJustify()
{
    return call(CMD_JUSTIFY);
}

QString TeXCommands::callChapter(QString chapterText)
{
    return call(CMD_CHAPTER, chapterText);
}

QString TeXCommands::callSection(QString sectionText)
{
    return call(CMD_SECTION, sectionText);
}

QString TeXCommands::callSubSection(QString subSectionText)
{
    return call(CMD_SUBSECTION, subSectionText);
}

QString TeXCommands::callSubSubSection(QString subSubSectionText)
{
    return call(CMD_SUBSUBSECTION, subSubSectionText);
}

QString TeXCommands::callChapterNoN(QString chapterText)
{
    return call(CMD_CHAPTER_NONUMBERING, chapterText);
}

QString TeXCommands::callSectionNoN(QString sectionText)
{
    return call(CMD_SECTION_NONUMBERING, sectionText);
}

QString TeXCommands::callSubSectionNoN(QString subSectionText)
{
    return call(CMD_SUBSECTION_NONUMBERING, subSectionText);
}

QString TeXCommands::callSubSubSectionNoN(QString subSubSectionText)
{
    return call(CMD_SUBSUBSECTION_NONUMBERING, subSubSectionText);
}

QString TeXCommands::callTextBold(QString boldText)
{
    return call(CMD_BOLD, boldText);
}

QString TeXCommands::callTextUnderline(QString underlineText)
{
    return call(CMD_UNDERLINE, underlineText);
}

QString TeXCommands::callTextItalic(QString italicText)
{
    return call(CMD_ITALIC, italicText);
}

QString TeXCommands::callTextSmallCaps(QString smallCapsText)
{
    return call(CMD_SMALL_CAPS, smallCapsText);
}

QString TeXCommands::callTextColor(QString color, QString coloredText)
{
    QStringList args;
    args.append(color);
    args.append(coloredText);
    return call(CMD_COLOR, args);
}

QString TeXCommands::callTextEmphatize(QString emphatizeQString)
{
    return call(CMD_EMPHATIZE, emphatizeQString);
}

QString TeXCommands::callTextStrikethrough(QString strikethroughQString)
{
    return call(CMD_STRIKETHROUGH_SOUT, strikethroughQString);
}

QString TeXCommands::callTextAlternativeStrikethrough(QString strikethroughQString)
{
    return call(CMD_STRIKETHROUGH_ST, strikethroughQString);
}


QString TeXCommands::callBegin(QString environment)
{
    return call(CMD_BEGIN, environment);
}

QString TeXCommands::callBegin(QString environment, QString options)
{
    QStringList args;
    args.append(environment);
    args.append(options);
    return call(CMD_BEGIN, args);
}

QString TeXCommands::callEnd(QString environment)
{
    return call(CMD_END, environment);
}

QString TeXCommands::callDocumentClass()
{
    return call(CMD_DOCUMENT_CLASS);
}

QString TeXCommands::callDocumentClass(QString documentClass)
{
    return call(CMD_DOCUMENT_CLASS, documentClass);
}

QString TeXCommands::callDocumentClass(QString documentClass,
                                       QString documentClassOptions)
{
    return call(CMD_DOCUMENT_CLASS, documentClass, documentClassOptions);
}

QString TeXCommands::callUsePackage(QString packageName)
{
    return call(CMD_USE_PACKAGE, packageName);
}

QString TeXCommands::callUsePackage(QString packageName, QString options)
{
    return call(CMD_USE_PACKAGE, options, packageName);
}

QString TeXCommands::callAuthor(QString author)
{
    return call(CMD_AUTHOR, author);
}

QString TeXCommands::callDate(QString date)
{
    return call(CMD_DATE, date);
}

QString TeXCommands::callAddress(QString address)
{
    return call(CMD_ADDRESS, address);
}

QString TeXCommands::callSetMainFont()
{
    return call(CMD_SETMAINFONT);
}

QString TeXCommands::callSetMainFont(QString font)
{
    return call(CMD_SETMAINFONT, font);
}
QString TeXCommands::callBFSeries()
{
    return call(CMD_BFSERIES);
}

QString TeXCommands::callTextWidth()
{
    return call(CMD_TEXTWIDTH);
}

QString TeXCommands::callVFill()
{
    return call(CMD_VFILL);
}
QString TeXCommands::callIncludeGraphics(QString path, QString options)
{
    return call(CMD_INCLUDE_GRAPHICS, options, path);
}
QString TeXCommands::callIncludeGraphics()
{
    return call(CMD_INCLUDE_GRAPHICS);
}
QString TeXCommands::callCaption(QString text)
{
    return call(CMD_CAPTION, text);
}
QString TeXCommands::callCaption()
{
    return call(CMD_CAPTION);
}
QString TeXCommands::callLabel(QString text)
{
    return call(CMD_LABEL, text);
}
QString TeXCommands::callLabel()
{
    return call(CMD_LABEL);
}
QString TeXCommands::callEndOfDump()
{
    return call(CMD_ENDOFDUMP);
}
QString TeXCommands::callThisPageStyle(QString style)
{
    return call(CMD_THISPAGESTYLE, style);
}
QString TeXCommands::callMBox(QString text)
{
    return call(CMD_MBOX, text);
}
QString TeXCommands::callFootNote(QString text)
{
    return call(CMD_FOOTNOTE, text);
}
QString TeXCommands::callUrl(QString url)
{
    return call(CMD_URL, url);
}
QString TeXCommands::callTiny()
{
    return call(CMD_TINY);
}
QString TeXCommands::callScriptSize()
{
    return call(CMD_SCRIPTSIZE);
}
QString TeXCommands::callFootNoteSize()
{
    return call(CMD_FOOTNOTESIZE);
}
QString TeXCommands::callSmall()
{
    return call(CMD_SMALL);
}
QString TeXCommands::callNormalSize()
{
    return call(CMD_NORMALSIZE);
}
QString TeXCommands::callLargeSize()
{
    return call(CMD_LARGE);
}
QString TeXCommands::callXLargeSize()
{
    return call(CMD_XLARGE);
}
QString TeXCommands::callXXLargeSize()
{
    return call(CMD_XXLARGE);

}
QString TeXCommands::callHugeSize()
{
    return call(CMD_HUGE);

}
QString TeXCommands::callXHugeSize()
{
    return call(CMD_XHUGE);

}
QString TeXCommands::callBibliography(QString filePath)
{
    return call(CMD_BIBLIOGRAPHY, filePath);
}
QString TeXCommands::callBibliographyStyle(QString style)
{
    return call(CMD_BIBLIOGRAPHYSTYLE, style);
}
QString TeXCommands::callCite(QString item)
{
    return call(CMD_CITE, item);
}
QString TeXCommands::callNoCite(QString item)
{
    return call(CMD_NOCITE, item);
}
QString TeXCommands::callLstInputListing(QString options, QString path)
{
    return call(CMD_LSTINPUTLISTING, path, options);
}
QString TeXCommands::callPageStyle(QString options)
{
    return call(CMD_PAGESTYLE, options);
}
QString TeXCommands::callReference(QString item)
{
    return call(CMD_REFERENCE, item);
}
QString TeXCommands::callEqReference(QString item)
{
    return call(CMD_EQREFERENCE, item);
}
QString TeXCommands::callRMDefault(QString item)
{
    return call(CMD_RMDEFAULT, item);
}
QString TeXCommands::callLineSpread(QString item)
{
    return call(CMD_LINESPREAD, item);
}
QString TeXCommands::callHTMLColor(QString color)
{
    return call(CMD_HTML_COLOR, color);
}
QString TeXCommands::callText(QString string)
{
    return call(CMD_TEXT, string);
}
QString TeXCommands::callRowColor(QString code)
{
    return call(CMD_ROWCOLOR, code);
}
QString TeXCommands::callLogo(QString code)
{
    return call(CMD_LOGO, code);
}
