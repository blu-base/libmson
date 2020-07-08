#ifndef DOCUMENTSINGLETON_H
#define DOCUMENTSINGLETON_H

#include <QtCore/qglobal.h>

#include "MSONDocument.h"

namespace MSONcommon {

class DocumentSingleton {
private:
  /* Here will be the instance stored. */
  static DocumentSingleton *instance;

  static MSONDocument *doc;

  /* Private constructor to prevent instancing. */
  DocumentSingleton();

public:
  /* Static access method. */
  static DocumentSingleton *getInstance();

  DocumentSingleton(DocumentSingleton const &) = delete;
  void operator=(DocumentSingleton const &) = delete;

  static MSONDocument *getDoc();
  static void setDoc(MSONDocument *value);
};

} // namespace MSONcommon

#endif // DOCUMENTSINGLETON_H
