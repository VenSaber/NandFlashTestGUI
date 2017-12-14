#pragma once
#include <qwidget.h>
#include <qstring.h>
#include "ui_AddWidget.h"

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

class AddWidget : public QWidget
{
	Q_OBJECT
public:
	AddWidget(QWidget* parent = Q_NULLPTR);
	~AddWidget() = default;
	void closeEvent(QCloseEvent* ev) override;
private:
	Ui::AddWidgetClass ui;
};

