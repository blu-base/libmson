#include "IRevisionStoreFileToXmlable.h"

namespace MSONcommon {

QXmlStreamWriter &operator<<(QXmlStreamWriter &xmlWriter,
                             const IRevisionStoreFileToXmlable &obj) {
  obj.writeLowLevelXml(xmlWriter);
  return xmlWriter;
}

} // namespace MSONcommon
