#include "FormatIdentifier.h"

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>

namespace libmson {


class FormatIdentifier::Impl {
private:
  std::string m_fileName;

  bool m_isParsed = false;

  OnFormat m_format = OnFormat::Unrecoqnized;

  Supported m_support = Supported::Inapplicable;

  inline static const std::map<OnFormat, Supported> m_supportMap{
      {OnFormat::One03_revStore, Supported::No},
      {OnFormat::OneToc03_revStore, Supported::No},
      {OnFormat::One10_revStore, Supported::Yes},
      {OnFormat::OneToc10_revStore, Supported::Yes},
      {OnFormat::OnePkg, Supported::No},
      {OnFormat::One_packStore, Supported::No},
      {OnFormat::OneToc_packStore, Supported::No},
      {OnFormat::Unrecoqnized, Supported::Inapplicable}};

  // offset 0x00
  static constexpr const std::array<uint8_t, 16> revisionStoreFileType_One{
      0xe4, 0x52, 0x5c, 0x7b, 0x8c, 0xd8, 0xa7, 0x4d,
      0xae, 0xb1, 0x53, 0x78, 0xd0, 0x29, 0x96, 0xd3};
  static constexpr const std::array<uint8_t, 16> revisionStoreFileType_OneToc{
      0xa1, 0x2f, 0xff, 0x43, 0xd9, 0xef, 0x76, 0x4c,
      0x9e, 0xe2, 0x10, 0xea, 0x57, 0x22, 0x76, 0x5f};

  static constexpr const uint16_t revisionStoreFileFormat_offset = 0x30;
  static constexpr const std::array<uint8_t, 16> revisionStoreFileFormat{
      0x3f, 0xdd, 0x9a, 0x10, 0x1b, 0x91, 0xf5, 0x49,
      0xa5, 0xd0, 0x17, 0x91, 0xed, 0xc8, 0xae, 0xd8};
  static constexpr const std::array<uint8_t, 16> packageStoreFileFormat{
      0x2f, 0xe9, 0x8d, 0x63, 0xd4, 0xa6, 0xc1, 0x4b,
      0x9a, 0x36, 0xb3, 0xfc, 0x25, 0x11, 0xa5, 0xb7};


  static constexpr const uint16_t packageStoreFileFormat_offset_base = 0x44;
  static constexpr const std::array<uint8_t, 16> packageStoreFileType_One{
      0xb4, 0x7c, 0x93, 0x1f, 0x6f, 0xb2, 0x5f, 0x44,
      0xb9, 0xf8, 0x17, 0xe2, 0x01, 0x60, 0xe4, 0x61};
  static constexpr const std::array<uint8_t, 16> packageStoreFileType_OneToc{
      0x38, 0xfd, 0xdb, 0xe4, 0xc7, 0xe5, 0x8b, 0x40,
      0xa8, 0xa1, 0x0e, 0x7b, 0x42, 0x1e, 0x1f, 0x5f};


  static constexpr const uint16_t guidLegacyFileVersion_offset = 0x20;
  static constexpr const std::array<uint8_t, 16>
      guidLegacyFileVersion{}; // only zeros


  // only applies to revision store format
  static constexpr const uint16_t ffv_offset = 0x40;
  static constexpr const std::array<uint8_t, 4> ffv_legacy{
      0x09, 0x00, 0x00, 0x00};
  static constexpr const std::array<uint8_t, 4> ffv_one{0x2a, 0x00, 0x00, 0x00};
  static constexpr const std::array<uint8_t, 4> ffv_onetoc2{
      0x1b, 0x00, 0x00, 0x00};


  // cab signature "MSCF" at offset 0x00.
  static constexpr const std::array<uint8_t, 4> onepkg_signature_head{
      0x4D, 0x53, 0x43, 0x46};
  // cab version signature at offset 0x24,
  static constexpr const uint16_t onepkg_signature_version_offset = 0x24;
  static constexpr const std::array<uint8_t, 2> onepkg_signature_version{
      0x03, 0x01};


public:
  Impl() : m_fileName("") {}
  Impl(const std::string fileName) : m_fileName(fileName) { parseFile(); }

  ~Impl() = default;

  std::string getFileName() const { return m_fileName; }
  void setFileName(const std::string& fileName)
  {
    m_fileName = fileName;
    parseFile();
  }


  OnFormat getFormat()
  {
    // file has already been categorized
    if (m_isParsed == true) {
      return m_format;
    }

    parseFile();
    return m_format;
  }

  Supported getSupported()
  {
    // file has already been categorized
    if (m_isParsed == true) {
      return m_support;
    }

    parseFile();
    return m_support;
  }

  void setDefaults()
  {
    m_format   = OnFormat::Unrecoqnized;
    m_support  = m_supportMap.at(m_format);
    m_isParsed = false;
  }


  void parseFile()
  {
    // Check if fileName input can be inspected
    std::error_code ec{};
    bool isRegular = std::filesystem::is_regular_file(m_fileName, ec);

    if (!isRegular) {
      std::cout << "Error: " << m_fileName << " is not a regular file"
                << std::endl;
      setDefaults();
      return;
    }
    else if (ec == std::error_code{}) {
      std::cout << "Error: while accessing file. Message: " << ec.message()
                << std::endl;
      setDefaults();
      return;
    }

    // Cache File size
    const auto f_size = std::filesystem::file_size(m_fileName, ec);
    if (!(ec == std::error_code{})) {
      std::cout << "Error while accessing file " << m_fileName << '\n'
                << "size: " << f_size << "Message: " << ec.message()
                << std::endl;
      setDefaults();
      return;
    }


    std::ifstream fileStream(m_fileName, std::ios::binary);

    // cache file header
    std::array<char, 0x400> buff;
    fileStream.read(buff.data(), buff.size());


    bool isCabFormat =
        compareBuffWithRefArray(buff, onepkg_signature_head, 0) &&
        compareBuffWithRefArray(
            buff, onepkg_signature_version, onepkg_signature_version_offset);

    if (isCabFormat) {
      m_format   = OnFormat::OnePkg;
      m_support  = m_supportMap.at(m_format);
      m_isParsed = true;
      return;
    }

    bool hasRevisionStoreFormatGUID = compareBuffWithRefArray(
        buff, revisionStoreFileFormat, revisionStoreFileFormat_offset);
    bool hasPackageStoreFormatGUID = compareBuffWithRefArray(
        buff, packageStoreFileFormat, revisionStoreFileFormat_offset);
    bool hasRevisionStoreFileTypeOneGUID =
        compareBuffWithRefArray(buff, revisionStoreFileType_One, 0);

    // destinguish between revisionStore(if) and packageStore(else if)
    if (hasRevisionStoreFormatGUID) {


      bool hasRevisionStoreFileTypeOneTocGUID =
          compareBuffWithRefArray(buff, revisionStoreFileType_OneToc, 0);

      bool hasNonZeroLegacyFileVersionGUID = !compareBuffWithRefArray(
          buff, guidLegacyFileVersion, guidLegacyFileVersion_offset);

      bool ffv_isFfvOne = compareBuffWithRefArray(buff, ffv_one, ffv_offset);
      bool ffv_isFfvOneToc =
          compareBuffWithRefArray(buff, ffv_onetoc2, ffv_offset);
      bool ffv_isFfvLegacy =
          compareBuffWithRefArray(buff, ffv_legacy, ffv_offset);

      if (hasRevisionStoreFileTypeOneGUID) {
        if (hasNonZeroLegacyFileVersionGUID && ffv_isFfvLegacy) {
          m_format   = OnFormat::One03_revStore;
          m_support  = m_supportMap.at(m_format);
          m_isParsed = true;
          return;
        }
        else if (!hasNonZeroLegacyFileVersionGUID && ffv_isFfvOne) {
          m_format   = OnFormat::One10_revStore;
          m_support  = m_supportMap.at(m_format);
          m_isParsed = true;
          return;
        }
      }
      else if (hasRevisionStoreFileTypeOneTocGUID) {
        if (hasNonZeroLegacyFileVersionGUID && ffv_isFfvLegacy) {
          m_format   = OnFormat::OneToc03_revStore;
          m_support  = m_supportMap.at(m_format);
          m_isParsed = true;
          return;
        }
        else if (!hasNonZeroLegacyFileVersionGUID && ffv_isFfvOneToc) {
          m_format   = OnFormat::OneToc10_revStore;
          m_support  = m_supportMap.at(m_format);
          m_isParsed = true;
          return;
        }
      }
    }
    else if (hasPackageStoreFormatGUID && hasRevisionStoreFileTypeOneGUID) {

      // determine width of variable ExtendedGUID in packageStoreFile
      uint16_t packageStoreFileFormat_offset =
          packageStoreFileFormat_offset_base;

      uint8_t varWidthByte =
          static_cast<uint8_t>(buff.at(packageStoreFileFormat_offset_base));

      if (varWidthByte == 0) {
        packageStoreFileFormat_offset += 1;
      }
      else if (varWidthByte >= 4u) {
        packageStoreFileFormat_offset += 17;
      }
      else if (varWidthByte >= 32u) {
        packageStoreFileFormat_offset += 18;
      }
      else if (varWidthByte >= 64u) {
        packageStoreFileFormat_offset += 19;
      }
      else if (varWidthByte == 128u) {
        packageStoreFileFormat_offset += 21;
      }

      bool hasPackageStoreFileTypeOneGUID = compareBuffWithRefArray(
          buff, packageStoreFileType_One, packageStoreFileFormat_offset);
      bool hasPackageStoreFileTypeOneTocGUID = compareBuffWithRefArray(
          buff, packageStoreFileType_OneToc, packageStoreFileFormat_offset);


      if (hasPackageStoreFileTypeOneGUID) {
        m_format   = OnFormat::One_packStore;
        m_support  = m_supportMap.at(m_format);
        m_isParsed = true;
        return;
      }
      else if (hasPackageStoreFileTypeOneTocGUID) {
        m_format   = OnFormat::OneToc_packStore;
        m_support  = m_supportMap.at(m_format);
        m_isParsed = true;
        return;
      }
    }

    // invalid content
    setDefaults();
    m_isParsed = true;
  };
private:

  template <size_t N>
  bool compareBuffWithRefArray(
      std::array<char, 0x400>& buff, std::array<uint8_t, N> ref,
      uint16_t offset)
  {

    typedef typename std::array<uint8_t, N>::iterator RefArrayIterator;

    auto buffItBegin = buff.begin();
    auto refItBegin  = ref.begin();
    auto buffItEnd   = buff.end();
    auto refItEnd    = ref.end();
    std::array<char, 0x400>::iterator buffIt;
    RefArrayIterator refIt;

    // initial conditions
    std::advance(buffItBegin, offset);
    bool isEqual = true;

    for (buffIt = buffItBegin, refIt = refItBegin;
         (refIt != refItEnd) && (buffIt != buffItEnd); ++buffIt, ++refIt) {
      isEqual = isEqual && (static_cast<uint8_t>(*buffIt) == *refIt);
    }

    return isEqual;
  }

};


FormatIdentifier::FormatIdentifier()
    : p{std::make_unique<FormatIdentifier::Impl>()}
{
}
FormatIdentifier::FormatIdentifier(const std::string& fileName)
    : p{std::make_unique<FormatIdentifier::Impl>(fileName)}
{
}

OnFormat FormatIdentifier::getFormat() { return p->getFormat(); }

Supported FormatIdentifier::getSupported() { return p->getSupported(); }

bool FormatIdentifier::isSupported()
{
  return p->getSupported() == Supported::Yes;
}

std::string FormatIdentifier::getFileName() { return p->getFileName(); }

void FormatIdentifier::setFileName(const std::string& fileName)
{
  p->setFileName(fileName);
}

void FormatIdentifier::reparse() { p->parseFile(); }

} // namespace libmson
