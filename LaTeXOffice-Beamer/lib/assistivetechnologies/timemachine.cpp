#include "timemachine.h"

TimeMachineThread  *TimeMachine::timeMachineThread;
QList<backup> TimeMachine::backupsList;

/*************************************************************************************************/
/**
  @brief This function overrides the standard transference operator to catch the data stored in the structure and store it to a data stream.
  @param stream file data stream to use.
  @param &data reference to the structure.
  @returns Returns a proper stream to be used to store the structure list on a file.
  */
QDataStream &operator<<(QDataStream &stream, const backup &data)
{
    stream << data.id << data.date << data.fileContent;
    return stream;
}
/*************************************************************************************************/
/**
  @brief This function overrides the standard transference operator to recover the data stored in a file and store it to the structure.
  @param stream file data stream to use.
  @param &data reference to the structure.
  @returns Returns a proper stream to be used to store the file data to the structure list.
  */
QDataStream &operator>>(QDataStream &stream, backup &data)
{
    stream >> data.id;
    stream >> data.date;
    stream >> data.fileContent;
    return stream;
}
/*************************************************************************************************/
/**
  @brief Open the file and read the stored data to populate the backups list. If the file does not exist, the function quits. Take note that the Time Machine is
  compressed using a DEFLATE algorithm, so before load it, the file needs to be uncompressed. In order to avoid conflict when extracting files with the same name of the
  Time Machine compressed file, the Time Machine File is renamed and uses a temporal extension.

}
  */
void TimeMachine::loadTimeMachineFile(QString filePath)
{
    JlCompress::extractFile(filePath, filePath.replace(".tmf", ".tmp"));
    QFile().remove(filePath.replace(".tmp", ".tmf"));
    QFile().rename(filePath.replace(".tmf", ".tmp"), filePath.replace(".tmp", ".tmf"));
    QFile file(filePath.replace(".tmp", ".tmf"));
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QDataStream stream(&file);
    backupsList.clear();
    stream >> backupsList;
    file.close();
}

QList<backup> TimeMachine::getBackupsList()
{
    return backupsList;
}
/*************************************************************************************************/
/**
  @brief Open the file and save the backups list content to a file. If the program does not have correct permissions to write the file, the function quits. Before saving it, a DEFLATE
  compression algorithm is applied to the file.
  */
void TimeMachine::saveTimeMachineFile(QString filePath)
{
    QFile file(filePath.replace(".tmf", ".tmp"));


    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }
    QDataStream stream(&file);
    stream << backupsList;
    file.close();
    JlCompress::compressFile(filePath.replace(".tmp", ".tmf"), file.fileName());
    if (file.exists()) {
        file.remove();
    }

}

void TimeMachine::makeBackup(QDateTime date, QStringList fileContent)
{
    backup newBackup;
    newBackup.id = backupsList.count();
    newBackup.date = date;
    newBackup.fileContent = fileContent;
    backupsList.append(newBackup);
    QFile file("settings/timemachineinterval.los");

    if (!file.exists()) {
        if (backupsList.count() > MAX_BACKUPS) {
            backupsList.removeFirst();
        }
    } else {
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
        }
        file.close();
        if (backupsList.count() > line.toInt()) {
            backupsList.removeFirst();
        }
    }
}

void TimeMachine::deleteBackup(int id)
{
    for (int index = 0; index < backupsList.count(); index++) {
        if (backupsList.at(index).id == id) {
            backupsList.removeAt(index);
        }
    }
}

void TimeMachine::newTimeMachine(QString machineFilePath, TeXFile *documentFile,
                                 int interval)
{
    timeMachineThread = new TimeMachineThread;
    timeMachineThread->setRunState(true);
    timeMachineThread->setData(machineFilePath, documentFile, interval);
    loadTimeMachineFile(machineFilePath);
    timeMachineThread->start();
}

void TimeMachine::stopTimeMachine(QString machineFilePath)
{
    timeMachineThread->setRunState(false);
    timeMachineThread->terminate();
    saveTimeMachineFile(machineFilePath);
}
