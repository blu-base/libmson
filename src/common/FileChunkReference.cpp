#include "FileChunkReference.h"

#include <QDebug>
#include <QDataStream>


QByteArray I_FileChunkReference::getCb() const
{
  return m_cb;
}

void I_FileChunkReference::setCb(QByteArray cb)
{
  m_cb = cb;
}

uint64_t I_FileChunkReference::getCBsize() const
{
  return m_cb.size();
}

I_FileChunkReference::I_FileChunkReference()
{

}

void I_FileChunkReference::set_fcrNil()
{
  m_stp = QByteArray(m_stp.size(),'\xFF');
  m_cb = QByteArray(m_cb.size(),'\0');
}

bool I_FileChunkReference::is_fcrNil() const
{
  return m_stp == QByteArray(m_stp.size(),'\xFF') && m_cb == QByteArray(m_cb.size(),'\0');
}

void I_FileChunkReference::set_fcrZero()
{
  m_stp = QByteArray(m_stp.size(),'\0');
  m_cb = QByteArray(m_cb.size(),'\0');
}

bool I_FileChunkReference::is_fcrZero() const
{
  return m_stp == QByteArray(m_stp.size(),'\0') && m_cb == QByteArray(m_cb.size(),'\0');
}


QDebug operator<<(QDebug dbg, const I_FileChunkReference& obj)
{
  QDebugStateSaver saver(dbg);
  dbg.nospace() << QString("FileChunkReference(stp: ") << QString::fromStdString(obj.getStp().toHex().toStdString()) << QString(", cb: ") << obj.getCb().toHex() << QString(")");
  return dbg;
}


QByteArray I_FileChunkReference::getStp() const
{
  return m_stp;
}

void I_FileChunkReference::setStp(const QByteArray stp)
{
  m_stp = stp;
}

ulong I_FileChunkReference::getStpSize() const
{
  return m_stp.size();
}





FileChunkReference32::FileChunkReference32()
{
  m_stp.resize(4);
  m_cb.resize(4);

}

FileChunkReference32::FileChunkReference32(INITTYPE inittype)
{
  FileChunkReference32();

  switch (inittype) {
    case INITTYPE::INIT_FCRNIL:
      this->set_fcrNil();
      break;
    case INITTYPE::INIT_FCRZERO:
      this->set_fcrZero();
      break;
  }

}

QDataStream& operator<<(QDataStream& s,  FileChunkReference32& obj)
{
  s << obj.getStp() << obj.getCb();
}

QDataStream& operator>>(QDataStream& s, FileChunkReference32& obj)
{
  int length = 4;
  char temp [length];

  s.readRawData(temp, length);
  obj.m_stp.replace(0,length,temp );

  s.readRawData(temp, length);
  obj.m_cb.replace(0,length,temp );

  return s;
}






FileChunkReference64::FileChunkReference64()
{
  m_stp.resize(8);
  m_cb.resize(8);
}


FileChunkReference64x32::FileChunkReference64x32()
{
  m_stp.resize(8);
  m_cb.resize(4);
}

FileChunkReference64x32::FileChunkReference64x32(I_FileChunkReference::INITTYPE inittype)
{
  FileChunkReference64x32();

  switch (inittype) {
    case INITTYPE::INIT_FCRNIL:
      this->set_fcrNil();
      break;
    case INITTYPE::INIT_FCRZERO:
      this->set_fcrZero();
      break;
  }
}





FileNodeChunkReference::FileNodeChunkReference(STP_FORMAT stpFormat, CB_FORMAT cbFormat)
{
  m_stpFormat = stpFormat;
  m_cbFormat = cbFormat;

  switch (stpFormat)
  {
    case STP_FORMAT::UNCOMPRESED_8BYTE:
      m_stp.resize(8);
      break;
    case STP_FORMAT::UNCOMPRESED_4BYTE:
      m_stp.resize(4);
      break;
    case STP_FORMAT::COMPRESSED_2BYTE:
      m_stp.resize(2);
      break;
    case STP_FORMAT::COMPRESSED_4BYTE:
      m_stp.resize(4);
      break;
  }

  switch (cbFormat) {
    case CB_FORMAT::UNCOMPRESED_8BYTE:
      m_cb.resize(8);
      break;
    case CB_FORMAT::UNCOMPRESED_4BYTE:
      m_cb.resize(4);
      break;
    case CB_FORMAT::COMPRESSED_1BYTE:
      m_cb.resize(1);
      break;
    case CB_FORMAT::COMPRESSED_2BYTE:
      m_cb.resize(2);
      break;

  }
}

bool FileNodeChunkReference::isSTPcompressed()
{
  return m_stpFormat == STP_FORMAT::COMPRESSED_4BYTE ||
      m_stpFormat == STP_FORMAT::COMPRESSED_2BYTE;
}

bool FileNodeChunkReference::isCBcompressed()
{
  return m_cbFormat == CB_FORMAT::COMPRESSED_2BYTE ||
      m_cbFormat == CB_FORMAT::COMPRESSED_1BYTE;
}
