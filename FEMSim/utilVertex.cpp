#include "utilVertex.h"

// Constructors
UtilVertex::UtilVertex()
{
}

UtilVertex::UtilVertex(const QVector3D &position) :
    m_position(position)
{
}

UtilVertex::UtilVertex(const QVector3D &position, const QVector3D &color) :
    m_position(position), m_color(color)
{
}

const QVector3D& UtilVertex::position() const
{
    return m_position;
}

const QVector3D& UtilVertex::color() const 
{
    return m_color;
}

void UtilVertex::setPosition(const QVector3D& position) 
{
    m_position = position;
}

void UtilVertex::setColor(const QVector3D& color) 
{
    m_color = color;
}

int UtilVertex::positionOffset() 
{
    return offsetof(UtilVertex, m_position);
}

int UtilVertex::colorOffset() 
{
    return offsetof(UtilVertex, m_color);
}

int UtilVertex::stride() 
{
    return sizeof(UtilVertex);
}

