#include "RevisionManifestList.h"

#include "commonTypes/Enums.h"
#include <algorithm>

#include "DocumentSingleton.h"

#include "FileNodeTypes/ObjectGroupListReferenceFND.h"
#include "helper/Helper.h"
namespace MSONcommon {
FileNodeChunkReference RevisionManifestList::getRef() const { return mRef; }

void RevisionManifestList::setRef(const FileNodeChunkReference &ref) {
  mRef = ref;
}

QDataStream &operator>>(QDataStream &ds, RevisionManifestList &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const RevisionManifestList &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void RevisionManifestList::deserialize(QDataStream &ds) {
  FileNodeListFragment *fragment = new FileNodeListFragment(mRef);

  ds.device()->seek(mRef.stp());

  ds >> *fragment;

  mFileNodeListFragments.push_back(fragment);

  for (auto *entry : fragment->rgFileNodes()) {
    if (entry->getFileNodeID() !=
            static_cast<quint16>(FileNodeTypeID::ChunkTerminatorFND) &&
        entry->getFileNodeID() != 0) {
      mFileNodeSequence.push_back(entry);
    }
  }

  //  copy_if(fragment->rgFileNodes().begin(), fragment->rgFileNodes().end(),
  //          back_inserter(mFileNodeSequence), [](FileNode *entry) {
  //            return entry->getFileNodeID() !=
  //                       static_cast<quint16>(
  //                           FileNodeTypeID::ChunkTerminatorFND) &&
  //                   entry->getFileNodeID() != 0;
  //          });

  RevisionManifest *revManifest{};

  std::copy_if(mFileNodeSequence.begin(), mFileNodeSequence.end(),
               back_inserter(mRevisionRoleDeclarations), [](FileNode *entry) {
                 return entry->getFileNodeID() ==
                        static_cast<quint16>(
                            FileNodeTypeID::RevisionRoleDeclarationFND);
               });

  std::copy_if(
      mFileNodeSequence.begin(), mFileNodeSequence.end(),
      back_inserter(mRevisionRoleAndContextDeclarations), [](FileNode *entry) {
        return entry->getFileNodeID() ==
               static_cast<quint16>(
                   FileNodeTypeID::RevisionRoleAndContextDeclarationFND);
      });

  for (FileNode *fn : mFileNodeSequence) {
    if (fn->getFileNodeID() ==
            static_cast<quint16>(FileNodeTypeID::RevisionManifestStart6FND) ||
        fn->getFileNodeID() ==
            static_cast<quint16>(FileNodeTypeID::RevisionManifestStart7FND) ||
        fn->getFileNodeID() ==
            static_cast<quint16>(FileNodeTypeID::RevisionManifestStart4FND)) {

      revManifest = new RevisionManifest();
      revManifest->FileNodeSquence.push_back(fn);

    } else if (fn->getFileNodeID() ==
               static_cast<quint16>(FileNodeTypeID::RevisionManifestEndFND)) {
      revManifest->FileNodeSquence.push_back(fn);
      mRevisionManifests.push_back(revManifest);
      revManifest = new RevisionManifest();
    } else if (fn->getFileNodeID() !=
                   static_cast<quint16>(FileNodeTypeID::ChunkTerminatorFND) &&
               fn->getFileNodeID() !=
                   static_cast<quint16>(
                       FileNodeTypeID::RevisionManifestListStartFND)) {
      if (fn->getFileNodeID() ==
          static_cast<quint16>(FileNodeTypeID::ObjectDataEncryptionKeyV2FNDX)) {

        MSONcommon::DocumentSingleton::getDoc()->setIsEncrypted(true);
      }

      revManifest->FileNodeSquence.push_back(fn);
      if (fn->getFileNodeID() ==
          static_cast<quint16>(FileNodeTypeID::ObjectGroupListReferenceFND)) {

        auto *objectGroupListRef =
            dynamic_cast<ObjectGroupListReferenceFND *>(fn->getFnt());

        ObjectGroupList *objectGroupList =
            new ObjectGroupList(objectGroupListRef->ref());

        ds.device()->seek(objectGroupListRef->ref().stp());
        ds >> *objectGroupList;

        mObjectGroupLists.push_back(objectGroupList);
      }
    }
  }
}

void RevisionManifestList::toDebugString(QDebug dbg) const {

    dbg << "RevisionManifestList:\n";
    dbg << "ref: " << mRef << '\n';
    dbg << "FileNodeListFragments count:              " << mFileNodeListFragments.size() << '\n';
    dbg << "RevisionManifests count:                  " << mRevisionManifests.size() << '\n';
    dbg << "RevisionRoleDeclarations count:           " << mRevisionRoleDeclarations.size() << '\n';
    dbg << "RevisionRoleAndContextDeclarations count: " << mRevisionRoleAndContextDeclarations.size() << '\n';
    dbg << "ObjectGroupLists count:                   " << mObjectGroupLists.size() << '\n';
    dbg << "FileNodeSequence count:                   " << mFileNodeSequence.size() << '\n';


    dbg << "\nRevisionManifestList FileNodeListFragments....\n";
    for(size_t i {0}; i < mFileNodeListFragments.size(); i++) {
        dbg << *mFileNodeListFragments[i];
    }

    dbg << "\nRevisionManifestList RevisionManifests....\n";
    for(size_t i {0}; i < mRevisionManifests.size(); i++) {
        dbg << *mRevisionManifests[i];
    }
    dbg << "\nRevisionManifestList RevisionRoleDeclarations....\n";
    for(size_t i {0}; i < mRevisionRoleDeclarations.size(); i++) {
        dbg << *mRevisionRoleDeclarations[i];
    }
    dbg << "\nRevisionManifestList RevisionRoleAndContextDeclarations....\n";
    for(size_t i {0}; i < mRevisionRoleAndContextDeclarations.size(); i++) {
        dbg << *mRevisionRoleAndContextDeclarations[i];
    }
    dbg << "\nRevisionManifestList ObjectGroupLists....\n";
    for(size_t i {0}; i < mObjectGroupLists.size(); i++) {
        dbg << *mObjectGroupLists[i];
    }
    dbg << "\nRevisionManifestList FileNodeSequence....\n";
    for(size_t i {0}; i < mFileNodeSequence.size(); i++) {
        dbg << *mFileNodeSequence[i];
    }




}

RevisionManifestList::RevisionManifestList(FileNodeChunkReference ref)
    : mRef{ref}, mFileNodeSequence{} {}

RevisionManifestList::~RevisionManifestList() {
  for (auto *entry : mFileNodeListFragments) {
    delete entry;
  }
  for (auto *entry : mRevisionManifests) {
    delete entry;
  }
  for (auto *entry : mRevisionRoleDeclarations) {
    delete entry;
  }
  for (auto *entry : mRevisionRoleAndContextDeclarations) {
    delete entry;
  }
  for (auto *entry : mObjectGroupLists) {
    delete entry;
  }
  for (auto *entry : mFileNodeSequence) {
    delete entry;
  }
}

std::vector<FileNode *> RevisionManifestList::getFileNodeSequence() const {
  return mFileNodeSequence;
}

void RevisionManifestList::setFileNodeSequence(
    const std::vector<FileNode *> &value) {
  mFileNodeSequence = value;
}

std::vector<ObjectGroupList *>
RevisionManifestList::getObjectGroupLists() const {
  return mObjectGroupLists;
}

void RevisionManifestList::setObjectGroupLists(
    const std::vector<ObjectGroupList *> &value) {
  mObjectGroupLists = value;
}

std::vector<FileNode *>
RevisionManifestList::getRevisionRoleAndContextDeclarations() const {
  return mRevisionRoleAndContextDeclarations;
}

void RevisionManifestList::setRevisionRoleAndContextDeclarations(
    const std::vector<FileNode *> &value) {
  mRevisionRoleAndContextDeclarations = value;
}

std::vector<FileNode *>
RevisionManifestList::getRevisionRoleDeclarations() const {
  return mRevisionRoleDeclarations;
}

void RevisionManifestList::setRevisionRoleDeclarations(
    const std::vector<FileNode *> &value) {
  mRevisionRoleDeclarations = value;
}

std::vector<RevisionManifest *>
RevisionManifestList::getRevisionManifests() const {
  return mRevisionManifests;
}

void RevisionManifestList::setRevisionManifests(
    const std::vector<RevisionManifest *> &value) {
  mRevisionManifests = value;
}

std::vector<FileNodeListFragment *>
RevisionManifestList::getFileNodeListFragments() const {
  return mFileNodeListFragments;
}

void RevisionManifestList::setFileNodeListFragments(
    const std::vector<FileNodeListFragment *> &value) {
  mFileNodeListFragments = value;
}
} // namespace MSONcommon
