#pragma once
#include <qwidget.h>
#include <qtablewidget.h>

class FlashTypeTable : public QTableWidget
{
	Q_OBJECT
public:
	FlashTypeTable(QWidget* parent = Q_NULLPTR);
	~FlashTypeTable() = default;
protected:
	void keyPressEvent(QKeyEvent* ev) override;
};

