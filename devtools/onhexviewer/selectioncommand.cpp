#include "selectioncommand.h"


#include <QDebug>
#include <qhexview.h>

SelectionCommand::SelectionCommand(
    QTreeView* treeView, QHexView* hexView, const QModelIndex& newIndex,
    QUndoCommand* parent)
    : QUndoCommand(parent), m_treeView(treeView), m_hexView(hexView),
      m_oldIndex(treeView->selectionModel()->currentIndex()),
      m_newIndex(newIndex)
{

  this->setText(
      "SelectionCommand from (" + QString::number(m_oldIndex.row()) + ", " +
      QString::number(m_oldIndex.column()) + ") to " +
      QString::number(m_newIndex.row()) + ", " +
      QString::number(m_newIndex.column()) + ")");
}

SelectionCommand::~SelectionCommand() {}

void SelectionCommand::undo()
{
  if (m_oldIndex.isValid()) {

    m_treeView->setCurrentIndex(m_oldIndex);
    updateHexFocus(m_oldIndex);
  }
}

void SelectionCommand::redo()
{
  m_treeView->setCurrentIndex(m_newIndex);

  updateHexFocus(m_newIndex);
}

bool SelectionCommand::mergeWith(const QUndoCommand* other)
{

  if (other->id() != id()) {
    return false;
  }

  auto* otherCom = dynamic_cast<const SelectionCommand*>(other);

  if (!otherCom) {
    return false;
  }

  if (m_oldIndex == otherCom->m_newIndex) {
    m_oldIndex = otherCom->m_newIndex;
    return true;
  }

  return false;
}

void SelectionCommand::updateHexFocus(const QModelIndex& index)
{
  QHexMetadata* hexmetadata = m_hexView->document()->metadata();
  hexmetadata->clear();


  quint64 begin =
      index.siblingAtColumn(3).data().toString().toUInt(nullptr, 16);
  quint64 offset =
      index.siblingAtColumn(4).data().toString().toUInt(nullptr, 16);

  hexmetadata->metadata(
      begin, begin + offset, Qt::white, Qt::darkBlue, QString());


  m_hexView->document()->cursor()->moveTo(
      index.siblingAtColumn(3).data().toString().toUInt(nullptr, 16));
}
