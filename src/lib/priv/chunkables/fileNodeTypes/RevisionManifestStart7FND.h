#ifndef REVISIONMANIFESTSTART7FND_H
#define REVISIONMANIFESTSTART7FND_H

#include <QtCore/qglobal.h>

#include "../../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"
#include "RevisionManifestStart6FND.h"

namespace libmson{
namespace priv{
/**
 * @brief specifies the beginning of a revision manifest for a context of an
 * object space
 * @class RevisionManifestStart7FND
 *
 * FileNode Type defined by [MS-ONESTORE]
 * 2.5.8 RevisionManifestStart7FND
 */
class RevisionManifestStart7FND : public IFileNodeType {
private:
  /**
   * @var base
   * @brief specifies the identity and other attributes of this revision
   *
   */
  RevisionManifestStart6FND m_base;

  /**
   * @var gctxid
   * @brief specifies the context that labels this revision
   */
  ExtendedGUID m_gctxid;

public:
  RevisionManifestStart7FND() = default;

  RevisionManifestStart6FND getBase() const;
  void setBase(const RevisionManifestStart6FND &value);

  ExtendedGUID getGctxid() const;
  void setGctxid(const ExtendedGUID &value);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;




};

} //namespace priv
} // namespace libmson

#endif // REVISIONMANIFESTSTART7FND_H
