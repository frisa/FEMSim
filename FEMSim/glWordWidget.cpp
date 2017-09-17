#include "glWorldWidget.h"

GLWorldWidget::GLWorldWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

void GLWorldWidget::initializeGL()
{
	m_fcn = QOpenGLContext::currentContext()->functions();
	m_fcn->glClearColor(0.0f, 0.1f, 0.0f, 1.0f);

	// Application-specific initialization
	{
		createTriangle();
		// Create Shader (Do not release until VAO is created)
		m_program = new QOpenGLShaderProgram();
		m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/Resources/Shaders/simple.vert");
		m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/Resources/Shaders/simple.frag");
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
	sg_vertexes[0] = UtilVertex(QVector3D(0.00f, 1.00f, 1.0f), QVector3D(1.0f, 1.0f, 0.0f));
	sg_vertexes[1] = UtilVertex(QVector3D(1.00f, -1.0f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f));
	sg_vertexes[2] = UtilVertex(QVector3D(-1.00f, -1.0f, 1.0f), QVector3D(0.0f, 1.0f, 1.0f));
	log1("Create triangle");
}

void GLWorldWidget::renderPart(int GLenum, UtilVertex vertexes[], int vertexes_cnt)
{
	m_program->link();
	m_program->bind();
	/* create the buffer of the vertices */
	m_vertex.create();
	m_vertex.bind();
	m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
	m_vertex.allocate(vertexes, vertexes_cnt);

	m_object.create();
	m_object.bind();

	m_program->enableAttributeArray(0);
	m_program->enableAttributeArray(1);
	m_program->setAttributeBuffer(0, GL_FLOAT, UtilVertex::positionOffset(), UtilVertex::PositionTupleSize, UtilVertex::stride());
	m_program->setAttributeBuffer(1, GL_FLOAT, UtilVertex::colorOffset(), UtilVertex::ColorTupleSize, UtilVertex::stride());

	m_object.release();
	m_vertex.release();
	m_program->release();

	update();
	log1("->render: %d", GLenum);
}

GLWorldWidget::~GLWorldWidget()
{
}
