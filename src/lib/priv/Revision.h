#ifndef REVISION_H
#define REVISION_H

#include <QtCore/qglobal.h>

#include "commonTypes/ExtendedGUID.h"
#include <QUuid>
#include <list>
#include <map>
#include <memory>

namespace libmson {
namespace priv {

typedef std::weak_ptr<class FileNode> FileNode_WPtr_t;

class Revision {
private:
  std::map<quint32, QUuid> m_globalId;
  std::list<FileNode_WPtr_t> m_manifestList;

  ExtendedGUID m_gosid;
  ExtendedGUID m_dependent;

public:
  Revision();
  Revision(
      const std::map<quint32, QUuid>& globalId,
      const std::list<FileNode_WPtr_t>& manifestList, const ExtendedGUID& gosid,
      const ExtendedGUID& dependent);

  std::map<quint32, QUuid> getGlobalId() const;
  void setGlobalId(const std::map<quint32, QUuid>& globalId);
  std::list<FileNode_WPtr_t> getManifestList() const;
  void setManifestList(const std::list<FileNode_WPtr_t>& manifestList);
  ExtendedGUID getGosid() const;
  void setGosid(const ExtendedGUID& gosid);
  ExtendedGUID getDependent() const;
  void setDependent(const ExtendedGUID& dependent);

  friend class RevisionStoreFileParser;
};

} // namespace priv
} // namespace libmson

#endif // REVISION_H
