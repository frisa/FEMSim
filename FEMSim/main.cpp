#include <QtWidgets/QApplication>
#include <QFile>
#include <QMessageBox>

#include "viewModelWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ViewModelWindow w;
	QString sStyle;
	//QFile fStyleSheet(":/StyleSheet/Resources/StyleSheets/Style.css");
	QFile fStyleSheet("e:\\_git\\FEMSim\\FEMSim\\Resources\\StyleSheets\\Style.css");

	fStyleSheet.open(QFile::ReadOnly);
	sStyle = fStyleSheet.readAll();
	a.setStyleSheet(sStyle);
	fStyleSheet.close();

	w.show();
	return a.exec();
}
