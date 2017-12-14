#pragma once
#include <qwidget.h>
#include "AddWidget.h"

class FlashViewer : public QWidget 
{
	Q_OBJECT
public:
	FlashViewer(QWidget* parent = Q_NULLPTR);
	~FlashViewer() = default;
	// Qt Event function
	void	paintEvent(QPaintEvent* ev) override;
	// get and set interface
	int		getMinWidth() { return minWidth; }
	int		getMinHeight() { return minHeight; }
	// normal interface 
	void	wheelViewerUp();
	void	wheelViewerDown();

	static void setCurrentFlash(Flash myflash) 
	{ currentFlash = myflash; };
private:
	static Flash currentFlash;
	int minWidth;	 // the minmum viewer width 
	int minHeight;	 // the minmum viewer height
};
