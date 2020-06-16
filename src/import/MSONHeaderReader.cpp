#include "MSONHeaderReader.h"

MSONHeaderReader::MSONHeaderReader()
{

}


//QDataStream &operator<<(QDataStream &ds, const MSONDocument &obj) {
//  ds << *obj.m_header;

//  return ds;
//}

//QDataStream &operator>>(QDataStream &ds, MSONDocument &obj) {
//  if (!ds.byteOrder()) {
//    ds.setByteOrder(QDataStream::LittleEndian);
//  }

//  ds >> *obj.m_header;

//  ds >> obj.m_fnlRoot;

//  return ds;
//}

//QDebug operator<<(QDebug dbg, const MSONDocument &obj) {

//  QDebugStateSaver saver(dbg);
//  dbg.setAutoInsertSpaces(false);

//  dbg << "MSON Document\n";
//  dbg << *obj.m_header;

//  dbg << obj.m_fnlRoot;

//  return dbg;
//}
