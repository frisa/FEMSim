#include "FEMSim.h"

#include <QXmlStreamWriter>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QDomDocument>
#include <QTextStream>

#include "SolutionModel.h"
#include "QtModelWidget.h"

using namespace std;


FEMSim::FEMSim(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//ui.ModelGLWidget = new QtModelWidget();

	/* Initialize connection */
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(OpenModel()));

	FEMSim::LoadDefaultModel();
}

void FEMSim::Test()
{
	vector<int> pInts;
	
}

void FEMSim::LoadDefaultModel(QString sFilePath)
{
	QDomProcessingInstruction domHeader;
	QDomDocument *domDocument = new QDomDocument();

	QDomElement domRootSolutionElement;
	QDomElement domProjectElement;
	QDomElement domModelElement;
	QDomElement domCubeElement;

	QDomNodeList domNodeList;
	QDomText	domText;

	/* Initialize default solution file */
	QString sSolutionFile = QStringLiteral("E:\\solution.xml");
	QFile *fSolutionFile;

	solutionModel = new SolutionModel(*domDocument, this);
	fSolutionFile = new QFile(sSolutionFile);

	if (!fSolutionFile->exists())
	{
		qDebug("[%s] File %s does not exist and will be created", __FUNCTION__, sSolutionFile.toLatin1().constData());
	}
	else
	{
		qDebug("[%s] File %s does exist", __FUNCTION__, sSolutionFile.toLatin1().constData());
	}

	if (fSolutionFile->isOpen())
	{
		qDebug("[%s] File %s was opened, try to close");
		fSolutionFile->close();
	}

	if (fSolutionFile->open(QIODevice::WriteOnly | QIODevice::Text))
	{
		//domHeader = domDocument->createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
		//domDocument->appendChild(domHeader);
		domRootSolutionElement = domDocument->createElement("solution");
		domRootSolutionElement.setAttribute("name", "DefaultSolution");
		domDocument->appendChild(domRootSolutionElement);

		domProjectElement = domDocument->createElement("project");
		domProjectElement.setAttribute("name", "DefaultProject1");
		domRootSolutionElement.appendChild(domProjectElement);
		
		domModelElement = domDocument->createElement("model");
		domModelElement.setAttribute("name", "DefaultModel1");
		domProjectElement.appendChild(domModelElement);

		domCubeElement = domDocument->createElement("part");
		domCubeElement.setAttribute("name", "Cube1");
		domCubeElement.setAttribute("x", "10");
		domCubeElement.setAttribute("y", "20");
		domModelElement.appendChild(domCubeElement);

		fSolutionFile->write(domDocument->toByteArray());
		fSolutionFile->close();
	}

	/* The default solution file will be printed to the debug window */
	if (fSolutionFile->open(QIODevice::ReadOnly | QIODevice::Text))
	{
		int iNodesCnt = 0;
		int iIdx = 0;

		domDocument->setContent(fSolutionFile);
		domRootSolutionElement = domDocument->namedItem("solution").toElement();
		domNodeList = domRootSolutionElement.childNodes();
		iNodesCnt = domNodeList.count();

		for (iIdx; iIdx < iNodesCnt; iIdx++)
		{
			domProjectElement = domNodeList.at(iIdx).toElement();
			qDebug("[%s] type=%s", __FUNCTION__, domProjectElement.attribute("name").toLatin1().constData());
		}
	}
	SolutionModel *newModel = new SolutionModel(*domDocument, this);
	ui.SolutionTreeView->setModel(newModel);
	delete solutionModel;
	solutionModel = newModel;

	this->ui.SolutionTreeView->setColumnWidth(0, 150);
}

void FEMSim::LoadModel(QString sFilePath)
{
}

void FEMSim::SaveModel(QString sFilePath)
{
}

void FEMSim::OpenModel()
{
	QString xmlPath = "E:\\E:\solution.xml";
	QString filePath = QFileDialog::getOpenFileName(this, "Open solution file", xmlPath, "XML files (*.xml)");
	qDebug("File: " + filePath.toLatin1());
	QMessageBox msg;

	if (!filePath.isEmpty()) 
	{
		QFile file(filePath);
		if (file.open(QIODevice::ReadOnly)) 
		{
			QDomDocument document;
			if (document.setContent(&file)) 
			{
				qDebug("[%s] FilePath = %s", __FUNCTION__, filePath.toLatin1().constData());
				SolutionModel *newModel = new SolutionModel(document, this);
				try {
					ui.SolutionTreeView->setModel(newModel);
					delete solutionModel;
					solutionModel = newModel;
					xmlPath = filePath;
				}
				catch (std::exception &e)
				{
					//QMessageBox(this, "Exception", e.what(), QMessageBox::Ok);
					qDebug("Exception: %s\n", e.what());
				}

			}
			else
			{
				msg.setText("The XML file cannot be opened");
				msg.exec();
			}
			file.close();
		}
		else
		{
			QMessageBox::critical(this, "The file can not be open", "File" + filePath + "can not be open.", QMessageBox::Ok);
		}
	}
}


