#include <QtWidgets/QApplication>
#include <QFile>
#include <QMessageBox>

#include "viewModelWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ViewModelWindow w;
	w.show();
	return a.exec();
}
