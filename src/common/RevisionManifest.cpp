#include "RevisionManifest.h"
namespace MSONcommon {
std::vector<FileNode *> RevisionManifest::getFileNodeSquence() const {
  return FileNodeSquence;
}

void RevisionManifest::setFileNodeSquence(
    const std::vector<FileNode *> &value) {
  FileNodeSquence = value;
}

QDataStream &operator<<(QDataStream &ds, const RevisionManifest &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, RevisionManifest &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const RevisionManifest &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void RevisionManifest::deserialize(QDataStream &ds) {}

void RevisionManifest::serialize(QDataStream &ds) const {}

void RevisionManifest::toDebugString(QDebug dbg) const {}

RevisionManifest::RevisionManifest() : FileNodeSquence{} {}

RevisionManifest::~RevisionManifest() {
  for (auto *entry : FileNodeSquence) {
    delete entry;
  }
}
} // namespace MSONcommon
