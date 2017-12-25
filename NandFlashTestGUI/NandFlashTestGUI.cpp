/**
 * @file		NandFlashTestGUI.cpp
 * @author		ventury
 * @version		0.6.1
 */
/**
 * @todo ENABLE OPEN 2 FORMAT FILE, ONE IS STRING, ANOTHER IS DIGITAL
 */
#include <qevent.h>
#include <qpainter.h>
#include <qbrush.h>
#include <qmenu.h>
#include <qfiledialog.h>
#include <qdebug.h>
#include "NandFlashTestGUI.h"

/**@brief standard width*/
#define		STD_WIDTH		1280
/**@brief standard height*/
#define		STD_HEIGHT		720
/**@brief menu bar height*/
#define		MENU_HEIGHT		40
/**@brief subwindow remain space*/
#define		REMAIN_SPACE	5

/**@brief the border factor between *genWindow* and *viewer* */
const double vWidthFac = 0.88; 
/**@brief the border factor between *viewer* and *infoEdit* */
const double vHeightFac = 0.81;

/**
 * @brief the constructure function.
 * @param parent this parameter is the parent of this class
 * @since 0.1.0
 */
NandFlashTestGUI::NandFlashTestGUI(QWidget *parent)
	: QMainWindow(parent), genWindow(new GeneralMenu(this)),
	viewer(new FlashViewer(this, genWindow)), infoEdit(new QTextEdit(this)) 
{
	ui.setupUi(this);
	this->size().setWidth(STD_WIDTH);
	this->size().setHeight(STD_HEIGHT);
	this->setMinimumSize(STD_WIDTH, STD_HEIGHT);

	FileMenuInit();

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

/**
 * @brief draw a red line to draw a border line. 
 * @param ev Qt paint event pointer
 * @since 0.1.0
 */
void NandFlashTestGUI::paintEvent(QPaintEvent * ev)
{
	QPainter painter(this);
	painter.setPen(QColor{ 255, 0, 0 });
	painter.drawRect(size().width() * (1 - vWidthFac), MENU_HEIGHT,
					 size().width() * vWidthFac - REMAIN_SPACE, 
					 size().height() * vHeightFac);
}

/**
 * @brief call the keyPressEvent of the Flashviewer class.
 * @param ev Qt key press event pointer
 * @since 0.6.0
 */
void NandFlashTestGUI::keyPressEvent(QKeyEvent * ev)
{
	viewer->keyPressEvent(ev);
}

/**
 * @brief when the main window size changed, the proportion would not change. 
 * @param ev Qt resize event pointer
 * @since 0.1.0
 */
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

/**
 * @brief setting the file menu.
 * @since 0.6.1
 */
void NandFlashTestGUI::FileMenuInit()
{
	menuOpen = new QMenu("Open", this);
	actionErrorString = new QAction("Error String", this);
	connect(actionErrorString, &QAction::triggered, [this]() {
		auto filename = QFileDialog::getOpenFileName(this,
			 "Open File", "C:/", "Error String File(*.esf)");
		qDebug() << "the file name is " << filename;
	});
	actionPureDigital = new QAction("Pure Digital", this);
	connect(actionPureDigital, &QAction::triggered, [this]() {
		auto filename = QFileDialog::getOpenFileName(this,
			 "Open File", "C:/", "Pure Digital File(*.pd)");
		qDebug() << "the file name is " << filename;
	});
	menuOpen->addAction(actionErrorString);
	menuOpen->addAction(actionPureDigital);
	ui.menuFile->addMenu(menuOpen);
}
