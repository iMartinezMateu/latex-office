#ifndef SHAREEMAIL_H
#define SHAREEMAIL_H

#include <QString>
#include <QList>
#include <QFile>
#include <QDataStream>
#include <QStringList>
/**
 *
 * @brief This is the E-mail Structure which will store all information regarding to the e-mail account.
 */
struct emailAddress {
    QString serverAddress; //!<  SMTP server address for sending e-mails.
    int serverPort; //!<  SMTP server port.
    int connectionType; //!<  Use security protocol(0->TCP, 1->SSL, 2->TLS)
    QString user;//!<  SMTP user.
    QString password; //!<  SMTP password.
};
/**
 *
 * @namespace ShareEmail
 * The ShareEmail namespace contains some useful functions to control the e-mail account data access.
 * @author Iván Martínez Mateu
 */
namespace ShareEmail
{
    extern QList<emailAddress> definitionsList; //!< This is a no limit definitions list for storing e-mail accounts.
    /**
      @brief This function load a previous definitions file and stores its e-mail accounts data to the definitions list.
      @param filePath definitions file path.
      @returns This is a void function.
      */
    void loadDefinitionsFile(QString filePath);
    /*************************************************************************************************/
    /**
      @brief This function save the definitions list to a file.
      @param filePath definitions file path.
      @returns This is a void function.
      */
    void saveDefinitionsFile(QString filePath);
    /**
    @brief This function creates a new e-mail account definition inside the definitions list.
    @param serverAddress SMTP server address for sending e-mails.
    @param serverPort SMTP server port.
    @param connectionType use security protocol.
    @param user SMTP user.
    @param password SMTP password.
    @returns This is a void function.
    */
    void createDefinition(QString serverAddress,int serverPort, int connectionType, QString user, QString password);
    /*************************************************************************************************/
    /**
      @brief This function deletes all definitions stored in the list.
      @returns This is a void function.
      */
    void clearDefinitions();
    /*************************************************************************************************/
    /**
      @brief This function gets the current definitions list and converts it to a string list, so it can be used by another class.
      @returns Returns a string list containing the definitions list.
      */
    QStringList getEmailAddressStringList();

}
#endif // SHAREEMAIL_H
