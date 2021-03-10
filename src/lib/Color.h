#ifndef COLOR_H
#define COLOR_H

#include <QtCore/qglobal.h>
#include <memory>

namespace libmson {

class Color
{
public:
  Color();



  quint8 getRed();
  quint8 getGreen();
  quint8 getBlue();

  bool isAutomatic();
  bool isNone();


  /**
   * @brief formated as "#[a-fA-F0-9]{6}|none|automatic"
   * @return
   */
  QString toString();


private:
class Impl;

std::unique_ptr<Impl> p;

};

}

#endif // COLOR_H
