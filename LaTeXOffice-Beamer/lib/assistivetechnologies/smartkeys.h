#ifndef SMARTKEYS_H
#define SMARTKEYS_H

#include <QString>
#include <QList>
#include <QFile>
#include <QDataStream>
#include <QStringList>
/**
 * @brief This is the SmartKeys Definition Structure which will store all information regarding to a SmartKeys word.
 */
struct definitions
{
    int id;//!<  Unique identificator for a word.
    QString replaceString;//!<  Word to replace.
    QString forString;//!<  New word.
};
/**
 *
 * @namespace SmartKeys
 * The SmartKeys namespace contains some useful functions to control the SmartKeys Assistance Technology.
 * @author Iván Martínez Mateu
 */
namespace SmartKeys
{

    extern QList<definitions> definitionsList;//!<  This is a no limit definitions list.
    /*************************************************************************************************/
    /**
      @brief This function load a previous definitions file and stores its data to the definitions list.
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
    /*************************************************************************************************/
    /**
      @brief This function creates a new definition inside the definitions list.
      @param id unique identificator for the new definition.
      @param replaceString word to replace.
      @param forString new word.
      @returns This is a void function.
      */
    void createDefinition(int id, QString replaceString, QString forString);
    /*************************************************************************************************/
    /**
      @brief This function deletes a definition inside the definitions list.
      @param id unique identificator for the definition to delete.
      @returns This is a void function.
      */
    void deleteDefinition(int id);
    /*************************************************************************************************/
    /**
      @brief This function deletes all definitions stored in the list.
      @returns This is a void function.
      */
    void clearDefinitions();
    /*************************************************************************************************/
    /**
      @brief This function gets the current definitions list.
      @returns Returns the definitions list.
      */
    QList<definitions> getDefinitionsList();
    /*************************************************************************************************/
    /**
      @brief This function gets the current definitions list and converts it to a string list, so it can be used by another class.
      @returns Returns a string list containing the definitions list.
      */
    QList<QStringList> getDefinitionsStringList();

}

#endif // SMARTKEYS_H
