#include "SolutionItem.h"



SolutionItem::SolutionItem(QDomNode & node, int row, SolutionItem * parent)
{
	domNode = node;
	// Record the item's location within its parent.
	rowNumber = row;
	parentItem = parent;
}

SolutionItem::~SolutionItem()
{
	QHash<int, SolutionItem*>::iterator itr;
	for (itr = childItems.begin(); itr != childItems.end(); ++itr)
	{
		delete itr.value();
	}
}

SolutionItem * SolutionItem::child(int i)
{
	SolutionItem* ret;
	if (childItems.contains(i))
	{
		ret = childItems[i];
	}
	else
	{
		if ((i >= 0) && (i < domNode.childNodes().count()))
		{
			QDomNode childNode = domNode.childNodes().item(i);
			SolutionItem *childItem = new SolutionItem(childNode, i, this);
			childItems[i] = childItem;
			ret = childItem;
		}
	}
	return ret;
}

SolutionItem * SolutionItem::parent()
{
	return parentItem;
}

QDomNode SolutionItem::node() const
{
	return domNode;
}

int SolutionItem::row()
{
	return rowNumber;
}
