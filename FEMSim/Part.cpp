#include "Part.h"

Part::Part(const QList<QVariant> &data, Part * parent)
{
	m_parentItem = parent;
	m_itemData = data;
}

Part::~Part()
{
	qDeleteAll(m_childItems);
}

void Part::appendChild(Part * item)
{
	m_childItems.append(item);
}

Part * Part::child(int row)
{
	return m_childItems.value(row);;
}

int Part::childCount() const
{
	return m_childItems.count();
}

int Part::columnCount() const
{
	return m_itemData.count();
}

QVariant Part::data(int column) const
{
	return m_itemData.value(column);
}

Part * Part::parentItem()
{
	return m_parentItem;
}

int Part::row() const
{
	if (m_parentItem)
		return m_parentItem->m_childItems.indexOf(const_cast<Part*>(this));

	return 0;
}

