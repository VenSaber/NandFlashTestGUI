#include <QtWidgets/QApplication>
#include "NandFlashTestGUI.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NandFlashTestGUI w;
	w.show();
	return a.exec();
}
