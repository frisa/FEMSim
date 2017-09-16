#include "viewModelWindow.h"

using namespace std;

ViewModelWindow::ViewModelWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//ui.ModelGLWidget = new QtModelWidget();

	/* Initialize connection */
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(OpenModel()));

	UtilLoggerSingleton::instance()->addOutput(m_SolutionOutputId, ui.tbSolutionLog);
	UtilLoggerSingleton::instance()->addOutput(m_ModelOutputId, ui.tbModelLog);

	ViewModelWindow::LoadDefaultModel();
}

void ViewModelWindow::LoadDefaultModel(QString sFilePath)
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

	solutionModel = new ModelSolution(*domDocument, this);
	fSolutionFile = new QFile(sSolutionFile);

	if (!fSolutionFile->exists())
	{
		log0("File %s does not exist and will be created", sSolutionFile.toLatin1().constData());
	}
	else
	{
		log0("File %s does exist", sSolutionFile.toLatin1().constData());
	}

	if (fSolutionFile->isOpen())
	{
		log0("File %s was opened, try to close", sSolutionFile.toLatin1().constData());
		fSolutionFile->close();
	}

	/* Create the default solution file */
	if (fSolutionFile->open(QIODevice::WriteOnly | QIODevice::Text))
	{
		log0("Create default solution to %s", sSolutionFile.toLatin1().constData());
		domRootSolutionElement = domDocument->createElement("solution");
		domRootSolutionElement.setAttribute("name", "OpenGL 4.6");
		domDocument->appendChild(domRootSolutionElement);

		domProjectElement = domDocument->createElement("project");
		domProjectElement.setAttribute("name", "OpenGL Basics");
		domRootSolutionElement.appendChild(domProjectElement);
		
		domModelElement = domDocument->createElement("model");
		domModelElement.setAttribute("name", "Model (Shaders)");
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
		log0("Open default solution from %s", sSolutionFile.toLatin1().constData());
		domDocument->setContent(fSolutionFile);
		domRootSolutionElement = domDocument->namedItem("solution").toElement();
		domNodeList = domRootSolutionElement.childNodes();
		iNodesCnt = domNodeList.count();

		for (iIdx; iIdx < iNodesCnt; iIdx++)
		{
			domProjectElement = domNodeList.at(iIdx).toElement();
			log1("-> type=%s", domProjectElement.attribute("name").toLatin1().constData());
		}
	}

	/* Load the default solution file to as model */
	ModelSolution *newModel = new ModelSolution(*domDocument, this);
	ui.SolutionTreeView->setModel(newModel);
	delete solutionModel;
	solutionModel = newModel;

	/* Set the layout of the tree view */
	this->ui.SolutionTreeView->expandAll();
	this->ui.SolutionTreeView->setColumnWidth(0, 150);
}

void ViewModelWindow::LoadModel(QString sFilePath)
{
}

void ViewModelWindow::SaveModel(QString sFilePath)
{
}

void ViewModelWindow::OpenModel()
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
				ModelSolution *newModel = new ModelSolution(document, this);
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


