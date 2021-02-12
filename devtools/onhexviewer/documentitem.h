#ifndef DOCUMENTITEM_H
#define DOCUMENTITEM_H

#include <QStandardItem>
#include <QtCore/qglobal.h>

class DocumentItem
{
public:
  explicit DocumentItem(const QVector<QVariant> &data, DocumentItem *parentItem = nullptr);

  ~DocumentItem();

  void appendChild(DocumentItem *child);

  DocumentItem *child(int row);
  int childCount() const;
  int columnCount() const;
  QVariant data(int column) const;
  int row() const;
  DocumentItem *parentItem();

private:
  QVector<DocumentItem*> m_childItems;
  QVector<QVariant> m_itemData;
  DocumentItem *m_parentItem;
};

#endif // DOCUMENTITEM_H
