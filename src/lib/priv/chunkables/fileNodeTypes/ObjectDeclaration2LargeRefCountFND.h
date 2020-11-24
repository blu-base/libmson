#ifndef OBJECTDECLARATION2LARGEREFCOUNTFND_H
#define OBJECTDECLARATION2LARGEREFCOUNTFND_H


#include "../objectTypes/ObjectDeclaration2Body.h"

#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

typedef std::shared_ptr<class ObjectSpaceObjectPropSet>
    ObjectSpaceObjectPropSet_SPtr_t;
typedef std::weak_ptr<class ObjectSpaceObjectPropSet>
    ObjectSpaceObjectPropSet_WPtr_t;

class ObjectDeclaration2LargeRefCountFND : public IFileNodeType {
private:
  ObjectSpaceObjectPropSet_WPtr_t m_blobRef;
  ObjectDeclaration2Body m_body;
  quint32 m_cRef;

public:
  ObjectDeclaration2LargeRefCountFND(FileNode_SPtr_t parentFileNode);
  virtual ~ObjectDeclaration2LargeRefCountFND() = default;

  ObjectSpaceObjectPropSet_WPtr_t getBlobRef();
  void setBlobRef(const ObjectSpaceObjectPropSet_SPtr_t& blobRef);

  ObjectDeclaration2Body getBody() const;
  void setBody(const ObjectDeclaration2Body& body);

  quint32 getCRef() const;
  void setCRef(const quint32& cRef);

  virtual quint64 getSizeInFile() const override;

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTDECLARATION2LARGEREFCOUNTFND_H
