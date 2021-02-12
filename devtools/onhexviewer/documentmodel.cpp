#include "documentmodel.h"

#include "documentitem.h"


DocumentModel::DocumentModel(QObject* parent) : QAbstractItemModel(parent)
{
  rootItem = new DocumentItem({"Object", "Type", "Value", "STP", "ByteCount"});
}

DocumentModel::~DocumentModel() { delete rootItem; }

Qt::ItemFlags DocumentModel::flags(const QModelIndex& index) const
{
  if (!index.isValid())
    return Qt::NoItemFlags;

  return QAbstractItemModel::flags(index);
}

QVariant DocumentModel::headerData(
    int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return rootItem->data(section);

  return QVariant();
}


QModelIndex
DocumentModel::index(int row, int column, const QModelIndex& parent) const
{
  if (!hasIndex(row, column, parent)) {
    return QModelIndex();
  }

  DocumentItem* parentItem;

  if (!parent.isValid()) {
    parentItem = rootItem;
  }
  else {
    parentItem = static_cast<DocumentItem*>(parent.internalPointer());
  }

  auto* childItem = parentItem->child(row);
  if (childItem != nullptr) {
    return createIndex(row, column, childItem);
  }
  return QModelIndex();
}

QModelIndex DocumentModel::parent(const QModelIndex& child) const
{
  if (!child.isValid()) {
    return QModelIndex();
  }

  auto* childItem  = static_cast<DocumentItem*>(child.internalPointer());
  auto* parentItem = childItem->parentItem();

  if (parentItem == rootItem) {
    return QModelIndex();
  }

  return createIndex(parentItem->row(), 0, parentItem);
}

int DocumentModel::rowCount(const QModelIndex& parent) const
{
  DocumentItem* parentItem;

  if (parent.column() > 0) {
    return 0;
  }

  if (!parent.isValid()) {
    parentItem = rootItem;
  }
  else {
    parentItem = static_cast<DocumentItem*>(parent.internalPointer());
  }

  return parentItem->childCount();
}

int DocumentModel::columnCount(const QModelIndex& parent) const
{
  if (parent.isValid()) {
    return static_cast<DocumentItem*>(parent.internalPointer())->columnCount();
  }
  return rootItem->columnCount();
}

QVariant DocumentModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid()) {
    return QVariant();
  }

  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  auto* item = static_cast<DocumentItem*>(index.internalPointer());

  return item->data(index.column());
}

DocumentItem* DocumentModel::root() { return rootItem;

}

