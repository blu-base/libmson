#ifndef JCID_H
#define JCID_H

#include <QtCore/qglobal.h>

#include "../commonTypes/Enums.h"

#include <QXmlStreamWriter>

static constexpr const quint32 JCID_relmaskValue = 0xFFFF;
static constexpr const quint32 JCID_relmaskIsBinary = 0x1;
static constexpr const quint32 JCID_relmaskIsPropertySet = 0x1;
static constexpr const quint32 JCID_relmaskIsGraphNode = 0x1;
static constexpr const quint32 JCID_relmaskIsFileData = 0x1;
static constexpr const quint32 JCID_relmaskIsReadOnly = 0x1;

static constexpr const quint32 JCID_shiftValue = 0;
static constexpr const quint32 JCID_shiftIsBinary = 16;
static constexpr const quint32 JCID_shiftIsPropertySet = 17;
static constexpr const quint32 JCID_shiftIsGraphNode = 18;
static constexpr const quint32 JCID_shiftIsFileData = 19;
static constexpr const quint32 JCID_shiftIsReadOnly = 20;

static constexpr const quint32 JCID_imaskValue = 0x001F0000;
static constexpr const quint32 JCID_imaskIsBinary = 0x001EFFFF;
static constexpr const quint32 JCID_imaskIsPropertySet = 0x001DFFFF;
static constexpr const quint32 JCID_imaskIsGraphNode = 0x001BFFFF;
static constexpr const quint32 JCID_imaskIsFileData = 0x0017FFFF;
static constexpr const quint32 JCID_imaskIsReadOnly = 0x000FFFFF;

class JCID {
private:
  quint32 m_value;

public:
  JCID();

  friend QDataStream &operator<<(QDataStream &ds, const JCID &obj);
  friend QDataStream &operator>>(QDataStream &ds, JCID &obj);

  friend QDebug operator<<(QDebug dbg, const JCID &obj);

  void generateXml(QXmlStreamWriter &xmlWriter) const;

  quint16 index() const;
  void setIndex(const quint16 &index);

  bool IsBinary() const;
  void setIsBinary(bool IsBinary);

  bool IsPropertySet() const;
  void setIsPropertySet(bool IsPropertySet);

  bool IsGraphNode() const;
  void setIsGraphNode(bool IsGraphNode);

  bool IsFileData() const;
  void setIsFileData(bool IsFileData);

  bool IsReadOnly() const;
  void setIsReadOnly(bool IsReadOnly);

  JCIDs type() const;
  QString typeToString() const;

private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;
};

#endif // JCID_H
