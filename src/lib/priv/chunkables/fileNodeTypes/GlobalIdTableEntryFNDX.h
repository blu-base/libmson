#ifndef GLOBALIDTABLEENTRYFNDX_H
#define GLOBALIDTABLEENTRYFNDX_H

#include "../../IStreamable.h"
#include "IFileNodeType.h"
#include <QUuid>
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class GlobalIdTableEntryFNDX
    : public IFileNodeType
    , public IStreamable {
private:
  quint32 m_index;
  QUuid m_guid;

public:
  GlobalIdTableEntryFNDX(FileNode_SPtr_t parentFileNode);
  virtual ~GlobalIdTableEntryFNDX() = default;

  quint32 getIndex() const;
  void setIndex(const quint32& value);

  QUuid getGuid() const;
  void setGuid(const QUuid& value);

  virtual quint64 getSizeInFile() const override;
  virtual FileNodeTypeID getType() const override
  {
    return FileNodeTypeID::GlobalIdTableEntryFNDX;
  };

  friend class RevisionStoreFileParser;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;

  static const quint64 sizeInFile = 20;
};

} // namespace priv
} // namespace libmson

#endif // GLOBALIDTABLEENTRYFNDX_H
