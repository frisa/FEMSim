#pragma once

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <gl/GLU.h>
#include <gl/GL.h>

class QtModelWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	QtModelWidget(QWidget *parent);
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	~QtModelWidget();
};
