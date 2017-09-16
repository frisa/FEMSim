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
#include "utilLoggerSingleton.h"

class ViewModelWindow : public QMainWindow, public UtilAbstractLoggedClass
{
	Q_OBJECT
private:
	int m_SolutionOutputId = 0;
	int m_ModelOutputId = 0;
	ModelSolution* solutionModel;
	Ui::FEMSimClass ui;
	UtilLoggerSingleton* lg;


public:
	ViewModelWindow(QWidget *parent = Q_NULLPTR);
	void LoadDefaultModel(QString sFilePath = "E:\default.fsm");
	void LoadModel(QString sFilePath);
	void SaveModel(QString sFilePath);

private slots:
	void OpenModel();
};
