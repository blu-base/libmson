#include "ColorRef.h"


namespace libmson {

static const quint32 maskRed   = 0x00FF0000;
static const quint32 maskGreen = 0x0000FF00;
static const quint32 maskBlue  = 0x000000FF;

static const quint8 shiftRed       = 4;
static const quint8 shiftGreen     = 2;
static const quint8 shiftBlue      = 0;
static const quint8 shiftAutomatic = 6;

static const quint32 automaticValue = 0xFF000000;


ColorRef::ColorRef() : m_colorVal() {}

ColorRef::ColorRef(const quint32 colorVal) : m_colorVal(colorVal) {}

bool ColorRef::isSetToAutomatic() const
{
  return (m_colorVal >> shiftAutomatic) == 0xFF;
}

void ColorRef::setToAutomatic() { m_colorVal = automaticValue; }

quint32 ColorRef::getColorRef() const { return m_colorVal; }
void ColorRef::setColorRef(const quint32 colorVal) { m_colorVal = colorVal; }


qint16 ColorRef::getRed() const
{
  if (isSetToAutomatic()) {
    return -1;
  }

  return maskRed & m_colorVal;
}

void ColorRef::setRed(const quint8 val)
{
  // make sure colorref is not automatic anymore, and keep other colors
  m_colorVal &= ~(maskRed + automaticValue);
  m_colorVal += val << shiftRed;
}

qint16 ColorRef::getGreen() const
{
  if (isSetToAutomatic()) {
    return -1;
  }

  return maskGreen & m_colorVal;
}

void ColorRef::setGreen(const quint8 val)
{
  m_colorVal &= ~(maskGreen + automaticValue);
  m_colorVal += val << shiftGreen;
}

qint16 ColorRef::getBlue() const
{
  if (isSetToAutomatic()) {
    return -1;
  }

  return maskBlue & m_colorVal;
}

void ColorRef::setBlue(const quint8 val)
{
  m_colorVal &= ~(maskBlue + automaticValue);
  m_colorVal += val << shiftBlue;
}

void ColorRef::deserialize(QDataStream& ds)
{
  ds.setByteOrder(QDataStream::LittleEndian);
  ds >> m_colorVal;
}

void ColorRef::serialize(QDataStream& ds) const { ds << m_colorVal; }


} // namespace libmson
