#ifndef CONSTANTS
#define CONSTANTS

/**
 * This file defines some constants used on some parts of the entire program.
 *  APP_NAME It's the current name of the application. This constant is widely used on the message boxes titles.
 *  BACKUP_TIME Time interval for Time Machine. When it reaches this interval, it makes a backup of the document (in msec. , default 900000 msec)
 *  THREAD_COMPILE_INTERVAL Time interval for Compiler Thread. When it reaches this interval, it compiles the document (in msec. , default 2500 msec)
 * @author Iván Martínez Mateu
 */
#define APP_NAME "LaTeX Office Writer"
#define BACKUP_TIME 900000
#define THREAD_COMPILE_INTERVAL 2500
#endif // CONSTANTS

