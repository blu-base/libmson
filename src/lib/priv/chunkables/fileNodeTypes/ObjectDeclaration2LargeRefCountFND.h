#ifndef OBJECTDECLARATION2LARGEREFCOUNTFND_H
#define OBJECTDECLARATION2LARGEREFCOUNTFND_H


#include "../Chunkable.h"
#include "../ObjectSpaceObjectPropSet.h"
#include "../objectTypes/ObjectDeclaration2Body.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class ObjectDeclaration2LargeRefCountFND : public IFileNodeType {
private:
  ObjectSpaceObjectPropSet_WPtr_t m_blobRef;
  ObjectDeclaration2Body m_body;
  quint32 m_cRef;

public:
  ObjectDeclaration2LargeRefCountFND(FileNode_WPtr_t parentFileNode);
  virtual ~ObjectDeclaration2LargeRefCountFND() = default;

  ObjectSpaceObjectPropSet_WPtr_t getBlobRef() const;
  void setBlobRef(const ObjectSpaceObjectPropSet_WPtr_t& blobRef);

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
