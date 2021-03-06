#ifndef REVISIONMANIFESTSTART6FND_H
#define REVISIONMANIFESTSTART6FND_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

namespace libmson {
namespace priv {
/**
 * @brief specifies the beginning of a revision manifest for the default context
 * of an object space.
 * @class RevisionManifestStart6FND
 *
 * FileNode Type defined by [MS-ONESTORE]
 * 2.5.7 RevisionManifestStart6FND
 */
class RevisionManifestStart6FND
    : public IFileNodeType
    , public IStreamable {
private:
  /**
   * @var rid
   * @brief specifies the identity of this revision.
   *
   * \li MUST NOT be "{{00000000-0000-0000-0000-000000000000}, 0}"
   * \li MUST be unique among RevisionManifestStart6FND.rid and
   * RevisionManifestStart7FND.base.rid fields within the
   * containing revision manifest list.
   */
  ExtendedGUID m_rid;

  /**
   * @var ridDependent
   * @brief specifies the identity of a dependency revision
   *
   * If the value is "{{00000000-0000-0000-0000-000000000000}, 0}",
   * then this revision manifest has no dependency revision.
   *
   * Otherwise, this value MUST be equal to the RevisionManifestStart6FND.rid
   * and RevisionManifestStart7FND.base.rid fields of a previous revision
   * manifest within this revision manifest list.
   */
  ExtendedGUID m_ridDependent;

  /**
   * @var revisionRole
   * @brief specifies the revision role that labels this revision
   */
  qint32 m_revisionRole;

  /**
   * @var odcsDefault
   * @brief specifies whether the data contained by this revision manifest is
   * encrypted.
   *
   * Values:
   * \li 0x0000 - No encryption.
   * \li 0x0002 - Encrypted.
   *
   * If encrypted, Property sets within this revision manifest MUST be ignored
   * and MUST NOT be altered.
   */
  quint16 m_odcsDefault;

public:
  RevisionManifestStart6FND(FileNode_SPtr_t parentFileNode);
  virtual ~RevisionManifestStart6FND() = default;


  quint16 getOdcsDefault() const;
  void setOdcsDefault(const quint16& value);

  qint32 getRevisionRole() const;
  void setRevisionRole(const qint32& value);

  ExtendedGUID getRidDependent() const;
  void setRidDependent(const ExtendedGUID& value);

  ExtendedGUID getRid() const;
  void setRid(const ExtendedGUID& value);

  virtual quint64 getSizeInFile() const override;
  virtual FileNodeTypeID getType() const override
  {
    return FileNodeTypeID::RevisionManifestStart6FND;
  };

  friend class RevisionStoreFileParser;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;


  static const quint64 sizeInFile;
};

} // namespace priv
} // namespace libmson

#endif // REVISIONMANIFESTSTART6FND_H
