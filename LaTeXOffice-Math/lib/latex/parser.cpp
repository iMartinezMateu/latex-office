#include "parser.h"

QString fromHTML(QString code)
{
    TeXCommands command;
    code = code.remove("\n");
    code = code.remove("<!DOCTYPE HTML PUBLIC \"-\/\/W3C\/\/DTD HTML 4.0\/\/EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">");
    code = code.remove("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">");
    code = code.remove("p, li { white-space: pre-wrap; }");
    code = code.remove("</style>");
    code = code.remove("</head>");
    code = code.remove("<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;");
    code = code.remove("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;");
    code = code.remove("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;");
    code = code.remove("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:2; text-indent:0px;");
    code = code.remove("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:3; text-indent:0px;");
    code = code.remove("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:4; text-indent:0px;");
    code = code.remove("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:5; text-indent:0px;");
    code = code.remove("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:6; text-indent:0px;");
    code = code.remove("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:7; text-indent:0px;");
    code = code.remove("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:8; text-indent:0px;");
    code = code.remove("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;");
    code = code.remove("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;");
    code = code.remove("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:2; text-indent:0px;");
    code = code.remove("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:3; text-indent:0px;");
    code = code.remove("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:4; text-indent:0px;");
    code = code.remove("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:5; text-indent:0px;");
    code = code.remove("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:6; text-indent:0px;");
    code = code.remove("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:7; text-indent:0px;");
    code = code.remove("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:8; text-indent:0px;");
    code = code.remove("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:8; text-indent:0px;");
    code = code.remove("<p align=\"justify\" style=\"margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:8; text-indent:0px; ");
    QRegularExpression bodyRegex("(\<body.*?\>)");
    if (bodyRegex.match(code).hasMatch()) {
        code = code.remove(bodyRegex.match(code).captured(1));
    }

    QRegularExpression colorRegex("(<span style=\".*? color:\#(.*?)\;\"\>)");
    QRegularExpressionMatchIterator colorRegexIterator = colorRegex.globalMatch(code);
    while (colorRegexIterator.hasNext())
    {
        QRegularExpressionMatch match = colorRegexIterator.next();
        code = code.replace(match.captured(1),
                            command.callHTMLColor(match.captured(2).toUpper()));
    }

    QRegularExpression bulletListRegex("(\<ul style=\".*?)\<li .*?");
    if (bulletListRegex.match(code).hasMatch()) {
        code = code.replace(bulletListRegex.match(code).captured(1),
                            command.callBegin(ENV_ITEMIZE));
    }
    QRegularExpression enumerateListRegex("(\<ol style=\".*?)\<li .*?");
    if (enumerateListRegex.match(code).hasMatch()) {
        code = code.replace(enumerateListRegex.match(code).captured(1),
                            command.callBegin(ENV_ENUMERATE));
    }
    QRegularExpression emptyItemListRegex("(\<li.*?\>");
    if (emptyItemListRegex.match(code).hasMatch()) {
        code = code.remove(emptyItemListRegex.match(code).captured(0));
    }
    QRegularExpression itemListRegex("\<li.*?\"\>(.*?)\<\/li>");
    if (itemListRegex.match(code).hasMatch()) {
        code = code.replace(itemListRegex.match(code).captured(0),
                            command.callItem() + " " + itemListRegex.match(code).captured(1));
        code = code.replace("<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"center\" style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"right\" style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"right\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"justify\" style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"center\" style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"right\" style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"right\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"justify\" style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"justify\" style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
        code = code.replace("<li align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">",
                            command.callItem() + " ");
    }

    QRegularExpression centerAlignRegex("(\<p align=\"center\".*?\>)");
    if (centerAlignRegex.match(code).hasMatch()) {

        code = code.replace(centerAlignRegex.match(code).captured(0),
                            command.callBegin(TEXT_CENTER));
    }
    QRegularExpression rightAlignRegex("(\<p align=\"right\".*?\>)");
    if (rightAlignRegex.match(code).hasMatch()) {
        code = code.replace(rightAlignRegex.match(code).captured(0),
                            command.callBegin(TEXT_RIGHT));
    }
    QRegularExpression justifyAlignRegex("(\<p align=\"justify\".*?\>)");
    if (justifyAlignRegex.match(code).hasMatch()) {
        code = code.replace(justifyAlignRegex.match(code).captured(0), "");
    }

    QRegularExpression hrefRegex("(\<a href=\"(.*?)\"\>.*<\/a>)");
    if (hrefRegex.match(code).hasMatch()) {
        code = code.replace(hrefRegex.match(code).captured(1),
                            command.callUrl(hrefRegex.match(code).captured(2)));

    }

    QRegularExpression emptyParagraphRegex("(\<p.*?\>)");
    if (emptyParagraphRegex.match(code).hasMatch()) {
        code = code.remove(emptyParagraphRegex.match(code).captured(0));
    }



    //Colores
    code = code.remove("color:#0000ff;");

    code = code.replace("•", command.callItem());
    code = code.remove("<span style=\"");
    code = code.remove("\">");
    code = code.replace("font-weight:600;", QString(CMD_BOLD) + "{");
    code = code.replace("font-size:7.33pt;", command.callTiny() + " ");
    code = code.replace("font-size:10pt;", command.callSmall() + " ");
    code = code.replace("font-size:12.5pt;", command.callNormalSize() + " ");
    code = code.replace("font-size:15pt;", command.callLargeSize() + " ");
    code = code.replace("font-size:18pt;", command.callXLargeSize() + " ");
    code = code.replace("font-size:21pt;", command.callXXLargeSize() + " ");
    code = code.replace("font-size:24pt;", command.callHugeSize() + " ");
    code = code.replace("font-size:28pt;", command.callXHugeSize() + " ");
    code = code.replace("font-weight:600;", QString(CMD_BOLD) + "{");
    code = code.replace("font-style:italic;", QString(CMD_ITALIC) + "{");
    code = code.replace("text-decoration: underline;", QString(CMD_UNDERLINE) + "{");
    code = code.replace("text-decoration: line-through;",
                        QString(CMD_STRIKETHROUGH_ST) + "{");
    code = code.replace("font-variant:small-caps;", QString(CMD_SMALL_CAPS) + "{");
    code = code.replace("font-weight:16; font-style:italic;", QString(CMD_EMPHATIZE) + "{");
    code = code.replace("<a href=\"", QString(CMD_URL) + "{");
    code = code.replace("vertical-align:sub;", QString(CMD_FOOTNOTE) + "{");
    code = code.replace("</span>", "}");
    code = code.remove("</li>");
    if (code.contains(command.callBegin(TEXT_LEFT))) {
        code = code.replace("</p>", command.callEnd(TEXT_LEFT));
    } else if (code.contains(command.callBegin(TEXT_CENTER))) {
        code = code.replace("</p>", command.callEnd(TEXT_CENTER));
    } else if (code.contains(command.callBegin(TEXT_RIGHT))) {
        code = code.replace("</p>", command.callEnd(TEXT_RIGHT));
    } else if (code.contains(command.callBegin(ENV_ITEMIZE))) {
        code = code.replace("</ul>", command.callEnd(ENV_ITEMIZE));
    } else if (code.contains(command.callBegin(ENV_ENUMERATE))) {
        code = code.replace("</ol>", command.callEnd(ENV_ENUMERATE));
    }

    code = code.remove("</p>");
    code = code.remove("</ol>");
    code = code.remove("</ul>");
    code = code.remove("</body>");
    code = code.remove("</html>");
    code = code.replace("&quot;", "''");
    code = code.replace("<br />", "\n\n");
    code = code.replace("<" , "$" + QString(SYM_LESS) + "$");
    code = code.replace("&lt;" , "$" + QString(SYM_LESS) + "$");
    code = code.replace("≤" , "$" + QString(SYM_LESSOREQUAL) + "$");
    code = code.replace("≪" , "$" + QString(SYM_MUCHLESS) + "$");
    code = code.replace("⊂" , "$" + QString(SYM_SUBSET) + "$");
    code = code.replace("⊆" , "$" + QString(SYM_SUBSETOREQUAL) + "$");
    code = code.replace("⊈" , "$" + QString(SYM_NOTSUBSETOREQUAL) + "$");
    code = code.replace("⊏" , "$" + QString(SYM_SQUAREDSUBSET) + "$");
    code = code.replace("≼" , "$" + QString(SYM_PRECEDESOREQUAL) + "$");
    code = code.replace(">" , "$" + QString(SYM_GREATER) + "$");
    code = code.replace("&gt;" , "$" + QString(SYM_GREATER) + "$");
    code = code.replace("≥" , "$" + QString(SYM_GREATEROREQUAL) + "$");
    code = code.replace("≫" , "$" + QString(SYM_MUCHGREATER) + "$");
    code = code.replace("⊃" , "$" + QString(SYM_SUPERSET) + "$");
    code = code.replace("⊇" , "$" + QString(SYM_SUPERSETOREQUAL) + "$");
    code = code.replace("⊉" , "$" + QString(SYM_NOTSUPERSETOREQUAL) + "$");
    code = code.replace("⊐" , "$" + QString(SYM_SQUAREDSUPERSET) + "$");
    code = code.replace("⊒" , "$" + QString(SYM_SQUAREDSUPERSETOREQUAL) + "$");
    code = code.replace("≽", "$" + QString(SYM_SUCCEEDSOREQUAL) + "$");
    code = code.replace("=", "$" + QString(SYM_EQUAL) + "$");
    code = code.replace("≐" , "$" + QString(SYM_EQUALWITHADOTABOVEIT) + "$");
    code = code.replace("≡" , "$" + QString(SYM_EQUIVALENT) + "$");
    code = code.replace("≈" , "$" + QString(SYM_APPROXIMATELYEQUAL) + "$");
    code = code.replace("≅" , "$" + QString(SYM_CONGRUENT) + "$");
    code = code.replace("≃", "$" + QString(SYM_SIMILAROREQUAL) + "$");
    code = code.replace("∼" , "$" + QString(SYM_SIMILAR) + "$");
    code = code.replace("∝" , "$" + QString(SYM_PROPORTIONAL) + "$");
    code = code.replace("≠", "$" + QString(SYM_NOTEQUAL) + "$");
    code = code.replace("∥" , "$" + QString(SYM_PARALLEL) + "$");
    code = code.replace("≃", "$" + QString(SYM_ASYMPTOTICALLYEQUAL) + "$");
    code = code.replace("⊢" ,
                        "$" + QString(SYM_SHORTVERTICALBARTOUCHINGAHORIZONTALBAR) + "$");
    code = code.replace("∈" , "$" + QString(SYM_ELEMENTOF) + "$");
    code = code.replace("⌣" , "$" + QString(SYM_SMILE) + "$");
    code = code.replace("⊧", "$" + QString(SYM_MODELS) + "$");
    code = code.replace("⊥" , "$" + QString(SYM_PERPENDICULAR) + "$");
    code = code.replace("≺" , "$" + QString(SYM_PRECEDE) + "$");
    code = code.replace("∢" , "$" + QString(SYM_SPHERICALANGLE) + "$");
    code = code.replace("∦" , "$" + QString(SYM_NOTPARALLEL) + "$");
    code = code.replace("⋈", "$" + QString(SYM_NORMALSUBGROUPOF) + "$");
    code = code.replace("⊣", "$" + QString(SYM_REVERSEDASH) + "$");
    code = code.replace("∋" , "$" + QString(SYM_CONTAINSASMEMBER) + "$");
    code = code.replace("⌢" , "$" + QString(SYM_FROWN) + "$");
    code = code.replace("∉" , "$" + QString(SYM_NOTIN) + "$");
    code = code.replace("∣" , "$" + QString(SYM_MIDDLE) + "$");
    code = code.replace("≻" , "$" + QString(SYM_SUCCEEDS) + "$");
    code = code.replace("∡" , "$" + QString(SYM_MEASUREDANGLE) + "$");
    code = code.replace("±" , "$" + QString(SYM_PLUSORMINUS) + "$");
    code = code.replace("∓" , "$" + QString(SYM_MINUSORPLUS) + "$");
    code = code.replace("×" , "$" + QString(SYM_TIMES) + "$");
    code = code.replace("÷", "$" + QString(SYM_DIVISOR) + "$");
    code = code.replace("*", "$" + QString(SYM_ASTERISK) + "$");
    code = code.replace("†", "$" + QString(SYM_DAGGAR) + "$");
    code = code.replace("‡" , "$" + QString(SYM_DOUBLEDAGGAR) + "$");
    code = code.replace("∩" , "$" + QString(SYM_INTERSECTION) + "$");
    code = code.replace("∪", "$" + QString(SYM_UNION) + "$");
    code = code.replace("⊎" , "$" + QString(SYM_MULTISETUNION) + "$");
    code = code.replace("⊓", "$" + QString(SYM_SQUAREINTERSECTION) + "$");
    code = code.replace("⊔" , "$" + QString(SYM_SQUAREUNION) + "$");
    code = code.replace("⋁", "$" + QString(SYM_LOGICALOR) + "$");
    code = code.replace("⋁" , "$" + QString(SYM_VOPERATOR) + "$");
    code = code.replace("∧" , "$" + QString(SYM_LOGICALAND) + "$");
    code = code.replace("∧", "$" + QString(SYM_WEDGE) + "$");
    code = code.replace("⋅" , "$" + QString(SYM_DOTMULTIPLICATION) + "$");
    code = code.replace("⋄" , "$" + QString(SYM_DIAMONDOPERATOR) + "$");
    code = code.replace("△" , "$" + QString(SYM_WIDEUPTRIANGLE) + "$");
    code = code.replace("▽" , "$" + QString(SYM_WIDEDOWNTRIANGLE) + "$");
    code = code.replace("◃" , "$" + QString(SYM_LEFTPOINTINGTRIANGLE) + "$");
    code = code.replace("▹" , "$" + QString(SYM_RIGHTPOINTINGTRIANGLE) + "$");
    code = code.replace("◯" , "$" + QString(SYM_LARGECIRCLE) + "$");
    code = code.replace("•" , "$" + QString(SYM_BULLET) + "$");
    code = code.replace("≀", "$" + QString(SYM_WREATHPRODUCT) + "$");
    code = code.replace("⊕" , "$" + QString(SYM_CIRCLEDPLUS) + "$");
    code = code.replace("⊖" , "$" + QString(SYM_CIRCLEDMINUS) + "$");
    code = code.replace("⊗" , "$" + QString(SYM_CIRCLEDTIMES) + "$");
    code = code.replace("Ø" , "$" + QString(SYM_CIRCLEDSLASH) + "$");
    code = code.replace("⊙", "$" + QString(SYM_CIRCLEDDOT) + "$");
    code = code.replace("∘", "$" + QString(SYM_RINGOPERATOR) + "$");
    code = code.replace("∖", "$" + QString(SYM_SETMINUS) + "$");
    code = code.replace("∐", "$" + QString(SYM_AMALGAMATION) + "$");
    code = code.replace("∐" , "$" + QString(SYM_COPRODUCT) + "$");
    code = code.replace("∃" , "$" + QString(SYM_THEREEXISTSATLEASTONE) + "$");
    code = code.replace("∃!" , "$" + QString(SYM_THEREEXISTSONEANDONLYONE) + "$");
    code = code.replace("∄" , "$" + QString(SYM_THEREISNO) + "$");
    code = code.replace("∀", "$" + QString(SYM_FORALL) + "$");
    code = code.replace("¬", "$" + QString(SYM_LOGICALNOT) + "$");
    code = code.replace("⊂" , "$" + QString(SYM_SUBSET) + "$");
    code = code.replace("⊃", "$" + QString(SYM_SUPSET) + "$");
    code = code.replace("∈", "$" + QString(SYM_IN) + "$");
    code = code.replace("∉", "$" + QString(SYM_NOTIN) + "$");
    code = code.replace("∋" , "$" + QString(SYM_CONTAINS) + "$");
    code = code.replace("∧", "$" + QString(SYM_LOGICALAND) + "$");
    code = code.replace("∨", "$" + QString(SYM_LOGICALOR) + "$");
    code = code.replace("→" , "$" + QString(SYM_RIGHTARROW) + "$");
    code = code.replace("←" , "$" + QString(SYM_LEFTARROW) + "$");
    code = code.replace("↦", "$" + QString(SYM_MAPSTO) + "$");
    code = code.replace("⇒", "$" + QString(SYM_IMPLIES) + "$");
    code = code.replace("⇒" , "$" + QString(SYM_RIGHTARROW_CAPS) + "$");
    code = code.replace("↔", "$" + QString(SYM_LEFTRIGHTARROW) + "$");
    code = code.replace("⇔" , "$" + QString(SYM_IFF) + "$");
    code = code.replace("⇔" , "$" + QString(SYM_LEFTRIGHTARROW_CAPS) + "$");
    code = code.replace("⊤" , "$" + QString(SYM_TOP) + "$");
    code = code.replace("⊥" , "$" + QString(SYM_BOTTOM) + "$");
    code = code.replace("∅" , "$" + QString(SYM_EMPTYSET) + "$");
    code = code.replace("∅" , "$" + QString(SYM_NOTHING) + "$");
    code = code.replace("∣" , "$" + QString(SYM_VERTICALBAR) + "$");
    code = code.replace("↑" , "$" + QString(SYM_UPARROW) + "$");
    code = code.replace("↓" , "$" + QString(SYM_DOWNARROW) + "$");
    code = code.replace("‖", "$" + QString(SYM_DOUBLEVERTICALBAR) + "$");
    code = code.replace("↑" , "$" + QString(SYM_UPARROW_CAPS) + "$");
    code = code.replace("↓" , "$" + QString(SYM_DOWNARROW_CAPS) + "$");
    code = code.replace("‹", "$" + QString(SYM_LEFTANGLEBRACKET) + "$");
    code = code.replace("⌈" , "$" + QString(SYM_LEFTCEIL) + "$");
    code = code.replace("⌊" , "$" + QString(SYM_LEFTFLOOR) + "$");
    code = code.replace("›" , "$" + QString(SYM_RIGHTANGLEBRACKET) + "$");
    code = code.replace("⌉" , "$" + QString(SYM_RIGHTCEIL) + "$");
    code = code.replace("⌋" , "$" + QString(SYM_RIGHTFLOOR) + "$");
    code = code.replace("Α" , "$" + QString(SYM_A) + "$");
    code = code.replace("α" , "$" + QString(SYM_ALPHA) + "$");
    code = code.replace("Β" , "$" + QString(SYM_B) + "$");
    code = code.replace("β" , "$" + QString(SYM_BETA) + "$");
    code = code.replace("Γ", "$" + QString(SYM_GAMMA_CAPS) + "$");
    code = code.replace("γ", "$" + QString(SYM_GAMMA) + "$");
    code = code.replace("Δ", "$" + QString(SYM_DELTA_CAPS) + "$");
    code = code.replace("δ" , "$" + QString(SYM_DELTA) + "$");
    code = code.replace("Ε" , "$" + QString(SYM_E) + "$");
    code = code.replace("ε" , "$" + QString(SYM_EPSILON) + "$");
    code = code.replace("ϵ" , "$" + QString(SYM_VAREPSILON) + "$");
    code = code.replace("Ζ" , "$" + QString(SYM_Z) + "$");
    code = code.replace("ζ" , "$" + QString(SYM_ZETA) + "$");
    code = code.replace("Η" , "$" + QString(SYM_H) + "$");
    code = code.replace("η", "$" + QString(SYM_ETA) + "$");
    code = code.replace("Θ" , "$" + QString(SYM_THETA_CAPS) + "$");
    code = code.replace("θ", "$" + QString(SYM_THETA) + "$");
    code = code.replace("ϑ" , "$" + QString(SYM_VARTHETA) + "$");
    code = code.replace("Ι" , "$" + QString(SYM_I) + "$");
    code = code.replace("ι" , "$" + QString(SYM_IOTA) + "$");
    code = code.replace("K" , "$" + QString(SYM_K) + "$");
    code = code.replace("κ" , "$" + QString(SYM_KAPPA) + "$");
    code = code.replace("ϰ" , "$" + QString(SYM_VARKAPPA) + "$");
    code = code.replace("Λ" , "$" + QString(SYM_LAMBDA_CAPS) + "$");
    code = code.replace("λ" , "$" + QString(SYM_LAMBDA) + "$");
    code = code.replace("Μ" , "$" + QString(SYM_M) + "$");
    code = code.replace("μ", "$" + QString(SYM_MU) + "$");
    code = code.replace("Ν", "$" + QString(SYM_N) + "$");
    code = code.replace("ν", "$" + QString(SYM_NU) + "$");
    code = code.replace("Ξ", "$" + QString(SYM_XI_CAPS) + "$");
    code = code.replace("ξ", "$" + QString(SYM_XI) + "$");
    code = code.replace("Ο", "$" + QString(SYM_O) + "$");
    code = code.replace("ο", "$" + QString(SYM_OMICRON) + "$");
    code = code.replace("Π", "$" + QString(SYM_PI_CAPS) + "$");
    code = code.replace("π" , "$" + QString(SYM_PI) + "$");
    code = code.replace("ϖ" , "$" + QString(SYM_VARPI) + "$");
    code = code.replace("ρ", "$" + QString(SYM_RHO) + "$");
    code = code.replace("ϱ" , "$" + QString(SYM_VARRHO) + "$");
    code = code.replace("Σ" , "$" + QString(SYM_SIGMA_CAPS) + "$");
    code = code.replace("σ", "$" + QString(SYM_SIGMA) + "$");
    code = code.replace("ς", "$" + QString(SYM_VARSIGMA) + "$");
    code = code.replace("Τ", "$" + QString(SYM_T) + "$");
    code = code.replace("τ" , "$" + QString(SYM_TAU) + "$");
    code = code.replace("Υ" , "$" + QString(SYM_UPSILON_CAPS) + "$");
    code = code.replace("υ" , "$" + QString(SYM_UPSILON) + "$");
    code = code.replace("Φ" , "$" + QString(SYM_PHI_CAPS) + "$");
    code = code.replace("φ", "$" + QString(SYM_PHI) + "$");
    code = code.replace("ϕ", "$" + QString(SYM_VARPHI) + "$");
    code = code.replace("Χ" , "$" + QString(SYM_X) + "$");
    code = code.replace("χ" , "$" + QString(SYM_CHI) + "$");
    code = code.replace("Ψ" , "$" + QString(SYM_PSI_CAPS) + "$");
    code = code.replace("ψ" , "$" + QString(SYM_PSI) + "$");
    code = code.replace("Ω" , "$" + QString(SYM_OMEGA_CAPS) + "$");
    code = code.replace("ω" , "$" + QString(SYM_OMEGA) + "$");
    code = code.replace("∂" , "$" + QString(SYM_PARTIAL) + "$");
    code = code.replace("∂" , "$" + QString(SYM_DERIVATE) + "$");
    code = code.replace("ð" , "$" + QString(SYM_ETH) + "$");
    code = code.replace("ℏ" , "$" + QString(SYM_REDUCEDPLANCKCONSTANT) + "$");
    code = code.replace("ı" , "$" + QString(SYM_IMATH) + "$");
    code = code.replace("ĵ" , "$" + QString(SYM_JMATH) + "$");
    code = code.replace("ℓ" , "$" + QString(SYM_ELL) + "$");
    code = code.replace("ℜ" , "$" + QString(SYM_REALPART) + "$");
    code = code.replace("ℑ" , "$" + QString(SYM_IMAGINARYPART) + "$");
    code = code.replace("℘" , "$" + QString(SYM_WEIERSTRASSPOWERSET) + "$");
    code = code.replace("∇" , "$" + QString(SYM_NABLA) + "$");
    code = code.replace("□" , "$" + QString(SYM_BOX) + "$");
    code = code.replace("∞" , "$" + QString(SYM_INFINITY) + "$");
    code = code.replace("ℵ", "$" + QString(SYM_ALEPH) + "$");
    code = code.replace("ℶ" , "$" + QString(SYM_BETH) + "$");
    code = code.replace("ℷ" , "$" + QString(SYM_GIMEL) + "$");
    code = code.replace("#" , "\\#");
    code = code.replace("%" , "\\%");
    code = code.replace("€" , "\\textup{\\euro}");
    code = code.replace("$" , "\\$");
    code = code.replace("£" , "\\textup{\\pounds}");
    code = code.replace("¢" , "\\cent");
    code = code.replace("¥" , "\\yen");


    code = code.remove(QRegExp("<(?:div|span|tr|td|br|body|html|tt|a|strong|p)[^>]*>",
                               Qt::CaseInsensitive));
    return code;
}

QString toHTML(QString code)
{
    TeXCommands command;
    QRegularExpression boldRegularExpresion("\\\\textbf\{(.*?)\}");
    QRegularExpressionMatchIterator iterator = boldRegularExpresion.globalMatch(code);
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString styledString = match.captured(1);
        code = code.replace(command.callTextBold(styledString), "<b>" + styledString + "</b>");
    }
    QRegularExpression italicsRegularExpresion("\\\\textit\{(.*?)\}");
    iterator = italicsRegularExpresion.globalMatch(code);
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString styledString = match.captured(1);
        code = code.replace(command.callTextItalic(styledString), "<i>" + styledString + "</i>");
    }
    QRegularExpression underlinedRegularExpresion("\\\\underline\{(.*?)\}");
    iterator = underlinedRegularExpresion.globalMatch(code);
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString styledString = match.captured(1);
        code = code.replace(command.callTextUnderline(styledString),
                            "<u>" + styledString + "</u>");
    }
    QRegularExpression  strikethroughRegularExpresion("\\\\sout\{(.*?)\}");
    iterator = strikethroughRegularExpresion.globalMatch(code);
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString styledString = match.captured(1);
        code = code.replace(command.callTextStrikethrough(styledString),
                            "<strike>" + styledString + "</strike>");
    }
    QRegularExpression  anotherStrikethroughRegularExpresion("\\\\st\{(.*?)\}");
    iterator = anotherStrikethroughRegularExpresion.globalMatch(code);
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString styledString = match.captured(1);
        code = code.replace(command.callTextAlternativeStrikethrough(styledString), styledString);
        code = code.replace(styledString, "<strike>" + styledString + "</strike>");
    }
    QRegularExpression smallCapsRegularExpresion("\\\\textsc\{(.*?)\}");
    iterator = smallCapsRegularExpresion.globalMatch(code);
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString styledString = match.captured(1);
        code = code.replace(command.callTextSmallCaps(styledString),
                            "<span style=\"font-variant: small-caps;\">" + styledString + "</span>");
    }
    QRegularExpression emphatizeRegularExpresion("\\\\emph\{(.*?)\}");
    iterator = emphatizeRegularExpresion.globalMatch(code);
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString styledString = match.captured(1);
        code = code.replace(command.callTextEmphatize(styledString),
                            "<em>" + styledString + "</em>");
    }
    QRegularExpression urlRegularExpresion("\\\\url\{(.*?)\}");
    iterator = urlRegularExpresion.globalMatch(code);
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString styledString = match.captured(1);
        code = code.replace(command.callUrl(styledString),
                            "<a href=\"" + styledString + "\">" + styledString + "</a>");
    }
    QRegularExpression footNoteRegularExpresion("\\\\footnote\{(.*?)\}");
    iterator = footNoteRegularExpresion.globalMatch(code);
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString styledString = match.captured(1);
        code = code.replace(command.callFootNote(styledString),
                            "<footnote><sub>" + styledString + "</sub></footnote>");
    }
    QRegularExpression chapterRegularExpresion("\\\\chapter\{(.*?)\}");
    iterator = chapterRegularExpresion.globalMatch(code);
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString styledString = match.captured(1);
        code = code.replace(command.callChapter(styledString), "<h1>" + styledString + "</h1>");
    }
    QRegularExpression sectionRegularExpresion("\\\\section\{(.*?)\}");
    iterator = sectionRegularExpresion.globalMatch(code);
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString styledString = match.captured(1);
        code = code.replace(command.callSection(styledString), "<h2>" + styledString + "</h2>");
    }
    QRegularExpression subSectionRegularExpresion("\\\\subsection\{(.*?)\}");
    iterator = subSectionRegularExpresion.globalMatch(code);
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString styledString = match.captured(1);
        code = code.replace(command.callSection(styledString), "<h3>" + styledString + "</h3>");
    }
    QRegularExpression subSubSectionRegularExpresion("\\\\subsubsection\{(.*?)\}");
    iterator = subSubSectionRegularExpresion.globalMatch(code);
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString styledString = match.captured(1);
        code = code.replace(command.callSubSubSection(styledString),
                            "<h4>" + styledString + "</h4>");
    }
    QRegularExpression bracketsRegularExpresion("\\[(.*?)\\]");
    iterator = bracketsRegularExpresion.globalMatch(code);
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString styledString = match.captured(1);
        code = code.replace("[" + styledString + "]",
                            "<breakline measure=" + styledString + "></breakline>");
    }

    code = code.replace(CMD_LINE_BREAK, "<br />");
    code = code.replace(command.callLowDots(), "...");
    code = code.replace("''", "&quot;");
    code = code.replace(command.callBegin(TEXT_LEFT), "<p align=\"left\">");
    code = code.replace(command.callBegin(TEXT_CENTER), "<p align=\"center\">");
    code = code.replace(command.callBegin(TEXT_RIGHT), "<p align=\"right\">");
    code = code.replace(command.callEnd(TEXT_LEFT), "</p>");
    code = code.replace(command.callEnd(TEXT_CENTER), "</p>");
    code = code.replace(command.callEnd(TEXT_RIGHT), "</p>");
    code = code.replace(command.callJustify(), "");
    code = code.replace("%justify%", "<p align=\"justify\">");
    code = code.replace(command.callTiny(), "<p style=\"font-size:7.33pt\">",
                        Qt::CaseInsensitive);
    code = code.replace(command.callSmall(), "<p style=\"font-size:10pt\">",
                        Qt::CaseInsensitive);
    code = code.replace(command.callNormalSize(), "<p style=\"font-size:12.5pt\">",
                        Qt::CaseInsensitive);
    code = code.replace(command.callLargeSize(), "<p style=\"font-size:large\">",
                        Qt::CaseInsensitive);
    code = code.replace(command.callHugeSize(), "<p style=\"font-size:xx-large\">");
    code = code.replace(command.callBFSeries(), "<bfseries>");
    code = code.replace(command.callItem(), "<li>");
    code = code.replace(command.callBegin(ENV_ITEMIZE), "<ul>");
    code = code.replace(command.callBegin(ENV_ENUMERATE) , "<ol>");
    code = code.replace(command.callEnd(ENV_ITEMIZE), "</ul>");
    code = code.replace(command.callEnd(ENV_ENUMERATE) , "</ol>");
    code = code.replace("$" + QString(SYM_LESS) + "$", "<");
    code = code.replace("$" + QString(SYM_LESSOREQUAL) + "$", "≤");
    code = code.replace("$" + QString(SYM_MUCHLESS) + "$", "≪");
    code = code.replace("$" + QString(SYM_SUBSET) + "$", "⊂");
    code = code.replace("$" + QString(SYM_SUBSETOREQUAL) + "$", "⊆");
    code = code.replace("$" + QString(SYM_NOTSUBSETOREQUAL) + "$", "⊈");
    code = code.replace("$" + QString(SYM_SQUAREDSUBSET) + "$", "⊏");
    code = code.replace("$" + QString(SYM_PRECEDESOREQUAL) + "$", "≼");
    code = code.replace("$" + QString(SYM_GREATER) + "$", ">");
    code = code.replace("$" + QString(SYM_GREATEROREQUAL) + "$", "≥");
    code = code.replace("$" + QString(SYM_MUCHGREATER) + "$", "≫");
    code = code.replace("$" + QString(SYM_SUPERSET) + "$", "⊃");
    code = code.replace("$" + QString(SYM_SUPERSETOREQUAL) + "$", "⊇");
    code = code.replace("$" + QString(SYM_NOTSUPERSETOREQUAL) + "$", "⊉");
    code = code.replace("$" + QString(SYM_SQUAREDSUPERSET) + "$", "⊐");
    code = code.replace("$" + QString(SYM_SQUAREDSUPERSETOREQUAL) + "$", "⊒");
    code = code.replace("$" + QString(SYM_SUCCEEDSOREQUAL) + "$", "≽");
    code = code.replace("$" + QString(SYM_EQUAL) + "$", "=");
    code = code.replace("$" + QString(SYM_EQUALWITHADOTABOVEIT) + "$", "≐");
    code = code.replace("$" + QString(SYM_EQUIVALENT) + "$", "≡");
    code = code.replace("$" + QString(SYM_APPROXIMATELYEQUAL) + "$", "≈");
    code = code.replace("$" + QString(SYM_CONGRUENT) + "$", "≅");
    code = code.replace("$" + QString(SYM_SIMILAROREQUAL) + "$", "≃");
    code = code.replace("$" + QString(SYM_SIMILAR) + "$", "∼");
    code = code.replace("$" + QString(SYM_PROPORTIONAL) + "$", "∝");
    code = code.replace("$" + QString(SYM_NOTEQUAL) + "$", "≠");
    code = code.replace("$" + QString(SYM_PARALLEL) + "$", "∥");
    code = code.replace("$" + QString(SYM_ASYMPTOTICALLYEQUAL) + "$", "≃");
    code = code.replace("$" + QString(SYM_SHORTVERTICALBARTOUCHINGAHORIZONTALBAR) + "$",
                        "⊢");
    code = code.replace("$" + QString(SYM_ELEMENTOF) + "$", "∈");
    code = code.replace("$" + QString(SYM_SMILE) + "$", "⌣");
    code = code.replace("$" + QString(SYM_MODELS) + "$", "⊧");
    code = code.replace("$" + QString(SYM_PERPENDICULAR) + "$", "⊥");
    code = code.replace("$" + QString(SYM_PRECEDE) + "$", "≺");
    code = code.replace("$" + QString(SYM_SPHERICALANGLE) + "$", "∢");
    code = code.replace("$" + QString(SYM_NOTPARALLEL) + "$", "∦");
    code = code.replace("$" + QString(SYM_NORMALSUBGROUPOF) + "$", "⋈");
    code = code.replace("$" + QString(SYM_REVERSEDASH) + "$", "⊣");
    code = code.replace("$" + QString(SYM_CONTAINSASMEMBER) + "$", "∋");
    code = code.replace("$" + QString(SYM_FROWN) + "$", "⌢");
    code = code.replace("$" + QString(SYM_NOTIN) + "$", "∉");
    code = code.replace("$" + QString(SYM_MIDDLE) + "$", "∣");
    code = code.replace("$" + QString(SYM_SUCCEEDS) + "$", "≻");
    code = code.replace("$" + QString(SYM_MEASUREDANGLE) + "$", "∡");
    code = code.replace("$" + QString(SYM_PLUSORMINUS) + "$", "±");
    code = code.replace("$" + QString(SYM_MINUSORPLUS) + "$", "∓");
    code = code.replace("$" + QString(SYM_TIMES) + "$", "×");
    code = code.replace("$" + QString(SYM_DIVISOR) + "$", "÷");
    code = code.replace("$" + QString(SYM_ASTERISK) + "$", "*");
    code = code.replace("$" + QString(SYM_DAGGAR) + "$", "†");
    code = code.replace("$" + QString(SYM_DOUBLEDAGGAR) + "$", "‡");
    code = code.replace("$" + QString(SYM_INTERSECTION) + "$", "∩");
    code = code.replace("$" + QString(SYM_UNION) + "$", "∪");
    code = code.replace("$" + QString(SYM_MULTISETUNION) + "$", "⊎");
    code = code.replace("$" + QString(SYM_SQUAREINTERSECTION) + "$", "⊓");
    code = code.replace("$" + QString(SYM_SQUAREUNION) + "$", "⊔");
    code = code.replace("$" + QString(SYM_LOGICALOR) + "$", "⋁");
    code = code.replace("$" + QString(SYM_VOPERATOR) + "$", "⋁");
    code = code.replace("$" + QString(SYM_LOGICALAND) + "$", "∧");
    code = code.replace("$" + QString(SYM_WEDGE) + "$", "∧");
    code = code.replace("$" + QString(SYM_DOTMULTIPLICATION) + "$", "⋅");
    code = code.replace("$" + QString(SYM_DIAMONDOPERATOR) + "$", "⋄");
    code = code.replace("$" + QString(SYM_WIDEUPTRIANGLE) + "$", "△");
    code = code.replace("$" + QString(SYM_WIDEDOWNTRIANGLE) + "$", "▽");
    code = code.replace("$" + QString(SYM_LEFTPOINTINGTRIANGLE) + "$", "◃");
    code = code.replace("$" + QString(SYM_RIGHTPOINTINGTRIANGLE) + "$", "▹");
    code = code.replace("$" + QString(SYM_LARGECIRCLE) + "$", "◯");
    code = code.replace("$" + QString(SYM_BULLET) + "$", "•");
    code = code.replace("$" + QString(SYM_WREATHPRODUCT) + "$", "≀");
    code = code.replace("$" + QString(SYM_CIRCLEDPLUS) + "$", "⊕");
    code = code.replace("$" + QString(SYM_CIRCLEDMINUS) + "$", "⊖");
    code = code.replace("$" + QString(SYM_CIRCLEDTIMES) + "$", "⊗");
    code = code.replace("$" + QString(SYM_CIRCLEDSLASH) + "$", "Ø");
    code = code.replace("$" + QString(SYM_CIRCLEDDOT) + "$", "⊙");
    code = code.replace("$" + QString(SYM_RINGOPERATOR) + "$", "∘");
    code = code.replace("$" + QString(SYM_SETMINUS) + "$", "∖");
    code = code.replace("$" + QString(SYM_AMALGAMATION) + "$", "∐");
    code = code.replace("$" + QString(SYM_COPRODUCT) + "$", "∐");
    code = code.replace("$" + QString(SYM_THEREEXISTSATLEASTONE) + "$", "∃");
    code = code.replace("$" + QString(SYM_THEREEXISTSONEANDONLYONE) + "$", "∃!");
    code = code.replace("$" + QString(SYM_THEREISNO) + "$", "∄");
    code = code.replace("$" + QString(SYM_FORALL) + "$", "∀");
    code = code.replace("$" + QString(SYM_LOGICALNOT) + "$", "¬");
    code = code.replace("$" + QString(SYM_SUBSET) + "$", "⊂");
    code = code.replace("$" + QString(SYM_SUPSET) + "$", "⊃");
    code = code.replace("$" + QString(SYM_IN) + "$", "∈");
    code = code.replace("$" + QString(SYM_NOTIN) + "$", "∉");
    code = code.replace("$" + QString(SYM_CONTAINS) + "$", "∋");
    code = code.replace("$" + QString(SYM_LOGICALAND) + "$", "∧");
    code = code.replace("$" + QString(SYM_LOGICALOR) + "$", "∨");
    code = code.replace("$" + QString(SYM_RIGHTARROW) + "$", "→");
    code = code.replace("$" + QString(SYM_LEFTARROW) + "$", "←");
    code = code.replace("$" + QString(SYM_MAPSTO) + "$", "↦");
    code = code.replace("$" + QString(SYM_IMPLIES) + "$", "⇒");
    code = code.replace("$" + QString(SYM_RIGHTARROW_CAPS) + "$", "⇒");
    code = code.replace("$" + QString(SYM_LEFTRIGHTARROW) + "$", "↔");
    code = code.replace("$" + QString(SYM_IFF) + "$", "⇔");
    code = code.replace("$" + QString(SYM_LEFTRIGHTARROW_CAPS) + "$", "⇔");
    code = code.replace("$" + QString(SYM_TOP) + "$", "⊤");
    code = code.replace("$" + QString(SYM_BOTTOM) + "$", "⊥");
    code = code.replace("$" + QString(SYM_EMPTYSET) + "$", "∅");
    code = code.replace("$" + QString(SYM_NOTHING) + "$", "∅");
    code = code.replace("$" + QString(SYM_VERTICALBAR) + "$", "∣");
    code = code.replace("$" + QString(SYM_OPENBRACE) + "$", "{");
    code = code.replace("$" + QString(SYM_UPARROW) + "$", "↑");
    code = code.replace("$" + QString(SYM_DOWNARROW) + "$", "↓");
    code = code.replace("$" + QString(SYM_DOUBLEVERTICALBAR) + "$", "‖");
    code = code.replace("$" + QString(SYM_CLOSEBRACE) + "$", "}");
    code = code.replace("$" + QString(SYM_UPARROW_CAPS) + "$", "↑");
    code = code.replace("$" + QString(SYM_DOWNARROW_CAPS) + "$", "↓");
    code = code.replace("$" + QString(SYM_SLASH) + "$", "/");
    code = code.replace("$" + QString(SYM_LEFTANGLEBRACKET) + "$", "‹");
    code = code.replace("$" + QString(SYM_LEFTCEIL) + "$", "⌈");
    code = code.replace("$" + QString(SYM_LEFTFLOOR) + "$", "⌊");
    code = code.replace("$" + QString(SYM_BACKSLASH) + "$", "∖");
    code = code.replace("$" + QString(SYM_RIGHTANGLEBRACKET) + "$", "›");
    code = code.replace("$" + QString(SYM_RIGHTCEIL) + "$", "⌉");
    code = code.replace("$" + QString(SYM_RIGHTFLOOR) + "$", "⌋");
    code = code.replace("$" + QString(SYM_A) + "$", "Α");
    code = code.replace("$" + QString(SYM_ALPHA) + "$", "α");
    code = code.replace("$" + QString(SYM_B) + "$", "Β");
    code = code.replace("$" + QString(SYM_BETA) + "$", "β");
    code = code.replace("$" + QString(SYM_GAMMA_CAPS) + "$", "Γ");
    code = code.replace("$" + QString(SYM_GAMMA) + "$", "γ");
    code = code.replace("$" + QString(SYM_DELTA_CAPS) + "$", "Δ");
    code = code.replace("$" + QString(SYM_DELTA) + "$", "δ");
    code = code.replace("$" + QString(SYM_E) + "$", "Ε");
    code = code.replace("$" + QString(SYM_EPSILON) + "$", "ε");
    code = code.replace("$" + QString(SYM_VAREPSILON) + "$", "ϵ");
    code = code.replace("$" + QString(SYM_Z) + "$", "Ζ");
    code = code.replace("$" + QString(SYM_ZETA) + "$", "ζ");
    code = code.replace("$" + QString(SYM_H) + "$", "Η");
    code = code.replace("$" + QString(SYM_ETA) + "$", "η");
    code = code.replace("$" + QString(SYM_THETA_CAPS) + "$", "Θ");
    code = code.replace("$" + QString(SYM_THETA) + "$", "θ");
    code = code.replace("$" + QString(SYM_VARTHETA) + "$", "ϑ");
    code = code.replace("$" + QString(SYM_I) + "$", "Ι");
    code = code.replace("$" + QString(SYM_IOTA) + "$", "ι");
    code = code.replace("$" + QString(SYM_K) + "$", "K");
    code = code.replace("$" + QString(SYM_KAPPA) + "$", "κ");
    code = code.replace("$" + QString(SYM_VARKAPPA) + "$", "ϰ");
    code = code.replace("$" + QString(SYM_LAMBDA_CAPS) + "$", "Λ");
    code = code.replace("$" + QString(SYM_LAMBDA) + "$", "λ");
    code = code.replace("$" + QString(SYM_M) + "$", "Μ");
    code = code.replace("$" + QString(SYM_MU) + "$", "μ");
    code = code.replace("$" + QString(SYM_N) + "$", "Ν");
    code = code.replace("$" + QString(SYM_NU) + "$", "ν");
    code = code.replace("$" + QString(SYM_XI_CAPS) + "$", "Ξ");
    code = code.replace("$" + QString(SYM_XI) + "$", "ξ");
    code = code.replace("$" + QString(SYM_O) + "$", "Ο");
    code = code.replace("$" + QString(SYM_OMICRON) + "$", "ο");
    code = code.replace("$" + QString(SYM_PI_CAPS) + "$", "Π");
    code = code.replace("$" + QString(SYM_PI) + "$", "π");
    code = code.replace("$" + QString(SYM_VARPI) + "$", "ϖ");
    code = code.replace("$" + QString(SYM_P) + "$", "P");
    code = code.replace("$" + QString(SYM_RHO) + "$", "ρ");
    code = code.replace("$" + QString(SYM_VARRHO) + "$", "ϱ");
    code = code.replace("$" + QString(SYM_SIGMA_CAPS) + "$", "Σ");
    code = code.replace("$" + QString(SYM_SIGMA) + "$", "σ");
    code = code.replace("$" + QString(SYM_VARSIGMA) + "$", "ς");
    code = code.replace("$" + QString(SYM_T) + "$", "Τ");
    code = code.replace("$" + QString(SYM_TAU) + "$", "τ");
    code = code.replace("$" + QString(SYM_UPSILON_CAPS) + "$", "Υ");
    code = code.replace("$" + QString(SYM_UPSILON) + "$", "υ");
    code = code.replace("$" + QString(SYM_PHI_CAPS) + "$", "Φ");
    code = code.replace("$" + QString(SYM_PHI) + "$", "φ");
    code = code.replace("$" + QString(SYM_VARPHI) + "$", "ϕ");
    code = code.replace("$" + QString(SYM_X) + "$", "Χ");
    code = code.replace("$" + QString(SYM_CHI) + "$", "χ");
    code = code.replace("$" + QString(SYM_PSI_CAPS) + "$", "Ψ");
    code = code.replace("$" + QString(SYM_PSI) + "$", "ψ");
    code = code.replace("$" + QString(SYM_OMEGA_CAPS) + "$", "Ω");
    code = code.replace("$" + QString(SYM_OMEGA) + "$", "ω");
    code = code.replace("$" + QString(SYM_PARTIAL) + "$", "∂");
    code = code.replace("$" + QString(SYM_DERIVATE) + "$", "∂");
    code = code.replace("$" + QString(SYM_ETH) + "$", "ð");
    code = code.replace("$" + QString(SYM_REDUCEDPLANCKCONSTANT) + "$", "ℏ");
    code = code.replace("$" + QString(SYM_IMATH) + "$", "ı");
    code = code.replace("$" + QString(SYM_JMATH) + "$", "ĵ");
    code = code.replace("$" + QString(SYM_ELL) + "$", "ℓ");
    code = code.replace("$" + QString(SYM_REALPART) + "$", "ℜ");
    code = code.replace("$" + QString(SYM_IMAGINARYPART) + "$", "ℑ");
    code = code.replace("$" + QString(SYM_WEIERSTRASSPOWERSET) + "$", "℘");
    code = code.replace("$" + QString(SYM_NABLA) + "$", "∇");
    code = code.replace("$" + QString(SYM_BOX) + "$", "□");
    code = code.replace("$" + QString(SYM_INFINITY) + "$", "∞");
    code = code.replace("$" + QString(SYM_ALEPH) + "$", "ℵ");
    code = code.replace("$" + QString(SYM_BETH) + "$", "ℶ");
    code = code.replace("$" + QString(SYM_GIMEL) + "$", "ℷ");
    //code = code.replace("}","</span>");
    code = code.replace("////", "<br/>");
    code = code.replace("\\\\", "<br/>");
    code = code.replace("\\#" , "#");
    code = code.replace("\\%" , "%");
    code = code.replace( "\\textup{\\euro}","€");
    code = code.replace("\\$" , "$");
    code = code.replace("\\textup{\\pounds}","£" );
    code = code.replace( "\\cent","¢" );
    code = code.replace( "\\yen","¥" );
    code = code.remove("\n");
    return code;
}
