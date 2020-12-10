#ifndef READONLYOBJECTDECLARATION2LARGEREFCOUNTFND_H
#define READONLYOBJECTDECLARATION2LARGEREFCOUNTFND_H

#include "IFileNodeType.h"

#include "../objectTypes/ObjectDeclaration2Body.h"

#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

typedef std::shared_ptr<class ObjectSpaceObjectPropSet>
    ObjectSpaceObjectPropSet_SPtr_t;
typedef std::weak_ptr<class ObjectSpaceObjectPropSet>
    ObjectSpaceObjectPropSet_WPtr_t;

class ReadOnlyObjectDeclaration2LargeRefCountFND : public IFileNodeType {
private:
  ObjectSpaceObjectPropSet_WPtr_t m_blobRef;
  ObjectDeclaration2Body m_body;
  quint32 m_cRef;

  QByteArray m_md5hash;

public:
  ReadOnlyObjectDeclaration2LargeRefCountFND(FileNode_SPtr_t parentFileNode);
  virtual ~ReadOnlyObjectDeclaration2LargeRefCountFND() = default;

  ObjectSpaceObjectPropSet_WPtr_t getBlobRef();
  void setBlobRef(const ObjectSpaceObjectPropSet_SPtr_t& blobRef);

  ObjectDeclaration2Body getBody() const;
  void setBody(const ObjectDeclaration2Body& body);

  quint32 getCRef() const;
  void setCRef(const quint32& cRef);

  QByteArray getMd5hash() const;
  void setMd5hash(const QByteArray& value);

  virtual quint64 getSizeInFile() const override;
  virtual FileNodeTypeID getType() const override
  {
    return FileNodeTypeID::ReadOnlyObjectDeclaration2LargeRefCountFND;
  };

  friend class RevisionStoreFileParser;

  static const quint64 md5HashSize = 16;
};

} // namespace priv
} // namespace libmson

#endif // READONLYOBJECTDECLARATION2LARGEREFCOUNTFND_H
