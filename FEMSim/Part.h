#pragma once

#include <QList>
#include <QVariant>


class Part
{
public:
	explicit Part(const QList<QVariant> &data, Part *parentItem = 0);
	~Part();

	void appendChild(Part *child);
	Part *child(int row);
	int childCount() const;
	int columnCount() const;
	QVariant data(int column) const;
	int row() const;
	Part *parentItem();

private:
	QList<Part*> m_childItems;
	QList<QVariant> m_itemData;
	Part *m_parentItem;
};

