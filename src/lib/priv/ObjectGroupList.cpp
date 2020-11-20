#include "ObjectGroupList.h"
#include "commonTypes/Enums.h"

#include "utils/Helper.h"

namespace libmson {
namespace priv {


// void ObjectGroupList::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("ObjectGroupList");
//  xmlWriter.writeAttribute("stp", qStringHex(m_ref.stp(), 16));
//  xmlWriter.writeAttribute("cb", qStringHex(m_ref.cb(), 16));
//  //  xmlWriter.writeStartElement("ref");
//  //  xmlWriter << m_ref;
//  //  xmlWriter.writeEndElement();

//  xmlWriter.writeStartElement("fileNodeSequence");
//  for (const auto &entry : m_fileNodeSequence) {
//    xmlWriter << *entry;
//  }
//  xmlWriter.writeEndElement();

//  //    xmlWriter.writeStartElement("fileNodeListFragments");
//  //    for(const auto& entry : m_fileNodeListFragments) {
//  //        xmlWriter << entry;
//  //    }
//  //    xmlWriter.writeEndElement();

//  xmlWriter.writeEndElement();
//}

// void ObjectGroupList::deserialize(QDataStream& ds)
//{

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
//}


} // namespace priv
} // namespace libmson
