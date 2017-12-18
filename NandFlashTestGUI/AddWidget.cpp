#include "AddWidget.h"
#include "DataBaseProcess.h"
#include <qsqlquery.h>
#include <qdebug.h>

AddWidget::AddWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setMinimumSize(400, 200);
	this->setMaximumSize(400, 200);

	// when we click ok button, we input the data to the database
	// and the table widget should show the new type
	connect(ui.okButton, &QPushButton::clicked, [this]() {
		auto& db = DataBaseProcess::OpenDataBase();
		QSqlQuery query(DataBaseProcess::InsertIntoFlashType(getWidgetInfo()));
		DataBaseProcess::CloseDataBase(db);
		emit NoticeMenu(ui.flashTypeEdit->text());
		this->close();
	});
	connect(ui.cancelButton, &QPushButton::clicked, [this]() {
		this->close(); 
	});
}

void AddWidget::closeEvent(QCloseEvent* ev)
{
	ui.flashTypeEdit->clear();
	ui.blkCntEdit->clear();
	ui.ppbEdit->clear();
	ui.rowBox->setCurrentIndex(0);
	ui.colBox->setCurrentIndex(0);
	this->hide();
}

QVector<QString> AddWidget::getWidgetInfo()
{
	QVector<QString> content;
	content.push_back(ui.flashTypeEdit->text());
	content.push_back(ui.blkCntEdit->text());
	content.push_back(ui.ppbEdit->text());
	content.push_back(ui.rowBox->currentText());
	content.push_back(ui.colBox->currentText());
	return content;
}
