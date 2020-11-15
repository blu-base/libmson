#ifndef READONLYOBJECTDECLARATION2LARGEREFCOUNTFND_H
#define READONLYOBJECTDECLARATION2LARGEREFCOUNTFND_H

#include "../../commonTypes/FileNodeChunkReference.h"
#include "IFileNodeType.h"
#include "ObjectDeclaration2LargeRefCountFND.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class ReadOnlyObjectDeclaration2LargeRefCountFND : public IFileNodeType {
private:
  ObjectDeclaration2LargeRefCountFND m_base;

  QByteArray m_md5hash;

public:
  ReadOnlyObjectDeclaration2LargeRefCountFND(FileNode_WPtr_t parentFileNode);
  virtual ~ReadOnlyObjectDeclaration2LargeRefCountFND() = default;

  ObjectSpaceObjectPropSet_WPtr_t getBlobRef() const;

  ObjectDeclaration2Body getBody() const;

  ObjectDeclaration2LargeRefCountFND getBase() const;
  void setBase(const ObjectDeclaration2LargeRefCountFND& value);

  QByteArray getMd5hash() const;
  void setMd5hash(const QByteArray& value);

  virtual quint64 getSizeInFile() const override;

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;

private:
  static const quint64 md5HashSize = 16;
};

} // namespace priv
} // namespace libmson

#endif // READONLYOBJECTDECLARATION2LARGEREFCOUNTFND_H
