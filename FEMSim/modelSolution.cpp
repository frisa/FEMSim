#include "modelSolution.h"

ModelSolution::ModelSolution(QDomDocument document, QObject *parent) : QAbstractItemModel(parent), domDocument(document)
{
	//log0("[%s] document: %s", __FUNCTION__, document.toString().toLatin1().data());
    rootItem = new ModelSolutionItem(domDocument, 0);
}

ModelSolution::~ModelSolution()
{
    delete rootItem;
}

QVariant ModelSolution::headerData(int section, Qt::Orientation orientation, int role)
{
    QVariant ret;

    if ((orientation == Qt::Horizontal) && (role == Qt::DisplayRole))
    {
        switch (section)
        {
            case 0:
            {
                ret = "NAME";
                break;
            }
            case 1:
            {
                ret = "ATTRIBUTE";
                break;
            }
            case 2:
            {
                ret = "VALUE";
                break;
            }
            default:
                ret = QVariant();
        }
    }
	//log0("[%s] seciton = %d, ret = %d", __FUNCTION__, ret, section);
    return ret;
}

Qt::ItemFlags ModelSolution::flags(const QModelIndex & index) const
{
    Qt::ItemFlags ret;
    if (false == index.isValid())
    {
        ret = 0;
    }
    else
    {
        ret = QAbstractItemModel::flags(index);
    }
    return ret;
}

Q_INVOKABLE QModelIndex ModelSolution::index(int row, int column, const QModelIndex & parent) const
{
    QModelIndex ret;

    if (!hasIndex(row, column, parent))
    {
        ret = QModelIndex();
    }
    else
    {
		ModelSolutionItem *parentItem;
        if (parent.isValid())
        {
            parentItem = static_cast<ModelSolutionItem*>(parent.internalPointer());
        }
        else
        {
            parentItem = rootItem;
        }

		ModelSolutionItem *childItem = parentItem->child(row);
        if (childItem)
        {
            ret = createIndex(row, column, childItem);
        }
        else
        {
            ret = QModelIndex();
        }
    }
	//log0("[%s] r=%d, c=%d, idx.internalId=%d", __FUNCTION__, row, column, ret.internalId());
    return ret;
}

Q_INVOKABLE QModelIndex ModelSolution::parent(const QModelIndex & child) const
{
    QModelIndex ret;
    if (!child.isValid())
    {
        ret = QModelIndex();
    }
    else
    {
		ModelSolutionItem *childItem = static_cast<ModelSolutionItem*>(child.internalPointer());
		ModelSolutionItem *parentItem = childItem->parent();

        if ((!parentItem) || (parentItem == rootItem))
        {
            ret = QModelIndex();
        }
        else
        {
            ret = createIndex(parentItem->row(), 0, parentItem);
        }
    }
	//log0("[%s] ret = %d", __FUNCTION__, ret);
    return ret;
}

Q_INVOKABLE int ModelSolution::rowCount(const QModelIndex & parent) const
{
	ModelSolutionItem *parentItem;
    int ret;

    if (parent.column() > 0)
    {
        ret = 0;
    }

    if (!parent.isValid())
    {
        parentItem = rootItem;
    }
    else
    {
        parentItem = static_cast<ModelSolutionItem*>(parent.internalPointer());
    }
    ret = parentItem->node().childNodes().count();
	//log0("[%s] ret = %d", __FUNCTION__, ret);
    return ret;
}

Q_INVOKABLE int ModelSolution::columnCount(const QModelIndex & parent) const
{
    int ret = COUNT_OF_COLUMNS;
	//log0("[%s] ret = %d", __FUNCTION__, ret);
    return ret;
}

Q_INVOKABLE QVariant ModelSolution::data(const QModelIndex & index, int role) const
{
    QVariant ret;
    int i32Column = 0;
    if (!index.isValid())
    {
        ret = QVariant();
    }
    else
    {
        if (role != Qt::DisplayRole)
        {
            ret = QVariant();
        }
        else
        {
			ModelSolutionItem *item = static_cast<ModelSolutionItem*>(index.internalPointer());
            //ret = parseElementDefault(index, item);
            ret = parseElementSolution(index, item);

        }
    }
    //log0("[%s] column = %d, ret = %d", __FUNCTION__, ret, i32Column);
    return ret;
}

QVariant ModelSolution::parseElementDefault(const QModelIndex & index, ModelSolutionItem* item) const
{
    QVariant ret;
    QDomNode node = item->node();
    QStringList attributes;
    QDomNamedNodeMap attributeMap = node.attributes();
    switch (index.column())
    {
        case COLUMN0:
        {
            ret = node.nodeName();
            break;
        }
        case COLUMN1:
        {
            for (int i = 0; i < attributeMap.count(); ++i)
            {
                QDomNode attribute = attributeMap.item(i);
                attributes << attribute.nodeName() + "=\""
                           + attribute.nodeValue() + '"';
            }
            ret = attributes.join(' ');
            break;
        }
        case COLUMN2:
        {
            ret = node.nodeValue().split("\n").join(' ');
            break;
        }
        default:
            ret = QVariant();
    }
    return ret;
}

QVariant ModelSolution::parseElementSolution(const QModelIndex & index, ModelSolutionItem * item) const
{
    QVariant ret;
    QDomElement domElement = item->node().toElement();

    switch (index.column())
    {
        case COLUMN0:
        {
			if (domElement.hasAttribute("name"))
			{
				ret = domElement.attribute("name");
			}
            break;
        }
        case COLUMN1:
        {
			if (domElement.hasAttribute("GLenum"))
			{
				QString str;
				str.append("GLenum = ");
				str.append(domElement.attribute("GLenum"));
				ret = str;
			}
            break;
        }
        case COLUMN2:
        {
			if (domElement.hasAttribute("x") && domElement.hasAttribute("y") && domElement.hasAttribute("z"))
			{
				QString str;
				str.append("[");
				str.append(domElement.attribute("x"));
				str.append(",");
				str.append(domElement.attribute("y"));
				str.append(",");
				str.append(domElement.attribute("z"));
				str.append("]");
				ret = str;
			}
			break;
        }
		default:
		{
			ret = QVariant();
			break;
		}
    }
	return ret;
}


