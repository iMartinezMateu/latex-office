#ifndef CAJA_H
#define CAJA_H

#include <QWidget>
#include <QTextEdit>
namespace Ui {

class Caja;
}
/**
 * The Caja class represents the functionality and implementation of this widget. It is used to communicate with the user, so the program can really know what the author wants to be typed on the document.
 *
 * @author Iván Martínez Mateu
 */
class Caja : public QWidget
{
    Q_OBJECT

public:
    /*Public functions*/
    /*************************************************************************************************/
    /**
      @brief This function is called when Caja is placed on the UI for the first time. It connects the combobox interaction to the slot changeSize().
      @param parent The UI widget that becomes the parent of <<Caja>> (it will be the Document Viewer widget, always).
      @returns This is a void function.
      */
    explicit Caja(QWidget *parent = 0);
    /*************************************************************************************************/
    /**
      @brief This function detects when it is going to be necessary to apply the widget translation.
      @returns This is a void function.
      */
    void changeEvent(QEvent *event);

    /*************************************************************************************************/
    /**
      @brief This function destroys Caja.
      @returns This is a void function.
      */
    ~Caja();
    /*************************************************************************************************/
    /**
      @brief This function returns a reference of the UI QTextEdit component.
      @returns Returns a QTextEdit which was instantiated when the program was executed.
      */
    QTextEdit *getTextEdit();
    /*************************************************************************************************/
    /**
      @brief This function reduces the text scale by putting the command \tiny on the document (7.33 pt).
      @returns This is a void function.
      */
    void setTextTiny();
    /*************************************************************************************************/
    /**
      @brief This function reduces the text scale by putting the command \small on the document (10 pt).
      @returns This is a void function.
      */
    void setTextSmall();
    /*************************************************************************************************/
    /**
      @brief This function changes the text scale by putting the command \normal on the document (12.5 pt).
      @returns This is a void function.
      */
    void setTextNormal();
    /*************************************************************************************************/
    /**
      @brief This function increases the text scale by putting the command \large on the document(15 pt).
      @returns This is a void function.
      */
    void setTextLarge();
    /*************************************************************************************************/
    /**
      @brief This function increases the text scale by putting the command \huge on the document(24 pt).
      @returns This is a void function.
      */
    void setTextHuge();
    /*End of declaration of public functions*/

public slots:
    void changeSize();

signals:
    /*************************************************************************************************/
    /**
      @brief This function maps a UI combobox slot so the user can change the text size by choosing an option in the combobox.
      @returns This is a void function.
      */
    void sizeChanged();
    /*************************************************************************************************/
    /**
      @brief This function emits the Bold Style Signal when the tool button is clicked, so the program can apply the bold style on the document viewer.
      @returns This is a void function.
      */
    void boldStyleChanged();
    /*************************************************************************************************/
    /**
      @brief This function emits the Italic Style Signal when the tool button is clicked , so the program can apply the italic style on the document viewer.
      @returns This is a void function.
      */
    void italicStyleChanged();
    /*************************************************************************************************/
    /**
      @brief This function emits the Underline Style Signal when the tool button is clicked , so the program can apply the underline style on the document viewer.
      @returns This is a void function.
      */
    void underlineStyleChanged();
    /*************************************************************************************************/
    /**
      @brief This function emits the Strikethrough Style Signal when the tool button is clicked , so the program can apply the strikethrough style on the document viewer.
      @returns This is a void function.
      */
    void strikethroughStyleChanged();
    /*************************************************************************************************/
    /**
      @brief This function emits the Small caps Style Signal when the tool button is clicked , so the program can apply the small caps style on the document viewer.
      @returns This is a void function.
      */
    void smallCapsStyleChanged();
    /*************************************************************************************************/
    /**
      @brief This function emits the Emphatize Style Signal when the tool button is clicked , so the program can apply the emphatize style on the document viewer.
      @returns This is a void function.
      */
    void emphatizeStyleChanged();
    /*************************************************************************************************/
    /**
      @brief This function emits the Hyperlink Signal when the tool button is clicked , so the program can interact properly when a hyperlink is being added on the document viewer.
      @returns This is a void function.
      */
    void hyperlinkStyleChanged();
    /*************************************************************************************************/
    /**
      @brief This function emits the Footnote Signal when the tool button is clicked , so the program can interact properly when a footnote is being added on the document viewer.
      @returns This is a void function.
      */
    void footnoteStyleChanged();
    /*************************************************************************************************/
    /**
      \deprecated This function is deprecated.
      @brief This function emits the Left Align Signal when the tool button is clicked , so the program can interact properly when the user wants text to be left aligned.
      @returns This is a void function.
      */
    void leftAlignStyleChanged();
    /*************************************************************************************************/
    /**
      @brief This function emits the Center Align Signal when the tool button is clicked , so the program can interact properly when the user wants text to be center aligned.
      @returns This is a void function.
      */
    void centerAlignStyleChanged();
    /*************************************************************************************************/
    /**
      @brief This function emits the Right Align Signal when the tool button is clicked , so the program can interact properly when the user wants text to be right aligned.
      @returns This is a void function.
      */
    void rightAlignStyleChanged();
    /*************************************************************************************************/
    /**
      @brief This function emits the Justify Signal when the tool button is clicked , so the program can interact properly when the user wants text to be justified .
      @returns This is a void function.
      */
    void justifyStyleChanged();
    /*************************************************************************************************/
    /**
      @brief This function emits the Itemize Signal when the tool button is clicked , so the program can interact properly when the user wants to insert a bulleted list on the document viewer .
      @returns This is a void function.
      */
    void bulletListAdded();
    /*************************************************************************************************/
    /**
      @brief This function emits the Enumerate Signal when the tool button is clicked , so the program can interact properly when the user wants to insert a numbered list on the document viewer .
      @returns This is a void function.
      */
    void numberedListAdded();
    /*************************************************************************************************/
    /**
      @brief This function emits the Symbol Signal when the tool button is clicked , so the program can interact properly when the user wants to insert a symbol on the document viewer .
      @returns This is a void function.
      */
    void symbolInserted();
    /*************************************************************************************************/
    /**
      @brief This function emits the Cite Signal when the tool button is clicked , so the program can interact properly when the user wants to insert a cite on the document viewer .
      @returns This is a void function.
      */
    void citeInserted();
    /*************************************************************************************************/
    /**
      @brief This function emits the Reference Signal when the tool button is clicked , so the program can interact properly when the user wants to insert a reference on the document viewer .
      @returns This is a void function.
      */
    void referenceInserted();
    /*************************************************************************************************/
    /**
      @brief This function is fired when the users changes the text stored in the QTextEdit component.
    This is necessary so the program can calculate the corresponding ratios so it can know how many words are in bold, in italics, etc. and with that calculated, the program
    can give advices to the document author.
      @returns This is a void function.
      */
    void cajaTextChanged();


private slots:
    void on_toolButtonBold_clicked();
    void on_toolButtonItalic_clicked();
    void on_toolButtonUnderline_clicked();
    void on_toolButtonStrikethrough_clicked();
    void on_toolButtonSmallCaps_clicked();
    void on_toolButtonEmphatize_clicked();
    void on_toolButtonHyperlink_clicked();
    void on_toolButton_Footnote_clicked();
    void on_toolButtonLeftAlign_clicked();
    void on_toolButtonCenterAlign_clicked();
    void on_toolButtonRightAlign_clicked();
    void on_toolButtonJustify_clicked();
    void on_toolButtonItemize_clicked();
    void on_toolButtonEnumerate_clicked();
    void on_toolButtonSymbol_clicked();
    void on_textEdit_textChanged();
    void on_toolButtonCite_clicked();
    void on_toolButtonReference_clicked();

private:
    /*Private functions*/
    /*************************************************************************************************/
    /**
      @brief This function retranslates Caja when the default language is changed.
      @returns This is a void function.
      */
    void retranslate();
    /*End of private functions*/
    /*Private variables*/
    Ui::Caja *ui; //!<This variable encapsulates all of the UI operations regarding to Caja.
    /*End of declaration of private variables*/
};

#endif // CAJA_H
