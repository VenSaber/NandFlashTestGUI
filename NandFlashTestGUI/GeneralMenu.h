#pragma once
#include <QWidget>
#include "FlashTypeTable.h"
#include "ui_GeneralMenu.h"

struct Flash
{
public:
	void operator= (Flash& rhs)
	{
		name = rhs.name;
		blkCnt = rhs.blkCnt;
		ppb = rhs.ppb;
		rowNum = rhs.rowNum;
		colNum = rhs.colNum;
	}

public:
	// flash info
	QString name;
	int		blkCnt;
	int		ppb;
	// viewer paint info
	int		rowNum;
	int		colNum;
};

class GeneralMenu : public QWidget
{
	Q_OBJECT
public:
	GeneralMenu(QWidget *parent);
	~GeneralMenu() = default;
signals:
	void FlashTypeChanged(Flash& flash);
private slots:
	void DoubleClickProcess();
	void AddNewLine(const QString& name);
	void DeleteProcess();
private:
	void FlashTableInit();
private:
	Ui::GeneralMenuClass ui;

	int selectRow; 
	FlashTypeTable* flashTable;
	QTableWidgetItem* selectSign;
};
