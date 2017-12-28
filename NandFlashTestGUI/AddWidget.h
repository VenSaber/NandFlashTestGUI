/**
 * @file		AddWidget.h
 * @author		ventury
 * @version		0.6.1
 * @note
 * **History**  
 *    data   |  version	 |             content
 * :--------:|:---------:|----------------------------------
 * 2017-12-11|0.1.0		 |construct the basic GUI
 * 2017-12-12|0.2.0		 |basic zoomIn and zoomOut
 * 2017-12-14|0.3.0	     |enable paint arbitrary flash
 * 2017-12-18|0.4.0		 |use MySQL to manage the flash type
 * 2017-12-19|0.4.1		 |fixed some bugs and optimizate code
 * 2017-12-20|0.5.0		 |enable move flash viewer and fixed bugs
 * 2017-12-23|0.6.0		 |add viewer reset func & prev/next viewer func
 * 2017-12-25|0.6.1		 |change to doxygen comment style
 * 2017-12-28|0.7.0		 |read test error file to show in the flash viewer
 */
#pragma once
#include <qwidget.h>
#include <qstring.h>
#include "ui_AddWidget.h"

/**
 * @class AddWidget [AddWidget.h]
 * @brief the dialog that use to input the flash type information.
 * @since 0.3.0
 */
class AddWidget : public QWidget
{
	Q_OBJECT
public:
	/**@brief the constructure function*/
	AddWidget(QWidget* parent = Q_NULLPTR);
	/**@brief default destructure function*/
	~AddWidget() = default;
signals:
	/**@brief signal to emit name to the flash table*/
	void NoticeMenu(const QString& name);
protected:
	/**@brief rewrite the close event to re-init the addWidget and hide the widget.*/
	void closeEvent(QCloseEvent* ev) override;
private:
	/**@brief get all information that AddWidget contain.*/
	QVector<QString> getWidgetInfo();
private:
	Ui::AddWidgetClass ui; /*!> the ui class that descript this class*/
};

