#include "ObjectDataEncryptionKeyV2FNDX.h"

ObjectDataEncryptionKeyV2FNDX::ObjectDataEncryptionKeyV2FNDX(
    FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : ref(stpFormat, cbFormat), header(), footer() {}
ObjectDataEncryptionKeyV2FNDX::ObjectDataEncryptionKeyV2FNDX(quint8 stpFormat,
                                                             quint8 cbFormat)
    : ref(stpFormat, cbFormat), header(), footer() {}

QByteArray ObjectDataEncryptionKeyV2FNDX::getEncryptionData() const {
  return EncryptionData;
}

void ObjectDataEncryptionKeyV2FNDX::setEncryptionData(const QByteArray &value) {
  EncryptionData = value;
}

quint64 ObjectDataEncryptionKeyV2FNDX::getFooter() const { return footer; }

void ObjectDataEncryptionKeyV2FNDX::setFooter(const quint64 &value) {
  footer = value;
}

quint64 ObjectDataEncryptionKeyV2FNDX::getHeader() const { return header; }

void ObjectDataEncryptionKeyV2FNDX::setHeader(const quint64 &value) {
  header = value;
}

FileNodeChunkReference ObjectDataEncryptionKeyV2FNDX::getRef() const {
  return ref;
}

void ObjectDataEncryptionKeyV2FNDX::setRef(
    const FileNodeChunkReference &value) {
  ref = value;
}

/**
 * @brief ObjectDataEncryptionKeyV2FNDX::deserialize
 * @param ds
 *
 * \todo there is probably an error here
 */
void ObjectDataEncryptionKeyV2FNDX::deserialize(QDataStream &ds) {
  ds >> ref;

  quint64 currentloc = ds.device()->pos();

  ds.device()->seek(ref.stp());
  ds >> header;
  EncryptionData = ds.device()->peek(ref.cb());
  ds >> footer;

  ds.device()->seek(currentloc);
}

/**
 * @brief ObjectDataEncryptionKeyV2FNDX::serialize
 * @param ds
 *
 * \todo figure out when encrypted data should be stored, currently
 * unimplemented
 */
void ObjectDataEncryptionKeyV2FNDX::serialize(QDataStream &ds) const {
  ds << ref;
}

void ObjectDataEncryptionKeyV2FNDX::toDebugString(QDebug dbg) const {
  dbg << " ObjectDataEncryptionKeyV2FNDX:\n"
      << " Ref: " << ref << '\n';
}