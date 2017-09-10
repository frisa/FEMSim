#include "FEMSim.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include <Assembly.h>
#include <QMessageBox>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FEMSim w;
	w.show();


	return a.exec();
}
