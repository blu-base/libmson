#include "ObjectSpaceManifestList.h"

#include <memory>

#include "FileNodeTypes/ObjectSpaceManifestListStartFND.h"
#include "FileNodeTypes/RevisionManifestListReferenceFND.h"
#include "commonTypes/ExtendedGUID.h"

#include "commonTypes/Enums.h"
#include "helper/Helper.h"

namespace MSONcommon {

ObjectSpaceManifestList::ObjectSpaceManifestList(
    const FileNodeChunkReference &ref)
    : m_ref{ref} {}

FileNodeChunkReference ObjectSpaceManifestList::getRef() const { return m_ref; }

void ObjectSpaceManifestList::setRef(const FileNodeChunkReference &ref) {
  m_ref = ref;
}

void ObjectSpaceManifestList::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectSpaceManifestList");

  ExtendedGUID gosid =
      std::dynamic_pointer_cast<ObjectSpaceManifestListStartFND>(
          m_objectSpaceManifestListStart->getFnt())
          ->gosid();

  xmlWriter.writeAttribute("start", gosid.toString());

  xmlWriter.writeAttribute("stp", qStringHex(m_ref.stp(), 16));
  xmlWriter.writeAttribute("cb", qStringHex(m_ref.cb(), 16));

  xmlWriter.writeStartElement("revisionManifestLists");
  for (const auto &entry : m_revisionManifestLists) {
    entry->generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fileNodeSequence");
  for (const auto &entry : m_fileNodeSequence) {
    entry->generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}

QDebug operator<<(QDebug dbg, const ObjectSpaceManifestList &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void ObjectSpaceManifestList::deserialize(QDataStream &ds) {
  qInfo() << "Parsing ObjectSpaceManifestList";
  m_fileNodeListFragments = parseFileNodeListFragments(ds, m_ref);

  for (const auto &fragment : m_fileNodeListFragments) {
    const auto &rgFileNodes = fragment->rgFileNodes();
    copy_if(rgFileNodes.begin(), rgFileNodes.end(),
            back_inserter(m_fileNodeSequence),
            [](const std::shared_ptr<FileNode> &entry) {
              return entry->getFileNodeTypeID() !=
                     FileNodeTypeID::ChunkTerminatorFND;
            });
  }

  std::vector<std::shared_ptr<FileNode>> objectSpaceManifestListStarts{};

  std::copy_if(m_fileNodeSequence.begin(), m_fileNodeSequence.end(),
               back_inserter(objectSpaceManifestListStarts),
               [](const std::shared_ptr<FileNode> &entry) {
                 return entry->getFileNodeID() ==
                        static_cast<quint16>(
                            FileNodeTypeID::ObjectSpaceManifestListStartFND);
               });

  if (objectSpaceManifestListStarts.size() == 1) {
    m_objectSpaceManifestListStart = objectSpaceManifestListStarts.at(0);
  }

  std::vector<std::shared_ptr<FileNode>> revisionManifestListRefs{};

  std::copy_if(m_fileNodeSequence.begin(), m_fileNodeSequence.end(),
               back_inserter(revisionManifestListRefs),
               [](const std::shared_ptr<FileNode> &entry) {
                 return entry->getFileNodeID() ==
                        static_cast<quint16>(
                            FileNodeTypeID::RevisionManifestListReferenceFND);
               });

  for (const auto &entry : revisionManifestListRefs) {

    FileNodeChunkReference rmlr =
        std::dynamic_pointer_cast<RevisionManifestListReferenceFND>(
            entry->getFnt())
            ->getRef();

    std::shared_ptr<RevisionManifestList> rmfl =
        std::make_shared<RevisionManifestList>(rmlr);

    ds.device()->seek(rmlr.stp());
    ds >> *rmfl;

    m_revisionManifestLists.push_back(rmfl);
  }
}

void ObjectSpaceManifestList::toDebugString(QDebug dbg) const {
  dbg << " ObjectSpaceManifestList:\n"
      << " fileNodeListFragments:\n";

  if (m_fileNodeListFragments.empty()) {
    dbg << "none\n";
  } else {
    for (const auto &entry : m_fileNodeListFragments) {
      dbg << *entry;
    }
  }

  dbg << "objectSpaceManifestListStart: " << *m_objectSpaceManifestListStart
      << " revisionManifestLists:\n";
  if (m_revisionManifestLists.empty()) {
    dbg << "none\n";
  } else {
    for (const auto &entry : m_revisionManifestLists) {
      dbg << *entry;
    }
  }

  dbg << " fileNodeSequence:\n";
  if (m_fileNodeSequence.empty()) {
    dbg << "none\n";
  } else {
    for (const auto &entry : m_fileNodeSequence) {
      dbg << *entry;
    }
  }
}

std::vector<std::shared_ptr<FileNode>>
ObjectSpaceManifestList::getFileNodeSequence() const {
  return m_fileNodeSequence;
}

void ObjectSpaceManifestList::setFileNodeSequence(
    const std::vector<std::shared_ptr<FileNode>> &value) {
  m_fileNodeSequence = value;
}

std::vector<std::shared_ptr<RevisionManifestList>>
ObjectSpaceManifestList::getRevisionManifestLists() {
  return m_revisionManifestLists;
}

void ObjectSpaceManifestList::setRevisionManifestLists(
    const std::vector<std::shared_ptr<RevisionManifestList>> &value) {
  m_revisionManifestLists = value;
}

std::shared_ptr<FileNode>
ObjectSpaceManifestList::getObjectSpaceManifestListStart() const {
  return m_objectSpaceManifestListStart;
}

void ObjectSpaceManifestList::setObjectSpaceManifestListStart(
    const std::shared_ptr<FileNode> &value) {
  m_objectSpaceManifestListStart = value;
}

std::vector<std::shared_ptr<FileNodeListFragment>>
ObjectSpaceManifestList::getFileNodeListFragments() const {
  return m_fileNodeListFragments;
}

void ObjectSpaceManifestList::setFileNodeListFragments(
    const std::vector<std::shared_ptr<FileNodeListFragment>> &value) {
  m_fileNodeListFragments = value;
}
} // namespace MSONcommon
