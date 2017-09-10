#pragma once
#include <QDomNode>
#include <QHash>

class SolutionItem
{
public:
	SolutionItem(QDomNode &node, int row, SolutionItem *parent = 0);
	~SolutionItem();
	SolutionItem *child(int i);
	SolutionItem *parent();
	QDomNode node() const;
	int row();
private:
	QDomNode domNode;
	QHash<int, SolutionItem*> childItems;
	SolutionItem *parentItem;
	int rowNumber;
};

