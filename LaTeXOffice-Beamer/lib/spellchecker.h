/*
Copyright (c) 2011, Volker Götz
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <QObject>
class Hunspell;
/**
 * The SpellChecker class represents the functions that LaTeX Office provide to check the spelling.
 *
 * @author Iván Martínez Mateu
 */
class SpellChecker
{
public:
    /*Public functions*/
    /*************************************************************************************************/
    /**
      @brief This is the constructor function that reads the dictionary files to start checking the document.
      @param dictionaryPath a dictionary file path to supply the correct words.
      @param userDictionary a dictionary file path made by the user to supply more words.
      @returns This is a void function.
      */
    SpellChecker(const QString &dictionaryPath, const QString &userDictionary);
    /*************************************************************************************************/
    /**
      @brief Destroy a SpellChecker instance.
      @returns This is a void function.
      */
    ~SpellChecker();
    /*************************************************************************************************/
    /**
      @brief This is a public function that checks if the word is spelled correctly.
      @param word word to be checked.
      @returns This function returns true if the word is spelled correctly. Otherwise, returns false.
      */
    bool spell(const QString &word);
    /*************************************************************************************************/
    /**
      @brief This is a public function that returns the list of suggestions to correct a mispelled word.
      @param word word to be checked.
      @returns This function returns a string list of suggestions.
      */
    QStringList suggest(const QString &word);
    /*************************************************************************************************/
    /**
      @brief This is a public function that ignores the spell checking of a word.
      @param word word to be checked.
      @returns This is a void function.
      */
    void ignoreWord(const QString &word);
    /*************************************************************************************************/
    /**
      @brief This is a public function that adds the word to be checked to the user dictionary.
      @param word word to be checked.
      @returns This is a void function.
      */
    void addToUserWordlist(const QString &word);
    /*End of public functions*/

private:
    /*Private functions*/
    /*************************************************************************************************/
    /**
      @brief This is a private function that inserts the correct word to the document. Hunspell encapsulates this, so the program does only supply the correct word.
      @param word correct word.
      @returns This is a void function.
      */
    void insertWord(const QString &word);
    /*End of private functions*/
    /*Private variables*/
    Hunspell *_hunspell;
    QString _userDictionary;
    QString _encoding;
    QTextCodec *_codec;
    /*End of private variables*/
};

#endif // SPELLCHECKER_H
