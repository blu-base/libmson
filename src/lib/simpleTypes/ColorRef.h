#ifndef COLORREF_H
#define COLORREF_H

#include <QDataStream>
#include <QtCore/qglobal.h>


#include "../interfaces/IStreamable.h"

namespace libmson {

/** @class ColorRef
 * @brief complex type COLORREF according to [MS-ONE] section 2.2.8
 *
 * must be value in range [0x00000000,0x00FFFFFF] as rgb color values, or
 * [0xFF000000] for automatic color
 */
class ColorRef : public IStreamable {
private:
  quint32 m_colorVal;

public:
  ColorRef();
  ColorRef(const quint32 colorVal);


  /** returns whether the color of the referencing object is automatically
   * selectable */
  bool isSetToAutomatic() const;

  /** changes this instances to be an automatically selected color. Previous
   * color will be overriden. */
  void setToAutomatic();


  /** returns RGB values within the mask 0x00FFFFFF, or 0xFF000000 if this
   * instance is set to be an automatic color */
  quint32 getColorRef() const;

  /** specifies an rgb value in the range [0x00000000,0x00FFFFFF], or
   * [0xFF000000] if this color can be choosen automatically. */
  void setColorRef(const quint32 colorVal);

  /** returns the red value in the range of [0x00,0xFF] or -1 if this ColorRef
   * is setToAutomatic */
  qint16 getRed() const;
  void setRed(const quint8 val);

  /** returns the green value in the range of [0x00,0xFF] or -1 if this ColorRef
   * is setToAutomatic */
  qint16 getGreen() const;
  void setGreen(const quint8 val);

  /** returns the blue value in the range of [0x00,0xFF] or -1 if this ColorRef
   * is setToAutomatic */
  qint16 getBlue() const;
  void setBlue(const quint8 val);

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};

} // namespace libmson

#endif // COLORREF_H
