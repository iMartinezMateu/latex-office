#include "timemachine.h"

QList<backup> TimeMachine::backupsList;
QTimer TimeMachine::chrono;

QDataStream &operator<<( QDataStream &stream, const backup &data )
{
  stream << data.id << data.date << data.fileContent;
  return stream;
}

QDataStream &operator>>( QDataStream &stream, backup &data )
{
  stream >> data.id;
  stream >> data.date;
  stream >> data.fileContent;
  return stream;
}

void TimeMachine::loadTimeMachineFile(QString filePath)
{
    QFile file( filePath);
     if( !file.open( QIODevice::ReadOnly ) )
       return;

     QDataStream stream( &file );
     backupsList.clear();
     stream >> backupsList;
     file.close();
}

void TimeMachine::saveTimeMachineFile(QString filePath)
{
    QFile file(filePath);
    if (file.exists())
        file.remove();
    if (!file.open(QIODevice::WriteOnly))
        return;
    QDataStream stream( &file );
    stream << backupsList;
    file.close();
}

void TimeMachine::makeBackup(QTime date,QStringList fileContent)
{
    backup newBackup;
    for (int index=0; index<backupsList.count();index++)
    {
        if (backupsList.at(index).id == NULL)
        {
           newBackup.id = index;
           newBackup.date = date;
           newBackup.fileContent = fileContent;
           if (backupsList.isEmpty())
                backupsList.append(newBackup);
           else
           {
               backupsList.insert(index,newBackup);
               if (backupsList.count() > MAX_BACKUPS)
               {
                   backupsList.removeLast();
               }
           }
           break;
        }
    }

}

void TimeMachine::deleteBackup(int id)
{
    for (int index=0; index<backupsList.count();index++)
    {
        if (backupsList.at(index).id == id)
        {
            backupsList.removeAt(index);
        }
    }
}

void TimeMachine::newTimeMachine(QString machineFilePath, TeXFile* documentFile, int interval)
{
    chrono.start();
    while (chrono.interval()<interval)
    {
        if (chrono.interval()>interval)
        {
            loadTimeMachineFile(machineFilePath);
            makeBackup(QTime().currentTime(),documentFile->getFileContent());
            saveTimeMachineFile(machineFilePath);
            chrono.setInterval(0);
        }
    }

}

void TimeMachine::stopTimeMachine(QString machineFilePath)
{
   chrono.stop();
   saveTimeMachineFile(machineFilePath);
   chrono.setInterval(0);
}
