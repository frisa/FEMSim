#pragma once

#include <QtGlobal>
#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>


#include <gl/GLU.h>
#include <gl/GL.h>

#include <QVector3D>

class Vertex
{
public:
	// Constructors
	Q_DECL_CONSTEXPR Vertex();
	Q_DECL_CONSTEXPR explicit Vertex(const QVector3D &position);
	Q_DECL_CONSTEXPR Vertex(const QVector3D &position, const QVector3D &color);

	// Accessors / Mutators
	Q_DECL_CONSTEXPR const QVector3D& position() const;
	Q_DECL_CONSTEXPR const QVector3D& color() const;
	void setPosition(const QVector3D& position);
	void setColor(const QVector3D& color);

	// OpenGL Helpers
	static const int PositionTupleSize = 3;
	static const int ColorTupleSize = 3;
	static Q_DECL_CONSTEXPR int positionOffset();
	static Q_DECL_CONSTEXPR int colorOffset();
	static Q_DECL_CONSTEXPR int stride();

private:
	QVector3D m_position;
	QVector3D m_color;
};

// Note: Q_MOVABLE_TYPE means it can be memcpy'd.
Q_DECLARE_TYPEINFO(Vertex, Q_MOVABLE_TYPE);

class QtModelWidget : public QOpenGLWidget
{
	Q_OBJECT

private:
	QOpenGLFunctions * m_fcn;
	QOpenGLBuffer m_vertex;
	QOpenGLVertexArrayObject m_object;
	QOpenGLShaderProgram *m_program;


public:
	QtModelWidget(QWidget *parent);
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	~QtModelWidget();
};
