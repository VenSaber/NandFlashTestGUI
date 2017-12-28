/**
 * @file		NandFlashTestGUI.cpp
 * @author		ventury
 * @version		0.6.1
 */
/**
 * @todo USE THE FLASHERRORVEC TO PAINT THE FLASH VIEWER
 */
#include <qevent.h>
#include <qpainter.h>
#include <qbrush.h>
#include <qmenu.h>
#include <qfiledialog.h>
#include <qfile.h>
#include <qdebug.h>
#include "NandFlashTestGUI.h"

/**@brief standard width*/
#define		STD_WIDTH		1280
/**@brief standard height*/
#define		STD_HEIGHT		720
/**@brief menu bar height*/
#define		MENU_HEIGHT		40
/**@brief subwindow remain space*/
#define		REMAIN_SPACE	5

/**@brief the border factor between *genWindow* and *viewer* */
const double vWidthFac = 0.88; 
/**@brief the border factor between *viewer* and *infoEdit* */
const double vHeightFac = 0.81;

/**
 * @brief the constructure function.
 * @param parent this parameter is the parent of this class
 * @since 0.1.0
 */
NandFlashTestGUI::NandFlashTestGUI(QWidget *parent)
	: QMainWindow(parent), genWindow(new GeneralMenu(this)),
	viewer(new FlashViewer(this, genWindow)), infoEdit(new QTextEdit(this)) 
{
	ui.setupUi(this);
	this->size().setWidth(STD_WIDTH);
	this->size().setHeight(STD_HEIGHT);
	this->setMinimumSize(STD_WIDTH, STD_HEIGHT);

	FileMenuInit();

	// set the general menu window
	genWindow->setGeometry(0, MENU_HEIGHT,
						   size().width() * (1 - vWidthFac), 
						   size().height() - MENU_HEIGHT);
	genWindow->raise();
	genWindow->show();

	// set the flash viewer
	viewer->setGeometry(STD_WIDTH * (1 - vWidthFac), MENU_HEIGHT,
						STD_WIDTH * vWidthFac - REMAIN_SPACE,
						STD_HEIGHT * vHeightFac - MENU_HEIGHT);
	viewer->raise();
	viewer->show();

	// set the infomation text editor
	infoEdit->setGeometry(STD_WIDTH * (1 - vWidthFac), 
						  STD_HEIGHT * vHeightFac + 1,
						  STD_WIDTH * vWidthFac - REMAIN_SPACE + 1, 
						  STD_HEIGHT * (1 - vHeightFac)- 2);
	infoEdit->setReadOnly(true);
	infoEdit->show();

}

/**
 * @brief draw a red line to draw a border line. 
 * @param ev Qt paint event pointer
 * @since 0.1.0
 */
void NandFlashTestGUI::paintEvent(QPaintEvent * ev)
{
	QPainter painter(this);
	painter.setPen(QColor{ 255, 0, 0 });
	painter.drawRect(size().width() * (1 - vWidthFac), MENU_HEIGHT,
					 size().width() * vWidthFac - REMAIN_SPACE, 
					 size().height() * vHeightFac);
}

/**
 * @brief call the keyPressEvent of the Flashviewer class.
 * @param ev Qt key press event pointer
 * @since 0.6.0
 */
void NandFlashTestGUI::keyPressEvent(QKeyEvent * ev)
{
	viewer->keyPressEvent(ev);
}

/**
 * @brief when the main window size changed, the proportion would not change. 
 * @param ev Qt resize event pointer
 * @since 0.1.0
 */
void NandFlashTestGUI::resizeEvent(QResizeEvent * ev)
{
	// reset the main window with the fixed factor
	viewer->setGeometry(size().width() * (1 - vWidthFac), MENU_HEIGHT,
						size().width() * vWidthFac - REMAIN_SPACE, 
						size().height() * vHeightFac - MENU_HEIGHT);
	infoEdit->setGeometry(size().width() * (1 - vWidthFac), 
						  size().height() * vHeightFac + 2,
						  size().width() * vWidthFac - REMAIN_SPACE + 1, 
						  size().height() * (1 - vHeightFac) - 1);
	genWindow->setGeometry(0, MENU_HEIGHT,
						   size().width() * (1 - vWidthFac), 
						   size().height() - MENU_HEIGHT);
}

/**
 * @brief setting the file menu.
 * @since 0.6.1
 */
void NandFlashTestGUI::FileMenuInit()
{
	menuOpen = new QMenu("Open", this);
	actionErrorString = new QAction("Error String", this);
	connect(actionErrorString, &QAction::triggered, [this]() {
		auto filename = QFileDialog::getOpenFileName(this,
			 "Open File", "C:/", "Error String File(*.esf)");
		SaveStringErrorInfo(filename);
	});
	actionPureDigital = new QAction("Pure Digital", this);
	connect(actionPureDigital, &QAction::triggered, [this]() {
		auto filename = QFileDialog::getOpenFileName(this,
			 "Open File", "C:/", "Pure Digital File(*.pd)");
		SaveDigitalErrorInfo(filename);
	});
	menuOpen->addAction(actionErrorString);
	menuOpen->addAction(actionPureDigital);
	ui.menuFile->addMenu(menuOpen);
}

/**
 * @brief send the flash read write error information from the string file to the FlashViewer
 * @param filename the name of the Error String File (*.esp)
 * @since 0.7.0
 */
void NandFlashTestGUI::SaveStringErrorInfo(const QString& filename)
{		
	QFile espFile(filename);
	if (!espFile.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QTextStream in(&espFile);
	QString line = in.readLine();
	QVector<FlashErrorInfo> flashErrorVec;
	while (!line.isNull())
	{
		if (line.contains("Check Error"))
		{
			// deal with the first line
			// be careful that this code delete the matching string
			// so, do not write \d, you should write \D
			QStringList firstLineInfo = line.split(QRegExp("\\D"), QString::SkipEmptyParts);
			quint16 blkNum = firstLineInfo.at(0).toShort();
			quint16 pgeNum = firstLineInfo.at(1).toShort();
			quint16 bteNum = firstLineInfo.at(2).toShort();

			// jump to and deal with the second line
			line = in.readLine(); 
			QStringList secondLineInfo = line.split(" ");
			QString cDataStr = secondLineInfo.at(secondLineInfo.size() - 1);
			cDataStr = cDataStr.remove(0, 2);
			QByteArray cData = QByteArray::fromHex(cDataStr.toLocal8Bit());

			// jump to and deal with the third line
			line = in.readLine();
			QStringList thirdLineInfo = line.split(" ");
			QString eDataStr = thirdLineInfo.at(thirdLineInfo.size() - 1);
			eDataStr = eDataStr.remove(0, 2);
			QByteArray eData = QByteArray::fromHex(eDataStr.toLocal8Bit());
				
			// jump to and deal with the forth line
			line = in.readLine();
			QStringList forthLineInfo = line.split(" ");
			QString xDataStr = forthLineInfo.at(forthLineInfo.size() - 1);
			xDataStr = xDataStr.remove(0, 2);
			QByteArray xData = QByteArray::fromHex(xDataStr.toLocal8Bit());

			flashErrorVec.push_back(FlashErrorInfo{blkNum, pgeNum, bteNum,
				cData, eData, xData});
		}
		line = in.readLine();
	}
	emit SendFlashErrorInfo(flashErrorVec);
	espFile.close();
}

/**
 * @brief send the flash read write error information from the digital file to the FlashViewer
 * @param filename the name of the Pure Digital File (*.df)
 * @since 0.7.0
 */
void NandFlashTestGUI::SaveDigitalErrorInfo(const QString & filename)
{
	QFile dfFile(filename);
	if (!dfFile.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QTextStream in(&dfFile);
	QString line = in.readLine();
	QVector<FlashErrorInfo> flashErrorVec;
	while (!line.isNull())
	{
		QStringList effectiveData = line.split(QRegExp(" "), QString::SkipEmptyParts);
		QVector<quint16> flashInfo;
		QVector<QByteArray> dataInfo;
		for (auto i = 0; i < effectiveData.size(); ++i)
		{
			if (i < 3)
				flashInfo.push_back(effectiveData.at(i).toShort());
			else
			{
				QString temp = effectiveData.at(i);
				temp = temp.remove(0, 2);
				QByteArray data = QByteArray::fromHex(temp.toLocal8Bit());
				dataInfo.push_back(data);
			}
		}
		flashErrorVec.push_back(FlashErrorInfo{flashInfo[0], flashInfo[1], flashInfo[2],
			dataInfo[0], dataInfo[1], dataInfo[2]});
		line = in.readLine();
	}
	emit SendFlashErrorInfo(flashErrorVec);
	dfFile.close();
}