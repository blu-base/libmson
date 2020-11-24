#ifndef OBJECTDECLARATIONWITHREFCOUNTFNDX_H
#define OBJECTDECLARATIONWITHREFCOUNTFNDX_H

#include <QtCore/qglobal.h>

#include "../objectTypes/ObjectDeclarationWithRefCountBody.h"

#include "IFileNodeType.h"

namespace libmson {
namespace priv {

typedef std::shared_ptr<class ObjectSpaceObjectPropSet>
    ObjectSpaceObjectPropSet_SPtr_t;
typedef std::weak_ptr<class ObjectSpaceObjectPropSet>
    ObjectSpaceObjectPropSet_WPtr_t;

class ObjectDeclarationWithRefCountFNDX : public IFileNodeType {
private:
  ObjectSpaceObjectPropSet_WPtr_t m_objectRef;
  ObjectDeclarationWithRefCountBody m_body;
  quint8 m_cRef;

public:
  ObjectDeclarationWithRefCountFNDX(FileNode_SPtr_t parentFileNode);
  virtual ~ObjectDeclarationWithRefCountFNDX() = default;

  ObjectSpaceObjectPropSet_WPtr_t getObjectRef() const;
  void setObjectRef(const ObjectSpaceObjectPropSet_SPtr_t& value);

  ObjectDeclarationWithRefCountBody getBody() const;
  void setBody(const ObjectDeclarationWithRefCountBody& value);

  quint8 getCRef() const;
  void setCRef(const quint8& value);

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
