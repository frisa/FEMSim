#pragma once

#include "Assembly.h"
#include <QtWidgets/QMainWindow>
#include "ui_FEMSim.h"
#include "SolutionModel.h"

class FEMSim : public QMainWindow
{
	Q_OBJECT
private:

public:
	FEMSim(QWidget *parent = Q_NULLPTR);
	void Test();
	void LoadDefaultModel(QString sFilePath = "E:\default.fsm");
	void LoadModel(QString sFilePath);
	void SaveModel(QString sFilePath);

private:
	Assembly* assemblyModel;
	SolutionModel* solutionModel;
	Ui::FEMSimClass ui;

private slots:
	void OpenModel();
};
