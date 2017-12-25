/**
 * @file		DataBaseProcess.cpp
 * @author		ventury
 * @version		0.6.1
 */
#include <qvector.h>
#include <qsqlquery.h>
#include "DataBaseProcess.h"

namespace DataBaseProcess
{
	/**
	 * @brief open the database that contain flash information.
	 * @return the database object that alread opened
	 * @since 0.4.0
	 */
	QSqlDatabase OpenDataBase()
	{
		QSqlDatabase db;
		if (QSqlDatabase::contains("qt_sql_default_connection"))
			db = QSqlDatabase::database("qt_sql_default_connection");
		else
			db = QSqlDatabase::addDatabase("QMYSQL");
		db.setDatabaseName("qt_gui_employ");
		db.setUserName("root");
		db.setPassword("123");
		db.open();
		return db;
	}

	/**
	 * @brief close the database that contain flash information.
	 * @param db the database that would be closed
	 * @since 0.4.0
	 */
	void CloseDataBase(QSqlDatabase & db)
	{
		db.close();
	}

	/**
	 * @brief the statement that select all information from the specified table.
	 * @param tableName the table name that want to get all information.
	 * @return the SQL statement
	 * @since 0.4.0
	 */
	QString SelectAllFrom(const QString& tableName)
	{
		QString SqlStr = "select * from " + tableName + ";";
		return SqlStr;
	}

	/**
	 * @brief the statement that select specified colomn title from flash table.
	 * @param valueName the specified colomn title name
	 * @return the SQL statement 
	 * @since  0.4.0
	 */
	QString SelectFromFlashType(const QString & valueName)
	{
		QString SqlStr = "select " + valueName + " from flash_type;";
		return SqlStr;
	}

	/**
	 * @brief the statement that insert flash content into flash table.
	 * @param content a vector that contain the flash information
	 * @return the SQL statement 
	 * @since 0.4.0
	 */
	QString InsertIntoFlashType(const QVector<QString>& content)
	{
		QString SqlStr = "insert into flash_type values(\"" + content[0] + "\", ";
		for (auto index = 1; index < 4; ++index)
			SqlStr = SqlStr + content[index] + ", ";
		SqlStr = SqlStr + content[4] + ");";
		return SqlStr;
	}

	/**
	 * @brief the statement that select specified flash information.
	 * @param name the flash type name
	 * @return the SQL statement 
	 * @see DeleteFlashByName
	 * @since 0.4.0
	 */
	QString SelectFlashByName(const QString & name)
	{
		QString SqlStr = "select * from flash_type where name = \"" + name + "\";";
		return SqlStr;
	}

	/**
	 * @brief the statement that delete specified flash information.
	 * @param name the flash type name
	 * @return the SQL statement
	 * @see SelectFlashByName
	 * @since 0.4.0
	 */
	QString DeleteFlashByName(const QString & name)
	{
		QString SqlStr = "delete from flash_type where name = \"" + name + "\";";
		return SqlStr;
	}
}