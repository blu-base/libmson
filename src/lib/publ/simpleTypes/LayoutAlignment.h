#ifndef LAYOUTALIGNMENT_H
#define LAYOUTALIGNMENT_H

#include <QtCore/qglobal.h>

#include <QDataStream>

#include "../../priv/IStreamable.h"

namespace libmson {

/** Prescribed horizontal alignments for the LayoutAlignment class, according to
 * [MS-ONE] section 2.3.2.
 *
 * \todo there seem to be cases where the undocumented values (val0, val6, and
 * val7) seem to occur. Deduct what they mean! */
enum class HAlignment : quint32 {
  val0                 = 0x00,
  left                 = 0x01,
  center               = 0x02,
  right                = 0x03,
  inReadDirection      = 0x04,
  reverseReadDirection = 0x05,
  val6                 = 0x06,
  val7                 = 0x07,
};

/** Prescribed vertical alignments for the LayoutAlignment class, according to
 * [MS-ONE] section 2.3.2. */
enum class VAlignment : quint32 {
  bottom = 0x00,
  top    = 0x01,
};


/** @class LayoutAlignment
 * @brief Alignment settings for content
 *
 * represents the simple type according to [MS-ONE] section 2.3.2
 */
class LayoutAlignment : public priv::IStreamable {
private:
  /** \todo replace composite member variable with separated variables*/
  quint32 m_value;

public:
  LayoutAlignment();

  /** Horizontal alignment within the parent node. Sets the lha bits. */
  HAlignment getHAlignment() const;

  /** Set horizontal alignemnt of content within the parent node. */
  void setAlignment(const HAlignment& val);

  /** Vertical alignment within the parent node. sets the lva bits.*/
  VAlignment getVAlignment() const;

  /** Set vertical alignment of content within the parent node. */
  void setAlignment(const VAlignment& val);

  /** returns whether the horizontal aligment is the same as the page's text
   * direction(true) or inverse to the page's text direction(false)
   */
  bool getFHorizMargin() const;

  /** specifies in which way content is horizontally aligned to the page margin,
   * depending on the read direction of the specified page direction.
   * true:the same as the page's direction,
   * false:inverse to the page's direction */
  void setFHorizMargin(const bool val);

  /** returns whether the content is top aligned(true) or bottom aligned(false)
  within the page margins */
  bool getFVertMargin() const;

  /** specifies in which way content is vertically aligned to the page margin,
   * true=top, false:bottom */
  void setFVertMargin(const bool val);

  /** returns whether this instance should be ignored(true) or not(false) */
  bool isNil() const;

  /** specifies whether this instance should be ignored(true) or not (false) */
  void setNil(const bool val);

  static QString hAlignmentToString(const HAlignment& val);
  static QString vAlignmentToString(const VAlignment& val);


private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;

  static constexpr const quint32 LayoutAlignment_maskLha          = 0x00000003;
  static constexpr const quint32 LayoutAlignment_maskFHorizMargin = 0x00000004;
  static constexpr const quint32 LayoutAlignment_maskLva          = 0x00010000;
  static constexpr const quint32 LayoutAlignment_maskFVertMargin  = 0x00080000;
  static constexpr const quint32 LayoutAlignment_maskLaNil        = 0x80000000;

  static constexpr const quint32 LayoutAlignment_shiftLha          = 0;
  static constexpr const quint32 LayoutAlignment_shiftLva          = 3;
  static constexpr const quint32 LayoutAlignment_shiftFHorizMargin = 16;
  static constexpr const quint32 LayoutAlignment_shiftFVertMargin  = 19;
  static constexpr const quint32 LayoutAlignment_shiftLaNil        = 31;
};

} // namespace libmson

#endif // LAYOUTALIGNMENT_H
