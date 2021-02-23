#ifndef FORMATIDENTIFIER_H
#define FORMATIDENTIFIER_H

#include <memory>
#include <string>

namespace libmson {


/** lists ON file formats */
enum class OnFormat {
  /** Undocumented, and currently unsupported*/
  One03_revStore,
  OneToc03_revStore,

  //  One07_revStore,
  //  OneToc07_revStore,

  /** conventional MS-ONESTORE revision store file format (2010)*/
  One10_revStore,
  /** conventional MS-ONESTORE revision store toc file format (2010)*/
  OneToc10_revStore,

  /** compressed (CAB) directory which should contain MS-ONESTORE files */
  OnePkg,

  /** SOAP packaged MS-ONESTORE file format */
  One_packStore,
  /** SOAP packaged MS-ONESTORE toc file format */
  OneToc_packStore,

  /** files not relevant or unrecoqnized by this library*/
  Unrecoqnized,
};

/** Switch for current support of this library*/
enum class Supported { Yes, No, Inapplicable };

class FormatIdentifier {
public:
  FormatIdentifier();
  FormatIdentifier(std::string fileName);

  ~FormatIdentifier();

  // movable:
  FormatIdentifier(FormatIdentifier&& rhs) = delete ;
  FormatIdentifier& operator=(FormatIdentifier&& rhs) = delete ;

  // and copyable
  FormatIdentifier(const FormatIdentifier& rhs) = delete ;
  FormatIdentifier& operator=(const FormatIdentifier& rhs) = delete ;


  /** returns recoqnized Format*/
  OnFormat getFormat();

  /** returns whether the file with fileName is supported*/
  Supported getSupported();
  /** returns true if file is supported; returns false if unsupported or if
   * inapplicable file format*/
  bool isSupported();


  /** identifies given file again */
  void reparse();


  std::string getFileName();

  /** sets the file to be identified and caches the result, so that not every
   * subsequent call of getFormat, and getSupported will parse the file again.
   * Use reparse() if you expect the file to be changed after the initializing
   * of the FormatIdentifer or after using setFileName.*/
  void setFileName(std::string fileName);

private:
  class Impl;

  std::unique_ptr<Impl> p;
};

} // namespace libmson

#endif // FORMATIDENTIFIER_H
