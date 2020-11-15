#ifndef GLOBALIDTABLESTARTFNDX_H
#define GLOBALIDTABLESTARTFNDX_H

#include "../../IStreamable.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class GlobalIdTableStartFNDX
    : public IFileNodeType
    , public IStreamable {
private:
  quint8 m_reserved;

public:
  GlobalIdTableStartFNDX(FileNode_WPtr_t parentFileNode);
  virtual ~GlobalIdTableStartFNDX() = default;

  quint8 getReserved() const;
  void setReserved(const quint8& value);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;

  static const quint64 sizeInFile = 1;
};

} // namespace priv
} // namespace libmson

#endif // GLOBALIDTABLESTARTFNDX_H
