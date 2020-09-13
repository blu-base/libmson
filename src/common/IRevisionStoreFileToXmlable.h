#ifndef IREVISONSTOREFILETOXMLABLE_H
#define IREVISONSTOREFILETOXMLABLE_H

#include <QtCore/qglobal.h>

#include <QXmlStreamWriter>

namespace MSONcommon {

class IRevisionStoreFileToXmlable {
protected:
  IRevisionStoreFileToXmlable() = default;
  virtual ~IRevisionStoreFileToXmlable() = default;

public:
  friend QXmlStreamWriter &operator<<(QXmlStreamWriter &xmlWriter,
                                      const IRevisionStoreFileToXmlable &obj);

private:
  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const = 0;
};

} // namespace MSONcommon

#endif // IREVISONSTOREFILETOXMLABLE_H
