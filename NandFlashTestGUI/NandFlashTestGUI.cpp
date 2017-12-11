#include "NandFlashTestGUI.h"
#include "qevent.h"
#include "qpainter.h"
#include "qbrush.h"
#include "qdebug.h"

#define STD_WIDTH	1280
#define STD_HEIGHT	720
#define MENU_HEIGHT 40

// Fac means factor
const double vWidthFac = 0.88;
const double vHeightFac = 0.81;

NandFlashTestGUI::NandFlashTestGUI(QWidget *parent)
	: QMainWindow(parent), viewer(new FlashViewer(this)),
	infoEdit(new QTextEdit(this))
{
	ui.setupUi(this);
	this->size().setWidth(STD_WIDTH);
	this->size().setHeight(STD_HEIGHT);
	this->setMinimumSize(STD_WIDTH, STD_HEIGHT);
	this->flashViewW = this->size().width() * vWidthFac;

	// set the flash viewer
	viewer->setGeometry(STD_WIDTH- flashViewW, MENU_HEIGHT,
		viewer->getMinWidth(), viewer->getMinHeight());
	viewer->show();

	// set the infomation text editor
	infoEdit->setGeometry(STD_WIDTH - flashViewW, size().height() * vHeightFac + 1,
		flashViewW - 4, STD_HEIGHT - viewer->getMinHeight() - MENU_HEIGHT - 2);
	infoEdit->setReadOnly(true);
	infoEdit->show();
}

// draw a red line to draw a border line
void NandFlashTestGUI::paintEvent(QPaintEvent * ev)
{
	QPainter painter(this);
	painter.setPen(QColor{ 255, 0, 0 });
	painter.drawRect(this->size().width() - flashViewW, MENU_HEIGHT,
		flashViewW - 5, size().height() * vHeightFac);
}

void NandFlashTestGUI::resizeEvent(QResizeEvent * ev)
{
	this->flashViewW = this->size().width() * vWidthFac;
	viewer->setGeometry(this->size().width()- flashViewW, MENU_HEIGHT,
		viewer->getMinWidth(), viewer->getMinHeight());
	infoEdit->setGeometry(size().width() - flashViewW, size().height() * vHeightFac + 2,
		flashViewW - 4, size().height() * (1 - vHeightFac) - 1);
}
