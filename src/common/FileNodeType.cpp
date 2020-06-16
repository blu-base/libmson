#include <QDataStream>
#include <QDebug>

#include "FileNodeType.h"

FileNodeType::FileNodeType() {}

FileNodeType::FileNodeType(FileNodeType::FileNodeData) {}

FileNodeType::~FileNodeType() {}

//ObjectSpaceManifestListReferenceFND::ObjectSpaceManifestListReferenceFND()
//  : ref{FileNodeChunkReference(0, 0)}, gosid{}
//{

//}

//ObjectSpaceManifestListReferenceFND::ObjectSpaceManifestListReferenceFND(
//    const quint8 stpFormat, const quint8 cbFormat)
//  : ref{FileNodeChunkReference(stpFormat, cbFormat)}, gosid{ExtendedGUID()} {}

//ObjectSpaceManifestListReferenceFND::~ObjectSpaceManifestListReferenceFND()
//{

//}

//void ObjectSpaceManifestListReferenceFND::parse(QDataStream &ds) {

//  ds.setByteOrder(QDataStream::LittleEndian);

//  ds >> ref;
//  ds >> gosid;
//}

//void ObjectSpaceManifestListReferenceFND::serialize(QDataStream &ds) const {}

//void ObjectSpaceManifestListReferenceFND::toDebugString(QDebug dbg) const {
//  QDebugStateSaver saver(dbg);
//  dbg.nospace();

//  dbg << "ObjectSpaceManifestListReferenceFND: " << ref << ", " << gosid
//      << '\n';
//}
