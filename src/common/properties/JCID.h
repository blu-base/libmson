#ifndef JCID_H
#define JCID_H

#include <QtCore/qglobal.h>

class JCID {
private:
  quint16 m_index;
  bool m_IsBinary;
  bool m_IsPropertySet;
  bool m_IsGraphNode;
  bool m_IsFileData;
  bool m_IsReadOnly;

public:
  JCID();

  friend QDataStream &operator<<(QDataStream &ds, const JCID &obj);
  friend QDataStream &operator>>(QDataStream &ds, JCID &obj);

  friend QDebug operator<<(QDebug dbg, const JCID &obj);

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

private:
  void deserialize(QDataStream &ds);
  void serialize(QDataStream &ds) const;
  void toDebugString(QDebug dbg) const;
};

#endif // JCID_H
