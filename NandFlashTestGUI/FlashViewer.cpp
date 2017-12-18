#include "FlashViewer.h"
#include <qlabel.h>
#include <qpainter.h>
#include <qevent.h>
#include <qdebug.h>

const int spacew = 10;
const int spaceh = 10;
static int sublen = 2;

Flash FlashViewer::currentFlash{"default", 2048, 64, 2, 8};

FlashViewer::FlashViewer(QWidget* parent) :QWidget(parent),
	minWidth(spacew * (currentFlash.colNum + 1) + sublen * currentFlash.ppb * currentFlash.colNum),
	minHeight(spaceh * (currentFlash.rowNum + 1) + sublen * currentFlash.blkCnt / currentFlash.colNum)
{
	connect(controller, &GeneralMenu::FlashTypeChanged, [this](Flash& flash) {
		//currentFlash = flash;
		//this->repaint();
		qDebug() << "flash type changed";
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
				painter.drawLine(spacew * (colIndex + 1) + currentFlash.ppb * sublen * colIndex,
					spaceh * (rowIndex + 1) + sublen * (subrowCnt * rowIndex + subrow),
					spacew * (colIndex + 1) + currentFlash.ppb * sublen * (1 + colIndex),
					spaceh * (rowIndex + 1) + sublen * (subrowCnt * rowIndex + subrow));
			}
			for (auto subcol = 0; subcol <= currentFlash.ppb; ++subcol)
			{
				painter.drawLine(spacew * (colIndex + 1) + sublen * (currentFlash.ppb * colIndex + subcol),
					spaceh * (rowIndex + 1) + subrowCnt * sublen * rowIndex,
					spacew * (colIndex + 1) + sublen * (currentFlash.ppb * colIndex + subcol),
					spaceh * (rowIndex + 1) + subrowCnt * sublen * (rowIndex + 1));
			}
		}
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