#pragma once

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

#include <QFileInfo>
#include <QMessageBox>

#include <gl/GLU.h>
#include <gl/GL.h>

#include "utilAbstractLoggedClass.h"
#include "utilVertex.h"

class GLWorldWidget : public QOpenGLWidget, public UtilAbstractLoggedClass
{
	Q_OBJECT

private:
	QOpenGLFunctions * m_fcn;
	QOpenGLBuffer m_vertex;
	QOpenGLVertexArrayObject m_object;
	QOpenGLShaderProgram *m_program;
	UtilVertex sg_vertexes[3];

public:
	GLWorldWidget(QWidget *parent);
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	void createTriangle();
	~GLWorldWidget();
};
