#include "timemachinethread.h"
#include "timemachine.h"
void TimeMachineThread::setData(QString machineFilePath, TeXFile *documentFile,
                                int interval)
{
    this->machineFilePath = machineFilePath;
    this->documentFile = documentFile;
    this->interval = interval;
}

void TimeMachineThread::setRunState(bool state)
{
    this->runState = state;
}
/*************************************************************************************************/
/**
  @brief The thread will be in a constant loop, so the presence of a chronometer is necessary due to the need of having more control on what's going on the loop. When the chronometer reaches a maximum interval, then the loop is restarted and so do the chronometer.
  The only way to stop the thread is setting runState to false and then, using the function quit() inherited from QThread class.
  Inside the loop, the Time Machine instance is called to create the backup and the thread waits for its ending. Then, a signal is emited when the thread finishes the backup generation.
  @returns This is a void function.
  */
void TimeMachineThread::run()
{
    if (this->isRunning())
        if (runState) {
            chrono = new QTime();
            chrono->start();
            TimeMachine::makeBackup(QDateTime().currentDateTime(), documentFile->getFileContent());
            TimeMachine::saveTimeMachineFile(machineFilePath);
            while (chrono->elapsed() > -1) {
                if (chrono->elapsed() > interval) {
                    TimeMachine::makeBackup(QDateTime().currentDateTime(), documentFile->getFileContent());
                    TimeMachine::saveTimeMachineFile(machineFilePath);
                    chrono->restart();
                }
            }

        }
}

