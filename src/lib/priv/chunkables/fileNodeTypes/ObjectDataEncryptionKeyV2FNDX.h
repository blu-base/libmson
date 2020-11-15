#ifndef OBJECTDATAENCRYPTIONKEYV2FNDX_H
#define OBJECTDATAENCRYPTIONKEYV2FNDX_H

#include "../Chunkable.h"
#include "../EncryptedData.h"
#include "IFileNodeType.h"
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {

class ObjectDataEncryptionKeyV2FNDX : public IFileNodeType {
private:
  EncryptedData_WPtr_t m_blobRef;

public:
  ObjectDataEncryptionKeyV2FNDX(FileNode_WPtr_t parentFileNode);
  virtual ~ObjectDataEncryptionKeyV2FNDX() = default;

  EncryptedData_WPtr_t getBlobRef() const;
  void setBlobRef(const EncryptedData_WPtr_t& value);

  virtual quint64 getSizeInFile() const override;

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTDATAENCRYPTIONKEYV2FNDX_H
