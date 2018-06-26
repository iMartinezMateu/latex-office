#include <QString>
#include <QRegularExpressionMatchIterator>
#include "lib/latex/commands.h"
#include "lib/latex/constants.h"
#include "lib/latex/symbols.h"
#include <QDebug>
#include <QRegExp>
#ifndef PARSER
#define PARSER
/**
 *
 * The Parser component converts the LaTeX code to HTML and viceversa. This is widely used in <<Caja>>, so it can show the text style correctly.
 * @author Iván Martínez Mateu
 */
/*************************************************************************************************/
/**
  @brief This function will convert a LaTeX code to HTML.
  @param code LaTeX code to convert.
  @returns The function returns the HTML conversion of a LaTeX document.
  */
QString toHTML(QString code);
/*************************************************************************************************/
/**
  @brief This function will convert a HTML code to LaTeX.
  @param code HTML code to convert.
  @returns The function returns the LaTeX conversion of a HTML document.
  */
QString fromHTML(QString code);

#endif // PARSER

