#include "smartkeys.h"
QList<definitions> SmartKeys::definitionsList;

/*************************************************************************************************/
/**
  @brief This function overrides the standard transference operator to catch the data stored in the structure and store it to a data stream.
  @param stream file data stream to use.
  @param &data reference to the structure.
  @returns Returns a proper stream to be used to store the structure list on a file.
  */
QDataStream &operator<<(QDataStream &stream, const definitions &data)
{
    stream << data.id << data.replaceString << data.forString;
    return stream;
}
/*************************************************************************************************/
/**
  @brief This function overrides the standard transference operator to recover the data stored in a file and store it to the structure.
  @param stream file data stream to use.
  @param &data reference to the structure.
  @returns Returns a proper stream to be used to store the file data to the structure list.
  */
QDataStream &operator>>(QDataStream &stream, definitions &data)
{
    stream >> data.id;
    stream >> data.replaceString;
    stream >> data.forString;
    return stream;
}
/*************************************************************************************************/
/**
  @brief Open the file and read the stored data to populate the definitions list. If the file does not exist, the function quits.
  */
void SmartKeys::loadDefinitionsFile(QString filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QDataStream stream(&file);
    definitionsList.clear();
    stream >> definitionsList;
    file.close();
}
/*************************************************************************************************/
/**
  @brief Open the file and save the definitions list content to a file. If the program does not have correct permissions to write the file, the function quits.
  */
void SmartKeys::saveDefinitionsFile(QString filePath)
{
    QFile file(filePath);
    if (file.exists()) {
        file.remove();
    }
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }
    QDataStream stream(&file);
    stream << definitionsList;
    file.close();
}

void SmartKeys::createDefinition(int id, QString replaceString, QString forString)
{
    definitions newDefinition;
    newDefinition.id = id;
    newDefinition.replaceString = replaceString;
    newDefinition.forString = forString;
    definitionsList.append(newDefinition);
}

void  SmartKeys::deleteDefinition(int id)
{
    int position = 0;
    foreach (definitions item, definitionsList) {
        if (item.id == id) {
            definitionsList.removeAt(position);
        }
        position++;
    }
}
void  SmartKeys::clearDefinitions()
{
    definitionsList.clear();
}
QList<definitions>  SmartKeys::getDefinitionsList()
{
    return definitionsList;
}
QList<QStringList> SmartKeys::getDefinitionsStringList()
{
    QStringList definitionItem;
    QList<QStringList> definitionStringList;
    foreach (definitions item, definitionsList) {
        definitionItem.clear();
        definitionItem.append(QString::number(item.id));
        definitionItem.append(item.replaceString);
        definitionItem.append(item.forString);
        definitionStringList.append(definitionItem);
    }
    return definitionStringList;
}
