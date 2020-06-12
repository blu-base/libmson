#ifndef FILECHUNKREFERENCE_H
#define FILECHUNKREFERENCE_H

#include <QtCore/qglobal.h>
#include <QByteArray>

#include <iostream>



class I_FileChunkReference
{
protected:
  QByteArray m_stp;
  QByteArray m_cb;




public:
  I_FileChunkReference();
  I_FileChunkReference(const QByteArray &stp, const QByteArray &cb);

  enum class INITTYPE {
    INIT_FCRZERO,
    INIT_FCRNIL,
  };

  void set_fcrNil();
  bool is_fcrNil() const;
  void set_fcrZero();
  bool is_fcrZero() const;





  bool equals(const I_FileChunkReference &obj) const;

  void toString() const;



  quint64 get_location();
  quint64 get_size();
  quint32 get_size_in_file();

  void set_zero();


  virtual ~I_FileChunkReference() = default;


  QByteArray getStp() const;
  void setStp(const QByteArray &stp);
  quint64 getStpSize() const;

  QByteArray getCb() const;
  void setCb(const QByteArray &cb);
  quint64 getCBsize() const;
};



class FileChunkReference32 : public I_FileChunkReference {
public:
  FileChunkReference32();
  FileChunkReference32(I_FileChunkReference::INITTYPE inittype);



};

class FileChunkReference64 : public I_FileChunkReference {
public:
  FileChunkReference64();
};

class FileChunkReference64x32 : public I_FileChunkReference {
public:
  FileChunkReference64x32();
  FileChunkReference64x32(I_FileChunkReference::INITTYPE inittype);

};



enum class STP_FORMAT {
  UNCOMPRESED_8BYTE = 0,
  UNCOMPRESED_4BYTE = 1,
  COMPRESSED_2BYTE  = 2,
  COMPRESSED_4BYTE  = 3,
};

enum class CB_FORMAT {
  UNCOMPRESED_8BYTE = 1,
  UNCOMPRESED_4BYTE = 0,
  COMPRESSED_1BYTE  = 2,
  COMPRESSED_2BYTE  = 3,
};



class FileNodeChunkReference : public I_FileChunkReference {
private:
  STP_FORMAT m_stpFormat;
  CB_FORMAT m_cbFormat;
public:
  FileNodeChunkReference(STP_FORMAT stpFormat, CB_FORMAT cbFormat);
//  FileNodeChunkReference(const QByteArray stp, const QByteArray cb);

  bool isSTPcompressed();
  bool isCBcompressed();
};


#endif // FILECHUNKREFERENCE_H
