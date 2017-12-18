#pragma once
#include <qwidget.h>
#include "GeneralMenu.h"

class FlashViewer : public QWidget 
{
	Q_OBJECT
public:
	FlashViewer(QWidget* parent = Q_NULLPTR);
	~FlashViewer() = default;
	// get and set interface
	int		getMinWidth() { return minWidth; }
	int		getMinHeight() { return minHeight; }
	void	setController(GeneralMenu* _controller)
	{ controller = _controller; }
	// normal interface 
	void	wheelViewerUp();
	void	wheelViewerDown();
protected:
	void	paintEvent(QPaintEvent* ev) override;
private:
	GeneralMenu* controller = nullptr;
	static Flash currentFlash;
	int minWidth;	 // the minmum viewer width 
	int minHeight;	 // the minmum viewer height
};
