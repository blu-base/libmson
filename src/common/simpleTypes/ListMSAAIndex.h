#ifndef LISTMSAAINDEX_H
#define LISTMSAAINDEX_H

#include <QtCore/qglobal.h>

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {

enum class ListSymbolID : quint16 {
  nil = 0x0,
  circle_solid_small = 0x1,
  circle_hollow_small = 0x2,
  circle_solid = 0x3,
  circle_hollow = 0x4,
  donut_solid = 0x5,
  donut_hollow = 0x6,
  square_solid_small = 0x7,
  square_hollow_small = 0x8,
  square_solid = 0x9,
  square_hollow = 0x10,
  triangle_narrow = 0x11,
  triangle_wide = 0x12,
  diamond_hollow_large = 0x13,
  diamond_hollow = 0x14,
  diamond_solid_small = 0x15,
  fourSmallDiamonds = 0x16,
  star_solid_large = 0x17,
  star_hollow_large = 0x18,
  sun_solid_large = 0x19,
  greaterThan_sign = 0x20,
  arrow_single_line = 0x21,
  arrow_double_line = 0x22,
  arrow_hollow_large = 0x23,
  asterisk = 0x24,
  dash = 0x25,
  enDash = 0x26,
  emDash = 0x27,
  smilingFace = 0x28,
  neutralFace = 0x29,
  frowningFace = 0x30,
  checkMark = 0x31,
  telephone = 0x32,
  EnvelopeBack = 0x33,
  diamond_solid = 0x34,
};

  static QString IDtoString(const ListSymbolID id);
  static QString IDtoString(const quint16 id);

class ListMSAAIndex : public IRevisionStoreFileObject {
private:
  quint16 m_value;

public:
  ListMSAAIndex();

  void setID(const ListSymbolID id);
  ListSymbolID getID() const;

  void setIDValue(const quint16 id);
  quint16 getIDValue() const;




private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter& xmlWriter) const override;

  virtual void toDebugString(QDebug& dbg) const override;
};

} // namespace MSONcommon

#endif // LISTMSAAINDEX_H
