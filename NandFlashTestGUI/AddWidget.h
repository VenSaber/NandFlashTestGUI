#pragma once
#include <qwidget.h>
#include <qstring.h>
#include "ui_AddWidget.h"

class AddWidget : public QWidget
{
	Q_OBJECT
public:
	AddWidget(QWidget* parent = Q_NULLPTR);
	~AddWidget() = default;
signals:
	void NoticeMenu(const QString& name);
protected:
	void closeEvent(QCloseEvent* ev) override;
private:
	QVector<QString> getWidgetInfo();
private:
	Ui::AddWidgetClass ui;
};

