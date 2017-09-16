#pragma once
#include <QAbstractItemModel>
#include <QDomDocument>
#include "modelSolutionItem.h"
#include "utilAbstractLoggedClass.h"

class ModelSolution :
    public QAbstractItemModel, public UtilAbstractLoggedClass
{
	Q_OBJECT

		enum Columns
		{
			COLUMN0 = 0,
			COLUMN1 = 1,
			COLUMN2 = 2,
			COUNT_OF_COLUMNS = 3
		};
    public:
        explicit ModelSolution(QDomDocument document, QObject *parent=0);
        ~ModelSolution();
        // The additional functions
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole);
        Qt::ItemFlags flags(const QModelIndex &index) const override;
        // Inherited via QAbstractItemModel
        virtual Q_INVOKABLE QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const override;
        virtual Q_INVOKABLE QModelIndex parent(const QModelIndex & child) const override;
        virtual Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const override;
        virtual Q_INVOKABLE int columnCount(const QModelIndex & parent = QModelIndex()) const override;
        virtual Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

		QVariant ModelSolution::parseElementDefault(const QModelIndex & index, ModelSolutionItem* item) const;
		QVariant ModelSolution::parseElementSolution(const QModelIndex & index, ModelSolutionItem* item) const;

    private:
        QDomDocument domDocument;
        ModelSolutionItem *rootItem;
};

