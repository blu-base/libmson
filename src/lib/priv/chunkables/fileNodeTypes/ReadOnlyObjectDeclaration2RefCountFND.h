#ifndef READONLYOBJECTDECLARATION2REFCOUNTFND_H
#define READONLYOBJECTDECLARATION2REFCOUNTFND_H

#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

#include "../ObjectSpaceObjectPropSet.h"
#include "../objectTypes/ObjectDeclaration2Body.h"

namespace libmson {
namespace priv {


class ReadOnlyObjectDeclaration2RefCountFND : public IFileNodeType {
private:
  ObjectSpaceObjectPropSet_WPtr_t m_blobRef;

  ObjectDeclaration2Body m_body;
  quint8 m_cRef;

  QByteArray m_md5hash;

public:
  ReadOnlyObjectDeclaration2RefCountFND(FileNode_SPtr_t parentFileNode);
  virtual ~ReadOnlyObjectDeclaration2RefCountFND() = default;

  ObjectSpaceObjectPropSet_WPtr_t getBlobRef();
  void setBlobRef(const ObjectSpaceObjectPropSet_SPtr_t& value);

  ObjectDeclaration2Body getBody() const;
  void setBody(const ObjectDeclaration2Body& value);

  quint8 getCRef() const;
  void setCRef(const quint8& value);

  QByteArray getMd5hash() const;
  void setMd5hash(const QByteArray& value);


  virtual quint64 getSizeInFile() const override;

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;

  static const constexpr quint64 md5HashSize = 16;
};

} // namespace priv
} // namespace libmson

#endif // READONLYOBJECTDECLARATION2REFCOUNTFND_H
