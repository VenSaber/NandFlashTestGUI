/**
 * @file		FlashViewer.h
 * @author		ventury
 * @version		0.6.1
 * @details		block count and page count should begin with 1
 *				block number first from left to right
 *				then from top to buttom
 * @note
 * **History**  
 *    data   |  version	 |             content
 * :--------:|:---------:|----------------------------------
 * 2017-12-11|0.1.0		 |construct the basic GUI
 * 2017-12-12|0.2.0		 |basic zoomIn and zoomOut
 * 2017-12-14|0.3.0	     |enable paint arbitrary flash
 * 2017-12-18|0.4.0		 |use MySQL to manage the flash type
 * 2017-12-19|0.4.1		 |fixed some bugs & optimizate code
 * 2017-12-20|0.5.0		 |enable move flash viewer & fixed bugs
 * 2017-12-23|0.6.0		 |add viewer reset func & prev/next viewer func
 * 2017-12-25|0.6.1		 |change to doxygen comment style
 * 2017-12-28|0.7.0		 |read test error file to show in the flash viewer
 * 2018-01-01|0.8.0		 |the text edit will input detail when double clicked the error page
 */
#pragma once
#include <qwidget.h>
#include <qstack.h>
#include <qtextedit.h>
#include "GeneralMenu.h"
#include "FlashErrorInfo.h"

/**
 * @struct PaintParam [FlashViewer.h]
 * @brief encapsulate the painting parameter
 * @author ventury
 * @since 0.6.0
 */
struct PaintParam
{
	int MoveX; /*!> the width that mouse midbutton move*/
	int MoveY; /**! the height that mouse midbutton move*/
	int preMouseX; /*!> the previous width that midbutton move*/
	int preMouseY; /*!> the previous height that midbutton move*/
	int sublen; /*!> the page square side length*/
};

/**
 * @class FlashViewer [FlashViewer.h]
 * @brief this class contain the flash viewer and the operation on the viewer.
 * @author ventury
 * @since 0.1.0
 */
class FlashViewer : public QWidget 
{
	Q_OBJECT
public:
	/**@brief the constructure function*/
	FlashViewer(QWidget* parent = Q_NULLPTR, GeneralMenu* _controller = nullptr, QTextEdit* _infoEdit = nullptr);
	/**@brief the default destructure function.*/
	~FlashViewer() = default;
	/**@brief previous/next viewer function that keyboard trigger*/
	void keyPressEvent(QKeyEvent* ev) override;
signals:
	/**@brief sent to infoEdit when double clicked the page square*/
	void doublePageClick(QVector<FlashErrorInfo> flasherror);
protected: // event virtual function
	/**@brief paint the flash viewer (basic unit : page)*/
	void paintEvent(QPaintEvent* ev) override;
	/**@brief zoomIn and zoomOut function that mouse wheel trigger*/
	void wheelEvent(QWheelEvent* ev) override;
	/**@brief move the viewer according to the mouse middle button moving path*/
	void mouseMoveEvent(QMouseEvent* ev) override;
	/**@brief the start point that the viewer move and menu execute when right button click*/
	void mousePressEvent(QMouseEvent* ev) override;
	/**@brief the end point that the viewer move*/
	void mouseReleaseEvent(QMouseEvent* ev) override;
	void mouseDoubleClickEvent(QMouseEvent* ev) override;
private:
	/**@brief init the menu that right button triggered*/
	void MenuInit();
	/**@brief reset the painting parameter*/
	void PaintParamRst(); 
	/**@brief initialize the stack that use to save viewer*/
	void StackInit();
	/**@brief zoom in the flash viewer*/
	void wheelViewerUp();
	/**@brief zoom out the flash viewer*/
	void wheelViewerDown();
	/**@brief previous flash viewer*/
	void preViewer();
	/**@brief next flash viewer*/
	void nxtViewer();
	/**@brief according to the flashErrorInfo to paint the page square with red color*/
	void paintFlashError(QPainter& painter);
private:
	static Flash currentFlash; /*!> current flash information **static***/
	GeneralMenu* controller; /*!> the general menu widget class*/
	QTextEdit* infoEdit;
	QMenu* rbtMenu = nullptr; /*!> the menu class that right button trigger*/
	QAction* resetAction = nullptr; /*!> reset action in the right button menu*/
	bool midButtonClick; /*!> Mouse Moving Flag*/
	PaintParam paintParam; /*!> the parameter that determine the location of the flash viewer*/
	QStack<PaintParam> preStack; /*!> the stack contain previous viewer*/
	QStack<PaintParam> nxtStack; /*!> the stack contain next viewer*/
	int originX; /*!> the x-coordinate left-top origin point*/
	int originY; /*!> the y-coordinate left-top origin point*/
	QVector<FlashErrorInfo> flashErrorVec; /*!> flash error information vector*/
	bool paintErrorFlag; /*!> the flag whether should paint flash error*/
};
