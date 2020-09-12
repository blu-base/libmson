#include "RevisionManifestList.h"

#include <algorithm>

#include "DocumentManager.h"
#include "FileNodeTypes/ObjectGroupListReferenceFND.h"
#include "commonTypes/Enums.h"
#include "commonTypes/FileChunkReference64x32.h"
#include "commonTypes/FileNodeChunkReference.h"
#include "helper/Helper.h"

namespace MSONcommon {

FileNodeChunkReference RevisionManifestList::getRef() const { return m_ref; }

void RevisionManifestList::setRef(const FileNodeChunkReference &ref) {
  m_ref = ref;
}

QDebug operator<<(QDebug dbg, const RevisionManifestList &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void RevisionManifestList::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("RevisionManifestList");
  xmlWriter.writeAttribute("stp", qStringHex(m_ref.stp(), 16));
  xmlWriter.writeAttribute("cb", qStringHex(m_ref.cb(), 16));

  xmlWriter.writeStartElement("RevisionManifests");
  for (const auto &entry : m_RevisionManifests) {
    entry->generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("RevisionRoleDeclarations");
  for (const auto &entry : m_RevisionRoleDeclarations) {
    entry->generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("RevisionRoleAndContextDeclarations");
  for (const auto &entry : m_RevisionRoleAndContextDeclarations) {
    entry->generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ObjectGroupLists");
  for (const auto &entry : m_ObjectGroupLists) {
    entry->generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("FileNodeSequence");
  for (const auto &entry : m_FileNodeSequence) {
    entry->generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}

void RevisionManifestList::deserialize(QDataStream &ds) {

  m_FileNodeListFragments = parseFileNodeListFragments(ds, m_ref);

  for (const auto &fragment : m_FileNodeListFragments) {
    const auto &rgFileNodes = fragment->rgFileNodes();
    copy_if(rgFileNodes.begin(), rgFileNodes.end(),
            back_inserter(m_FileNodeSequence),
            [](const std::shared_ptr<FileNode> &entry) {
              return entry->getFileNodeTypeID() !=
                     FileNodeTypeID::ChunkTerminatorFND;
            });
  }

  std::copy_if(m_FileNodeSequence.begin(), m_FileNodeSequence.end(),
               back_inserter(m_RevisionRoleDeclarations),
               [](const std::shared_ptr<FileNode> &entry) {
                 return entry->getFileNodeID() ==
                        static_cast<quint16>(
                            FileNodeTypeID::RevisionRoleDeclarationFND);
               });

  std::copy_if(
      m_FileNodeSequence.begin(), m_FileNodeSequence.end(),
      back_inserter(m_RevisionRoleAndContextDeclarations),
      [](const std::shared_ptr<FileNode> &entry) {
        return entry->getFileNodeID() ==
               static_cast<quint16>(
                   FileNodeTypeID::RevisionRoleAndContextDeclarationFND);
      });

  std::shared_ptr<RevisionManifest> revManifest =
      std::make_shared<RevisionManifest>();
  for (auto fn : m_FileNodeSequence) {

    switch (static_cast<FileNodeTypeID>(fn->getFileNodeID())) {
    case FileNodeTypeID::RevisionManifestStart6FND:
    case FileNodeTypeID::RevisionManifestStart7FND:
    case FileNodeTypeID::RevisionManifestStart4FND: {
      revManifest = std::make_shared<RevisionManifest>();

      revManifest->fileNodeSquence().push_back(fn);
      break;
    }

    case FileNodeTypeID::RevisionManifestEndFND: {
      revManifest->getFileNodeSquence().push_back(fn);
      m_RevisionManifests.push_back(revManifest);
      revManifest = std::make_shared<RevisionManifest>();
      break;
    }
    case FileNodeTypeID::ChunkTerminatorFND:
    case FileNodeTypeID::RevisionManifestListStartFND:
      break;
    case FileNodeTypeID::ObjectDataEncryptionKeyV2FNDX:
      DocumentManager::getDocument(ds)->setIsEncrypted(true);
      revManifest->fileNodeSquence().push_back(fn);
      break;
    default: {
      revManifest->fileNodeSquence().push_back(fn);
      if (fn->getFileNodeID() ==
          static_cast<quint16>(FileNodeTypeID::ObjectGroupListReferenceFND)) {

        const auto objectGroupListRef =
            std::dynamic_pointer_cast<ObjectGroupListReferenceFND>(fn->getFnt())
                ->ref();

        std::shared_ptr<ObjectGroupList> objectGroupList =
            std::make_shared<ObjectGroupList>(objectGroupListRef);

        ds.device()->seek(objectGroupListRef.stp());
        ds >> *objectGroupList;

        m_ObjectGroupLists.push_back(objectGroupList);
      }
      break;
    }
    }
  }
}

void RevisionManifestList::toDebugString(QDebug dbg) const {

  dbg << "RevisionManifestList:\n";
  dbg << "ref: " << m_ref << '\n';
  dbg << "FileNodeListFragments count:              "
      << m_FileNodeListFragments.size() << '\n';
  dbg << "RevisionManifests count:                  "
      << m_RevisionManifests.size() << '\n';
  dbg << "RevisionRoleDeclarations count:           "
      << m_RevisionRoleDeclarations.size() << '\n';
  dbg << "RevisionRoleAndContextDeclarations count: "
      << m_RevisionRoleAndContextDeclarations.size() << '\n';
  dbg << "ObjectGroupLists count:                   "
      << m_ObjectGroupLists.size() << '\n';
  dbg << "FileNodeSequence count:                   "
      << m_FileNodeSequence.size() << '\n';

  dbg << "\nRevisionManifestList FileNodeListFragments....\n";
  for (size_t i{0}; i < m_FileNodeListFragments.size(); i++) {
    dbg << *m_FileNodeListFragments[i];
  }

  dbg << "\nRevisionManifestList RevisionManifests....\n";
  for (size_t i{0}; i < m_RevisionManifests.size(); i++) {
    dbg << *m_RevisionManifests[i];
  }
  dbg << "\nRevisionManifestList RevisionRoleDeclarations....\n";
  for (size_t i{0}; i < m_RevisionRoleDeclarations.size(); i++) {
    dbg << *m_RevisionRoleDeclarations[i];
  }
  dbg << "\nRevisionManifestList RevisionRoleAndContextDeclarations....\n";
  for (size_t i{0}; i < m_RevisionRoleAndContextDeclarations.size(); i++) {
    dbg << *m_RevisionRoleAndContextDeclarations[i];
  }
  dbg << "\nRevisionManifestList ObjectGroupLists....\n";
  for (size_t i{0}; i < m_ObjectGroupLists.size(); i++) {
    dbg << *m_ObjectGroupLists[i];
  }
  dbg << "\nRevisionManifestList FileNodeSequence....\n";
  for (size_t i{0}; i < m_FileNodeSequence.size(); i++) {
    dbg << *m_FileNodeSequence[i];
  }
}

RevisionManifestList::RevisionManifestList(const FileNodeChunkReference &ref)
    : m_ref{ref} {}

std::vector<std::shared_ptr<FileNode>>
RevisionManifestList::getFileNodeSequence() const {
  return m_FileNodeSequence;
}

void RevisionManifestList::setFileNodeSequence(
    const std::vector<std::shared_ptr<FileNode>> &value) {
  m_FileNodeSequence = value;
}

std::vector<std::shared_ptr<ObjectGroupList>>
RevisionManifestList::getObjectGroupLists() const {
  return m_ObjectGroupLists;
}

void RevisionManifestList::setObjectGroupLists(
    const std::vector<std::shared_ptr<ObjectGroupList>> &value) {
  m_ObjectGroupLists = value;
}

std::vector<std::shared_ptr<FileNode>>
RevisionManifestList::getRevisionRoleAndContextDeclarations() const {
  return m_RevisionRoleAndContextDeclarations;
}

void RevisionManifestList::setRevisionRoleAndContextDeclarations(
    const std::vector<std::shared_ptr<FileNode>> &value) {
  m_RevisionRoleAndContextDeclarations = value;
}

std::vector<std::shared_ptr<FileNode>>
RevisionManifestList::getRevisionRoleDeclarations() const {
  return m_RevisionRoleDeclarations;
}

void RevisionManifestList::setRevisionRoleDeclarations(
    const std::vector<std::shared_ptr<FileNode>> &value) {
  m_RevisionRoleDeclarations = value;
}

std::vector<std::shared_ptr<RevisionManifest>>
RevisionManifestList::getRevisionManifests() const {
  return m_RevisionManifests;
}

void RevisionManifestList::setRevisionManifests(
    const std::vector<std::shared_ptr<RevisionManifest>> &value) {
  m_RevisionManifests = value;
}

std::vector<std::shared_ptr<FileNodeListFragment>>
RevisionManifestList::getFileNodeListFragments() const {
  return m_FileNodeListFragments;
}

void RevisionManifestList::setFileNodeListFragments(
    const std::vector<std::shared_ptr<FileNodeListFragment>> &value) {
  m_FileNodeListFragments = value;
}

} // namespace MSONcommon
