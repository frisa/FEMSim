#include "Assembly.h"

#include <QStringList>

Assembly::Assembly(const QString &data, QObject *parent) : QAbstractItemModel(parent)
{
	QList<QVariant> rootData;
	rootData << "Title" << "X" << "Y" << "W" << "H";
	rootItem = new Part(rootData);
	setupModelData(data.split(QString("\n")), rootItem);
}

Assembly::~Assembly()
{
	delete rootItem;
}

int Assembly::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return static_cast<Part*>(parent.internalPointer())->columnCount();
	else
		return rootItem->columnCount();
}

QVariant Assembly::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	Part *item = static_cast<Part*>(index.internalPointer());

	return item->data(index.column());
}

Qt::ItemFlags Assembly::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return QAbstractItemModel::flags(index);
}

QVariant Assembly::headerData(int section, Qt::Orientation orientation,	
int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return rootItem->data(section);

	return QVariant();
}

QModelIndex Assembly::index(int row, int column, const QModelIndex &parent)
const
{
	QModelIndex mIdx = QModelIndex();
	if (false == hasIndex(row, column, parent))
	{
		mIdx = QModelIndex();
	}
	else
	{
		Part *parentItem;
		if (!parent.isValid())
			parentItem = rootItem;
		else
			parentItem = static_cast<Part*>(parent.internalPointer());

		Part *childItem = parentItem->child(row);
		if (childItem)
			mIdx = createIndex(row, column, childItem);
		else
			mIdx = QModelIndex();
	}
	return mIdx;
}

QModelIndex Assembly::parent(const QModelIndex &index) const
{
	QModelIndex mIdx = QModelIndex();
	if (false == index.isValid())
	{
		mIdx = QModelIndex();
	}
	else
	{
		Part *childItem = static_cast<Part*>(index.internalPointer());
		Part *parentItem = childItem->parentItem();

		if (parentItem == rootItem)
		{
			mIdx = QModelIndex();
		}
		else
		{
			mIdx = createIndex(parentItem->row(), 0, parentItem);
		}
			
	}
	return mIdx;
}

int Assembly::rowCount(const QModelIndex &parent) const
{
	Part *parentItem;
	int ret;
	if (parent.column() > 0)
	{
		ret = 0;
	}
	else
	{
		if (!parent.isValid())
		{
			parentItem = rootItem;
		}
		else
		{
			parentItem = static_cast<Part*>(parent.internalPointer());
		}
		ret = parentItem->childCount();
	}
	return ret;
}

void Assembly::setupModelData(const QStringList &lines, Part *parent)
{
	QList<Part*> parents;
	QList<int> indentations;
	parents << parent;
	indentations << 0;
	int number = 0;

	while (number < lines.count()) {
		int position = 0;
		QString lineData = lines[number].mid(position).trimmed();
		if (!lineData.isEmpty())
		{
			QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
			QList<QVariant> columnData;
			for (int column = 0; column < columnStrings.count(); ++column)
				columnData << columnStrings[column];

			if (position > indentations.last()) 
			{
				if (parents.last()->childCount() > 0) 
				{
					parents << parents.last()->child(parents.last()->childCount() - 1);
					indentations << position;
				}
			}
			else {
				while (position < indentations.last() && parents.count() > 0) {
					parents.pop_back();
					indentations.pop_back();
				}
			}
			parents.last()->appendChild(new Part(columnData, parents.last()));
		}
		++number;
	}
}