//#ifndef FILECHUNKREFERENCE_H
//#define FILECHUNKREFERENCE_H

//#include <QByteArray>
//#include <QtCore/qglobal.h>

//#include <iostream>

///**
// * @brief The abstract I_FileChunkReference class
// */
// class I_FileChunkReference {
// protected:
//  QByteArray *m_stp;
//  QByteArray *m_cb;

// public:
//  /**
//   * @brief I_FileChunkReference default constructor
//   */
//  I_FileChunkReference();

//  /**
//   * @brief I_FileChunkReference
//   * @param stp
//   * @param cb
//   */
//  I_FileChunkReference(const QByteArray stp, const QByteArray cb);

//  ~I_FileChunkReference();

//  //  I_FileChunkReference(const I_FileChunkReference& source); // copy
//  //  constructor I_FileChunkReference(I_FileChunkReference&& source);      //
//  //  move constructor

//  /**
//   * @brief The INITTYPE enum
//   *
//   * States of FileChunkReferences.
//   *
//   * In FCRZERO state, alls bits of stp and cb are 0.
//   * In FCRNil state, all bits of stp are 1, while all bits in cb are 0;
//   */
//  enum class INITTYPE {
//    FCRZERO,
//    FCRNIL,
//  };

//  /**
//   * @brief set_fcrNil
//   *
//   * Sets the FileChunkRefernce to FCRNIL state
//   */
//  void set_fcrNil();
//  /**
//   * @brief is_fcrNil
//   * @return true if FileChunkRefernce is in FCRNIL state
//   */
//  bool is_fcrNil() const;
//  /**
//   * @brief set_fcrZero
//   * Sets the FileChunkRefernce to FCRZERO state
//   */

//  void set_fcrZero();
//  /**
//   * @brief is_fcrZero
//   * @return true if FileChunkRefernce is in FCRZERO state
//   */
//  bool is_fcrZero() const;

//  bool equals(const I_FileChunkReference &obj) const;
//  void toString() const;

//  uint64_t get_location();
//  uint64_t get_size();
//  uint32_t get_size_in_file();

//  //  I_FileChunkReference& operator=(const I_FileChunkReference& rhs); //
//  copy
//  //  assignment I_FileChunkReference& operator=(I_FileChunkReference&& rhs);
//  //
//  //  move assignment

//  //  friend bool operator==(const I_FileChunkReference& lhs, const
//  //  I_FileChunkReference& rhs) noexcept; friend bool operator!=(const
//  //  I_FileChunkReference& lhs, const I_FileChunkReference& rhs) noexcept;
//  //  friend bool operator<=(const I_FileChunkReference& lhs, const
//  //  I_FileChunkReference& rhs) noexcept; friend bool operator>=(const
//  //  I_FileChunkReference& lhs, const I_FileChunkReference& rhs) noexcept;

//  QByteArray *getStp() const;
//  void setStp(const QByteArray &stp);
//  uint64_t getStpSize() const;

//  QByteArray *getCb() const;
//  void setCb(const QByteArray &cb);
//  uint64_t getCBsize() const;
//};

//// class FileChunkReference32 : public I_FileChunkReference {
//// public:
////  FileChunkReference32();
////  FileChunkReference32(I_FileChunkReference::INITTYPE inittype);

////  virtual ~FileChunkReference32();
////};

// class FileChunkReference64 : public I_FileChunkReference {
// public:
//  FileChunkReference64();
//  FileChunkReference64(I_FileChunkReference::INITTYPE inittype);

//  virtual ~FileChunkReference64();
//};

// class FileChunkReference64x32 : public I_FileChunkReference {
// public:
//  FileChunkReference64x32();
//  //  FileChunkReference64x32(FileChunkReference64x32& source);
//  FileChunkReference64x32(I_FileChunkReference::INITTYPE inittype);
//  //  FileChunkReference64x32(const QByteArray stp, const QByteArray cb);

//  virtual ~FileChunkReference64x32();
//};

//// enum class STP_FORMAT {
////  UNCOMPRESED_8BYTE = 0,
////  UNCOMPRESED_4BYTE = 1,
////  COMPRESSED_2BYTE = 2,
////  COMPRESSED_4BYTE = 3,
////};

//// enum class CB_FORMAT {
////  UNCOMPRESED_8BYTE = 1,
////  UNCOMPRESED_4BYTE = 0,
////  COMPRESSED_1BYTE = 2,
////  COMPRESSED_2BYTE = 3,
////};

// class FileNodeChunkReference : public I_FileChunkReference {
// private:
//  STP_FORMAT m_stpFormat;
//  CB_FORMAT m_cbFormat;

// public:
//  FileNodeChunkReference();
//  FileNodeChunkReference(STP_FORMAT stpFormat, CB_FORMAT cbFormat);
//  FileNodeChunkReference(quint8 stpFormat, quint8 cbFormat);

//  void setStpFormatArray(STP_FORMAT stpFormat);
//  void setStpFormatArray(quint8 stpFormat);
//  void setCBFormatArray(CB_FORMAT cbFormat);
//  void setCBFormatArray(quint8 cbFormat);

//  bool isSTPcompressed();
//  bool isCBcompressed();

//  virtual ~FileNodeChunkReference();
//};

//#endif // FILECHUNKREFERENCE_H
