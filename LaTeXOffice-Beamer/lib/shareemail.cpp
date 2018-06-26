#include "shareemail.h"
#include <QDebug>
QList<emailAddress> ShareEmail::definitionsList;
/*************************************************************************************************/
/**
  @brief This function overrides the standard transference operator to catch the data stored in the structure and store it to a data stream.
  @param stream file data stream to use.
  @param &data reference to the structure.
  @returns Returns a proper stream to be used to store the structure list on a file.
  */
QDataStream &operator<<(QDataStream &stream, const emailAddress &data)
{
    stream << data.serverAddress << data.serverPort << data.connectionType << data.user <<
           data.password;
    return stream;
}
/*************************************************************************************************/
/**
  @brief This function overrides the standard transference operator to recover the data stored in a file and store it to the structure.
  @param stream file data stream to use.
  @param &data reference to the structure.
  @returns Returns a proper stream to be used to store the file data to the structure list.
  */
QDataStream &operator>>(QDataStream &stream,  emailAddress &data)
{
    stream >> data.serverAddress;
    stream >> data.serverPort;
    stream >> data.connectionType;
    stream >> data.user;
    stream >> data.password;
    return stream;
}

void ShareEmail::loadDefinitionsFile(QString filePath)
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

void ShareEmail::saveDefinitionsFile(QString filePath)
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

void ShareEmail::createDefinition(QString serverAddress, int serverPort,
                                  int connectionType, QString user, QString password)
{
    emailAddress newDefinition;
    newDefinition.serverAddress = serverAddress;
    newDefinition.serverPort = serverPort;
    newDefinition.connectionType = connectionType;
    newDefinition.user = user;
    newDefinition.password = password;
    definitionsList.clear();
    definitionsList.append(newDefinition);
}



QStringList ShareEmail::getEmailAddressStringList()
{
    QStringList emailAddressStringList;

    emailAddressStringList.append(definitionsList.at(0).serverAddress);
    emailAddressStringList.append(QString::number(definitionsList.at(0).serverPort));
    emailAddressStringList.append(QString::number(definitionsList.at(0).connectionType));
    emailAddressStringList.append(definitionsList.at(0).user);
    emailAddressStringList.append(definitionsList.at(0).password);

    return emailAddressStringList;

}
