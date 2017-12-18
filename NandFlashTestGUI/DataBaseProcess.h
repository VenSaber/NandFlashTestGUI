#pragma once
#include <qsqldatabase.h>

namespace DataBaseProcess
{
	QSqlDatabase OpenDataBase();
	void CloseDataBase(QSqlDatabase& db);
	QString SelectAllFrom(const QString& tableName);
	QString SelectFromFlashType(const QString& valueName);
	QString InsertIntoFlashType(const QVector<QString>& content);
	QString SelectFlashByName(const QString& name);
	QString DeleteFlashByName(const QString& name);
}