#ifndef TIMEMACHINE_H
#define TIMEMACHINE_H

#include <QString>
#include <QList>
#include <QFile>
#include <QDataStream>
#include <QStringList>
#include <QTimer>
#include "lib/latex/file.h"
#include "lib/assistivetechnologies/timemachinethread.h"
#include <JlCompress.h>
#define MAX_BACKUPS 672 //!< It's a constant that declares the standard maximum backups stored on the machine. Older backups will be erased.
/**
 *
 * @brief This is the Time Machine Structure which will store all information regarding to a backup made on a document.
 */
struct backup
{
    int id;//!<Unique identificator for a backup.
    QDateTime date;//!<Backup date.
    QStringList fileContent;//!<TeX file content stored on the backup.
};
/**
 *
 * @namespace TimeMachine
 * The TimeMachine namespace contains some useful functions to control the Time Machine Assistance Technology.
 * @author Iván Martínez Mateu
 */
namespace TimeMachine
{
    extern TimeMachineThread *timeMachineThread;//!<  This is a reference to the exclusive Time Machine thread.
    extern QList<backup> backupsList;//!<  This is a no limit backup list.
    /*************************************************************************************************/
    /**
      @brief This function load a previous Time Machine file and stores its backups entries to the backups list.
      @param filePath Time Machine file path.
      @returns This is a void function.
      */
    void loadTimeMachineFile(QString filePath);
    /*************************************************************************************************/
    /**
      @brief This function save the backups list to a file.
      @param filePath Time Machine file path.
      @returns This is a void function.
      */
    void saveTimeMachineFile(QString filePath);
    /*************************************************************************************************/
    /**
      @brief This function creates a backup and store its metadata to the backups list.
      @param date backup date.
      @param fileContent file content that was stored in the backup .
      @returns This is a void function.
      */
    void makeBackup(QDateTime date, QStringList fileContent);
    /*************************************************************************************************/
    /**
      @brief This function deletes a backup inside the backups list.
      @param id unique identificator for the backup to delete.
      @returns This is a void function.
      */
    void deleteBackup(int id);
    /*************************************************************************************************/
    /**
      @brief This function starts the Time Machine thread.
      @param filePath file path to recover last backups made to the file.
      @param documentFile TeX file reference, so Time Machine can catch its content to create the backup.
      @param interval interval creation of Time Machine backups.
      @returns This is a void function.
      */
    void newTimeMachine(QString machineFilePath, TeXFile* documentFile, int interval);
    /*************************************************************************************************/
    /**
      @brief This function stops the Time Machine thread.
      @param filePath file path to save the backups list.
      @returns This is a void function.
      */
    void stopTimeMachine(QString machineFilePath);
    /*************************************************************************************************/
    /**
      @brief This function gets the current backups list.
      @returns Returns the backup list.
      */
    QList<backup> getBackupsList();
}

#endif // TIMEMACHINE_H
