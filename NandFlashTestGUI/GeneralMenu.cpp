// TODO:SEARCH FLASH TYPE
#include "GeneralMenu.h"
#include "FlashViewer.h"
#include "AddWidget.h"
#include "DataBaseProcess.h"
#include <qmessagebox.h>
#include <qsqlquery.h>
#include <qevent.h>
#include <qdebug.h>

#define SIGN_PGE 0.2

GeneralMenu::GeneralMenu(QWidget *parent)
	: QWidget(parent), selectRow(0), selectSign(new QTableWidgetItem("O"))
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

void GeneralMenu::FlashTableInit()
{
	// output the flash type name to the table widget from database
	auto& db = DataBaseProcess::OpenDataBase();
	QSqlQuery query(DataBaseProcess::SelectFromFlashType("name"));
	int rowIndex = 0;
	while (query.next())
	{
		QString name = query.value(0).toString();
		ui.flashTabeWidget->insertRow(rowIndex);
		auto typeName = new QTableWidgetItem(name);
		ui.flashTabeWidget->setItem(rowIndex++, 1, typeName);
	}
	DataBaseProcess::CloseDataBase(db);

	// flash table widget setting
	ui.flashTabeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.flashTabeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.flashTabeWidget->setColumnWidth(0, ui.flashTabeWidget->width() * SIGN_PGE);
	ui.flashTabeWidget->setItem(0, 0, selectSign);

	QObject::connect(ui.flashTabeWidget, &QTableWidget::itemDoubleClicked,
					 this, &GeneralMenu::DoubleClickProcess);
}

void GeneralMenu::DoubleClickProcess()
{
	auto oldItem = ui.flashTabeWidget->takeItem(selectRow, 0);
	selectRow = ui.flashTabeWidget->currentRow();
	ui.flashTabeWidget->setItem(selectRow, 0, selectSign);

	auto& db = DataBaseProcess::OpenDataBase();
	QString name = ui.flashTabeWidget->item(selectRow, 1)->text();
	QSqlQuery query(DataBaseProcess::SelectFlashByName(name));
	query.next(); // watch out! this code must exit

	// painting the default flash according to the database data
	Flash flash{ query.value(0).toString(), query.value(1).toInt(),
		query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt() };
	emit FlashTypeChanged(flash);
	DataBaseProcess::CloseDataBase(db);
}

void GeneralMenu::AddNewLine(const QString & name)
{
	auto newItem = new QTableWidgetItem(name);
	int row = ui.flashTabeWidget->rowCount();
	ui.flashTabeWidget->setRowCount(row + 1);
	ui.flashTabeWidget->setItem(row, 1, newItem);
}

void GeneralMenu::DeleteProcess()
{
	const int currentRow = ui.flashTabeWidget->currentRow();
	const QString name = ui.flashTabeWidget->item(currentRow, 1)->text();
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
	const QString& flag = ui.flashTabeWidget->item(currentRow, 0)->text();
	if (flag == "O")
	{
		ui.flashTabeWidget->takeItem(currentRow, 0);
		ui.flashTabeWidget->setItem(0, 0, selectSign);
		Flash flash{ "default", 2048, 64, 2, 8 };
		emit FlashTypeChanged(flash);
	}
	ui.flashTabeWidget->removeRow(currentRow);
}