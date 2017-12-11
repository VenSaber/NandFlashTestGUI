#pragma once

#include <QtWidgets/QMainWindow>
#include <qtextedit.h>
#include "FlashViewer.h"
#include "ui_NandFlashTestGUI.h"

class NandFlashTestGUI : public QMainWindow
{
	Q_OBJECT
public:
	NandFlashTestGUI(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent* ev) override;
	void resizeEvent(QResizeEvent* ev) override;
private:
	// Containers
	Ui::NandFlashTestGUIClass ui;
	FlashViewer* viewer = nullptr;
	QTextEdit* infoEdit = nullptr;

	// attribute
	double flashViewW;
};

