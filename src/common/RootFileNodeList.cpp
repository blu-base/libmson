#include "RootFileNodeList.h"
#include "FileNodeTypes/ObjectSpaceManifestListReferenceFND.h"
#include "FileNodeTypes/ObjectSpaceManifestRootFND.h"
#include "commonTypes/Enums.h"
#include <QDebug>

#include <algorithm>

#include "helper/Helper.h"

namespace MSONcommon {

RootFileNodeList::RootFileNodeList(FileChunkReference64x32 &reference)
    :  m_fcrFileNodeListRoot{reference} {}

std::vector<std::shared_ptr<FileNode>>
RootFileNodeList::getFileDataStoreListReference() const {
  return m_fileDataStoreListReference;
}

void RootFileNodeList::setFileDataStoreListReference(
    const std::vector<std::shared_ptr<FileNode>> &value) {
  m_fileDataStoreListReference = value;
}

void RootFileNodeList::deserialize(QDataStream &ds) {
  qInfo() << "Parsing RootFileNodeList";

  m_fileNodeListFragments =
      parseFileNodeListFragments(ds, m_fcrFileNodeListRoot);

  for (const auto &fragment : m_fileNodeListFragments) {
    const auto &rgFileNodes = fragment->rgFileNodes();
    copy_if(rgFileNodes.begin(), rgFileNodes.end(),
            back_inserter(m_fileNodeSequence),
            [](const std::shared_ptr<FileNode> &entry) {
              return entry->getFileNodeTypeID() !=
                     FileNodeTypeID::ChunkTerminatorFND;
            });
  }

  // Parsing ObjectSpaceManifestLists
  std::vector<std::shared_ptr<FileNode>> objectSpaceManifestListReferences{};

  std::copy_if(m_fileNodeSequence.begin(), m_fileNodeSequence.end(),
               back_inserter(objectSpaceManifestListReferences),
               [](const std::shared_ptr<FileNode> &entry) {
                 return entry->getFileNodeTypeID() ==
                        FileNodeTypeID::ObjectSpaceManifestListReferenceFND;
               });

  for (const auto &entry : objectSpaceManifestListReferences) {
    const FileNodeChunkReference osmlr =
        std::dynamic_pointer_cast<ObjectSpaceManifestListReferenceFND>(entry->getFnt())
            ->getRef();

    std::shared_ptr<ObjectSpaceManifestList> osml =
        std::make_shared<ObjectSpaceManifestList>(osmlr);

    ds >> *osml;

    m_objectSpaceManifestList.push_back(osml);
  }

  // Parsing ObjectSpaceManifestRoot
  auto manifestRoot =
      std::find_if(m_fileNodeSequence.begin(), m_fileNodeSequence.end(),
                   [](const std::shared_ptr<FileNode> &entry) {
                     return entry->getFileNodeTypeID() ==
                            FileNodeTypeID::ObjectSpaceManifestRootFND;
                   });

  if (manifestRoot != m_fileNodeSequence.end()) {
    m_objectSpaceManifestRoot = *manifestRoot;
  }

  qInfo() << "Finished parsing RootFileNodeList";
}

void RootFileNodeList::serialize(QDataStream& ds) const
{

}


// void RootFileNodeList::serialize(QDataStream& ds) const
//{

//}

void RootFileNodeList::toDebugString(QDebug &dbg) const {
  dbg << "=========================================================\n";
  dbg << "RootFileNodeList\n"
      << "------------------\n";

  dbg << "\n\nRootFileNodeList fileNodeListFragments....\n";
  if (m_fileNodeListFragments.empty()) {
    dbg << "none\n";
  } else {
    for (const auto &entry : m_fileNodeListFragments) {
      dbg << *entry;
    }
  }

  dbg << "\n\nRootFileNodeList objectSpaceManifestRoot....\n"
      << *m_objectSpaceManifestRoot << '\n';

  dbg << "\n\nRootFileNodeList fileNodeSequence....\n";
  if (m_fileNodeSequence.empty()) {
    dbg << "none\n";
  } else {
    for (const auto &entry : m_fileNodeSequence) {
      dbg << *entry;
    }
  }

  dbg << "\n\nRootFileNodeList objectSpaceManifestList....\n";
  if (m_objectSpaceManifestList.empty()) {
    dbg << "none\n";
  } else {
    for (const auto &entry : m_objectSpaceManifestList) {
      dbg << *entry;
    }
  }

  dbg << "\n\nRootFileNodeList fileDataStoreListReference....\n";
  if (m_fileDataStoreListReference.empty()) {
    dbg << "none\n";
  } else {
    for (const auto &entry : m_fileDataStoreListReference) {
      dbg << *entry;
    }
  }

  dbg << "\n\nRootFileNodeList fcrFileNodeListRoot....\n"
      << m_fcrFileNodeListRoot << '\n';
  dbg << "\n\n\n";
}
std::vector<std::shared_ptr<ObjectSpaceManifestList>>
RootFileNodeList::getObjectSpaceManifestLists() const {
  return m_objectSpaceManifestList;
}

void RootFileNodeList::setObjectSpaceManifestLists(
    const std::vector<std::shared_ptr<ObjectSpaceManifestList>> &value) {
  m_objectSpaceManifestList = value;
}

std::vector<std::shared_ptr<FileNode>>
RootFileNodeList::getFileNodeSequence() const {
  return m_fileNodeSequence;
}

void RootFileNodeList::setFileNodeSequence(
    const std::vector<std::shared_ptr<FileNode>> &value) {
  m_fileNodeSequence = value;
}

std::shared_ptr<FileNode> RootFileNodeList::getObjectSpaceManifestRoot() {
  return m_objectSpaceManifestRoot;
}

void RootFileNodeList::setObjectSpaceManifestRoot(
    const std::shared_ptr<FileNode> &value) {
  m_objectSpaceManifestRoot = value;
}

std::vector<std::shared_ptr<FileNodeListFragment>>
RootFileNodeList::getFileNodeListFragments() const {
  return m_fileNodeListFragments;
}

void RootFileNodeList::setFileNodeListFragments(
    const std::vector<std::shared_ptr<FileNodeListFragment>> &value) {
  m_fileNodeListFragments = value;
}

FileChunkReference64x32 RootFileNodeList::getFcrFileNodeListRoot() const {
  return m_fcrFileNodeListRoot;
}

void RootFileNodeList::setFcrFileNodeListRoot(
    const FileChunkReference64x32 &fcrFileNodeListRoot) {
  m_fcrFileNodeListRoot = fcrFileNodeListRoot;
}

void RootFileNodeList::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("RootFileNodeList");

  //  xmlWriter.writeStartElement("fileNodeListFragments");
  //  for (const auto& entry : m_fileNodeListFragments) {
  //    xmlWriter << entry;
  //  }
  //  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("objectSpaceManifestRoot");
  xmlWriter.writeCharacters(std::dynamic_pointer_cast<ObjectSpaceManifestRootFND>(
                                m_objectSpaceManifestRoot->getFnt())
                                ->getGosidRoot()
                                .toString());
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fileNodeSequences");
  for (const auto &entry : m_fileNodeSequence) {
    xmlWriter << *entry;
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("objectSpaceManifestLists");
  for (const auto &entry : m_objectSpaceManifestList) {
    xmlWriter << *entry;
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fileDataStoreListReferences");
  for (const auto &entry : m_fileDataStoreListReference) {
    xmlWriter << *entry;
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("fcrFileNodeListRoot");
  xmlWriter << m_fcrFileNodeListRoot;
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}
} // namespace MSONcommon

