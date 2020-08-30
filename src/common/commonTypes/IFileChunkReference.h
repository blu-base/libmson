#ifndef IFILECHUNKREFERENCE_H
#define IFILECHUNKREFERENCE_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>

#include <QXmlStreamWriter>

enum FCR_INITTYPE {
  FCRZERO,
  FCRNIL,
};

template <typename S, typename C> class IFileChunkReference {
protected:
  S m_stp;
  C m_cb;

public:
  //    IFileChunkReference();

  virtual bool is_fcrNil() const = 0;
  virtual bool is_fcrZero() const = 0;

  virtual void set_fcrNil() = 0;
  virtual void set_fcrZero() = 0;

  virtual S stp() const = 0;
  virtual void setStp(const S &stp) = 0;

  virtual C cb() const = 0;
  virtual void setCb(const C &cb) = 0;

  virtual void generateXml(QXmlStreamWriter &xmlWriter) const = 0;

private:
  /**
   * @brief creates IFileChunkReference from QDataStream
   * @param ds <QDataStream> containing the deserializable IFileChunkReference
   */
  virtual void deserialize(QDataStream &ds) = 0;
  /**
   * @brief creates byte stream from IFileChunkReference object
   * @param ds <QDataStream> is the output stream to which the serialized
   * IFileChunkReference is send
   */
  virtual void serialize(QDataStream &ds) const = 0;

  /**
   * @brief prints the IFileChunkReference to a <QDebug> object
   * @param dbg <QDebug> string builder for the debug information
   */
  virtual void toDebugString(QDebug dbg) const = 0;

  friend QDataStream &operator<<(QDataStream &ds,
                                 const IFileChunkReference &obj) {
    obj.serialize(ds);
    return ds;
  };
  friend QDataStream &operator>>(QDataStream &ds, IFileChunkReference &obj) {
    obj.deserialize(ds);
    return ds;
  }
  friend QDebug operator<<(QDebug dbg, const IFileChunkReference &obj) {
    obj.toDebugString(dbg);
    return dbg;
  };
};

#endif // IFILECHUNKREFERENCE_H
