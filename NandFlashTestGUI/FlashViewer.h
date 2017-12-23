#pragma once
#include <qwidget.h>
#include <qstack.h>
#include "GeneralMenu.h"

struct PaintParam
{
	int MoveX;
	int MoveY;
	int preMouseX;
	int preMouseY;
	int sublen;
};

class FlashViewer : public QWidget 
{
	Q_OBJECT
public:
	FlashViewer(QWidget* parent = Q_NULLPTR, GeneralMenu* _controller = nullptr);
	~FlashViewer() = default;
	// set this event public to make main window call this func
	void	keyPressEvent(QKeyEvent* ev) override;
protected: // event virtual function
	void	paintEvent(QPaintEvent* ev) override;
	void	wheelEvent(QWheelEvent* ev) override;
	void	mouseMoveEvent(QMouseEvent* ev) override;
	void	mousePressEvent(QMouseEvent* ev) override;
	void	mouseReleaseEvent(QMouseEvent* ev) override;
private:
	void	MenuInit();	// init the menu that right button triggered
	void	PaintParamRst(); // reset the painting parameter
	void	StackInit();
	void	wheelViewerUp();
	void	wheelViewerDown();
	void	preViewer();
	void	nxtViewer();
private:
	static Flash currentFlash;
	// Control
	GeneralMenu* controller;
	QMenu* rbtMenu = nullptr;
	QAction* resetAction = nullptr;
	// Mouse Moving Flag
	bool midButtonClick;
	PaintParam paintParam;
	QStack<PaintParam> preStack;
	QStack<PaintParam> nxtStack;
};
