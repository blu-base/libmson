#ifndef REVISIONMANIFESTLISTSTARTFND_H
#define REVISIONMANIFESTLISTSTARTFND_H

#include <QtCore/qglobal.h>

#include "../../IStreamable.h"
#include "../../commonTypes/ExtendedGUID.h"
#include "IFileNodeType.h"

namespace libmson {
namespace priv {
/**
 * @brief specifies the beginning of a revision manifest list
 * @class RevisionManifestListStartFND
 *
 * FileNode Type defined by [MS-ONESTORE]
 * 2.5.5 RevisionManifestListStartFND
 */
class RevisionManifestListStartFND
    : public IFileNodeType
    , public IStreamable {
private:
  /**
   * @brief gosid
   * @var gosid
   * specifies the identity of the object space being revised
   * by the revisions in this list.
   */
  ExtendedGUID m_gosid;

  /**
   * @brief must be ignored
   * @var nInstance;
   */
  quint32 m_nInstance;

public:
  RevisionManifestListStartFND(FileNode_WPtr_t parentFileNode);
  virtual ~RevisionManifestListStartFND() = default;

  ExtendedGUID getGosid() const;
  void setGosid(const ExtendedGUID& value);

  quint32 getNInstance() const;
  void setNInstance(const quint32& value);

  virtual quint64 getSizeInFile() const override;

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace priv
} // namespace libmson

#endif // REVISIONMANIFESTLISTSTARTFND_H
