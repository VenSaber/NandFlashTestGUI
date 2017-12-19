#pragma once
#include <qwidget.h>
#include "GeneralMenu.h"

class FlashViewer : public QWidget 
{
	Q_OBJECT
public:
	FlashViewer(QWidget* parent = Q_NULLPTR, GeneralMenu* _controller = nullptr);
	~FlashViewer() = default;
	// get and set interface
	int		getMinWidth() { return minWidth; }
	int		getMinHeight() { return minHeight; }
	// normal interface 
	void	wheelViewerUp();
	void	wheelViewerDown();
protected:
	void	paintEvent(QPaintEvent* ev) override;
	void	wheelEvent(QWheelEvent* ev) override;
	void	mouseMoveEvent(QMouseEvent* ev) override;
private:
	GeneralMenu* controller;
	static Flash currentFlash;
	int minWidth;	 // the minmum viewer width 
	int minHeight;	 // the minmum viewer height
	double painterMoveX;
	double painterMoveY;
	double preMouseX;
	double preMouseY;
};
