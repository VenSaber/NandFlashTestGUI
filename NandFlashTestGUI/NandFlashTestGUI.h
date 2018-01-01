/** 
 * @file		NandFlashTestGUI.h
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
 * 2017-12-28|0.7.0		 |read test error file to show in the flash viewer
 * 2018-01-01|0.8.0		 |the text edit will input detail when double clicked the error page
 */
#pragma once
#include <QtWidgets/QMainWindow>
#include <qtextedit.h>
#include "FlashViewer.h"
#include "GeneralMenu.h"
#include "FlashErrorInfo.h"
#include "ui_NandFlashTestGUI.h"

/**
 * @class NandFlashTestGUI [NandFlashTestGUI.h]
 * @brief This class is the main window class. 
 * @author ventury
 * @since 0.1.0
 */
class NandFlashTestGUI : public QMainWindow
{
	Q_OBJECT
public:
	/**@brief the constructure function.*/
	NandFlashTestGUI(QWidget *parent = Q_NULLPTR);
	/**@brief the default destructure function.*/
	~NandFlashTestGUI() = default;
signals:
	/**@brief sent the error information to the flash viewer*/
	void SendFlashErrorInfo(QVector<FlashErrorInfo>& flashErrorVec);
protected:
	/**@brief draw a red line to draw a border line. */
	void paintEvent(QPaintEvent* ev) override;
	/**@brief call the keyPressEvent of the Flashviewer class. */
	void keyPressEvent(QKeyEvent* ev) override;
	/**@brief when the main window size changed, the proportion would not change. */
	void resizeEvent(QResizeEvent* ev) override;
private:
	/**@brief setting the file menu. */
	void FileMenuInit();
	/**@brief save the flash read write error information from the string file*/
	void SaveStringErrorInfo(const QString& filename);
	/**@brief save the flash read write error information from the digital file*/
	void SaveDigitalErrorInfo(const QString& filename);
private:
	// Containers
	Ui::NandFlashTestGUIClass ui; /*!> main window GUI description class */
	GeneralMenu* genWindow = nullptr;/*!> general controller sub-window */
	QTextEdit* infoEdit = nullptr; /*!> error information inputing sub-window */
	FlashViewer* viewer = nullptr; /*!> flash page unit viewer sub-window */
	QMenu* menuOpen = nullptr; /*!> open menu as the child menu of the File menu */
	QAction* actionErrorString = nullptr;/*!> open error string file action in the open menu */
	QAction* actionPureDigital = nullptr;/*!> open pure digital file action in the open menu */
};

