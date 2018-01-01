/**
 * @file		FlashErrorInfo.h
 * @author		ventury
 * @version		0.6.1
 * @note
 * **History**
 *    data   |  version	 |             content
 * :--------:|:---------:|----------------------------------
 * 2017-12-11|0.1.0		 |construct the basic GUI
 * 2017-12-12|0.2.0		 |basic zoomIn and zoomOut
 * 2017-12-14|0.3.0	     |enable paint arbitrary flash
 * 2017-12-18|0.4.0		 |use MySQL to manage the flash type
 * 2017-12-19|0.4.1		 |fixed some bugs & optimizate code
 * 2017-12-20|0.5.0		 |enable move flash viewer & fixed bugs
 * 2017-12-23|0.6.0		 |add viewer reset func & prev/next viewer func
 * 2017-12-24|0.6.1		 |change to doxygen comment style
 * 2017-12-28|0.7.0		 |read test error file to show in the flash viewer
 * 2018-01-01|0.8.0		 |the text edit will input detail when double clicked the error page
 */
#pragma once
#include <qtguiglobal.h>
#include <qbytearray.h>

 /**
  * @struct FlashErrorInfo [FlashErrorInfo.h]
  * @brief this class contain the wrong data information in the flash test
  * @author ventury
  * @since 0.7.0
  */
struct FlashErrorInfo
{
	quint16 blockNum; /*!> the block num of the error data */
	quint16 pageNum; /*!> the page num of the error data*/
	quint16 byteNum; /*!> the byte num of the error data*/
	QByteArray correctData; /*!> the correct value that should be*/
	QByteArray errorData; /*!> the error value that read from the flash*/
	QByteArray xorData; /*!> the data that exclusive or calculation between correct data and error data*/
};

