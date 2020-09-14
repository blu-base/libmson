#ifndef LAYOUTALIGNMENT_H
#define LAYOUTALIGNMENT_H

#include <QtCore/qglobal.h>

#include <QDataStream>
#include <QDebug>
#include <QXmlStreamWriter>

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {

static constexpr const quint32 LayoutAlignment_maskLha = 0x00000003;
static constexpr const quint32 LayoutAlignment_maskFHorizMargin = 0x00000004;
static constexpr const quint32 LayoutAlignment_maskLva = 0x00010000;
static constexpr const quint32 LayoutAlignment_maskFVertMargin = 0x00080000;
static constexpr const quint32 LayoutAlignment_maskLaNil = 0x80000000;

static constexpr const quint32 LayoutAlignment_shiftLha = 0;
static constexpr const quint32 LayoutAlignment_shiftLva = 3;
static constexpr const quint32 LayoutAlignment_shiftFHorizMargin = 16;
static constexpr const quint32 LayoutAlignment_shiftFVertMargin = 19;
static constexpr const quint32 LayoutAlignment_shiftLaNil = 31;

enum class HAlignment : quint32 {
  val0 = 0x00,
  left = 0x01,
  center = 0x02,
  right = 0x03,
  inReadDirection = 0x04,
  reverseReadDirection = 0x05,
  val6 = 0x06,
  val7 = 0x07,
};

enum class VAlignment : quint32 {
  bottom = 0x00,
  top = 0x01,
};

QString hAlignmentToString(const HAlignment &val);
QString vAlignmentToString(const VAlignment &val);

class LayoutAlignment : public IRevisionStoreFileObject {
private:
  quint32 m_value;

public:
  LayoutAlignment();

  HAlignment lha() const;
  void setLha(const HAlignment &val);

  VAlignment lva() const;
  void setLva(const VAlignment &val);

  bool fHorizMargin() const;
  void setFHorizMargin(const bool val);

  bool fVertMargin() const;
  void setFVertMargin(const bool val);

  bool laNil() const;
  void setLaNil(const bool val);

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // LAYOUTALIGNMENT_H