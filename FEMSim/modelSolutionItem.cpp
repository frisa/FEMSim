#include "modelSolutionItem.h"

ModelSolutionItem::ModelSolutionItem(QDomNode & node, int row, ModelSolutionItem * parent)
{
	domNode = node;
	// Record the item's location within its parent.
	rowNumber = row;
	parentItem = parent;
}

ModelSolutionItem::~ModelSolutionItem()
{
	QHash<int, ModelSolutionItem*>::iterator itr;
	for (itr = childItems.begin(); itr != childItems.end(); ++itr)
	{
		delete itr.value();
	}
}

ModelSolutionItem * ModelSolutionItem::child(int i)
{
	ModelSolutionItem* ret;
	if (childItems.contains(i))
	{
		ret = childItems[i];
	}
	else
	{
		if ((i >= 0) && (i < domNode.childNodes().count()))
		{
			QDomNode childNode = domNode.childNodes().item(i);
			ModelSolutionItem *childItem = new ModelSolutionItem(childNode, i, this);
			childItems[i] = childItem;
			ret = childItem;
		}
	}
	return ret;
}

ModelSolutionItem * ModelSolutionItem::parent()
{
	return parentItem;
}

QDomNode ModelSolutionItem::node() const
{
	return domNode;
}

int ModelSolutionItem::row()
{
	return rowNumber;
}
