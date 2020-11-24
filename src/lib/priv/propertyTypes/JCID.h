#ifndef JCID_H
#define JCID_H

#include <QtCore/qglobal.h>

#include "../IStreamable.h"

namespace libmson {
namespace priv {

enum class JCIDs : quint32 {
  jcidReadOnlyPersistablePropertyContainerForAuthor = 0x00120001,
  jcidPersistablePropertyContainerForTOC            = 0x00020001,
  jcidPersistablePropertyContainerForTOCSection     = 0x00020001,
  jcidSectionNode                                   = 0x00060007,
  jcidPageSeriesNode                                = 0x00060008,
  jcidPageNode                                      = 0x0006000B,
  jcidOutlineNode                                   = 0x0006000C,
  jcidOutlineElementNode                            = 0x0006000D,
  jcidRichTextOENode                                = 0x0006000E,
  jcidImageNode                                     = 0x00060011,
  jcidNumberListNode                                = 0x00060012,
  jcidOutlineGroup                                  = 0x00060019,
  jcidTableNode                                     = 0x00060022,
  jcidTableRowNode                                  = 0x00060023,
  jcidTableCellNode                                 = 0x00060024,
  jcidTitleNode                                     = 0x0006002C,
  jcidPageMetaData                                  = 0x00020030,
  jcidSectionMetaData                               = 0x00020031,
  jcidEmbeddedFileNode                              = 0x00060035,
  jcidPageManifestNode                              = 0x00060037,
  jcidConflictPageMetaData                          = 0x00020038,
  jcidVersionHistoryContent                         = 0x0006003C,
  jcidVersionProxy                                  = 0x0006003D,
  jcidNoteTagSharedDefinitionContainer              = 0x00120043,
  jcidRevisionMetaData                              = 0x00020044,
  jcidVersionHistoryMetaData                        = 0x00020046,
  jcidParagraphStyleObject                          = 0x0012004D,
  jcidParagraphStyleObjectForText                   = 0x0012004D,
  none                                              = 0x00000000,

  /** \brief Node contains single Stroke in native format
   *
   * it contains these Properties:
   * - undoc_StrokesBlob
   * - undoc_StrokesIndex
   * - unodc_StrokeLanguage
   * - unodc_StrokeLanguage
   * - undoc_StrokesGUID
   * - undoc_StrokesCreationTime
   * - 0x20003409 - ObjectID pointing to undoc_jciddrawingToolData (sometimes
   * CompactID's n seems to point nowhere)
   *
   * Maybe correlates with InkStroke
   */
  undoc_jcidDrawingNode = 0x00020047,

  /** \brief Node defining the tool properties used for undoc_jcidDrawingNode
   *
   * contains these Properties:
   * - undoc_Undetermined64byteBlock(0x1c00340a) - content does not to seem to
   * change for same computer, input device
   * - undoc_StrokesToolSizeHeight
   * - undoc_StrokesToolSizeWidth
   * - undoc_StrokesColor (optionally)
   * - 0x88003411, Bool, optionally, only present when highlighter (square tool)
   * is used
   * - 0x0c003412, OneByteOfData, optionally, only present when highlighter
   * (square tool) is used
   * - 0x0c003414, OneByteOfData, optionally, only present when highlighter
   * (square tool) is used
   * - 0x0c003413, OneByteOfData, optionally, only present when highlighter
   * (square tool) is used
   */
  undoc_jciddrawingToolData = 0x00120048,

  /** \brief Connects Handwritting matches with undoc_jcidDrawingNode
   *
   * if undoc_StrokesRecognitionContainer (0x24003416) Property points to this
   * node, it contains the properties:
   * - 0x1c003418 - unknown 16 bytes
   * - 0x24003416 - group of Strokes (undoc_jcidDrawingNode)
   * - unodc_StrokeLanguage
   * - 0x8800341f - unknown bool
   * - undoc_StrokesRecognizedText
   *
   * if undoc_StrokesContainer (0x20003415) Property points to this node, it
   * only contains:
   * - 0x24003416 - points to group of Strokes (undoc_jcidDrawingNode)
   * undoc_StrokesRecognizedText have been found
   *
   * Maybe correlates with OneNote.Interfaces.InkWordLoadOptions from onenoteapi
   */
  undoc_jcidDrawingGroupNode = 0x0002003b,

  /** \brief general container for shapes and drawings
   *
   * contains these Properties:
   * - LastModifiedTime
   * - OffsetFromParentHoriz
   * - OffsetFromParentVert
   * - undoc_StrokesContainer
   * - 0x14001d4e - FourBytesOfData, seem to have the same value as 0x140035a4,
   * observed values:
   * 01000000,02000000,03000000,04000000,05000000,06000000,0c000000,0e000000,10000000,18000000
   * - 0x140035a4 - FourBytesOfData, seem to have the same value as 0x14001d4e
   * - 0x1400349e - FourBytesOfData
   * - 0x1400349f - FourBytesOfData
   * - 0x140034a0 - FourBytesOfData
   * - 0x140034a1 - FourBytesOfData
   * - 0x140034a2 - FourBytesOfData
   * - 0x140034a3 - FourBytesOfData
   * - 0x140034a4 - FourBytesOfData
   * - 0x140034a5 - FourBytesOfData
   * - 0x1c001daa - likely contains a predefined vector shape
   * - 0x0c001d4f - OneByteOfData, observed values: 0b, 0c
   */
  undoc_jcidShape = 0x00060014,

};


class JCID : public IStreamable {
private:
  quint32 m_value;

public:
  JCID();

  quint16 index() const;
  void setIndex(const quint16& index);

  bool IsBinary() const;
  void setIsBinary(bool IsBinary);

  bool IsPropertySet() const;
  void setIsPropertySet(bool IsPropertySet);

  bool IsGraphNode() const;
  void setIsGraphNode(bool IsGraphNode);

  bool IsFileData() const;
  void setIsFileData(bool IsFileData);

  bool IsReadOnly() const;
  void setIsReadOnly(bool IsReadOnly);

  JCIDs type() const;
  QString typeToString() const;

  static quint64 getSizeInFile();

private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;


  static constexpr const quint32 JCID_relmaskValue         = 0xFFFF;
  static constexpr const quint32 JCID_relmaskIsBinary      = 0x1;
  static constexpr const quint32 JCID_relmaskIsPropertySet = 0x1;
  static constexpr const quint32 JCID_relmaskIsGraphNode   = 0x1;
  static constexpr const quint32 JCID_relmaskIsFileData    = 0x1;
  static constexpr const quint32 JCID_relmaskIsReadOnly    = 0x1;

  static constexpr const quint32 JCID_shiftValue         = 0;
  static constexpr const quint32 JCID_shiftIsBinary      = 16;
  static constexpr const quint32 JCID_shiftIsPropertySet = 17;
  static constexpr const quint32 JCID_shiftIsGraphNode   = 18;
  static constexpr const quint32 JCID_shiftIsFileData    = 19;
  static constexpr const quint32 JCID_shiftIsReadOnly    = 20;

  static constexpr const quint32 JCID_imaskValue         = 0x001F0000;
  static constexpr const quint32 JCID_imaskIsBinary      = 0x001EFFFF;
  static constexpr const quint32 JCID_imaskIsPropertySet = 0x001DFFFF;
  static constexpr const quint32 JCID_imaskIsGraphNode   = 0x001BFFFF;
  static constexpr const quint32 JCID_imaskIsFileData    = 0x0017FFFF;
  static constexpr const quint32 JCID_imaskIsReadOnly    = 0x000FFFFF;

  static const quint64 sizeInFile = 4;
};

} // namespace priv
} // namespace libmson

#endif // JCID_H
