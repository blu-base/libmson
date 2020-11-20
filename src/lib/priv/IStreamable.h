#ifndef ISTREAMABLE_H
#define ISTREAMABLE_H

#include <QDataStream>
#include <QtCore/qglobal.h>

namespace libmson {
namespace priv {


/// Non-chunkable objects, which can be trivially (de)serialized.
/// Typically such objects do not contain any file stream points, FileNodeChunkReferences, FileNodeListFragments, etc.
/// The latter is handled in the RevisionStoreFileParser and RevisionStoreFileWrite classes
class IStreamable {
protected:
  IStreamable()          = default;
  virtual ~IStreamable() = default;

private:
  /// Parsing method for unchunkable objects in the MS-ONESTORE specification
  virtual void deserialize(QDataStream& ds)     = 0;
  /// Writing method for unchunkable objects in the MS-ONESTORE specification
  virtual void serialize(QDataStream& ds) const = 0;

public:
  friend QDataStream& operator<<(QDataStream& ds, const IStreamable& obj);
  friend QByteArray& operator<<(QByteArray& ba, const IStreamable& obj);

  friend QDataStream& operator>>(QDataStream& ds, IStreamable& obj);
};

} // namespace priv
} // namespace libmson

#endif // ISTREAMABLE_H
