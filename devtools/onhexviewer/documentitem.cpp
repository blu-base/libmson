#include "documentitem.h"

DocumentItem::DocumentItem(
    const QVector<QVariant>& data, DocumentItem* parentItem)
    : m_itemData(data), m_parentItem(parentItem)
{
}

DocumentItem::~DocumentItem() { qDeleteAll(m_childItems); }

void DocumentItem::appendChild(DocumentItem* child)
{
  m_childItems.append(child);
}

DocumentItem* DocumentItem::child(int row)
{
  if (row < 0 || row >= m_childItems.size()) {
    return nullptr;
  }

  return m_childItems.at(row);
}

int DocumentItem::childCount() const { return m_childItems.count(); }

int DocumentItem::columnCount() const { return m_itemData.count(); }

QVariant DocumentItem::data(int column) const
{
  if (column < 0 || column >= m_itemData.size()) {
    return QVariant();
  }

  return m_itemData.at(column);
}

int DocumentItem::row() const
{
  if (m_parentItem != nullptr) {
    return m_parentItem->m_childItems.indexOf(const_cast<DocumentItem*>(this));
  }

  return 0;
}

DocumentItem* DocumentItem::parentItem() { return m_parentItem; }
