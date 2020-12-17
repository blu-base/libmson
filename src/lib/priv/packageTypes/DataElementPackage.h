#ifndef DATAELEMENTPACKAGE_H
#define DATAELEMENTPACKAGE_H

#include <memory>

#include <QtCore/qglobal.h>

#include "DataElement.h"
#include "StreamObjectHeader.h"

namespace libmson {
namespace packStore {

class DataElementPackage;

typedef std::shared_ptr<DataElementPackage> DataElementPackage_SPtr_t;
typedef std::weak_ptr<DataElementPackage> DataElementPackage_WPtr_t;

class DataElementPackage {
private:
  StreamObjectHeader_SPtr_t m_header;

  QByteArray m_data;

  DataElement_SPtr_t m_dataElement;

  std::vector<DataElementPackage_SPtr_t> m_children;

  // for Debug purpose
  quint64 m_stp = 0;

  //  std::shared_ptr<DataElement> m_data;

public:
  DataElementPackage();

  StreamObjectHeader_SPtr_t getHeader() const;
  void setHeader(const StreamObjectHeader_SPtr_t& header);

  //  std::shared_ptr<DataElement> getData() const;
  //  void setData(const std::shared_ptr<DataElement>& data);

  friend class PackageStoreFileParser;

  QByteArray getData() const;
  void setData(const QByteArray& data);

  std::vector<DataElementPackage_SPtr_t> getChildren() const;
  std::vector<DataElementPackage_SPtr_t>& children();
  void setChildren(const std::vector<DataElementPackage_SPtr_t>& children);
  DataElement_SPtr_t getDataElement() const;
  void setDataElement(const DataElement_SPtr_t& dataElement);
};


} // namespace packStore
} // namespace libmson


#endif // DATAELEMENTPACKAGE_H
