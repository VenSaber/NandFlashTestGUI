#pragma once
#include <qwidget.h>
#include "GeneralMenu.h"

class FlashViewer : public QWidget 
{
	Q_OBJECT
public:
	FlashViewer(QWidget* parent = Q_NULLPTR, GeneralMenu* _controller = nullptr);
	~FlashViewer() = default;
	// normal interface 
	void	wheelViewerUp();
	void	wheelViewerDown();
protected:
	void	paintEvent(QPaintEvent* ev) override;
	void	wheelEvent(QWheelEvent* ev) override;
	void	mouseMoveEvent(QMouseEvent* ev) override;
	void	mousePressEvent(QMouseEvent* ev) override;
	void	mouseReleaseEvent(QMouseEvent* ev) override;
private:
	GeneralMenu* controller;
	static Flash currentFlash;
	double painterMoveX;
	double painterMoveY;
	double preMouseX;
	double preMouseY;
	bool midButtonClick;
};
