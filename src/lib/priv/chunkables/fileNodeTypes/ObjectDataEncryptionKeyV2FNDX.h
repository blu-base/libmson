#ifndef OBJECTDATAENCRYPTIONKEYV2FNDX_H
#define OBJECTDATAENCRYPTIONKEYV2FNDX_H

#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

typedef std::shared_ptr<class EncryptedData> EncryptedData_SPtr_t;
typedef std::weak_ptr<class EncryptedData> EncryptedData_WPtr_t;


class ObjectDataEncryptionKeyV2FNDX : public IFileNodeType {
private:
  EncryptedData_WPtr_t m_blobRef;

public:
  ObjectDataEncryptionKeyV2FNDX(FileNode_SPtr_t parentFileNode);
  virtual ~ObjectDataEncryptionKeyV2FNDX() = default;

  EncryptedData_WPtr_t getBlobRef() const;
  void setBlobRef(const EncryptedData_SPtr_t& value);

  virtual quint64 getSizeInFile() const override;

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTDATAENCRYPTIONKEYV2FNDX_H
