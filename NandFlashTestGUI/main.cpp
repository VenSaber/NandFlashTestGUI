#include "NandFlashTestGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NandFlashTestGUI w;
	w.show();
	return a.exec();
}
