#ifndef PSFTOXML_H
#define PSFTOXML_H

#include <QtCore/qglobal.h>

#include <QFile>
#include <QXmlStreamWriter>

/// \todo make a proper library import....
#include "../../lib/priv/PackageStoreFile.h"
#include "../../lib/priv/packageTypes/PackagingStructure.h"


#include "../../lib/priv/packageTypes/CellManifest.h"
#include "../../lib/priv/packageTypes/DataElement.h"
#include "../../lib/priv/packageTypes/DataElementBody.h"
#include "../../lib/priv/packageTypes/DataElementFragment.h"
#include "../../lib/priv/packageTypes/ObjectDataBLOB.h"
#include "../../lib/priv/packageTypes/ObjectGroup.h"
#include "../../lib/priv/packageTypes/RevisionManifest.h"
#include "../../lib/priv/packageTypes/StorageIndex.h"
#include "../../lib/priv/packageTypes/StorageManifest.h"

#include "../../lib/priv/chunkables/ObjectSpaceObjectPropSet.h"

#include "../../lib/priv/commonTypes/CompactExtGuid.h"
#include "../../lib/priv/commonTypes/CompactID.h"


#include "../../lib/priv/propertyTypes/JCID.h"

#include "../../lib/priv/propertyTypes/PropertyID.h"
#include "../../lib/priv/propertyTypes/PropertySet.h"
#include "../../lib/priv/propertyTypes/PropertyType_ArrayNumber.h"
#include "../../lib/priv/propertyTypes/PropertyType_ArrayOfPropertyValues.h"
#include "../../lib/priv/propertyTypes/PropertyType_Bool.h"
#include "../../lib/priv/propertyTypes/PropertyType_ContextID.h"
#include "../../lib/priv/propertyTypes/PropertyType_EightBytesOfData.h"
#include "../../lib/priv/propertyTypes/PropertyType_FourBytesOfData.h"
#include "../../lib/priv/propertyTypes/PropertyType_FourBytesOfLengthFollowedByData.h"
#include "../../lib/priv/propertyTypes/PropertyType_NoData.h"
#include "../../lib/priv/propertyTypes/PropertyType_ObjectID.h"
#include "../../lib/priv/propertyTypes/PropertyType_ObjectSpaceID.h"
#include "../../lib/priv/propertyTypes/PropertyType_OneByteOfData.h"
#include "../../lib/priv/propertyTypes/PropertyType_PropertySet.h"
#include "../../lib/priv/propertyTypes/PropertyType_TwoBytesOfData.h"


#include "../../lib/publ/simpleTypes/BodyTextAlignment.h"
#include "../../lib/publ/simpleTypes/Charset.h"
#include "../../lib/publ/simpleTypes/ColorRef.h"
#include "../../lib/publ/simpleTypes/FileTime.h"
#include "../../lib/publ/simpleTypes/LCID.h"
#include "../../lib/publ/simpleTypes/LayoutAlignment.h"
#include "../../lib/publ/simpleTypes/ListMSAAIndex.h"
#include "../../lib/publ/simpleTypes/NoteTagShape.h"
#include "../../lib/publ/simpleTypes/PageSize.h"
#include "../../lib/publ/simpleTypes/Time32.h"


using namespace libmson;

class PSFtoXml {

public:
  static bool writeSequence(
      QFile& outputFile,
      const std::shared_ptr<packStore::PackageStoreFile>& packageStoreFile);

private:
  static QXmlStreamWriter& writePackagingStructure(
      const std::shared_ptr<packStore::PackageStoreFile>& packageStoreFile,
      QXmlStreamWriter& xmlWriter);


  static QXmlStreamWriter& writeStreamObjectHeader(
      const packStore::StreamObjectHeader_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);

  /*--------------------------------------------------------------------------*/
  /* package Types*/
  /*--------------------------------------------------------------------------*/

  static QXmlStreamWriter& writeDataElementPackage(
      const packStore::DataElementPackage& obj, QXmlStreamWriter& xmlWriter);

  static QXmlStreamWriter& writeDataElement(
      const packStore::DataElement_SPtr_t& obj, QXmlStreamWriter& xmlWriter);

  static QXmlStreamWriter& writeStorageIndex(
      const packStore::StorageIndex_SPtr_t& obj, QXmlStreamWriter& xmlWriter);

  static QXmlStreamWriter& writeStorageManifest(
      const packStore::StorageManifest_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);

  static QXmlStreamWriter& writeCellManifest(
      const packStore::CellManifest_SPtr_t& obj, QXmlStreamWriter& xmlWriter);

  static QXmlStreamWriter& writeRevisionManifest(
      const packStore::RevisionManifest_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);

  static QXmlStreamWriter& writeObjectGroup(
      const packStore::ObjectGroup_SPtr_t& obj, QXmlStreamWriter& xmlWriter);

  static QXmlStreamWriter& writeDataElementFragment(
      const packStore::DataElementFragment_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);

  static QXmlStreamWriter& writeObjectDataBLOB(
      const packStore::ObjectDataBLOB_SPtr_t& obj, QXmlStreamWriter& xmlWriter);


  /*--------------------------------------------------------------------------*/
  /* stream object Types*/
  /*--------------------------------------------------------------------------*/
  static QXmlStreamWriter& writeStorageIndexManifestMapping(
      const packStore::streamObj::StorageIndexManifestMapping_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeStorageIndexCellMapping(
      const packStore::streamObj::StorageIndexCellMapping_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeStorageIndexRevisionMapping(
      const packStore::streamObj::StorageIndexRevisionMapping_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeRootDeclare(
      const packStore::streamObj::StorageManifestRootDeclare_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeCellManifestCurrentRevision(
      const packStore::streamObj::CellManifestCurrentRevision_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeRevisionManifest(
      const packStore::streamObj::RevisionManifest_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeRevisionManifestObjectGroupReference(
      const packStore::streamObj::RevisionManifestObjectGroupReference_SPtr_t&
          obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeRevisionManifestRootDeclare(
      const packStore::streamObj::RevisionManifestRootDeclare_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);

  static QXmlStreamWriter& writeDataElementHash(
      const packStore::streamObj::DataElementHash_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectGroupDeclarations(
      const packStore::streamObj::ObjectGroupDeclarations_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectGroupMetadataDeclarations(
      const packStore::streamObj::ObjectGroupMetadataDeclarations_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectGroupData(
      const packStore::streamObj::ObjectGroupData_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectGroupObjectDeclare(
      const packStore::streamObj::ObjectGroupObjectDeclare_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectGroupObjectDataBLOBDeclaration(
      const packStore::streamObj::ObjectGroupObjectDataBLOBDeclaration_SPtr_t&
          obj,
      QXmlStreamWriter& xmlWriter);

  static QXmlStreamWriter& writeObjectGroupMetadata(
      const packStore::streamObj::ObjectGroupMetadata_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectGroupObjectDataBlobReference(
      const packStore::streamObj::ObjectGroupObjectDataBlobReference_SPtr_t&
          obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectGroupObjectData(
      const packStore::streamObj::ObjectGroupObjectData_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectGroupObjectExcludedData(
      const packStore::streamObj::ObjectGroupObjectExcludedData_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);

  static QXmlStreamWriter& writeObjectDataBLOB(
      const packStore::streamObj::ObjectDataBLOB_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);

  /*--------------------------------------------------------------------------*/
  /* common Types*/
  /*--------------------------------------------------------------------------*/
  static QXmlStreamWriter&
  writeCompactID(const priv::CompactID& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writeExtendedGUID(const priv::ExtendedGUID& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writeGUID(const QUuid& obj, QXmlStreamWriter& xmlWriter);

  static QXmlStreamWriter& writeCompactExtGuid(
      const packStore::CompactExtGuid& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeLongExtGuid(
      const packStore::LongExtGuid& obj, QXmlStreamWriter& xmlWriter);

  static QXmlStreamWriter&
  writeCellId(const packStore::CellId& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeBinaryItem(
      const packStore::BinaryItem& obj, QXmlStreamWriter& xmlWriter);

  static QXmlStreamWriter& writeCompactExtGuidArray(
      const packStore::CompactExtGuidArray& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeCellIdArray(
      const packStore::CellIdArray& obj, QXmlStreamWriter& xmlWriter);


  /*--------------------------------------------------------------------------*/
  // property Types
  /*--------------------------------------------------------------------------*/
  static QXmlStreamWriter&
  writeJCID(const priv::JCID& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writePropertyID(const priv::PropertyID& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeIPropertyType(
      const std::shared_ptr<priv::IPropertyType>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writePropertySet(const priv::PropertySet& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_ArrayNumber(
      const std::shared_ptr<priv::PropertyType_ArrayNumber>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_ArrayOfPropertyValues(
      const std::shared_ptr<priv::PropertyType_ArrayOfPropertyValues>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_Bool(QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_ContextID(
      const std::shared_ptr<priv::PropertyType_ContextID>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_EightBytesOfData(
      const std::shared_ptr<priv::PropertyType_EightBytesOfData>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_FourBytesOfData(
      const std::shared_ptr<priv::PropertyType_FourBytesOfData>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_FourBytesOfLengthFollowedByData(
      const std::shared_ptr<priv::PropertyType_FourBytesOfLengthFollowedByData>&
          obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writePropertyType_NoData(QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_ObjectID(
      const std::shared_ptr<priv::PropertyType_ObjectID>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writePropertyType_ObjectSpaceID(QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_OneByteOfData(
      const std::shared_ptr<priv::PropertyType_OneByteOfData>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_PropertySet(
      const std::shared_ptr<priv::PropertyType_PropertySet>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_TwoBytesOfData(
      const std::shared_ptr<priv::PropertyType_TwoBytesOfData>& obj,
      QXmlStreamWriter& xmlWriter);


  // MS-ONE stuff


  /*--------------------------------------------------------------------------*/
  // simpleTypes
  /*--------------------------------------------------------------------------*/
  static QXmlStreamWriter& writeBodyTextAlignment(
      const libmson::BodyTextAlignment& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writeFileTime(const libmson::FileTime& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeLayoutAlignment(
      const libmson::LayoutAlignment& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writeLCID(const libmson::LCID& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeListMSAAIndex(
      const libmson::ListMSAAIndex& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeNoteTagShape(
      const libmson::NoteTagShape& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writePageSize(const libmson::PageSize& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writeTime32(const libmson::Time32& obj, QXmlStreamWriter& xmlWriter);

  /*--------------------------------------------------------------------------*/
  // complex types
  /*--------------------------------------------------------------------------*/
  static QXmlStreamWriter&
  writeColorRef(const libmson::ColorRef& obj, QXmlStreamWriter& xmlWriter);
};


#endif // PSFTOXML_H
