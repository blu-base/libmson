#ifndef NOTETAGSHAPE_H
#define NOTETAGSHAPE_H

#include <QtCore/qglobal.h>

#include "../IRevisionStoreFileObject.h"

namespace MSONcommon {

enum class NoteTagShapeID : quint16 {
  NoIcon = 0x0,
  CheckBoxGreen = 0x1,
  CheckBoxYellow = 0x2,
  CheckBoxBlue = 0x3,
  CheckBoxGreenStar = 0x4,
  CheckBoxYellowStar = 0x5,
  CheckBoxBlueStar = 0x6,
  CheckBoxGreenExclamation = 0x7,
  ChckBoxYellowExclamation = 0x8,
  CheckBoxBlueExclamation = 0x9,
  CheckBoxGreenArrow = 0x10,
  CheckBoxYellowArrow = 0x11,
  CheckBoxBlueArrow = 0x12,
  Favorit = 0x13,
  FlagBlueFollowUp = 0x14,
  QuestionMark = 0x15,
  ArrowRightBlue = 0x16,
  HighPriority = 0x17,
  ContactInformation = 0x18,
  Meeting = 0x19,
  TimeSensitive = 0x20,
  Idea = 0x21,
  Pushpin = 0x22,
  Home = 0x23,
  CommentBubble = 0x24,
  SmilingFace = 0x25,
  AwardRibbon = 0x26,
  KeyYellow = 0x27,
  CheckBoxBlueNo1 = 0x28,
  CircleBlueNo1 = 0x29,
  CheckBoxBlueNo2 = 0x30,
  CicleBlueNo2 = 0x31,
  CheckBoxBlueNo3 = 0x32,
  CircleBlueNo3 = 0x33,
  Star8PointBlue = 0x34,
  CheckMarkBlue = 0x35,
  CircleBlue = 0x36,
  ArrowDownBlue = 0x37,
  ArrowLeftBlue = 0x38,
  TargetBlueSolid = 0x39,
  StarBlue = 0x40,
  SunBlue = 0x41,
  TargetBlue = 0x42,
  TriangleBlue = 0x43,
  UmbrellaBlue = 0x44,
  ArrowUpBlue = 0x45,
  CrossBlueDotted = 0x46,
  CrossBlue = 0x47,
  CheckBoxGreenNo1 = 0x48,
  CicleGreenNo1 = 0x49,
  CheckBoxGreenNo2 = 0x50,
  CircleGreenNo2 = 0x51,
  CheckBoxGreenNo3 = 0x52,
  CircleGreenNo3 = 0x53,
  Star8PointGreen = 0x54,
  CheckMarkGreen = 0x55,
  CircleGreen = 0x56,
  ArrowDownGreen = 0x57,
  ArrowLeftGreen = 0x58,
  ArrowRightGreen = 0x59,
  ArrowGreenSolid = 0x60,
  StarGreen = 0x61,
  SunGreen = 0x62,
  TargetGreen = 0x63,
  TriangleGreen = 0x64,
  UmbrellaGreen = 0x65,
  ArrowUpGreen = 0x66,
  CrossGreenDotted = 0x67,
  CrossGreen = 0x68,
  CheckBoxYellowNo1 = 0x69,
  CircleYellowNo1 = 0x70,
  CheckBoxYellowNo2 = 0x71,
  CircleYellowNo2 = 0x72,
  CheckBoxYellowNo3 = 0x73,
  CircleYellowNo3 = 0x74,
  Star8PointYellow = 0x75,
  CheckMarkYellow = 0x76,
  CircleYellow = 0x77,
  ArrowDownYellow = 0x78,
  ArrowLeftYellow = 0x79,
  ArrowRightYellow = 0x80,
  TargetYellowSolid = 0x81,
  SunYellow = 0x82,
  TargetYellow = 0x83,
  TriangleYellow = 0x84,
  UmbrellaYellow = 0x85,
  ArrowUpYellow = 0x86,
  CrossYellowDotted = 0x87,
  CrossYellow = 0x88,
  FollowUpFlagToday = 0x89,
  FollowUpFlagTomorrow = 0x90,
  FollowUpFlagThisWeek = 0x91,
  FollowUpFlagNextWeek = 0x92,
  FollowUpFlagNoDate = 0x93,
  PersonCheckBoxBlue = 0x94,
  PersonCheckBoxYellow = 0x95,
  PersonCheckBoxGreen = 0x96,
  CheckBoxBlueFlag = 0x97,
  CheckBoxRedFlag = 0x98,
  CheckBoxGreenFlag = 0x99,
  SquareRed = 0x100,
  SquareYellow = 0x101,
  SquareBlue = 0x102,
  SquareGreen = 0x103,
  SquareOrange = 0x104,
  SquarePink = 0x105,
  EmailMessage = 0x106,
  EnvelopeClosed = 0x107,
  EnvelopeOpen = 0x108,
  Mobilephone = 0x109,
  TelephoneWithClock = 0x110,
  QuestionBalloon = 0x111,
  PaperClip = 0x112,
  FrowningFace = 0x113,
  InstantMessaging = 0x114,
  PersonWithExclamationMark = 0x115,
  TwoPeople = 0x116,
  ReminderBell = 0x117,
  Contact = 0x118,
  Rose = 0x119,
  DateWithClock = 0x120,
  MusicalNote = 0x121,
  MovieClip = 0x122,
  QuotationMark = 0x123,
  Globe = 0x124,
  HyperlinkGlobe = 0x125,
  Laptop = 0x126,
  Plane = 0x127,
  Car = 0x128,
  Binoculars = 0x129,
  PresentationSlide = 0x130,
  Padlock = 0x131,
  OpenBook = 0x132,
  NotebookWithClock = 0x133,
  BlankPaperWithLines = 0x134,
  Research = 0x135,
  Pen = 0x136,
  DollarSign = 0x137,
  Coins = 0x138,
  ScheduledTask = 0x139,
  LightningBolt = 0x140,
  Cloud = 0x141,
  Heart = 0x142,
  Sunflower = 0x143,
};

static QString idToString(const NoteTagShapeID shape);
static QString idToString(const quint16 shape);

class NoteTagShape : public IRevisionStoreFileObject {
private:
  quint16 m_shape;

public:
  NoteTagShape();
  virtual ~NoteTagShape() = default;

  void setShapeID(const NoteTagShapeID shape);
  NoteTagShapeID getShapeID() const;

  void setShapeIDValue(const quint16 shape);
  quint16 getShapeIDValue() const;

private:
  virtual void deserialize(QDataStream &ds) override;
  virtual void serialize(QDataStream &ds) const override;

  virtual void writeLowLevelXml(QXmlStreamWriter &xmlWriter) const override;

  virtual void toDebugString(QDebug &dbg) const override;
};

} // namespace MSONcommon

#endif // NOTETAGSHAPE_H
