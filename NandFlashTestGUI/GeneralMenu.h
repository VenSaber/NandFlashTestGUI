/**
 * @file		GeneralMenu.h
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
 * 2017-12-19|0.4.1		 |fixed some bugs & optimizate code
 * 2017-12-20|0.5.0		 |enable move flash viewer & fixed bugs
 * 2017-12-23|0.6.0		 |add viewer reset func & prev/next viewer func
 * 2017-12-25|0.6.1		 |change to doxygen comment style
 */
#pragma once
#include <QWidget>
#include "FlashTypeTable.h"
#include "ui_GeneralMenu.h"

/**
 * @struct Flash [GeneralMenu.h]
 * @brief this structure contain the data information of the flash type.
 * @author ventury
 * @since 0.4.0
 */
struct Flash
{
public:
	/**
	 * @brief this function is operation overloading.
	 * @param rhs Flash value that would be assigned.
	 * @since 0.4.0
	 */
	void operator= (Flash& rhs)
	{
		name = rhs.name;
		blkCnt = rhs.blkCnt;
		ppb = rhs.ppb;
		rowNum = rhs.rowNum;
		colNum = rhs.colNum;
	}

public:
	QString name; /*!> flash type name*/  
	int		blkCnt; /*!> block count*/
	int		ppb; /*!> pages per block*/
	int		rowNum; /*!> row number that we paint flash*/
	int		colNum; /*!> colomn number that we paint flash*/
};

/**
 * @class GeneralMenu [GeneralMenu.h]
 * @brief this function
 * @since 0.2.0
 */
class GeneralMenu : public QWidget
{
	Q_OBJECT
public:
	/**@brief the constructure function*/
	GeneralMenu(QWidget *parent);
	/**@brief default destructure function*/
	~GeneralMenu() = default;
signals:
	/**@brief the signal would be emitted when flash type changed.*/
	void FlashTypeChanged(Flash& flash);
private slots:
	/**@brief the function that happen when double clicked the flash table item.*/
	void DoubleClickProcess();
	/**@brief add a new line in the flash table and fill the specified name.*/
	void AddNewLine(const QString& name);
	/**@brief the function that happen when delete button is clicked.*/
	void DeleteProcess();
private:
	/**@brief initialize the flash Table.*/
	void FlashTableInit();
private:
	Ui::GeneralMenuClass ui; /*!> the ui class that descript this class.*/
	int selectRow; /*!> the current row using in the DoubleClickProcess function*/
	FlashTypeTable* flashTable; /*!> the flash table class*/
	QTableWidgetItem* selectSign; /*!> the selected item with the 'O' sign*/
};
