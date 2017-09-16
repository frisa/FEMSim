#include "viewModelWindow.h"

using namespace std;

ViewModelWindow::ViewModelWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//ui.ModelGLWidget = new QtModelWidget();

	/* Initialize connection */
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openModelSlot()));

	UtilLoggerSingleton::instance()->addOutput(m_SolutionOutputId, ui.tbSolutionLog);
	UtilLoggerSingleton::instance()->addOutput(m_ModelOutputId, ui.tbModelLog);

	ViewModelWindow::LoadDefaultModel();
}

void ViewModelWindow::selectionChangedSlot(const QItemSelection &, const QItemSelection &)
{
	const QModelIndex index = this->ui.SolutionTreeView->selectionModel()->currentIndex();
	QString selectedText = index.data(Qt::DisplayRole).toString();
	int hierarchyLevel = 1;
	QModelIndex seekRoot = index;
	char cShowString[500];
	while (seekRoot.parent() != QModelIndex())
	{
		seekRoot = seekRoot.parent();
		hierarchyLevel++;
	}
	log0("-> selected[%d]: %s", hierarchyLevel, selectedText.toLatin1().data());
}

void ViewModelWindow::LoadDefaultModel(QString sFilePath)
{
	QDomProcessingInstruction domHeader;
	QDomDocument *domDocument = new QDomDocument();

	QDomElement domRootSolutionElement;
	QDomElement domProjectElement;
	QDomElement domModelElement;
	QDomElement domPartElement;
	QDomElement domVertexElement;

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

		domPartElement = domDocument->createElement("part");
		domPartElement.setAttribute("name", "PointCloud");
		domPartElement.setAttribute("GLenum", "GL_POINTS");
		domModelElement.appendChild(domPartElement);

		domVertexElement = domDocument->createElement("Vertex");
		domVertexElement.setAttribute("x", "0.00");
		domVertexElement.setAttribute("y", "0.75");
		domVertexElement.setAttribute("z", "1.00");
		domPartElement.appendChild(domVertexElement);

		domVertexElement = domDocument->createElement("Vertex");
		domVertexElement.setAttribute("x", "0.75");
		domVertexElement.setAttribute("y", "-0.75");
		domVertexElement.setAttribute("z", "1.00");
		domPartElement.appendChild(domVertexElement);

		domVertexElement = domDocument->createElement("Vertex");
		domVertexElement.setAttribute("x", "-0.75");
		domVertexElement.setAttribute("y", "-0.75");
		domVertexElement.setAttribute("z", "1.00");
		domPartElement.appendChild(domVertexElement);

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
	this->ui.SolutionTreeView->setColumnWidth(0, 170);
	this->ui.SolutionTreeView->setColumnWidth(1, 130);

	QItemSelectionModel *selectionModel = this->ui.SolutionTreeView->selectionModel();
	connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
		this, SLOT(selectionChangedSlot(const QItemSelection &, const QItemSelection &)));
}

void ViewModelWindow::LoadModel(QString sFilePath)
{
}

void ViewModelWindow::SaveModel(QString sFilePath)
{
}

void ViewModelWindow::openModelSlot()
{
	QString xmlPath = "E:\\E:\solution.xml";
	QString filePath = QFileDialog::getOpenFileName(this, "Open solution file", xmlPath, "XML files (*.xml)");
	log0("File: [%s]", filePath.toLatin1().data());

	if (!filePath.isEmpty()) 
	{
		QFile file(filePath);
		if (file.open(QIODevice::ReadOnly)) 
		{
			QDomDocument document;
			if (document.setContent(&file)) 
			{
				log0("[%s] Open %s", __FUNCTION__, filePath.toLatin1().constData());
				ModelSolution *newModel = new ModelSolution(document, this);
				try {
					ui.SolutionTreeView->setModel(newModel);
					delete solutionModel;
					solutionModel = newModel;
					xmlPath = filePath;
					/* Set the layout of the tree view */
					this->ui.SolutionTreeView->expandAll();
					this->ui.SolutionTreeView->setColumnWidth(0, 200);

					QItemSelectionModel *selectionModel = this->ui.SolutionTreeView->selectionModel();
					connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
						this, SLOT(selectionChangedSlot(const QItemSelection &, const QItemSelection &)));
				}
				catch (std::exception &e)
				{
					QMessageBox::critical(this, "The file can not be open", QString(e.what()), QMessageBox::Ok);
				}
			}
			else
			{
				QMessageBox::critical(this, "The file open error", "File" + filePath + "can not be open.", QMessageBox::Ok);
			}
			file.close();
		}
		else
		{
			QMessageBox::critical(this, "The file can not be open", "File" + filePath + "can not be open.", QMessageBox::Ok);
		}
	}
}


