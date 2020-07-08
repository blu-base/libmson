#include "DocumentSingleton.h"

namespace MSONcommon {

/* Null, because instance will be initialized on demand. */
DocumentSingleton *DocumentSingleton::instance = 0;

/* Null, because instance will be initialized on demand. */
MSONDocument *DocumentSingleton::doc = 0;

DocumentSingleton::DocumentSingleton() {}

DocumentSingleton *DocumentSingleton::getInstance() {
  if (instance == 0) {
    instance = new DocumentSingleton();
  }

  return instance;
}

MSONDocument *DocumentSingleton::getDoc() {
  if (doc == 0) {
    doc = new MSONDocument();
  }

  return doc;
}

void DocumentSingleton::setDoc(MSONDocument *value) { doc = value; }
} // namespace MSONcommon
