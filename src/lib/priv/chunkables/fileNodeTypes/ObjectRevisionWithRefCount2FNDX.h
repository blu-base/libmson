#ifndef OBJECTREVISIONWITHREFCOUNT2FNDX_H
#define OBJECTREVISIONWITHREFCOUNT2FNDX_H

#include <QtCore/qglobal.h>

#include "../../commonTypes/CompactID.h"

#include "IFileNodeType.h"

namespace libmson {
namespace priv {

typedef std::shared_ptr<class ObjectSpaceObjectPropSet>
    ObjectSpaceObjectPropSet_SPtr_t;
typedef std::weak_ptr<class ObjectSpaceObjectPropSet>
    ObjectSpaceObjectPropSet_WPtr_t;

class ObjectRevisionWithRefCount2FNDX : public IFileNodeType {
private:
  ObjectSpaceObjectPropSet_WPtr_t m_ref;

  CompactID m_oid;

  bool m_fHasOidReferences;
  bool m_fHasOsidReferences;

  quint32 m_cRef;

public:
  ObjectRevisionWithRefCount2FNDX(FileNode_SPtr_t parentFileNode);
  virtual ~ObjectRevisionWithRefCount2FNDX() = default;

  ObjectSpaceObjectPropSet_WPtr_t getRef() const;
  void setRef(const ObjectSpaceObjectPropSet_SPtr_t value);

  CompactID getOid() const;
  void setOid(const CompactID& value);

  bool getFHasOidReferences() const;
  void setFHasOidReferences(bool value);

  bool getFHasOsidReferences() const;
  void setFHasOsidReferences(bool value);

  quint32 getCRef() const;
  void setCRef(const quint32& value);


  virtual quint64 getSizeInFile() const override;
  virtual FileNodeTypeID getType() const override
  {
    return FileNodeTypeID::ObjectRevisionWithRefCount2FNDX;
  };

  friend class RevisionStoreFileParser;

private:
  //  virtual void deserialize(QDataStream& ds) override;
  //  virtual void serialize(QDataStream& ds) const override;


  static const quint64 sizeInFileBase = 12;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTREVISIONWITHREFCOUNT2FNDX_H
