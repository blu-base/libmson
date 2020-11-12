#ifndef OBJECTDECLARATIONWITHREFCOUNTFNDX_H
#define OBJECTDECLARATIONWITHREFCOUNTFNDX_H

#include <QtCore/qglobal.h>

#include "../ObjectSpaceObjectPropSet.h"
#include "../objectTypes/ObjectDeclarationWithRefCountBody.h"

#include "IFileNodeType.h"

namespace libmson {
namespace priv {

class ObjectDeclarationWithRefCountFNDX : public IFileNodeType {
private:
  RSChunkContainer_WPtr_t m_objectRef;
  ObjectDeclarationWithRefCountBody m_body;
  quint8 m_cRef;

public:
  ObjectDeclarationWithRefCountFNDX(RSChunkContainer_WPtr_t parentFileNode);
  virtual ~ObjectDeclarationWithRefCountFNDX() = default;

  RSChunkContainer_WPtr_t getObjectRef() const;
  void setObjectRef(const RSChunkContainer_WPtr_t& value);

  ObjectDeclarationWithRefCountBody getBody() const;
  void setBody(const ObjectDeclarationWithRefCountBody& value);

  quint8 getCRef() const;
  void setCRef(const quint8& value);

  std::shared_ptr<ObjectSpaceObjectPropSet> getPropSet();


  virtual quint64 getSizeInFile() const override;

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;

  // private:
  //  virtual void deserialize(QDataStream& ds) override;
  //  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTDECLARATIONWITHREFCOUNTFNDX_H
