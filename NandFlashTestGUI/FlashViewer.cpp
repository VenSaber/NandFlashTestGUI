#include "FlashViewer.h"
#include <qlabel.h>
#include <qpainter.h>
#include <qevent.h>
#include <qdebug.h>

#define HORIZONTAL_SQUARE	 64
#define VERTICAL_SQUARE		 128

const int spacew = 10;
const int spaceh = 10;
const int sublen = 2;


FlashViewer::FlashViewer(QWidget* parent)
	:QWidget(parent),
	minWidth(spacew * 9 + sublen * HORIZONTAL_SQUARE * 8),
	minHeight(spaceh * 3 + sublen * VERTICAL_SQUARE * 2)
{
}


FlashViewer::~FlashViewer()
{
}

void FlashViewer::paintEvent(QPaintEvent * ev)
{
	QPainter painter(this);
	for (auto rowIndex = 0; rowIndex < 2; ++rowIndex)
		for (auto colIndex = 0; colIndex < 8; ++colIndex)
		{
			for (auto subrow = 0; subrow <= 128; ++subrow)
			{
				painter.drawLine(spacew * (colIndex + 1) + 64 * sublen * colIndex,
					spaceh * (rowIndex + 1) + 128 * sublen * rowIndex + sublen * subrow,
					spacew * (colIndex + 1) + 64 * sublen + 64 * sublen * colIndex,
					spaceh * (rowIndex + 1) + 128 * sublen * rowIndex + sublen * subrow);
			}
			for (auto subcol = 0; subcol <= 64; ++subcol)
			{
				painter.drawLine(spacew * (colIndex + 1) + 64 * sublen * colIndex + sublen * subcol,
					spaceh * (rowIndex + 1) + 128 * sublen * rowIndex,
					spacew * (colIndex + 1) + 64 * sublen * colIndex + sublen * subcol,
					spaceh * (rowIndex + 1) + 128 * sublen * rowIndex + 128 * sublen);
			}
		}
}

void FlashViewer::wheelEvent(QWheelEvent* ev)
{
	//auto delta = ev->delta();
	//this->scale(delta, delta);
	// get the point that the mouce point
	QPoint& pt = ev->pos();
	qDebug() << "(" << pt.x() << ", " << pt.y() << ")\n";
}
