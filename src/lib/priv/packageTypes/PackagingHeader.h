#ifndef PACKAGINGHEADER_H
#define PACKAGINGHEADER_H

#include <QtCore/qglobal.h>

#include <QUuid>
#include <priv/IStreamable.h>


namespace libmson {
namespace packStore {


/**
 * @brief The PackagingHeader is part of the PackagingStructure described in
 * [MS-ONESTORE] section 2.8.1
 *
 * This part is separated because it is dissimilar to the [FSHTTPB] protocol and
 * unique to [MS-ONESTORE]
 */
class PackagingHeader : public priv::IStreamable {
public:
  PackagingHeader();
  PackagingHeader(QUuid guidFile);
  PackagingHeader(
      QUuid fileType, QUuid guidFile, QUuid guidLegacyFileVersion,
      QUuid fileFormat, quint32 reserved);

  QUuid getGuidFile() const;
  void setGuidFile(QUuid guidFile);

  QUuid getGuidFileType() const;
  void setGuidFileType(QUuid fileType);

  QUuid getGuidLegacyFileVersion() const;
  void setGuidLegacyFileVersion(QUuid guidLegacyFileVersion);

  QUuid getGuidFileFormat() const;
  void setGuidFileFormat(QUuid fileFormat);

  quint32 getReserved() const;
  void setReserved(quint32 reserved);


  static quint64 getSizeInFile() { return sizeInFile; }

  /**
   * @brief guidFileType contains the GUID specified in [MS-ONESTORE]
   * section 2.8.1
   */
  static const QUuid guidFileType;

  /**
   * @brief guidFileFormat contains the GUID specified in [MS-ONESTORE]
   * section 2.8.1
   */
  static const QUuid guidFileFormat;


  friend class PackageStoreFileParser;

private:
  QUuid m_guidFileType;
  QUuid m_guidFile;
  QUuid m_guidLegacyFileVersion; /* should have the same value as m_guidFile */
  QUuid m_guidFileFormat;

  quint32 m_reserved;


  // 4 GUID, and 4 bytes reserved
  static const quint8 sizeInFile = 0x44;

  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace fsshttpb
} // namespace libmson

#endif // PACKAGINGHEADER_H
