#ifndef OBJECTGROUPLIST_H
#define OBJECTGROUPLIST_H

#include <QtCore/qglobal.h>
#include <vector>


#include "chunkables/FileNode.h"
#include "chunkables/FileNodeListFragment.h"
#include "commonTypes/FileNodeChunkReference.h"


class QDataStream;

namespace libmson {
namespace priv {

class ObjectGroupList {
private:
  std::vector<std::shared_ptr<FileNodeListFragment>> m_fileNodeListFragments;

public:
  ObjectGroupList();
};

} // namespace priv
} // namespace libmson

#endif // OBJECTGROUPLIST_H
