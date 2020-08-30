#include "ObjectSpaceManifestList.h"

#include "FileNodeTypes/RevisionManifestListReferenceFND.h"
#include "commonTypes/Enums.h"
#include "helper/Helper.h"
namespace MSONcommon {
ObjectSpaceManifestList::ObjectSpaceManifestList(FileNodeChunkReference &ref)
    : m_ref{ref} {}

ObjectSpaceManifestList::~ObjectSpaceManifestList() {
  //  for (auto *fnlf : m_fileNodeListFragments) {
  //    delete fnlf;
  //  };

  for (auto *rml : m_revisionManifestLists) {
    delete rml;
  }

  //  for (auto *fns : m_fileNodeSequence) {
  //    delete fns;
  //  }
}

FileNodeChunkReference ObjectSpaceManifestList::getRef() const { return m_ref; }

void ObjectSpaceManifestList::setRef(const FileNodeChunkReference &ref) {
  m_ref = ref;
}

void ObjectSpaceManifestList::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("ObjectSpaceManifestList");

  xmlWriter.writeStartElement("ref");
  m_ref.generateXml(xmlWriter);
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("objectSpaceManifestListStart");
  m_objectSpaceManifestListStart.generateXml(xmlWriter);
  xmlWriter.writeEndElement();

  //    xmlWriter.writeStartElement("fileNodeListFragments");
  //    for (const auto& entry : m_fileNodeListFragments) {
  //        entry.generateXml(xmlWriter);
  //    }
  //    xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("revisionManifestLists");
  for (auto entry : m_revisionManifestLists) {
    entry->generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fileNodeSequence");
  for (const auto &entry : m_fileNodeSequence) {
    entry.generateXml(xmlWriter);
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}

QDataStream &operator>>(QDataStream &ds, ObjectSpaceManifestList &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const ObjectSpaceManifestList &obj) {
  obj.toDebugString(dbg);
  return dbg;
}

void ObjectSpaceManifestList::deserialize(QDataStream &ds) {
  qInfo() << "Parsing ObjectSpaceManifestList";
  m_fileNodeListFragments = parseFileNodeListFragments(ds, m_ref);

  for (const auto &fragment : m_fileNodeListFragments) {
    const auto &rgFileNodes = fragment.rgFileNodes();
    copy_if(rgFileNodes.begin(), rgFileNodes.end(),
            back_inserter(m_fileNodeSequence), [](const FileNode &entry) {
              return entry.getFileNodeTypeID() !=
                     FileNodeTypeID::ChunkTerminatorFND;
            });
  }

  std::vector<FileNode> objectSpaceManifestListStarts{};

  std::copy_if(m_fileNodeSequence.begin(), m_fileNodeSequence.end(),
               back_inserter(objectSpaceManifestListStarts),
               [](FileNode entry) {
                 return entry.getFileNodeID() ==
                        static_cast<quint16>(
                            FileNodeTypeID::ObjectSpaceManifestListStartFND);
               });

  if (objectSpaceManifestListStarts.size() == 1) {
    m_objectSpaceManifestListStart = objectSpaceManifestListStarts.at(0);
  }

  std::vector<FileNode> revisionManifestListRefs{};

  std::copy_if(m_fileNodeSequence.begin(), m_fileNodeSequence.end(),
               back_inserter(revisionManifestListRefs), [](FileNode entry) {
                 return entry.getFileNodeID() ==
                        static_cast<quint16>(
                            FileNodeTypeID::RevisionManifestListReferenceFND);
               });

  for (FileNode entry : revisionManifestListRefs) {
    auto *revisionManifestListReferenceFND =
        dynamic_cast<RevisionManifestListReferenceFND *>(entry.getFnt());

    RevisionManifestList *rmfl =
        new RevisionManifestList(revisionManifestListReferenceFND->getRef());

    ds.device()->seek(revisionManifestListReferenceFND->getRef().stp());
    ds >> *rmfl;

    m_revisionManifestLists.push_back(rmfl);
  }
}

void ObjectSpaceManifestList::toDebugString(QDebug dbg) const {
  dbg << " ObjectSpaceManifestList:\n";

  dbg << " fileNodeListFragments:\n";
  if (m_fileNodeListFragments.size() == 0) {
    dbg << "none\n";
  } else {
    for (const auto &entry : m_fileNodeListFragments) {
      dbg << entry;
    }
  }

  dbg << "objectSpaceManifestListStart: " << m_objectSpaceManifestListStart;

  dbg << " revisionManifestLists:\n";
  if (m_revisionManifestLists.size() == 0) {
    dbg << "none\n";
  } else {
    for (auto *entry : m_revisionManifestLists) {
      dbg << *entry;
    }
  }

  dbg << " fileNodeSequence:\n";
  if (m_fileNodeSequence.size() == 0) {
    dbg << "none\n";
  } else {
    for (const auto &entry : m_fileNodeSequence) {
      dbg << entry;
    }
  }
}

std::vector<FileNode> ObjectSpaceManifestList::getFileNodeSequence() const {
  return m_fileNodeSequence;
}

void ObjectSpaceManifestList::setFileNodeSequence(
    const std::vector<FileNode> &value) {
  m_fileNodeSequence = value;
}

std::vector<RevisionManifestList *>
ObjectSpaceManifestList::getRevisionManifestLists() {
  return m_revisionManifestLists;
}

void ObjectSpaceManifestList::setRevisionManifestLists(
    const std::vector<RevisionManifestList *> &value) {
  m_revisionManifestLists = value;
}

FileNode ObjectSpaceManifestList::getObjectSpaceManifestListStart() const {
  return m_objectSpaceManifestListStart;
}

void ObjectSpaceManifestList::setObjectSpaceManifestListStart(
    const FileNode &value) {
  m_objectSpaceManifestListStart = value;
}

std::vector<FileNodeListFragment>
ObjectSpaceManifestList::getFileNodeListFragments() const {
  return m_fileNodeListFragments;
}

void ObjectSpaceManifestList::setFileNodeListFragments(
    const std::vector<FileNodeListFragment> &value) {
  m_fileNodeListFragments = value;
}
} // namespace MSONcommon
