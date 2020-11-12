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
  static const quint64 m_header = 0xFB6BA385DAD1A067;
  QByteArray m_data;
  static const quint64 m_footer = 0x2649294F8E198B3C;

public:
  EncryptedData();
  EncryptedData(const QByteArray& data);

  QByteArray getData() const;
  void setData(const QByteArray& encryptionData);

  // Chunkable interface
  virtual quint64 cb() const override;
  virtual RevisionStoreChunkType getType() const override;


  friend class RevisionStoreFileParser;
  friend class RevisionStoreFileWriter;


  /// Edge case, where m_data.size() is 0. Only m_header and m_footer contribute in min case.
  static const quint64 minSizeInFile = 16;
};

} // namespace priv
} // namespace libmson

#endif // ENCRYPTEDDATA_H
