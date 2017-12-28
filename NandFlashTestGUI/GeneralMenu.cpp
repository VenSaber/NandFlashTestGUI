/**
 * @file		GeneralMenu.cpp
 * @author		ventury
 * @version		0.6.1
 */
/**@todo SEARCH FLASH TYPE */
/**@todo MAKE THIS WIDGET CHANGE SIZE WITH THE MAIN WINDOW RESIZE*/
/**@todo MAKE THE ROW NUMBER AND COLOMN NUMBER BE MODIFIED*/
#include <qmessagebox.h>
#include <qsqlquery.h>
#include <qevent.h>
#include <qdebug.h>
#include "GeneralMenu.h"
#include "FlashViewer.h"
#include "AddWidget.h"
#include "DataBaseProcess.h"

/**@brief the proportioner of the first colomn in the QTableWidget*/
#define SIGN_PGE 0.2

/**
 * @brief the constructure function.
 * @param parent this parameter is the parent of this class
 * @since 0.2.0
 */
GeneralMenu::GeneralMenu(QWidget *parent)
	: QWidget(parent), selectRow(0), 
	flashTable(new FlashTypeTable(this)),
	selectSign(new QTableWidgetItem("O"))
{
	ui.setupUi(this);
	FlashTableInit();
	AddWidget* widget = new AddWidget();
	connect(ui.addButton, &QPushButton::clicked, [widget]() {
		widget->show();
	});
	connect(widget, &AddWidget::NoticeMenu, this, &GeneralMenu::AddNewLine);
	connect(ui.deleteButton, &QPushButton::clicked, this, &GeneralMenu::DeleteProcess);
}

/**
 * @brief initialize the flash Table.
 * @since 0.4.0
 */
void GeneralMenu::FlashTableInit()
{
	flashTable->setGeometry(1, 34, 149, 131);
	// set the 2 colomn, one is "c", another is "type"
	flashTable->setColumnCount(2);
	QStringList colHeadTitle{ "C", "Type" };
	flashTable->setHorizontalHeaderLabels(colHeadTitle);

	// output the flash type name to the table widget from database
	auto& db = DataBaseProcess::OpenDataBase();
	QSqlQuery query(DataBaseProcess::SelectFromFlashType("name"));
	int rowIndex = 0;
	while (query.next())
	{
		QString name = query.value(0).toString();
		flashTable->insertRow(rowIndex);
		auto typeName = new QTableWidgetItem(name);
		flashTable->setItem(rowIndex++, 1, typeName);
	}
	DataBaseProcess::CloseDataBase(db);

	// flash table widget setting
	flashTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	flashTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	flashTable->setColumnWidth(0, flashTable->width() * SIGN_PGE);
	flashTable->setItem(0, 0, selectSign);

	QObject::connect(flashTable, &QTableWidget::itemDoubleClicked,
					 this, &GeneralMenu::DoubleClickProcess);
}

/**
 * @brief the function that happen when double clicked the flash table item.
 * @since 0.4.0
 */
void GeneralMenu::DoubleClickProcess()
{
	auto oldItem = flashTable->takeItem(selectRow, 0);
	selectRow = flashTable->currentRow();
	flashTable->setItem(selectRow, 0, selectSign);

	auto& db = DataBaseProcess::OpenDataBase();
	QString name = flashTable->item(selectRow, 1)->text();
	QSqlQuery query(DataBaseProcess::SelectFlashByName(name));
	query.next(); // watch out! this code must exit

	// painting the default flash according to the database data
	Flash flash{ query.value(0).toString(), query.value(1).toInt(),
		query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt() };
	emit FlashTypeChanged(flash);
	DataBaseProcess::CloseDataBase(db);
}

/**
 * @brief add a new line in the flash table and fill the specified name.
 * @since 0.4.0
 */
void GeneralMenu::AddNewLine(const QString & name)
{
	auto newItem = new QTableWidgetItem(name);
	int row = flashTable->rowCount();
	flashTable->setRowCount(row + 1);
	flashTable->setItem(row, 1, newItem);
}

/**
 * @brief the function that happen when delete button is clicked.
 * @since 0.4.0
 */
void GeneralMenu::DeleteProcess()
{
	const int currentRow = flashTable->currentRow();
	const QString name = flashTable->item(currentRow, 1)->text();
	if (name == "default")
	{
		QMessageBox* box = new QMessageBox(QMessageBox::Warning,
		   "Operation Aborting", "Sorry, the default item cannot be deleted" );
		box->exec();
		return ;
	}
	// delete the specified item
	auto& db = DataBaseProcess::OpenDataBase();
	QSqlQuery query(DataBaseProcess::DeleteFlashByName(name));
	DataBaseProcess::CloseDataBase(db);

	// if deleted item is selected, the item would become default
	const QString& flag = flashTable->item(currentRow, 0)->text();
	if (flag == "O")
	{
		flashTable->takeItem(currentRow, 0);
		flashTable->setItem(0, 0, selectSign);
		Flash flash{ "default", 2048, 64, 2, 8 };
		emit FlashTypeChanged(flash);
	}
	flashTable->removeRow(currentRow);
}