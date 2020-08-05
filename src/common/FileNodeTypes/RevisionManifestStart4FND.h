#ifndef REVISIONMANIFESTSTART4FND_H
#define REVISIONMANIFESTSTART4FND_H

#include <QtCore/qglobal.h>

#include "IFileNodeType.h"

#include "../commonTypes/ExtendedGUID.h"

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
class RevisionManifestStart4FND : public IFileNodeType {
public:
  RevisionManifestStart4FND();

  /**
   * @var rid
   * @brief pecifies the identity of this revision (section 2.1.8).
   *
   * \li MUST NOT be "{{00000000-0000-0000-0000-000000000000}, 0}"
   * \li MUST be unique among RevisionManifestStart4FND.rid fields within the
   * containing revision manifest list.
   */
  ExtendedGUID rid;

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
  ExtendedGUID ridDependent;

  /**
   * @var timeCreation
   * @brief undefined and must be ignored
   */
  quint64 timeCreation;

  /**
   * @var revisionRole
   * @brief specifies the revision role that labels this revision
   */
  qint32 revisionRole;

  /**
   * @var odcsDefault
   * @brief specifies whether the data contained by this revision manifest is
   * encrypted.
   *
   * MUST be 0 and MUST be ignored.
   */
  quint16 odcsDefault;

  quint16 getOdcsDefault() const;
  void setOdcsDefault(const quint16 &value);

  qint32 getRevisionRole() const;
  void setRevisionRole(const qint32 &value);

  quint64 getTimeCreation() const;
  void setTimeCreation(const quint64 &value);

  ExtendedGUID getRidDependent() const;
  void setRidDependent(const ExtendedGUID &value);

  ExtendedGUID getRid() const;
  void setRid(const ExtendedGUID &value);

  // IFileNodeType interfaces
private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;
};

#endif // REVISIONMANIFESTSTART4FND_H