#ifndef GLOBALIDTABLEENTRY2FNDX_H
#define GLOBALIDTABLEENTRY2FNDX_H

#include "../../IStreamable.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class GlobalIdTableEntry2FNDX
    : public IFileNodeType
    , public IStreamable {
private:
  quint32 m_iIndexMapFrom;
  quint32 m_iIndexMapTo;

public:
  GlobalIdTableEntry2FNDX(FileNode_WPtr_t parentFileNode);
  virtual ~GlobalIdTableEntry2FNDX() = default;

  quint32 getIIndexMapTo() const;
  void setIIndexMapTo(const quint32& value);

  quint32 getIIndexMapFrom() const;
  void setIIndexMapFrom(const quint32& value);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;


  static const quint64 sizeInFile = 8;
};

} // namespace priv
} // namespace libmson

#endif // GLOBALIDTABLEENTRY2FNDX_H
