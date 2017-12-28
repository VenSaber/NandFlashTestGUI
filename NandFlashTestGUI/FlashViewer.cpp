/**
 * @file		FlashViewer.cpp
 * @author		ventury
 * @version		0.6.1
 */
/**@todo ARBITRARY ANCHOR ZOOMIN AND ZOOMOUT*/
/**@todo PREVIOUS/NEXT VIEWER MAYBE HAVE BUG*/
/**@todo AFTER OPENING FILE, THE ERROR PAGE SHOULD PAINT RED*/
#include <qlabel.h>
#include <qpainter.h>
#include <qevent.h>
#include <qmenu.h>
#include <qaction.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include "FlashViewer.h"
#include "NandFlashTestGUI.h"

/**@brief free space in width*/
const int spacew = 10;
/**@brief free space in height*/
const int spaceh = 10;

Flash FlashViewer::currentFlash{"default", 2048, 64, 2, 8};

/**
 * @brief the constructure function
 * @param parent the parent of this class
 * @param _controller the general Menu class that use to communicate with
 * @since 0.1.0
 */
FlashViewer::FlashViewer(QWidget* parent, GeneralMenu* _controller)
	:QWidget(parent), controller(_controller), midButtonClick(false),
	paintErrorFlag(false)
{
	MenuInit();
	// Watch out! PaintParamRst function must appear firstly and StackInit secondly
	PaintParamRst();
	StackInit();
	this->setMouseTracking(false);
	connect(controller, &GeneralMenu::FlashTypeChanged, [this](Flash& flash) {
		currentFlash = flash;
		PaintParamRst();
		StackInit();
		this->repaint();
	});
	connect((NandFlashTestGUI*)parent, &NandFlashTestGUI::SendFlashErrorInfo, [this](QVector<FlashErrorInfo>& info) {
		flashErrorVec = info;
		paintErrorFlag = true;
		this->repaint();
	});
}

/**
 * @brief previous/next viewer function that keyboard trigger
 * @detail set this event public to make main window call this func
 * @param ev Qt key press event pointer
 * @since 0.6.0
 */
void FlashViewer::keyPressEvent(QKeyEvent * ev)
{
	if (ev->modifiers() == Qt::AltModifier)
	{
		if (ev->key() == Qt::Key_Left)
			preViewer();
		else if (ev->key() == Qt::Key_Right)
			nxtViewer();
	}
}

/**
 * @brief paint the flash viewer (basic unit : page)
 * @param ev Qt paint event pointer
 * @since 0.1.0
 */
void FlashViewer::paintEvent(QPaintEvent * ev)
{
	QPainter painter(this);
	for (auto rowIndex = 0; rowIndex < currentFlash.rowNum; ++rowIndex)
		for (auto colIndex = 0; colIndex < currentFlash.colNum; ++colIndex)
		{
			int subrowCnt = currentFlash.blkCnt / currentFlash.rowNum / currentFlash.colNum;
			for (auto subrow = 0; subrow <= subrowCnt; ++subrow)
			{
				painter.drawLine(spacew * (colIndex + 1) + currentFlash.ppb * paintParam.sublen * colIndex + paintParam.MoveX,
					spaceh * (rowIndex + 1) + paintParam.sublen * (subrowCnt * rowIndex + subrow) + paintParam.MoveY,
					spacew * (colIndex + 1) + currentFlash.ppb * paintParam.sublen * (1 + colIndex) + paintParam.MoveX,
					spaceh * (rowIndex + 1) + paintParam.sublen * (subrowCnt * rowIndex + subrow) + paintParam.MoveY);
			}
			for (auto subcol = 0; subcol <= currentFlash.ppb; ++subcol)
			{
				painter.drawLine(spacew * (colIndex + 1) + paintParam.sublen * (currentFlash.ppb * colIndex + subcol) + paintParam.MoveX,
					spaceh * (rowIndex + 1) + subrowCnt * paintParam.sublen * rowIndex + paintParam.MoveY,
					spacew * (colIndex + 1) + paintParam.sublen * (currentFlash.ppb * colIndex + subcol) + paintParam.MoveX,
					spaceh * (rowIndex + 1) + subrowCnt * paintParam.sublen * (rowIndex + 1) + paintParam.MoveY);
			}
		}
	if (paintErrorFlag)
	{
		// calculate the coordinate of the origin point
		originX = spacew + paintParam.MoveX;
		originY = spaceh + paintParam.MoveY;
		paintFlashError(painter);
	}
}

/**
 * @brief zoomIn and zoomOut function that mouse wheel trigger
 * @param ev Qt wheel event pointer
 * @since 0.1.0
 */
void FlashViewer::wheelEvent(QWheelEvent * ev)
{
	// control key plus wheel to zoom in and zoom out
	if (ev->modifiers() == Qt::ControlModifier)
	{
		if (ev->delta() > 0)
			this->wheelViewerUp();
		else 
			this->wheelViewerDown();
		preStack.push(paintParam);
		nxtStack.clear();
		this->repaint();
	}
}

/**
 * @brief move the viewer according to the mouse middle button moving path
 * @param ev Qt mouse move event pointer
 * @since 0.4.1
 */
void FlashViewer::mouseMoveEvent(QMouseEvent * ev)
{
	if (midButtonClick)
	{
		paintParam.MoveX = ev->pos().x() - paintParam.preMouseX;
		paintParam.MoveY = ev->pos().y() - paintParam.preMouseY;
		this->repaint();
	}
}

/**
 * @brief the start point that the viewer move and menu execute when right button click 
 * @param ev Qt mouse press event pointer
 * @since 0.5.0
 */
void FlashViewer::mousePressEvent(QMouseEvent * ev)
{
	if (ev->button() == Qt::MidButton)
	{
		// be careful that the value of the paintParam.MoveX 
		// and paintParam.MoveY should be always continuous
		// so, we should minus paintParam.MoveX and paintParam.MoveY
		// to calculate the paintParam.preMouseX and paintParam.preMouseY
		paintParam.preMouseX = ev->pos().x() - paintParam.MoveX;
		paintParam.preMouseY = ev->pos().y() - paintParam.MoveY;
		midButtonClick = true;
	}
	else if (ev->button() == Qt::RightButton)
		rbtMenu->exec(QCursor::pos());
}

/**
 * @brief the end point that the viewer move
 * @param ev Qt mouse release event pointer
 * @since 0.5.0
 */
void FlashViewer::mouseReleaseEvent(QMouseEvent * ev)
{
	if (ev->button() == Qt::MidButton)
	{
		midButtonClick = false;
		// when mouse moving, the mouseMoveEvent will be called for several times until release
		// the two steps will become very short, so we put stack-pushing here
		preStack.push(paintParam);
		nxtStack.clear();
	}
}

/**
 * @brief init the menu that right button triggered
 * @since 0.6.0
 */
void FlashViewer::MenuInit()
{
	rbtMenu = new QMenu();
	resetAction = new QAction("reset", this);
	connect(resetAction, &QAction::triggered, [this]() {
		PaintParamRst();
		preStack.push(paintParam);
		nxtStack.clear();
		this->repaint();
	});
	rbtMenu->addAction(resetAction);
}
/**
 * @brief reset the painting parameter
 * @detail PaintParamRst must appear firstly and StackInit secondly
 * @see StackInit 
 * @since 0.6.0
 */
void FlashViewer::PaintParamRst()
{	
	paintParam = { 0, 0, 0, 0, 2 };
	flashErrorVec.clear();
	paintErrorFlag = false;
}

/**
 * @brief initialize the stack that use to save viewer
 * @detail PaintParamRst must appear firstly and StackInit secondly
 * @see PaintParamRst
 * @since 0.6.0
 */
void FlashViewer::StackInit()
{
	preStack.clear();
	nxtStack.clear();
	preStack.push(paintParam);
}

/**
 * @brief zoom in the flash viewer
 * @see wheelViewerDown
 * @since 0.2.0
 */
void FlashViewer::wheelViewerUp()
{
	paintParam.sublen++;
}

/**
 * @brief zoom out the flash viewer
 * @see wheelViewerUp
 * @since 0.2.0
 */
void FlashViewer::wheelViewerDown()
{
	if (paintParam.sublen > 2)
		paintParam.sublen--;
}

/**
 * @brief previous flash viewer
 * @see nxtViewer
 * @since 0.6.0
 */
void FlashViewer::preViewer()
{
	if (preStack.size() > 1)
	{
		paintParam = preStack.pop();
		nxtStack.push(paintParam);
		paintParam = preStack.top();
		this->repaint();
	}
}

/**
 * @brief next flash viewer
 * @see preViewer
 * @since 0.6.0
 */
void FlashViewer::nxtViewer()
{
	if (!nxtStack.isEmpty())
	{
		paintParam = nxtStack.pop();
		preStack.push(paintParam);
		this->repaint();
	}
}

/**
 * @brief according to the flashErrorInfo to paint the page square with red color
 * @param the Qt painter to draw the red square
 * @since 0.7.0
 */
void FlashViewer::paintFlashError(QPainter& painter)
{
	painter.setBrush(Qt::red);
	for (auto it = flashErrorVec.begin(); it != flashErrorVec.end(); ++it)
	{
		if (it->blockNum > currentFlash.blkCnt || it->pageNum > currentFlash.ppb)
		{
			QMessageBox* msg = new QMessageBox(QMessageBox::Critical, "Paint Error",
											   "the error infomation is not suitable for this flash");
			flashErrorVec.clear();
			paintErrorFlag = false;
			this->repaint();
			msg->exec();
			return;
		}
		int subUnitBlk = currentFlash.blkCnt / currentFlash.colNum / currentFlash.rowNum;
		int subUnitIndex = (it->blockNum) / subUnitBlk;
		int subUnitOffset = (it->blockNum) % subUnitBlk;
		int row = subUnitIndex / currentFlash.colNum;
		int col = subUnitIndex % currentFlash.colNum;
		int x = originX + col * spacew + (col * currentFlash.ppb + it->pageNum) * paintParam.sublen;
		int y = originY + row * spaceh + (row * subUnitBlk + subUnitOffset) * paintParam.sublen;
		painter.drawRect(x, y, paintParam.sublen, paintParam.sublen);
	}
}
