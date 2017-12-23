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
	~NandFlashTestGUI() = default;
protected:
	void paintEvent(QPaintEvent* ev) override;
	void keyPressEvent(QKeyEvent* ev) override;
	void resizeEvent(QResizeEvent* ev) override;
private:
	// Containers
	Ui::NandFlashTestGUIClass ui;
	GeneralMenu* genWindow = nullptr;
	FlashViewer* viewer = nullptr;
	QTextEdit* infoEdit = nullptr;
};

