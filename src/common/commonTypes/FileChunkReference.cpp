//#include "FileChunkReference.h"

//#include <QBuffer>
//#include <QDataStream>
//#include <QDebug>
//#include <QtEndian>

// I_FileChunkReference::I_FileChunkReference() {
//  m_stp = new QByteArray();
//  m_cb = new QByteArray();
//}

// I_FileChunkReference::~I_FileChunkReference() {
//  delete m_stp;
//  delete m_cb;
//}

// I_FileChunkReference::I_FileChunkReference(const QByteArray stp,
//                                           const QByteArray cb) {
//  m_stp = new QByteArray(stp);
//  m_cb = new QByteArray(cb);
//}

////// copy constructor
//// I_FileChunkReference::I_FileChunkReference(const I_FileChunkReference&
//// source)
////  : m_stp { nullptr }, m_cb { nullptr }
////{
////  m_stp = new QByteArray(source.m_stp->size(),'\0');
////  m_cb = new QByteArray(source.m_cb->size(),'\0');

////  m_stp->replace(0,source.m_stp->size(),*(source.m_stp));
////  m_cb->replace(0,source.m_cb->size(),*(source.m_cb));
////}

////// move constructor
//// I_FileChunkReference::I_FileChunkReference(I_FileChunkReference&& source)
////  : m_stp { nullptr }, m_cb { nullptr }
////{
////  delete[] m_stp;
////  delete[] m_cb;

////  m_stp = source.m_stp;
////  m_stp = source.m_cb;

////  source.m_stp = nullptr;
////  source.m_cb = nullptr;

////}

// QByteArray *I_FileChunkReference::getCb() const { return m_cb; }

// void I_FileChunkReference::setCb(const QByteArray &cb) {

//  m_cb = new QByteArray(cb);
//}

// uint64_t I_FileChunkReference::getCBsize() const { return m_cb->size(); }

// void I_FileChunkReference::set_fcrNil() {
//  m_stp = new QByteArray(m_stp->size(), '\xFF');
//  m_cb = new QByteArray(m_cb->size(), '\0');
//}

// bool I_FileChunkReference::is_fcrNil() const {
//  return *m_stp == QByteArray(m_stp->size(), '\xFF') &&
//         *m_cb == QByteArray(m_cb->size(), '\0');
//}

// void I_FileChunkReference::set_fcrZero() {
//  m_stp = new QByteArray(m_stp->size(), '\0');
//  m_cb = new QByteArray(m_cb->size(), '\0');
//}

// bool I_FileChunkReference::is_fcrZero() const {
//  return *m_stp == QByteArray(m_stp->size(), '\0') &&
//         *m_cb == QByteArray(m_cb->size(), '\0');
//}

//// I_FileChunkReference& I_FileChunkReference::operator=(const
//// I_FileChunkReference& rhs)
////{
////  if(this == &rhs) {
////      return *this;
////  }
////  delete m_stp;
////  delete m_cb;

////  *m_stp = *(rhs.m_stp);
////  *m_cb = *(rhs.m_cb);

////  return *this;
////}

//// I_FileChunkReference&
///I_FileChunkReference::operator=(I_FileChunkReference&& / rhs)
////{
////  if(this == &rhs) {
////      return *this;
////  }

////  delete m_stp;
////  delete m_cb;

////  m_stp = rhs.m_stp;
////  m_cb = rhs.m_cb;

////  rhs.m_stp = nullptr:
////  rhs.m_cb = nullptr;

////  return *this;
////}

// QDataStream &operator<<(QDataStream &s, const I_FileChunkReference &obj) {
//  s << obj.getStp() << obj.getCb();

//  return s;
//}

///**
// * @brief operator >>
// * @param s
// * @param obj
// * @return
// *
// * TODO this is a mess, learn about templates
// */
// QDataStream &operator>>(QDataStream &s, I_FileChunkReference &obj) {
//  quint8 v_quint8;
//  quint16 v_quint16;
//  quint32 v_quint32;
//  quint64 v_quint64;

//  if (s.byteOrder()) {
//    s.setByteOrder(QDataStream::BigEndian);
//  }

//  switch (obj.getStpSize()) {
//  case 8: {
//    s >> v_quint64;
//    QByteArray temp(reinterpret_cast<const char *>(&v_quint64),
//                    sizeof(v_quint64));
//    obj.setStp(temp);
//    break;
//  }
//  case 4: {
//    s >> v_quint32;
//    QByteArray temp(reinterpret_cast<const char *>(&v_quint32),
//                    sizeof(v_quint32));
//    obj.setStp(temp);
//    break;
//  }
//  case 2: {
//    s >> v_quint16;
//    QByteArray temp(reinterpret_cast<const char *>(&v_quint16),
//                    sizeof(v_quint16));
//    obj.setStp(temp);
//    break;
//  }
//  case 1: {
//    s >> v_quint8;
//    QByteArray temp(reinterpret_cast<const char *>(&v_quint8),
//                    sizeof(v_quint8));
//    obj.setStp(temp);
//    break;
//  }
//  }

//  switch (obj.getCBsize()) {
//  case 8: {
//    s >> v_quint64;
//    QByteArray temp(reinterpret_cast<const char *>(&v_quint64),
//                    sizeof(v_quint64));
//    obj.setCb(temp);
//    break;
//  }
//  case 4: {
//    s >> v_quint32;
//    QByteArray temp(reinterpret_cast<const char *>(&v_quint32),
//                    sizeof(v_quint32));
//    obj.setCb(temp);
//    break;
//  }
//  case 2: {
//    s >> v_quint16;
//    QByteArray temp(reinterpret_cast<const char *>(&v_quint16),
//                    sizeof(v_quint16));
//    obj.setCb(temp);
//    break;
//  }
//  case 1: {
//    s >> v_quint8;
//    QByteArray temp(reinterpret_cast<const char *>(&v_quint8),
//                    sizeof(v_quint8));
//    obj.setCb(temp);
//    break;
//  }
//  }

//  s.setByteOrder(QDataStream::LittleEndian);
//  return s;
//}

// QDebug operator<<(QDebug dbg, const I_FileChunkReference &obj) {
//  QDebugStateSaver saver(dbg);
//  dbg.nospace() << "FileChunkReference(stp: " << obj.getStp()->toHex()
//                << ", cb: " << obj.getCb()->toHex() << ")";
//  return dbg;
//}

// QByteArray *I_FileChunkReference::getStp() const { return m_stp; }

// void I_FileChunkReference::setStp(const QByteArray &stp) {
//  m_stp = new QByteArray(stp);
//}

// ulong I_FileChunkReference::getStpSize() const { return m_stp->size(); }

// FileChunkReference32::FileChunkReference32() {
//  m_stp = new QByteArray(4, '\0');
//  m_cb = new QByteArray(4, '\0');
//}

// FileChunkReference32::FileChunkReference32(INITTYPE inittype)
//    : FileChunkReference32() {

//  switch (inittype) {
//  case INITTYPE::FCRNIL:
//    this->set_fcrNil();
//    break;
//  case INITTYPE::FCRZERO:
//    this->set_fcrZero();
//    break;
//  }
//}

// FileChunkReference32::~FileChunkReference32() {}

// FileChunkReference64::FileChunkReference64() {
//  m_stp = new QByteArray(8, '\0');
//  m_cb = new QByteArray(8, '\0');
//}

// FileChunkReference64::FileChunkReference64(
//    I_FileChunkReference::INITTYPE inittype)
//    : FileChunkReference64() {
//  switch (inittype) {
//  case INITTYPE::FCRNIL:
//    this->set_fcrNil();
//    break;
//  case INITTYPE::FCRZERO:
//    this->set_fcrZero();
//    break;
//  }
//}

// FileChunkReference64::~FileChunkReference64() {}

// FileChunkReference64x32::FileChunkReference64x32() {
//  m_stp = new QByteArray(8, '\0');
//  m_cb = new QByteArray(4, '\0');
//}

//// FileChunkReference64x32::FileChunkReference64x32(FileChunkReference64x32&
//// source)
////{
////  m_stp = new QByteArray(*source.m_stp);
////  m_cb = new QByteArray(*source.m_cb);

////}

// FileChunkReference64x32::FileChunkReference64x32(
//    I_FileChunkReference::INITTYPE inittype)
//    : FileChunkReference64x32() {
//  switch (inittype) {
//  case INITTYPE::FCRNIL:
//    this->set_fcrNil();
//    break;
//  case INITTYPE::FCRZERO:
//    this->set_fcrZero();
//    break;
//  }
//}

//// FileChunkReference64x32::FileChunkReference64x32(const QByteArray stp,
///const / QByteArray cb) /  : FileChunkReference64x32()
////{
////  *m_stp = stp;
////  *m_cb = cb;
////}

// FileChunkReference64x32::~FileChunkReference64x32() {
//  delete[] m_stp;
//  delete[] m_cb;
//}

// FileNodeChunkReference::FileNodeChunkReference()
//  : I_FileChunkReference()
//{

//}

// FileNodeChunkReference::FileNodeChunkReference(STP_FORMAT stpFormat,
//                                               CB_FORMAT cbFormat) {
//  m_stpFormat = stpFormat;
//  m_cbFormat = cbFormat;

//  setStpFormatArray(stpFormat);
//  setCBFormatArray(cbFormat);

//}

// FileNodeChunkReference::FileNodeChunkReference(quint8 stpFormat, quint8
// cbFormat)
// :
// FileNodeChunkReference(static_cast<STP_FORMAT>(stpFormat),static_cast<CB_FORMAT>(cbFormat))
//{

//}

// void FileNodeChunkReference::setStpFormatArray(quint8 stpFormat)
//{
//  setStpFormatArray(static_cast<STP_FORMAT>(stpFormat));
//}

// void FileNodeChunkReference::setCBFormatArray(quint8 cbFormat)
//{
//  setCBFormatArray(static_cast<CB_FORMAT>(cbFormat));
//}

// void FileNodeChunkReference::setStpFormatArray(STP_FORMAT stpFormat)
//{
//  switch (stpFormat) {
//  case STP_FORMAT::UNCOMPRESED_8BYTE:
//    m_stp = new QByteArray(8, '\0');
//    break;
//  case STP_FORMAT::UNCOMPRESED_4BYTE:
//  case STP_FORMAT::COMPRESSED_4BYTE:
//    m_stp = new QByteArray(4, '\0');
//    break;
//  case STP_FORMAT::COMPRESSED_2BYTE:
//    m_stp = new QByteArray(2, '\0');
//    break;
//  }
//}

// void FileNodeChunkReference::setCBFormatArray(CB_FORMAT cbFormat)
//{
//  switch (cbFormat) {
//  case CB_FORMAT::UNCOMPRESED_8BYTE:
//    m_cb = new QByteArray(8, '\0');
//    break;
//  case CB_FORMAT::UNCOMPRESED_4BYTE:
//    m_cb = new QByteArray(4, '\0');
//    break;
//  case CB_FORMAT::COMPRESSED_1BYTE:
//    m_cb = new QByteArray(1, '\0');
//    break;
//  case CB_FORMAT::COMPRESSED_2BYTE:
//    m_cb = new QByteArray(2, '\0');
//    break;
//  }
//}

// bool FileNodeChunkReference::isSTPcompressed() {
//  return m_stpFormat == STP_FORMAT::COMPRESSED_4BYTE ||
//         m_stpFormat == STP_FORMAT::COMPRESSED_2BYTE;
//}

// bool FileNodeChunkReference::isCBcompressed() {
//  return m_cbFormat == CB_FORMAT::COMPRESSED_2BYTE ||
//         m_cbFormat == CB_FORMAT::COMPRESSED_1BYTE;
//}

// FileNodeChunkReference::~FileNodeChunkReference() {}

// bool FileNodeChunkReference::is_fcrNil() const
//{

//}
