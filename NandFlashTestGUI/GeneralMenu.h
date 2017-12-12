#pragma once
#include <QWidget>
#include "ui_GeneralMenu.h"

class GeneralMenu : public QWidget
{
	Q_OBJECT

public:
	GeneralMenu(QWidget *parent);
	~GeneralMenu();
private:
	Ui::GeneralMenuClass ui;
};
