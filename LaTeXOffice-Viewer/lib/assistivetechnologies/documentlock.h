

#ifndef DOCUMENTLOCK_H
#define DOCUMENTLOCK_H


#include "lib/tiny-aes/aes.h"

#include <QDebug>
#include <QString>
#include <QDataStream>
#include <QCryptographicHash>
#include <Qt>

#define MAX_ENCRYPTION_LENGTH 2048
/**
 *
 * @namespace DocumentLock
 * The DocumentLock namespace contains some useful functions to control the Document Lock Assistance Technology.
 * @author Iván Martínez Mateu
 */
namespace DocumentLock
{
/*************************************************************************************************/
/**
  @brief This function calculates the lenght that the ciphered key will have.
  @param currSize file content size.
  @param alignment integer that the file content size must be aligned for calculating the ciphering keys properly.
  @returns This is a void function.
  */
    inline int getAlignedSize(int currSize, int alignment) ;
    /*************************************************************************************************/
    /**
      @brief This function ciphers the content of the document.
      @param rawText TeX File content to be ciphered.
      @param key password key to be used on the ciphering process.
      @returns Returns the file content ciphered.
      */
    QString lockFile( QString rawText,  QString key) ;
    /*************************************************************************************************/
    /**
      @brief This function ciphers the content of the document.
      @param hexEncodedText TeX File content that is ciphered.
      @param key password key used on the ciphering process.
      @returns Returns the plain file content.
      */
    QString unlockFile( QString hexEncodedText,  QString key) ;
}
#endif
