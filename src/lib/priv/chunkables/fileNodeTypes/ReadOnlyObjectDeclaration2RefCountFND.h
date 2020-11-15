#ifndef READONLYOBJECTDECLARATION2REFCOUNTFND_H
#define READONLYOBJECTDECLARATION2REFCOUNTFND_H

#include "IFileNodeType.h"
#include "ObjectDeclaration2RefCountFND.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class ReadOnlyObjectDeclaration2RefCountFND : public IFileNodeType {
private:
  ObjectDeclaration2RefCountFND m_base;

  QByteArray m_md5hash;

public:
  ReadOnlyObjectDeclaration2RefCountFND(FileNode_WPtr_t parentFileNode);
  virtual ~ReadOnlyObjectDeclaration2RefCountFND() = default;

  ObjectDeclaration2RefCountFND getBase() const;
  void setBase(const ObjectDeclaration2RefCountFND& value);

  QByteArray getMd5hash() const;
  void setMd5hash(const QByteArray& value);

  ObjectSpaceObjectPropSet_WPtr_t getBlobRef() const;

  ObjectDeclaration2Body getBody() const;


  virtual quint64 getSizeInFile() const override;

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;

private:
  static const quint64 md5HashSize = 16;
};

} // namespace priv
} // namespace libmson

#endif // READONLYOBJECTDECLARATION2REFCOUNTFND_H
