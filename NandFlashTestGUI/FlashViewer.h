#pragma once
#include <qwidget.h>

class FlashViewer : public QWidget 
{
	Q_OBJECT
public:
	FlashViewer(QWidget* parent = Q_NULLPTR);
	~FlashViewer();
	void paintEvent(QPaintEvent* ev) override;
	void wheelEvent(QWheelEvent* ev) override;

	int getMinWidth() { return minWidth; }
	int getMinHeight() { return minHeight; }
private:
	int minWidth;
	int minHeight;
};

