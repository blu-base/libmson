#include "RevisionManifestList.h"

#include "commonTypes/Enums.h"
#include <algorithm>

#include "DocumentSingleton.h"

#include "FileNodeTypes/ObjectGroupListReferenceFND.h"
#include "helper/Helper.h"
namespace MSONcommon {
FileNodeChunkReference RevisionManifestList::getRef() const { return m_Ref; }

void RevisionManifestList::setRef(const FileNodeChunkReference &ref) {
    m_Ref = ref;
}



QDataStream &operator>>(QDataStream &ds, RevisionManifestList &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const RevisionManifestList &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void RevisionManifestList::generateXml(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("RevisionManifestList");

    xmlWriter.writeStartElement("ref");
    m_Ref.generateXml(xmlWriter);
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("FileNodeListFragments");
    for (auto entry : m_FileNodeListFragments) {
        entry->generateXml(xmlWriter);
    }
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("RevisionManifests");
    for (auto entry : m_RevisionManifests) {
        entry->generateXml(xmlWriter);
    }
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("RevisionRoleDeclarations");
    for (auto entry : m_RevisionRoleDeclarations) {
        entry->generateXml(xmlWriter);
    }
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("RevisionRoleAndContextDeclarations");
    for (auto entry : m_RevisionRoleAndContextDeclarations) {
        entry->generateXml(xmlWriter);
    }
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("ObjectGroupLists");
    for (auto entry : m_ObjectGroupLists) {
        entry->generateXml(xmlWriter);
    }
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("FileNodeSequence");
    for (auto entry : m_FileNodeSequence) {
        entry->generateXml(xmlWriter);
    }
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
}

void RevisionManifestList::deserialize(QDataStream &ds) {
  FileNodeListFragment *fragment = new FileNodeListFragment(m_Ref);

  ds.device()->seek(m_Ref.stp());

  ds >> *fragment;

  m_FileNodeListFragments.push_back(fragment);

  for (auto *entry : fragment->rgFileNodes()) {
    if (entry->getFileNodeID() !=
            static_cast<quint16>(FileNodeTypeID::ChunkTerminatorFND) &&
        entry->getFileNodeID() != 0) {
      m_FileNodeSequence.push_back(entry);
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

  std::copy_if(m_FileNodeSequence.begin(), m_FileNodeSequence.end(),
               back_inserter(m_RevisionRoleDeclarations), [](FileNode *entry) {
                 return entry->getFileNodeID() ==
                        static_cast<quint16>(
                            FileNodeTypeID::RevisionRoleDeclarationFND);
               });

  std::copy_if(
      m_FileNodeSequence.begin(), m_FileNodeSequence.end(),
      back_inserter(m_RevisionRoleAndContextDeclarations), [](FileNode *entry) {
        return entry->getFileNodeID() ==
               static_cast<quint16>(
                   FileNodeTypeID::RevisionRoleAndContextDeclarationFND);
      });

  for (FileNode *fn : m_FileNodeSequence) {
    if (fn->getFileNodeID() ==
            static_cast<quint16>(FileNodeTypeID::RevisionManifestStart6FND) ||
        fn->getFileNodeID() ==
            static_cast<quint16>(FileNodeTypeID::RevisionManifestStart7FND) ||
        fn->getFileNodeID() ==
            static_cast<quint16>(FileNodeTypeID::RevisionManifestStart4FND)) {

      revManifest = new RevisionManifest();
      revManifest->getFileNodeSquence().push_back(fn);

    } else if (fn->getFileNodeID() ==
               static_cast<quint16>(FileNodeTypeID::RevisionManifestEndFND)) {
      revManifest->getFileNodeSquence().push_back(fn);
      m_RevisionManifests.push_back(revManifest);
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

      revManifest->getFileNodeSquence().push_back(fn);
      if (fn->getFileNodeID() ==
          static_cast<quint16>(FileNodeTypeID::ObjectGroupListReferenceFND)) {

        auto *objectGroupListRef =
            dynamic_cast<ObjectGroupListReferenceFND *>(fn->getFnt());

        ObjectGroupList *objectGroupList =
            new ObjectGroupList(objectGroupListRef->ref());

        ds.device()->seek(objectGroupListRef->ref().stp());
        ds >> *objectGroupList;

        m_ObjectGroupLists.push_back(objectGroupList);
      }
    }
  }
}

void RevisionManifestList::toDebugString(QDebug dbg) const {

    dbg << "RevisionManifestList:\n";
    dbg << "ref: " << m_Ref << '\n';
    dbg << "FileNodeListFragments count:              " << m_FileNodeListFragments.size() << '\n';
    dbg << "RevisionManifests count:                  " << m_RevisionManifests.size() << '\n';
    dbg << "RevisionRoleDeclarations count:           " << m_RevisionRoleDeclarations.size() << '\n';
    dbg << "RevisionRoleAndContextDeclarations count: " << m_RevisionRoleAndContextDeclarations.size() << '\n';
    dbg << "ObjectGroupLists count:                   " << m_ObjectGroupLists.size() << '\n';
    dbg << "FileNodeSequence count:                   " << m_FileNodeSequence.size() << '\n';


    dbg << "\nRevisionManifestList FileNodeListFragments....\n";
    for(size_t i {0}; i < m_FileNodeListFragments.size(); i++) {
        dbg << *m_FileNodeListFragments[i];
    }

    dbg << "\nRevisionManifestList RevisionManifests....\n";
    for(size_t i {0}; i < m_RevisionManifests.size(); i++) {
        dbg << *m_RevisionManifests[i];
    }
    dbg << "\nRevisionManifestList RevisionRoleDeclarations....\n";
    for(size_t i {0}; i < m_RevisionRoleDeclarations.size(); i++) {
        dbg << *m_RevisionRoleDeclarations[i];
    }
    dbg << "\nRevisionManifestList RevisionRoleAndContextDeclarations....\n";
    for(size_t i {0}; i < m_RevisionRoleAndContextDeclarations.size(); i++) {
        dbg << *m_RevisionRoleAndContextDeclarations[i];
    }
    dbg << "\nRevisionManifestList ObjectGroupLists....\n";
    for(size_t i {0}; i < m_ObjectGroupLists.size(); i++) {
        dbg << *m_ObjectGroupLists[i];
    }
    dbg << "\nRevisionManifestList FileNodeSequence....\n";
    for(size_t i {0}; i < m_FileNodeSequence.size(); i++) {
        dbg << *m_FileNodeSequence[i];
    }




}

RevisionManifestList::RevisionManifestList(FileNodeChunkReference ref)
    : m_Ref{ref}, m_FileNodeSequence{} {}

RevisionManifestList::~RevisionManifestList() {
  for (auto *entry : m_FileNodeListFragments) {
    delete entry;
  }
  for (auto *entry : m_RevisionManifests) {
    delete entry;
  }
  for (auto *entry : m_RevisionRoleDeclarations) {
    delete entry;
  }
  for (auto *entry : m_RevisionRoleAndContextDeclarations) {
    delete entry;
  }
  for (auto *entry : m_ObjectGroupLists) {
    delete entry;
  }
  for (auto *entry : m_FileNodeSequence) {
    delete entry;
  }
}

std::vector<FileNode *> RevisionManifestList::getFileNodeSequence() const {
  return m_FileNodeSequence;
}

void RevisionManifestList::setFileNodeSequence(
    const std::vector<FileNode *> &value) {
  m_FileNodeSequence = value;
}

std::vector<ObjectGroupList *>
RevisionManifestList::getObjectGroupLists() const {
  return m_ObjectGroupLists;
}

void RevisionManifestList::setObjectGroupLists(
    const std::vector<ObjectGroupList *> &value) {
  m_ObjectGroupLists = value;
}

std::vector<FileNode *>
RevisionManifestList::getRevisionRoleAndContextDeclarations() const {
  return m_RevisionRoleAndContextDeclarations;
}

void RevisionManifestList::setRevisionRoleAndContextDeclarations(
    const std::vector<FileNode *> &value) {
  m_RevisionRoleAndContextDeclarations = value;
}

std::vector<FileNode *>
RevisionManifestList::getRevisionRoleDeclarations() const {
  return m_RevisionRoleDeclarations;
}

void RevisionManifestList::setRevisionRoleDeclarations(
    const std::vector<FileNode *> &value) {
  m_RevisionRoleDeclarations = value;
}

std::vector<RevisionManifest *>
RevisionManifestList::getRevisionManifests() const {
  return m_RevisionManifests;
}

void RevisionManifestList::setRevisionManifests(
    const std::vector<RevisionManifest *> &value) {
  m_RevisionManifests = value;
}

std::vector<FileNodeListFragment *>
RevisionManifestList::getFileNodeListFragments() const {
  return m_FileNodeListFragments;
}

void RevisionManifestList::setFileNodeListFragments(
    const std::vector<FileNodeListFragment *> &value) {
  m_FileNodeListFragments = value;
}
} // namespace MSONcommon
