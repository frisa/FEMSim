#include "QtModelWidget.h"
#include <QFileInfo>
#include <QMessageBox>


/*******************************************************************************
* Inline Implementation
******************************************************************************/

// Constructors
Q_DECL_CONSTEXPR inline Vertex::Vertex() {}
Q_DECL_CONSTEXPR inline Vertex::Vertex(const QVector3D &position) : m_position(position) {}
Q_DECL_CONSTEXPR inline Vertex::Vertex(const QVector3D &position, const QVector3D &color) : m_position(position), m_color(color) {}

// Accessors / Mutators
Q_DECL_CONSTEXPR inline const QVector3D& Vertex::position() const { return m_position; }
Q_DECL_CONSTEXPR inline const QVector3D& Vertex::color() const { return m_color; }
void inline Vertex::setPosition(const QVector3D& position) { m_position = position; }
void inline Vertex::setColor(const QVector3D& color) { m_color = color; }

// OpenGL Helpers
Q_DECL_CONSTEXPR inline int Vertex::positionOffset() { return offsetof(Vertex, m_position); }
Q_DECL_CONSTEXPR inline int Vertex::colorOffset() { return offsetof(Vertex, m_color); }
Q_DECL_CONSTEXPR inline int Vertex::stride() { return sizeof(Vertex); }


// Create a colored triangle
static const Vertex sg_vertexes[] = {
	Vertex(QVector3D(0.00f,  0.75f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)),
	Vertex(QVector3D(0.75f, -0.75f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f)),
	Vertex(QVector3D(-0.75f, -0.75f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f))
};

/*******************************************************************************
* Implementation of the Model Widget
******************************************************************************/

QtModelWidget::QtModelWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

void QtModelWidget::initializeGL()
{
	QFileInfo fiVert("e:\\_git\\FEMSim\\FEMSim\\shaders\\simple.vert");
	QFileInfo fiFrag("e:\\_git\\FEMSim\\FEMSim\\shaders\\simple.frag");

	if (!(fiVert.exists() && fiFrag.exists()))
	{
		QMessageBox::critical(this, "The file can not be open", "Files in e:\_git\FEMSim\FEMSim\shaders can not be open.", QMessageBox::Ok);
	}

	m_fcn = QOpenGLContext::currentContext()->functions();
	m_fcn->glClearColor(0.0f, 0.1f, 0.0f, 1.0f);

	// Application-specific initialization
	{
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
		m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
		m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

		// Release (unbind) all
		m_object.release();
		m_vertex.release();
		m_program->release();
	}
}

void QtModelWidget::resizeGL(int w, int h)
{

}

void QtModelWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	m_program->bind();
	{
		m_object.bind();
		glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
		m_object.release();
	}
	m_program->release();
}

QtModelWidget::~QtModelWidget()
{
}
