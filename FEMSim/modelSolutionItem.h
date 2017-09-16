#pragma once
#include <QDomNode>
#include <QHash>

class ModelSolutionItem
{
public:
	ModelSolutionItem(QDomNode &node, int row, ModelSolutionItem *parent = 0);
	~ModelSolutionItem();
	ModelSolutionItem *child(int i);
	ModelSolutionItem *parent();
	QDomNode node() const;
	int row();
private:
	QDomNode domNode;
	QHash<int, ModelSolutionItem*> childItems;
	ModelSolutionItem *parentItem;
	int rowNumber;
};

