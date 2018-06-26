#ifndef TIMEMACHINETHREAD_H
#define TIMEMACHINETHREAD_H


#include <QThread>
#include <QTime>
#include "lib/latex/file.h"
/**
 * The TimeMachineThread class represents the Time Machine Assistance Technology core. The program will be able to make document backups in background using the multithreading paradigm.
 *
 * @author Iván Martínez Mateu
 */
class TimeMachineThread : public QThread
{
public:
    /*Public functions*/
    /*************************************************************************************************/
    /**
      @brief This function loads some data that the Time Machine thread needs to operate correctly.
      @param machineFilePath path to the Time Machine file where it is going to store the backups.
      @param documentFile TeX file reference, whose content is going to be captured to be inserted in a backup.
      @param interval interval creation of Time Machine backups.
      @returns This is a void function.
      */
        void setData(QString machineFilePath, TeXFile *documentFile, int interval);
        /*************************************************************************************************/
        /**
          @brief This function contains the commands that are going to be executed by the thread when it's running.
          @returns This is a void function.
          */
        void run();
        /*************************************************************************************************/
        /**
          @brief This function defines the thread state.
          @param state the boolean value defines wether the thread should be running (true) or it must wait to other event to start again (false).
          @returns This is a void function.
          */
        void setRunState(bool state);
    /*End of declaration of public functions*/
private:
    /*Private variables*/
        QString machineFilePath;
        TeXFile *documentFile;
        int interval;
        QTime *chrono;
        bool runState;
    /*End of declaration of private variables*/
};

#endif
