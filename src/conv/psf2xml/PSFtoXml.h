#ifndef PSFTOXML_H
#define PSFTOXML_H

#include <QtCore/qglobal.h>

#include <QFile>
#include <QXmlStreamWriter>

/// \todo make a proper library import....
#include "../../lib/priv/PackageStoreFile.h"
#include "../../lib/priv/packageTypes/PackagingStructure.h"

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

  static QXmlStreamWriter& writeDataElementPackage(
      const packStore::DataElementPackage& obj, QXmlStreamWriter& xmlWriter);


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
