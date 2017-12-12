#pragma once
#include <qwidget.h>

class FlashViewer : public QWidget 
{
	Q_OBJECT
public:
	FlashViewer(QWidget* parent = Q_NULLPTR);
	~FlashViewer();
	void paintEvent(QPaintEvent* ev) override;

	int getMinWidth() { return minWidth; }
	int getMinHeight() { return minHeight; }

	void wheelViewerUp();
	void wheelViewerDown();
private:
	int minWidth;
	int minHeight;
};

