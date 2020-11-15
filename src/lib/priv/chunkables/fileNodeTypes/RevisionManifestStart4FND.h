#ifndef REVISIONMANIFESTSTART4FND_H
#define REVISIONMANIFESTSTART4FND_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

namespace libmson {
namespace priv {
/**
 * @brief specifies the beginning of a revision manifest.
 * @class RevisionManifestStart4FND
 *
 * This revision manifest applies to the default context of the containing
 * object space.
 *
 * FileNode Type defined by [MS-ONESTORE]
 * 2.5.6 RevisionManifestStart4FND
 */
class RevisionManifestStart4FND
    : public IFileNodeType
    , public IStreamable {
private:
  /**
   * @var rid
   * @brief pecifies the identity of this revision (section 2.1.8).
   *
   * \li MUST NOT be "{{00000000-0000-0000-0000-000000000000}, 0}"
   * \li MUST be unique among RevisionManifestStart4FND.rid fields within the
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
   * Otherwise, this value MUST be equal to the RevisionManifestStart4FND.rid
   * field of a previous revision manifest within this revision manifest list.
   */
  ExtendedGUID m_ridDependent;

  /**
   * @var timeCreation
   * @brief undefined and must be ignored
   */
  quint64 m_timeCreation;

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
   * MUST be 0 and MUST be ignored.
   */
  quint16 m_odcsDefault;

public:
  RevisionManifestStart4FND(FileNode_WPtr_t parentFileNode);
  virtual ~RevisionManifestStart4FND() = default;


  quint16 getOdcsDefault() const;
  void setOdcsDefault(const quint16& value);

  qint32 getRevisionRole() const;
  void setRevisionRole(const qint32& value);

  quint64 getTimeCreation() const;
  void setTimeCreation(const quint64& value);

  ExtendedGUID getRidDependent() const;
  void setRidDependent(const ExtendedGUID& value);

  ExtendedGUID getRid() const;
  void setRid(const ExtendedGUID& value);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;


  static const quint64 sizeInFile;
};

} // namespace priv
} // namespace libmson

#endif // REVISIONMANIFESTSTART4FND_H
