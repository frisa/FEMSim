#pragma once
#include <QtGlobal>
#include <QVector3D>

class UtilVertex
{
public:
	// Constructors
	UtilVertex();
	explicit UtilVertex(const QVector3D &position);
	UtilVertex(const QVector3D &position, const QVector3D &color);

	// Accessors / Mutators
	const QVector3D& position() const;
	const QVector3D& color() const;
	void setPosition(const QVector3D& position);
	void setColor(const QVector3D& color);

	// OpenGL Helpers
	static const int PositionTupleSize = 3;
	static const int ColorTupleSize = 3;
	static int positionOffset();
	static int colorOffset();
	static int stride();

private:
	QVector3D m_position;
	QVector3D m_color;
};

// Note: Q_MOVABLE_TYPE means it can be memcpy'd.
Q_DECLARE_TYPEINFO(UtilVertex, Q_MOVABLE_TYPE);


