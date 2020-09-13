#include "PropertyType_Bool.h"
#include <QDebug>

namespace MSONcommon {

PropertyType_Bool::PropertyType_Bool() {}

void PropertyType_Bool::deserialize(QDataStream &ds) {}

void PropertyType_Bool::serialize(QDataStream &ds) const {}

void PropertyType_Bool::toDebugString(QDebug &dbg) const {}

void PropertyType_Bool::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {}

} // namespace MSONcommon
