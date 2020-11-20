#ifndef OBJECTDECLARATION2REFCOUNTFND_H
#define OBJECTDECLARATION2REFCOUNTFND_H

#include <QtCore/qglobal.h>

#include "../Chunkable.h"
#include "../ObjectSpaceObjectPropSet.h"
#include "../objectTypes/ObjectDeclaration2Body.h"
#include "IFileNodeType.h"

namespace libmson {
namespace priv {

class ObjectDeclaration2RefCountFND : public IFileNodeType {
private:
  ObjectSpaceObjectPropSet_WPtr_t m_blobRef;

  ObjectDeclaration2Body m_body;
  quint8 m_cRef;

public:
  ObjectDeclaration2RefCountFND(FileNode_WPtr_t parentFileNode);
  virtual ~ObjectDeclaration2RefCountFND() = default;

  ObjectSpaceObjectPropSet_WPtr_t getBlobRef();
  void setBlobRef(const ObjectSpaceObjectPropSet_WPtr_t& value);

  ObjectDeclaration2Body getBody() const;
  void setBody(const ObjectDeclaration2Body& value);

  quint8 getCRef() const;
  void setCRef(const quint8& value);

  virtual quint64 getSizeInFile() const override;

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTDECLARATION2REFCOUNTFND_H
