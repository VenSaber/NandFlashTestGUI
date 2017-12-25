/**
 * @file		FlashTypeTable.cpp
 * @author		ventury
 * @version		0.6.1
 */
#include <qevent.h>
#include <qsqlquery.h>
#include "FlashTypeTable.h"
#include "DataBaseProcess.h"

/**
 * @brief the constructure function.
 * @param parent this parameter is the parent of this class
 * @since 0.6.0
 */
FlashTypeTable::FlashTypeTable(QWidget* parent)
	: QTableWidget(parent)
{
}

/**
 * @brief ignore the keyPressEvent in this widget
 * @param ev Qt key press event pointer
 * since 0.6.0
 */
void FlashTypeTable::keyPressEvent(QKeyEvent * ev)
{
	ev->ignore();
}
