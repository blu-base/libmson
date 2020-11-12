#ifndef OBJECTDECLARATION2REFCOUNTFND_H
#define OBJECTDECLARATION2REFCOUNTFND_H

#include <QtCore/qglobal.h>

#include "../objectTypes/ObjectDeclaration2Body.h"
//#include "../../objectTypes/ObjectSpaceObjectPropSet.h"
#include "IFileNodeType.h"

#include "../ObjectSpaceObjectPropSet.h"
#include "../RevisionStoreChunkContainer.h"

namespace libmson {
namespace priv {

class ObjectDeclaration2RefCountFND : public IFileNodeType {
private:
  RSChunkContainer_WPtr_t m_blobRef;

  ObjectDeclaration2Body m_body;
  quint8 m_cRef;


  //  ObjectSpaceObjectPropSet m_blob;

public:
  ObjectDeclaration2RefCountFND(RSChunkContainer_WPtr_t parentFileNode);
  virtual ~ObjectDeclaration2RefCountFND() = default;

  RSChunkContainer_WPtr_t getBlobRef() const;
  void setBlobRef(const RSChunkContainer_WPtr_t& value);

  ObjectDeclaration2Body getBody() const;
  void setBody(const ObjectDeclaration2Body& value);

  quint8 getCRef() const;
  void setCRef(const quint8& value);

  std::shared_ptr<ObjectSpaceObjectPropSet> getPropSet();
  //  void setPropSet(const ObjectSpaceObjectPropSet& value);

  virtual quint64 getSizeInFile() const override;

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTDECLARATION2REFCOUNTFND_H
