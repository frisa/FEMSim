#include "SolutionModel.h"

#define COUNT_OF_COLUMNS 3

SolutionModel::SolutionModel(QDomDocument document, QObject *parent) : QAbstractItemModel(parent), domDocument(document)
{
    qDebug("[%s] document: %s", __FUNCTION__, document.toString().toLatin1());
    rootItem = new SolutionItem(domDocument, 0);
}

SolutionModel::~SolutionModel()
{
    delete rootItem;
}

QVariant SolutionModel::headerData(int section, Qt::Orientation orientation, int role)
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
    qDebug("[%s] seciton = %d, ret = %d", __FUNCTION__, ret, section);
    return ret;
}

Qt::ItemFlags SolutionModel::flags(const QModelIndex & index) const
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

Q_INVOKABLE QModelIndex SolutionModel::index(int row, int column, const QModelIndex & parent) const
{
    QModelIndex ret;

    if (!hasIndex(row, column, parent))
    {
        ret = QModelIndex();
    }
    else
    {
        SolutionItem *parentItem;
        if (parent.isValid())
        {
            parentItem = static_cast<SolutionItem*>(parent.internalPointer());
        }
        else
        {
            parentItem = rootItem;
        }

        SolutionItem *childItem = parentItem->child(row);
        if (childItem)
        {
            ret = createIndex(row, column, childItem);
        }
        else
        {
            ret = QModelIndex();
        }
    }
    qDebug("[%s] r=%d, c=%d, idx.internalId=%d", __FUNCTION__, row, column, ret.internalId());
    return ret;
}

Q_INVOKABLE QModelIndex SolutionModel::parent(const QModelIndex & child) const
{
    QModelIndex ret;
    if (!child.isValid())
    {
        ret = QModelIndex();
    }
    else
    {
        SolutionItem *childItem = static_cast<SolutionItem*>(child.internalPointer());
        SolutionItem *parentItem = childItem->parent();

        if ((!parentItem) || (parentItem == rootItem))
        {
            ret = QModelIndex();
        }
        else
        {
            ret = createIndex(parentItem->row(), 0, parentItem);
        }
    }
    qDebug("[%s] ret = %d", __FUNCTION__, ret);
    return ret;
}

Q_INVOKABLE int SolutionModel::rowCount(const QModelIndex & parent) const
{
    SolutionItem *parentItem;
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
        parentItem = static_cast<SolutionItem*>(parent.internalPointer());
    }
    ret = parentItem->node().childNodes().count();
    qDebug("[%s] ret = %d", __FUNCTION__, ret);
    return ret;
}

Q_INVOKABLE int SolutionModel::columnCount(const QModelIndex & parent) const
{
    int ret = COUNT_OF_COLUMNS;
    qDebug("[%s] ret = %d", __FUNCTION__, ret);
    return ret;
}

Q_INVOKABLE QVariant SolutionModel::data(const QModelIndex & index, int role) const
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
            SolutionItem *item = static_cast<SolutionItem*>(index.internalPointer());
            //ret = parseElementDefault(index, item);
            ret = parseElementSolution(index, item);

        }
    }
    qDebug("[%s] column = %d, ret = %d", __FUNCTION__, ret, i32Column);
    return ret;
}

QVariant SolutionModel::parseElementDefault(const QModelIndex & index, SolutionItem* item) const
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

QVariant SolutionModel::parseElementSolution(const QModelIndex & index, SolutionItem * item) const
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
			if (domElement.hasAttribute("x") && domElement.hasAttribute("y"))
			{
				QString str;
				str.append("x = ");
				str.append(domElement.attribute("x"));
				str.append(", ");
				str.append("y = ");
				str.append(domElement.attribute("y"));
				ret = str;
			}
            break;
        }
        case COLUMN2:
        {
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

