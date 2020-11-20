#ifndef RSFTOXML_H
#define RSFTOXML_H

#include <QXmlStreamWriter>
#include <QtCore/qglobal.h>

/// \todo make a proper library import....
#include "../../lib/priv/chunkables/ObjectSpaceObjectPropSet.h"
#include "../../lib/priv/chunkables/RevisionStoreChunkContainer.h"
#include "../../lib/priv/chunkables/fileNodeTypes/ChunkTerminatorFND.h"
#include "../../lib/priv/chunkables/fileNodeTypes/DataSignatureGroupDefinitionFND.h"
#include "../../lib/priv/chunkables/fileNodeTypes/FileDataStoreListReferenceFND.h"
#include "../../lib/priv/chunkables/fileNodeTypes/ObjectDataEncryptionKeyV2FNDX.h"
#include "../../lib/priv/chunkables/fileNodeTypes/ObjectDeclaration2LargeRefCountFND.h"
#include "../../lib/priv/chunkables/fileNodeTypes/ObjectDeclaration2RefCountFND.h"
//#include "../../lib/priv/chunkables/fileNodeTypes/PLACEHOLDERPLACEHOLDER.h"
//#include "../../lib/priv/chunkables/fileNodeTypes/PLACEHOLDERPLACEHOLDER.h"
//#include "../../lib/priv/chunkables/fileNodeTypes/PLACEHOLDERPLACEHOLDER.h"
//#include "../../lib/priv/chunkables/fileNodeTypes/PLACEHOLDERPLACEHOLDER.h"
//#include "../../lib/priv/chunkables/fileNodeTypes/PLACEHOLDERPLACEHOLDER.h"
//#include "../../lib/priv/chunkables/fileNodeTypes/PLACEHOLDERPLACEHOLDER.h"

using namespace libmson::priv;

class RSFtoXml {

public:
  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const ChunkTerminatorFND& fnd);
  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const DataSignatureGroupDefinitionFND& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const FileDataStoreListReferenceFND& fnd);
  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, ObjectDeclaration2RefCountFND& fnd);
  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, ObjectDeclaration2LargeRefCountFND& fnd);
  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const ObjectDataEncryptionKeyV2FNDX& fnd);
  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, ObjectSpaceObjectPropSet& obj);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  //  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd);
  friend QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const RSChunkContainer_SPtr_t& obj);
};


#endif // RSFTOXML_H
