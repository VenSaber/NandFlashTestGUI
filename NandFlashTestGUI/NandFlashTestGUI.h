#pragma once

#include <QtWidgets/QMainWindow>
#include <qtextedit.h>
#include "FlashViewer.h"
#include "GeneralMenu.h"
#include "ui_NandFlashTestGUI.h"

class NandFlashTestGUI : public QMainWindow
{
	Q_OBJECT
public:
	NandFlashTestGUI(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent* ev) override;
	void resizeEvent(QResizeEvent* ev) override;
	void wheelEvent(QWheelEvent* ev) override;
private:
	// Containers
	Ui::NandFlashTestGUIClass ui;
	FlashViewer* viewer = nullptr;
	GeneralMenu* genWindow = nullptr;
	QTextEdit* infoEdit = nullptr;
};

