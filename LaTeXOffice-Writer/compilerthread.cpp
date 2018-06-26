#include "compilerthread.h"
#include <QDebug>
void CompilerThread::setData(TeXFile *file, QString compilerPath, DocumentViewer *viewer)
{
    this->file = file;
    this->compilerPath = compilerPath;
    this->viewer = viewer;
}
void CompilerThread::setRunState(bool state)
{
    this->runState = state;
}
/*************************************************************************************************/
/**
  @brief The thread will be in a constant loop, so the presence of a chronometer is necessary due to the need of having more control on what's going on the loop. When the chronometer reaches a maximum interval, then the loop is restarted and so do the chronometer.
  The only way to stop the thread is setting runState to false and then, using the function quit() inherited from QThread class.
  Inside the loop, the compiler binary is called and the thread waits for its ending. Then, a signal is emited when the thread finishes the document compilation.
  @returns This is a void function.
  */
void CompilerThread::run()
{
    QProcess process ;
    QFile tmpFile(file->getDirectory() + "/" + file->getFileName().append(".tmp"));
    chrono->start();
    while (chrono->elapsed() > -1) {
        if (chrono->elapsed() > THREAD_COMPILE_INTERVAL) {
            if (tmpFile.exists()) {
                if (runState) {
                    QStringList commandArguments ;
                    file->deleteEmptyParagraphs();
                    commandArguments.clear();
                    commandArguments.append("-synctex=-1");
                    commandArguments.append("-interaction=nonstopmode");
                    commandArguments.append("\"" + file->getDirectory() + "/" +
                                            file->getFileName().append(".tmp") + "\"");
                    runState=false;
                    process.start(compilerPath, commandArguments, QIODevice::ReadWrite);
                    process.waitForFinished();
                    process.start(compilerPath, commandArguments, QIODevice::ReadWrite);
                    process.waitForFinished();
                    viewer->refresh(viewer->getCurrentPage());
                    runState=true;
                    file->saveFile();
                   }
                chrono->restart();
                qDebug() << "Loop restarted!";
            }
        }

    }
}
