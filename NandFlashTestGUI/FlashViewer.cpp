// TODO: ARBITRARY ANCHOR ZOOMIN AND ZOOMOUT
// TODO: RIGHT BUTTON CLICK, A MENU DIALOG
// TODO: THE RESET MENU: reset the flash image to the default position
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
	painterMoveX(0), painterMoveY(0), preMouseX(0), preMouseY(0), midButtonClick(false)
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

void FlashViewer::mouseMoveEvent(QMouseEvent * ev)
{
	if (midButtonClick)
	{
		painterMoveX = ev->pos().x() - preMouseX;
		painterMoveY = ev->pos().y() - preMouseY;
		this->repaint();
	}
}

void FlashViewer::mousePressEvent(QMouseEvent * ev)
{
	if (ev->button() == Qt::MidButton)
	{
		// be careful that the value of the painterMoveX 
		// and painterMoveY should be always continuous
		// so, we should minus painterMoveX and painterMoveY
		// to calculate the preMouseX and preMouseY
		preMouseX = ev->pos().x() - painterMoveX;
		preMouseY = ev->pos().y() - painterMoveY;
		midButtonClick = true;
	}
}

void FlashViewer::mouseReleaseEvent(QMouseEvent * ev)
{
	if (ev->button() == Qt::MidButton)
		midButtonClick = false;
}
