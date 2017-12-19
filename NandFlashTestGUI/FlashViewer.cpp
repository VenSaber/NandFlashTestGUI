#include "FlashViewer.h"
#include <qlabel.h>
#include <qpainter.h>
#include <qevent.h>
#include <qdebug.h>

const int spacew = 10;
const int spaceh = 10;
static int sublen = 2;

Flash FlashViewer::currentFlash{"default", 2048, 64, 2, 8};

FlashViewer::FlashViewer(QWidget* parent, GeneralMenu* _controller)
	:QWidget(parent), controller(_controller),
	minWidth(spacew * (currentFlash.colNum + 1) + sublen * currentFlash.ppb * currentFlash.colNum),
	minHeight(spaceh * (currentFlash.rowNum + 1) + sublen * currentFlash.blkCnt / currentFlash.colNum),
	painterMoveX(0), painterMoveY(0), preMouseX(0), preMouseY(0)
{
	this->setMouseTracking(false);
	connect(controller, &GeneralMenu::FlashTypeChanged, [this](Flash& flash) {
		//qDebug() << "flash type changed";
		currentFlash = flash;
		this->repaint();
	});
}

void FlashViewer::wheelViewerUp()
{
	sublen++;
	this->repaint();
}

void FlashViewer::wheelViewerDown()
{
	if (sublen > 2)
	{ 
		sublen--;
		this->repaint();
	}
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
				painter.drawLine(spacew * (colIndex + 1) + currentFlash.ppb * sublen * colIndex + painterMoveX,
					spaceh * (rowIndex + 1) + sublen * (subrowCnt * rowIndex + subrow) + painterMoveY,
					spacew * (colIndex + 1) + currentFlash.ppb * sublen * (1 + colIndex) + painterMoveX,
					spaceh * (rowIndex + 1) + sublen * (subrowCnt * rowIndex + subrow) + painterMoveY);
			}
			for (auto subcol = 0; subcol <= currentFlash.ppb; ++subcol)
			{
				painter.drawLine(spacew * (colIndex + 1) + sublen * (currentFlash.ppb * colIndex + subcol) + painterMoveX,
					spaceh * (rowIndex + 1) + subrowCnt * sublen * rowIndex + painterMoveY,
					spacew * (colIndex + 1) + sublen * (currentFlash.ppb * colIndex + subcol) + painterMoveX,
					spaceh * (rowIndex + 1) + subrowCnt * sublen * (rowIndex + 1) + painterMoveY);
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
		else this->wheelViewerDown();
	}
}

// TODO: need a effective solution
void FlashViewer::mouseMoveEvent(QMouseEvent * ev)
{
	painterMoveX = ev->pos().rx() - preMouseX;
	painterMoveY = ev->pos().ry() - preMouseY;
	this->repaint();
	preMouseX = ev->pos().rx();
	preMouseY = ev->pos().ry();
}
