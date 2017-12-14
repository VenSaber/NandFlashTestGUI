#include "GeneralMenu.h"
#include "AddWidget.h"
#include <qdebug.h>

GeneralMenu::GeneralMenu(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.addButton, &QPushButton::clicked, []() {
		auto widget = new AddWidget();
		widget->show();
	});
}
