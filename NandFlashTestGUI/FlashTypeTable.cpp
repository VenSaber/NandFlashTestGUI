#include <qevent.h>
#include <qsqlquery.h>
#include "FlashTypeTable.h"
#include "DataBaseProcess.h"

FlashTypeTable::FlashTypeTable(QWidget* parent)
	: QTableWidget(parent)
{
}

void FlashTypeTable::keyPressEvent(QKeyEvent * ev)
{
	ev->ignore();
}
