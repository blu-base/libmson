#ifndef SELECTIONCOMMAND_H
#define SELECTIONCOMMAND_H

#include <QModelIndex>
#include <QTreeView>
#include <QUndoCommand>
#include <QtCore/qglobal.h>

class QHexView;

class SelectionCommand : public QUndoCommand
{

public:
  SelectionCommand(QTreeView* treeView, QHexView* hexView, const QModelIndex& newIndex,
      QUndoCommand* parent = nullptr);
  ~SelectionCommand();

  // QUndoCommand interface
public:
  virtual void undo() override;
  virtual void redo() override;
  virtual bool mergeWith(const QUndoCommand* other) override;


private:
  void updateHexFocus(const QModelIndex& index);

private:
  QTreeView* m_treeView;
  QHexView* m_hexView;

  QPersistentModelIndex m_oldIndex;
  QPersistentModelIndex m_newIndex;

};






#endif // SELECTIONCOMMAND_H
