#ifndef GLOBALIDTABLEENTRY3FNDX_H
#define GLOBALIDTABLEENTRY3FNDX_H

#include "../../IStreamable.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class GlobalIdTableEntry3FNDX
    : public IFileNodeType
    , public IStreamable {
private:
  quint32 m_iIndexCopyFromStart;
  quint32 m_cEntriesToCopy;
  quint32 m_iIndexCopyToStart;

public:
  GlobalIdTableEntry3FNDX(FileNode_SPtr_t parentFileNode);
  virtual ~GlobalIdTableEntry3FNDX() = default;

  quint32 getIIndexCopyFromStart() const;
  void setIIndexCopyFromStart(const quint32& value);

  quint32 getCEntriesToCopy() const;
  void setCEntriesToCopy(const quint32& value);

  quint32 getIIndexCopyToStart() const;
  void setIIndexCopyToStart(const quint32& value);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;


  static const quint64 sizeInFile = 12;
};

} // namespace priv
} // namespace libmson

#endif // GLOBALIDTABLEENTRY3FNDX_H
