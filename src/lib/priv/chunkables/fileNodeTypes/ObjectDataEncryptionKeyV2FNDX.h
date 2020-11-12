#ifndef OBJECTDATAENCRYPTIONKEYV2FNDX_H
#define OBJECTDATAENCRYPTIONKEYV2FNDX_H

#include <QtCore/qglobal.h>

#include "IFileNodeType.h"

#include "../../chunkables/EncryptedData.h"
#include "../../chunkables/RevisionStoreChunkContainer.h"

namespace libmson {
namespace priv {

class ObjectDataEncryptionKeyV2FNDX : public IFileNodeType {
private:
  RSChunkContainer_WPtr_t m_blobRef;

public:
  ObjectDataEncryptionKeyV2FNDX(RSChunkContainer_WPtr_t parentFileNode);
  virtual ~ObjectDataEncryptionKeyV2FNDX() = default;

  RSChunkContainer_WPtr_t getBlobRef() const;
  void setBlobRef(const RSChunkContainer_WPtr_t& value);

  std::shared_ptr<EncryptedData> getEncryptionData() const;

  virtual quint64 getSizeInFile() const override;

  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;
};

} // namespace priv
} // namespace libmson

#endif // OBJECTDATAENCRYPTIONKEYV2FNDX_H
