/**
 * @file		DataBaseProcess.h
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
 * 2017-12-25|0.6.1		 |change to doxygen comment style
 * 2017-12-28|0.7.0		 |read test error file to show in the flash viewer
 */
#pragma once
#include <qsqldatabase.h>

namespace DataBaseProcess
{
	/**@brief open the database that contain flash information.*/
	QSqlDatabase OpenDataBase();
	/**@brief close the database that contain flash information.*/
	void CloseDataBase(QSqlDatabase& db);
	/**@brief the statement that select all information from the specified table.*/
	QString SelectAllFrom(const QString& tableName);
	/**@brief the statement that select specified colomn title from flash table.*/
	QString SelectFromFlashType(const QString& valueName);
	/**@brief the statement that insert flash content into flash table.*/
	QString InsertIntoFlashType(const QVector<QString>& content);
	/**@brief the statement that select specified flash information.*/
	QString SelectFlashByName(const QString& name);
	/**@brief the statement that delete specified flash information.*/
	QString DeleteFlashByName(const QString& name);
}