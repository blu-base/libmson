#include "ObjectSpaceManifestList.h"

#include "chunkables/fileNodeTypes/ObjectSpaceManifestListReferenceFND.h"


namespace libmson {
namespace priv {

ExtendedGUID ObjectSpaceManifestList::getGosid() const
{
    return m_gosid;
}

void ObjectSpaceManifestList::setGosid(const ExtendedGUID& gosid)
{
    m_gosid = gosid;
}

ObjectSpaceManifestList::ObjectSpaceManifestList(
        const FileNode_SPtr_t& referenceFND)
    : m_objectSpaceManifestListReferenceFND(referenceFND)
{
    
    if (referenceFND->getFileNodeTypeID() !=
      FileNodeTypeID::ObjectSpaceManifestListReferenceFND) {
    qFatal("ObjectSpaceManifestList was not initialized with "
           "ObjectSpaceManifestListReferenceFND");
  }

  auto fnd = std::static_pointer_cast<ObjectSpaceManifestListReferenceFND>(
      referenceFND->getFnt());

  m_gosid = fnd->getGosid();
}


// void ObjectSpaceManifestList::writeLowLevelXml(
//    QXmlStreamWriter& xmlWriter) const
//{
//  xmlWriter.writeStartElement("ObjectSpaceManifestList");

//  ExtendedGUID gosid =
//      std::dynamic_pointer_cast<ObjectSpaceManifestListStartFND>(
//          m_objectSpaceManifestListStart->getFnt())
//          ->gosid();

//  xmlWriter.writeAttribute("start", gosid.toString());

//  xmlWriter.writeAttribute("stp", qStringHex(m_ref.stp(), 16));
//  xmlWriter.writeAttribute("cb", qStringHex(m_ref.cb(), 16));

//  xmlWriter.writeStartElement("revisionManifestLists");
//  for (const auto& entry : m_revisionManifestLists) {
//    xmlWriter << *entry;
//  }
//  xmlWriter.writeEndElement();

//  xmlWriter.writeStartElement("fileNodeSequence");
//  for (const auto& entry : m_fileNodeSequence) {
//    xmlWriter << *entry;
//  }
//  xmlWriter.writeEndElement();

//  xmlWriter.writeEndElement();
//}

// void ObjectSpaceManifestList::deserialize(QDataStream& ds)
//{
//  qInfo() << "Parsing ObjectSpaceManifestList";
//  m_fileNodeListFragments = parseFileNodeListFragments(ds, m_ref);

//  for (const auto& fragment : m_fileNodeListFragments) {
//    const auto& rgFileNodes = fragment->rgFileNodes();
//    copy_if(
//        rgFileNodes.begin(), rgFileNodes.end(),
//        back_inserter(m_fileNodeSequence),
//        [](const std::shared_ptr<FileNode>& entry) {
//          return entry->getFileNodeTypeID() !=
//                 FileNodeTypeID::ChunkTerminatorFND;
//        });
//  }

//  std::vector<std::shared_ptr<FileNode>> objectSpaceManifestListStarts{};

//  std::copy_if(
//      m_fileNodeSequence.begin(), m_fileNodeSequence.end(),
//      back_inserter(objectSpaceManifestListStarts),
//      [](const std::shared_ptr<FileNode>& entry) {
//        return entry->getFileNodeTypeID() ==
//               FileNodeTypeID::ObjectSpaceManifestListStartFND;
//      });

//  if (objectSpaceManifestListStarts.size() == 1) {
//    m_objectSpaceManifestListStart = objectSpaceManifestListStarts.at(0);
//  }

//  std::vector<std::shared_ptr<FileNode>> revisionManifestListRefs{};

//  std::copy_if(
//      m_fileNodeSequence.begin(), m_fileNodeSequence.end(),
//      back_inserter(revisionManifestListRefs),
//      [](const std::shared_ptr<FileNode>& entry) {
//        return entry->getFileNodeTypeID() ==
//               FileNodeTypeID::RevisionManifestListReferenceFND;
//      });

//  for (const auto& entry : revisionManifestListRefs) {

//    FileNodeChunkReference rmlr =
//        std::dynamic_pointer_cast<RevisionManifestListReferenceFND>(
//            entry->getFnt())
//            ->getRef();

//    std::shared_ptr<RevisionManifestList> rmfl =
//        std::make_shared<RevisionManifestList>(rmlr);

//    ds.device()->seek(rmlr.stp());
//    ds >> *rmfl;

//    m_revisionManifestLists.push_back(rmfl);
//  }
//}


} // namespace priv
} // namespace libmson
