#ifndef DOCUMENTMODEL_H
#define DOCUMENTMODEL_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include <QAbstractItemModel>

class DocumentItem;


/**
 * @brief The DocumentModel class
 *
 *
 *
 * Columns |  ObjectClass | value   | stp     | offset  |
 * Type    | QString      | QString | quint64 | quint64 |
 *
 * rows in a DocumentItem are its child Items
 *
 */

class DocumentModel : public QAbstractItemModel
{
  Q_OBJECT

public:
  explicit DocumentModel(QObject* parent = nullptr);
  ~DocumentModel();

  // QAbstractItemModel interface
public:
  Qt::ItemFlags flags(const QModelIndex& index) const override;
  QVariant headerData(
      int section, Qt::Orientation orientation,
      int role = Qt::DisplayRole) const override;
  virtual QModelIndex
  index(int row, int column, const QModelIndex& parent) const override;
  virtual QModelIndex parent(const QModelIndex& child) const override;
  virtual int rowCount(const QModelIndex& parent) const override;
  virtual int columnCount(const QModelIndex& parent) const override;
  virtual QVariant data(const QModelIndex& index, int role) const override;

  DocumentItem* root();




private:
  DocumentItem *rootItem;
};




#endif // DOCUMENTMODEL_H
