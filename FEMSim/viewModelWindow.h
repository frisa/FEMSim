#pragma once
#include <QXmlStreamWriter>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QDomDocument>
#include <QTextStream>
#include <QtWidgets/QMainWindow>

#include "glWorldWidget.h"
#include "modelSolution.h"

#include "ui_view.h"
#include "modelSolution.h"

class ViewModelWindow : public QMainWindow
{
	Q_OBJECT
private:

public:
	ViewModelWindow(QWidget *parent = Q_NULLPTR);
	void LoadDefaultModel(QString sFilePath = "E:\default.fsm");
	void LoadModel(QString sFilePath);
	void SaveModel(QString sFilePath);
private:
	ModelSolution* solutionModel;
	Ui::FEMSimClass ui;

private slots:
	void OpenModel();
};
