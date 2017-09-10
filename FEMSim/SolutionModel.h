#pragma once
#include <QAbstractItemModel>
#include <QDomDocument>
#include "SolutionItem.h"

class SolutionModel :
    public QAbstractItemModel
{
        Q_OBJECT
		enum Columns
		{	
			COLUMN0 = 0,
			COLUMN1 = 1,
			COLUMN2 = 2,
		};
    public:
        explicit SolutionModel(QDomDocument document, QObject *parent=0);
        ~SolutionModel();
        // The additional functions
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole);
        Qt::ItemFlags flags(const QModelIndex &index) const override;
        // Inherited via QAbstractItemModel
        virtual Q_INVOKABLE QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const override;
        virtual Q_INVOKABLE QModelIndex parent(const QModelIndex & child) const override;
        virtual Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const override;
        virtual Q_INVOKABLE int columnCount(const QModelIndex & parent = QModelIndex()) const override;
        virtual Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

		QVariant SolutionModel::parseElementDefault(const QModelIndex & index, SolutionItem* item) const;
		QVariant SolutionModel::parseElementSolution(const QModelIndex & index, SolutionItem* item) const; 
    private:
        QDomDocument domDocument;
        SolutionItem *rootItem;
};

