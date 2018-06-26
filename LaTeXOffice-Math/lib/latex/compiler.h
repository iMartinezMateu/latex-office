#include <QString>
#include <QDebug>
#include <QDirIterator>
#ifndef COMPILER
/**
 *
 * @namespace TeXCompiler
 * The TeXCompiler namespace contains some useful functions to control the paths were binary compilers are.
 * @author Iván Martínez Mateu
 */
namespace TeXCompiler{
/*************************************************************************************************/
/**
  @brief This is the function that will search the BiBTeX binary compiler.
  @returns If the function found the BiBTeX binary compiler stored in the machine, then it returns the corresponding path.
  */
QString searchBiBTeXBinary();
/*************************************************************************************************/
/**
  @brief This is the function that will search the HTML binary converter.
  @returns If the function found the HTML binary converter stored in the machine, then it returns the corresponding path.
  */
QString searchHTMLConverterBinary();
/*************************************************************************************************/
/**
  @brief This is the function that will search the TXT binary converter.
  @returns If the function found the TXT binary converter stored in the machine, then it returns the corresponding path.
  */
QString searchTXTConverterBinary();
/*************************************************************************************************/
/**
  @brief This is the function that will search the RTF binary converter.
  @returns If the function found the RTF binary converter stored in the machine, then it returns the corresponding path.
  */
QString searchRTFConverterBinary();
/*************************************************************************************************/
/**
  @brief This is the function that will search the PDFLaTeX binary compiler.
  @returns If the function found the PDFLaTeX binary compiler stored in the machine, then it returns the corresponding path.
  */
QString searchCompilerBinary();
/*************************************************************************************************/
/**
  @brief This is the function that loads the PDFLaTeX compiler path stored in the corresponding preference file.
  @returns If the function found the corresponding preference file, it returns the file path stored in it.
  */
QString loadPDFCompilerPathSettings();
/*************************************************************************************************/
/**
  @brief This is the function that saves the PDFLaTeX compiler path to the corresponding preference file.
  @param compilerPath compiler binary file path.
  @returns This is a void function.
  */
void savePDFCompilerPathSettings(QString compilerPath);
/*************************************************************************************************/
/**
  @brief This is the function that loads the BiBLaTeX compiler path stored in the corresponding preference file.
  @returns If the function found the corresponding preference file, it returns the file path stored in it.
  */
QString loadBIBCompilerPathSettings() ;
/*************************************************************************************************/
/**
  @brief This is the function that saves the BiBLaTEX compiler path to the corresponding preference file.
  @param compilerPath compiler binary file path.
  @returns This is a void function.
  */
void saveBIBCompilerPathSettings(QString compilerPath) ;
/*************************************************************************************************/
/**
  @brief This is the function that loads the HTML converter path stored in the corresponding preference file.
  @returns If the function found the corresponding preference file, it returns the file path stored in it.
  */
QString loadHTMLConverterPathSettings() ;
/*************************************************************************************************/
/**
  @brief This is the function that saves the HTML converter path to the corresponding preference file.
  @param compilerPath converter binary file path.
  @returns This is a void function.
  */
void saveHTMLConverterPathSettings(QString compilerPath);
/*************************************************************************************************/
/**
  @brief This is the function that loads the HTML converter path stored in the corresponding preference file.
  @returns If the function found the corresponding preference file, it returns the file path stored in it.
  */
QString loadTXTConverterPathSettings();
/*************************************************************************************************/
/**
  @brief This is the function that saves the TXT converter path to the corresponding preference file.
  @param compilerPath converter binary file path.
  @returns This is a void function.
  */
void saveTXTConverterPathSettings(QString compilerPath);
/*************************************************************************************************/
/**
  @brief This is the function that loads the HTML converter path stored in the corresponding preference file.
  @returns If the function found the corresponding preference file, it returns the file path stored in it.
  */
QString loadRTFConverterPathSettings() ;
/*************************************************************************************************/
/**
  @brief This is the function that saves the RTF converter path to the corresponding preference file.
  @param compilerPath converter binary file path.
  @returns This is a void function.
  */
void saveRTFConverterPathSettings(QString compilerPath);
}


#define COMPILER

#endif // COMPILER

