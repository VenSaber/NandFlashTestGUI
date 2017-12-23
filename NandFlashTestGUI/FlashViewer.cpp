// TODO: ARBITRARY ANCHOR ZOOMIN AND ZOOMOUT
#include <qlabel.h>
#include <qpainter.h>
#include <qevent.h>
#include <qmenu.h>
#include <qaction.h>
#include <qdebug.h>
#include "FlashViewer.h"

const int spacew = 10;
const int spaceh = 10;

Flash FlashViewer::currentFlash{"default", 2048, 64, 2, 8};

FlashViewer::FlashViewer(QWidget* parent, GeneralMenu* _controller)
	:QWidget(parent), controller(_controller), midButtonClick(false)
{
	MenuInit();
	// watch out! PaintParamRst function must appear firstly and StackInit secondly
	PaintParamRst();
	StackInit();
	this->setMouseTracking(false);
	connect(controller, &GeneralMenu::FlashTypeChanged, [this](Flash& flash) {
		currentFlash = flash;
		PaintParamRst();
		StackInit();
		this->repaint();
	});
}

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
}

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

void FlashViewer::mouseMoveEvent(QMouseEvent * ev)
{
	if (midButtonClick)
	{
		paintParam.MoveX = ev->pos().x() - paintParam.preMouseX;
		paintParam.MoveY = ev->pos().y() - paintParam.preMouseY;
		this->repaint();
	}
}

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

void FlashViewer::PaintParamRst()
{	
	paintParam = { 0, 0, 0, 0, 2 };
}

void FlashViewer::StackInit()
{
	preStack.clear();
	nxtStack.clear();
	qDebug() << paintParam.MoveX << ", " << paintParam.MoveY << ", "
		<< paintParam.preMouseX << ", " << paintParam.preMouseY << ", " << paintParam.sublen;
	preStack.push(paintParam);
}

void FlashViewer::wheelViewerUp()
{
	paintParam.sublen++;
}

void FlashViewer::wheelViewerDown()
{
	if (paintParam.sublen > 2)
		paintParam.sublen--;
}

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

void FlashViewer::nxtViewer()
{
	if (!nxtStack.isEmpty())
	{
		paintParam = nxtStack.pop();
		preStack.push(paintParam);
		this->repaint();
	}
}
