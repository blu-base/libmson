#ifndef ENCRYPTEDDATA_H
#define ENCRYPTEDDATA_H

#include "Chunkable.h"
#include <QByteArray>
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {


/// Chunk referenced by ObjectDataEncryptionKeyV2FNDX FileNode
class EncryptedData : public Chunkable {
private:
  QByteArray m_data;


public:
  EncryptedData(const quint64 initialStp = 0, const quint64 initialCb = 0);
  EncryptedData(const QByteArray& data);

  QByteArray getData() const;
  void setData(const QByteArray& encryptionData);

  static const quint64 header = 0xFB6BA385DAD1A067;
  static const quint64 footer = 0x2649294F8E198B3C;

  friend class RevisionStoreFileParser;

  /// Edge case, where m_data.size() is 0. Only m_header and m_footer contribute
  /// in min case.
  static const quint64 minSizeInFile = 16;

private:
  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;
};

typedef std::shared_ptr<EncryptedData> EncryptedData_SPtr_t;
typedef std::weak_ptr<EncryptedData> EncryptedData_WPtr_t;

} // namespace priv
} // namespace libmson

#endif // ENCRYPTEDDATA_H
