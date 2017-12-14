#include "AddWidget.h"
#include "FlashViewer.h"
#include <qdebug.h>

AddWidget::AddWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setMinimumSize(400, 200);
	this->setMaximumSize(400, 200);
	connect(ui.okButton, &QPushButton::clicked, [this]() {
		Flash myflash;
		myflash.name = ui.flashTypeEdit->text();
		myflash.blkCnt = ui.blkCntEdit->text().toInt();
		myflash.ppb = ui.ppbEdit->text().toInt();
		myflash.rowNum = ui.rowBox->currentText().toInt();
		myflash.colNum = ui.colBox->currentText().toInt();
		FlashViewer::setCurrentFlash(myflash);
		this->close();
	});
	connect(ui.cancelButton, &QPushButton::clicked, [this]() {
		this->close(); 
	});
}

void AddWidget::closeEvent(QCloseEvent* ev)
{
	delete(this);
}
