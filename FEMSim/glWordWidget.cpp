#include "glWorldWidget.h"

GLWorldWidget::GLWorldWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

void GLWorldWidget::initializeGL()
{
	QFileInfo fiVert("e:\\_git\\FEMSim\\FEMSim\\shaders\\simple.vert");
	QFileInfo fiFrag("e:\\_git\\FEMSim\\FEMSim\\shaders\\simple.frag");

	if (!(fiVert.exists() && fiFrag.exists()))
	{
		QMessageBox::critical(this, "The file can not be open", "Files in e:\_git\FEMSim\FEMSim\shaders can not be open.", QMessageBox::Ok);
	}
	else
	{
		log1("Shader %s loading", "e:\\_git\\FEMSim\\FEMSim\\shaders\\simple.vert");
		log1("Shader %s loading", "e:\\_git\\FEMSim\\FEMSim\\shaders\\simple.frag");
	}

	m_fcn = QOpenGLContext::currentContext()->functions();
	m_fcn->glClearColor(0.0f, 0.1f, 0.0f, 1.0f);

	// Application-specific initialization
	{
		createTriangle();
		// Create Shader (Do not release until VAO is created)
		m_program = new QOpenGLShaderProgram();
		m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, fiVert.absoluteFilePath());
		m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fiFrag.absoluteFilePath());
		m_program->link();
		m_program->bind();

		// Create Buffer (Do not release until VAO is created)
		m_vertex.create();
		m_vertex.bind();
		m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
		m_vertex.allocate(sg_vertexes, sizeof(sg_vertexes));

		// Create Vertex Array Object
		m_object.create();
		m_object.bind();
		m_program->enableAttributeArray(0);
		m_program->enableAttributeArray(1);
		m_program->setAttributeBuffer(0, GL_FLOAT, UtilVertex::positionOffset(), UtilVertex::PositionTupleSize, UtilVertex::stride());
		m_program->setAttributeBuffer(1, GL_FLOAT, UtilVertex::colorOffset(), UtilVertex::ColorTupleSize, UtilVertex::stride());

		// Release (unbind) all
		m_object.release();
		m_vertex.release();
		m_program->release();
	}
}

void GLWorldWidget::resizeGL(int w, int h)
{
	log1("[%s]", __FUNCTION__);
}

void GLWorldWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	m_program->bind();
	{
		m_object.bind();
		glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
		m_object.release();
		log1("paintGL");
	}
	m_program->release();
}

void GLWorldWidget::createTriangle()
{
	sg_vertexes[0] = UtilVertex(QVector3D(0.00f, 0.75f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f));
	sg_vertexes[1] = UtilVertex(QVector3D(0.75f, -0.75f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f));
	sg_vertexes[2] = UtilVertex(QVector3D(-0.75f, -0.75f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f));
	log1("Create triangle");
}

GLWorldWidget::~GLWorldWidget()
{
}
