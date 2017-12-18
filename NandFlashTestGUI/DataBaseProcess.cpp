#include "DataBaseProcess.h"
#include <qvector.h>
#include <qsqlquery.h>

namespace DataBaseProcess
{
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

	void CloseDataBase(QSqlDatabase & db)
	{
		db.close();
	}

	QString SelectAllFrom(const QString& tableName)
	{
		QString SqlStr = "select * from " + tableName + ";";
		return SqlStr;
	}

	QString SelectFromFlashType(const QString & valueName)
	{
		QString SqlStr = "select " + valueName + " from flash_type;";
		return SqlStr;
	}

	QString InsertIntoFlashType(const QVector<QString>& content)
	{
		QString SqlStr = "insert into flash_type values(\"" + content[0] + "\", ";
		for (auto index = 1; index < 4; ++index)
			SqlStr = SqlStr + content[index] + ", ";
		SqlStr = SqlStr + content[4] + ");";
		return SqlStr;
	}

	QString SelectFlashByName(const QString & name)
	{
		QString SqlStr = "select * from flash_type where name = \"" + name + "\";";
		return SqlStr;
	}

	QString DeleteFlashByName(const QString & name)
	{
		QString SqlStr = "delete from flash_type where name = \"" + name + "\";";
		return SqlStr;
	}
}