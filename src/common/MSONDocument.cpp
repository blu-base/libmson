#include "MSONDocument.h"

#include <memory>

#include <QDataStream>
#include <QDebug>

namespace MSONcommon {

void MSONDocument::setFnlRoot(const FileNodeList &value) { m_fnlRoot = value; }

FileNodeList MSONDocument::fnlRoot() const { return m_fnlRoot; }

MSONDocument::MSONDocument() { m_header = new MSONHeader(); }

MSONDocument::~MSONDocument() {}

QDataStream &operator<<(QDataStream &ds, const MSONDocument &obj) {
  ds << *obj.m_header;

  return ds;
}

QDataStream &operator>>(QDataStream &ds, MSONDocument &obj) {
  if (!ds.byteOrder()) {
    ds.setByteOrder(QDataStream::LittleEndian);
  }

  ds >> *obj.m_header;

  ds >> obj.m_fnlRoot;

  return ds;
}

QDebug operator<<(QDebug dbg, const MSONDocument &obj) {

  QDebugStateSaver saver(dbg);
  dbg.setAutoInsertSpaces(false);

  dbg << "MSON Document\n";
  dbg << *obj.m_header;

  dbg << obj.m_fnlRoot;

  return dbg;
}

MSONHeader MSONDocument::header() const { return *m_header; }

// turn this->m_header;
//}MSONHeader* MSONDocument::header() const
//{
//  re

// void MSONDocument::setHeader(MSONHeader header)
//{
//  m_header = nullptr;
//  m_header = std::unique_ptr<MSONHeader>(&header);
//}
} // namespace mson_common
