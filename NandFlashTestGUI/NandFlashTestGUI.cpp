#include <qevent.h>
#include <qkeyeventtransition.h>
#include <qpainter.h>
#include <qbrush.h>
#include <qdebug.h>
#include "NandFlashTestGUI.h"

#define		STD_WIDTH		1280
#define		STD_HEIGHT		720
#define		MENU_HEIGHT		40
#define		REMAIN_SPACE	5

// Fac means factor
const double vWidthFac = 0.88;
const double vHeightFac = 0.81;

NandFlashTestGUI::NandFlashTestGUI(QWidget *parent)
	: QMainWindow(parent), genWindow(new GeneralMenu(this)),
	viewer(new FlashViewer(this, genWindow)), infoEdit(new QTextEdit(this)) 
{
	ui.setupUi(this);
	this->size().setWidth(STD_WIDTH);
	this->size().setHeight(STD_HEIGHT);
	this->setMinimumSize(STD_WIDTH, STD_HEIGHT);

	// set the general menu window
	genWindow->setGeometry(0, MENU_HEIGHT,
						   size().width() * (1 - vWidthFac), 
						   size().height() - MENU_HEIGHT);
	genWindow->raise();
	genWindow->show();

	// set the flash viewer
	viewer->setGeometry(STD_WIDTH * (1 - vWidthFac), MENU_HEIGHT,
						STD_WIDTH * vWidthFac - REMAIN_SPACE,
						STD_HEIGHT * vHeightFac - MENU_HEIGHT);
	viewer->raise();
	viewer->show();

	// set the infomation text editor
	infoEdit->setGeometry(STD_WIDTH * (1 - vWidthFac), 
						  STD_HEIGHT * vHeightFac + 1,
						  STD_WIDTH * vWidthFac - REMAIN_SPACE + 1, 
						  STD_HEIGHT * (1 - vHeightFac)- 2);
	infoEdit->setReadOnly(true);
	infoEdit->show();
}

// draw a red line to draw a border line
void NandFlashTestGUI::paintEvent(QPaintEvent * ev)
{
	QPainter painter(this);
	painter.setPen(QColor{ 255, 0, 0 });
	painter.drawRect(size().width() * (1 - vWidthFac), MENU_HEIGHT,
					 size().width() * vWidthFac - REMAIN_SPACE, 
					 size().height() * vHeightFac);
}

void NandFlashTestGUI::keyPressEvent(QKeyEvent * ev)
{
	viewer->keyPressEvent(ev);
}

// when the main window size changed, the proportion would not change
void NandFlashTestGUI::resizeEvent(QResizeEvent * ev)
{
	// reset the main window with the fixed factor
	viewer->setGeometry(size().width() * (1 - vWidthFac), MENU_HEIGHT,
						size().width() * vWidthFac - REMAIN_SPACE, 
						size().height() * vHeightFac - MENU_HEIGHT);
	infoEdit->setGeometry(size().width() * (1 - vWidthFac), 
						  size().height() * vHeightFac + 2,
						  size().width() * vWidthFac - REMAIN_SPACE + 1, 
						  size().height() * (1 - vHeightFac) - 1);
	genWindow->setGeometry(0, MENU_HEIGHT,
						   size().width() * (1 - vWidthFac), 
						   size().height() - MENU_HEIGHT);
}
