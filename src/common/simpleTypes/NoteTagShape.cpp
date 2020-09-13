#include "NoteTagShape.h"

namespace MSONcommon {

MSONcommon::NoteTagShape::NoteTagShape() : m_shape() {}

void NoteTagShape::setShapeID(const NoteTagShapeID shape) {
  m_shape = static_cast<quint16>(shape);
}

NoteTagShapeID NoteTagShape::getShapeID() const {
  return static_cast<NoteTagShapeID>(m_shape);
}

void NoteTagShape::setShapeIDValue(const quint16 shape) { m_shape = shape; }

quint16 NoteTagShape::getShapeIDValue() const { return m_shape; }

void NoteTagShape::deserialize(QDataStream &ds) { ds >> m_shape; }

void NoteTagShape::serialize(QDataStream &ds) const { ds << m_shape; }

void NoteTagShape::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("NoteTagShape");
  xmlWriter.writeCharacters(idToString(m_shape));
  xmlWriter.writeEndElement();
}

void NoteTagShape::toDebugString(QDebug &dbg) const {
  dbg << "NoteTagShape: " << idToString(m_shape) << '\n';
}

QString idToString(const quint16 shape) {
  return idToString(static_cast<NoteTagShapeID>(shape));
}

QString idToString(const NoteTagShapeID shape) {

  switch (static_cast<NoteTagShapeID>(shape)) {

  case MSONcommon::NoteTagShapeID::NoIcon:
    return "NoIcon";
  case MSONcommon::NoteTagShapeID::CheckBoxGreen:
    return "CheckBoxGreen";
  case MSONcommon::NoteTagShapeID::CheckBoxYellow:
    return "CheckBoxYellow";
  case MSONcommon::NoteTagShapeID::CheckBoxBlue:
    return "CheckBoxBlue";
  case MSONcommon::NoteTagShapeID::CheckBoxGreenStar:
    return "CheckBoxGreenStar";
  case MSONcommon::NoteTagShapeID::CheckBoxYellowStar:
    return "CheckBoxYellowStar";
  case MSONcommon::NoteTagShapeID::CheckBoxBlueStar:
    return "CheckBoxBlueStar";
  case MSONcommon::NoteTagShapeID::CheckBoxGreenExclamation:
    return "CheckBoxGreenExclamation";
  case MSONcommon::NoteTagShapeID::ChckBoxYellowExclamation:
    return "ChckBoxYellowExclamation";
  case MSONcommon::NoteTagShapeID::CheckBoxBlueExclamation:
    return "CheckBoxBlueExclamation";
  case MSONcommon::NoteTagShapeID::CheckBoxGreenArrow:
    return "CheckBoxGreenArrow";
  case MSONcommon::NoteTagShapeID::CheckBoxYellowArrow:
    return "CheckBoxYellowArrow";
  case MSONcommon::NoteTagShapeID::CheckBoxBlueArrow:
    return "CheckBoxBlueArrow";
  case MSONcommon::NoteTagShapeID::Favorit:
    return "Favorit";
  case MSONcommon::NoteTagShapeID::FlagBlueFollowUp:
    return "FlagBlueFollowUp";
  case MSONcommon::NoteTagShapeID::QuestionMark:
    return "QuestionMark";
  case MSONcommon::NoteTagShapeID::ArrowRightBlue:
    return "ArrowRightBlue";
  case MSONcommon::NoteTagShapeID::HighPriority:
    return "HighPriority";
  case MSONcommon::NoteTagShapeID::ContactInformation:
    return "ContactInformation";
  case MSONcommon::NoteTagShapeID::Meeting:
    return "Meeting";
  case MSONcommon::NoteTagShapeID::TimeSensitive:
    return "TimeSensitive";
  case MSONcommon::NoteTagShapeID::Idea:
    return "Idea";
  case MSONcommon::NoteTagShapeID::Pushpin:
    return "Pushpin";
  case MSONcommon::NoteTagShapeID::Home:
    return "Home";
  case MSONcommon::NoteTagShapeID::CommentBubble:
    return "CommentBubble";
  case MSONcommon::NoteTagShapeID::SmilingFace:
    return "SmilingFace";
  case MSONcommon::NoteTagShapeID::AwardRibbon:
    return "AwardRibbon";
  case MSONcommon::NoteTagShapeID::KeyYellow:
    return "KeyYellow";
  case MSONcommon::NoteTagShapeID::CheckBoxBlueNo1:
    return "CheckBoxBlueNo1";
  case MSONcommon::NoteTagShapeID::CircleBlueNo1:
    return "CircleBlueNo1";
  case MSONcommon::NoteTagShapeID::CheckBoxBlueNo2:
    return "CheckBoxBlueNo2";
  case MSONcommon::NoteTagShapeID::CicleBlueNo2:
    return "CicleBlueNo2";
  case MSONcommon::NoteTagShapeID::CheckBoxBlueNo3:
    return "CheckBoxBlueNo3";
  case MSONcommon::NoteTagShapeID::CircleBlueNo3:
    return "CircleBlueNo3";
  case MSONcommon::NoteTagShapeID::Star8PointBlue:
    return "Star8PointBlue";
  case MSONcommon::NoteTagShapeID::CheckMarkBlue:
    return "CheckMarkBlue";
  case MSONcommon::NoteTagShapeID::CircleBlue:
    return "CircleBlue";
  case MSONcommon::NoteTagShapeID::ArrowDownBlue:
    return "ArrowDownBlue";
  case MSONcommon::NoteTagShapeID::ArrowLeftBlue:
    return "ArrowLeftBlue";
  case MSONcommon::NoteTagShapeID::TargetBlueSolid:
    return "TargetBlueSolid";
  case MSONcommon::NoteTagShapeID::StarBlue:
    return "StarBlue";
  case MSONcommon::NoteTagShapeID::SunBlue:
    return "SunBlue";
  case MSONcommon::NoteTagShapeID::TargetBlue:
    return "TargetBlue";
  case MSONcommon::NoteTagShapeID::TriangleBlue:
    return "TriangleBlue";
  case MSONcommon::NoteTagShapeID::UmbrellaBlue:
    return "UmbrellaBlue";
  case MSONcommon::NoteTagShapeID::ArrowUpBlue:
    return "ArrowUpBlue";
  case MSONcommon::NoteTagShapeID::CrossBlueDotted:
    return "CrossBlueDotted";
  case MSONcommon::NoteTagShapeID::CrossBlue:
    return "CrossBlue";
  case MSONcommon::NoteTagShapeID::CheckBoxGreenNo1:
    return "CheckBoxGreenNo1";
  case MSONcommon::NoteTagShapeID::CicleGreenNo1:
    return "CicleGreenNo1";
  case MSONcommon::NoteTagShapeID::CheckBoxGreenNo2:
    return "CheckBoxGreenNo2";
  case MSONcommon::NoteTagShapeID::CircleGreenNo2:
    return "CircleGreenNo2";
  case MSONcommon::NoteTagShapeID::CheckBoxGreenNo3:
    return "CheckBoxGreenNo3";
  case MSONcommon::NoteTagShapeID::CircleGreenNo3:
    return "CircleGreenNo3";
  case MSONcommon::NoteTagShapeID::Star8PointGreen:
    return "Star8PointGreen";
  case MSONcommon::NoteTagShapeID::CheckMarkGreen:
    return "CheckMarkGreen";
  case MSONcommon::NoteTagShapeID::CircleGreen:
    return "CircleGreen";
  case MSONcommon::NoteTagShapeID::ArrowDownGreen:
    return "ArrowDownGreen";
  case MSONcommon::NoteTagShapeID::ArrowLeftGreen:
    return "ArrowLeftGreen";
  case MSONcommon::NoteTagShapeID::ArrowRightGreen:
    return "ArrowRightGreen";
  case MSONcommon::NoteTagShapeID::ArrowGreenSolid:
    return "ArrowGreenSolid";
  case MSONcommon::NoteTagShapeID::StarGreen:
    return "StarGreen";
  case MSONcommon::NoteTagShapeID::SunGreen:
    return "SunGreen";
  case MSONcommon::NoteTagShapeID::TargetGreen:
    return "TargetGreen";
  case MSONcommon::NoteTagShapeID::TriangleGreen:
    return "TriangleGreen";
  case MSONcommon::NoteTagShapeID::UmbrellaGreen:
    return "UmbrellaGreen";
  case MSONcommon::NoteTagShapeID::ArrowUpGreen:
    return "ArrowUpGreen";
  case MSONcommon::NoteTagShapeID::CrossGreenDotted:
    return "CrossGreenDotted";
  case MSONcommon::NoteTagShapeID::CrossGreen:
    return "CrossGreen";
  case MSONcommon::NoteTagShapeID::CheckBoxYellowNo1:
    return "CheckBoxYellowNo1";
  case MSONcommon::NoteTagShapeID::CircleYellowNo1:
    return "CircleYellowNo1";
  case MSONcommon::NoteTagShapeID::CheckBoxYellowNo2:
    return "CheckBoxYellowNo2";
  case MSONcommon::NoteTagShapeID::CircleYellowNo2:
    return "CircleYellowNo2";
  case MSONcommon::NoteTagShapeID::CheckBoxYellowNo3:
    return "CheckBoxYellowNo3";
  case MSONcommon::NoteTagShapeID::CircleYellowNo3:
    return "CircleYellowNo3";
  case MSONcommon::NoteTagShapeID::Star8PointYellow:
    return "Star8PointYellow";
  case MSONcommon::NoteTagShapeID::CheckMarkYellow:
    return "CheckMarkYellow";
  case MSONcommon::NoteTagShapeID::CircleYellow:
    return "CircleYellow";
  case MSONcommon::NoteTagShapeID::ArrowDownYellow:
    return "ArrowDownYellow";
  case MSONcommon::NoteTagShapeID::ArrowLeftYellow:
    return "ArrowLeftYellow";
  case MSONcommon::NoteTagShapeID::ArrowRightYellow:
    return "ArrowRightYellow";
  case MSONcommon::NoteTagShapeID::TargetYellowSolid:
    return "TargetYellowSolid";
  case MSONcommon::NoteTagShapeID::SunYellow:
    return "SunYellow";
  case MSONcommon::NoteTagShapeID::TargetYellow:
    return "TargetYellow";
  case MSONcommon::NoteTagShapeID::TriangleYellow:
    return "TriangleYellow";
  case MSONcommon::NoteTagShapeID::UmbrellaYellow:
    return "UmbrellaYellow";
  case MSONcommon::NoteTagShapeID::ArrowUpYellow:
    return "ArrowUpYellow";
  case MSONcommon::NoteTagShapeID::CrossYellowDotted:
    return "CrossYellowDotted";
  case MSONcommon::NoteTagShapeID::CrossYellow:
    return "CrossYellow";
  case MSONcommon::NoteTagShapeID::FollowUpFlagToday:
    return "FollowUpFlagToday";
  case MSONcommon::NoteTagShapeID::FollowUpFlagTomorrow:
    return "FollowUpFlagTomorrow";
  case MSONcommon::NoteTagShapeID::FollowUpFlagThisWeek:
    return "FollowUpFlagThisWeek";
  case MSONcommon::NoteTagShapeID::FollowUpFlagNextWeek:
    return "FollowUpFlagNextWeek";
  case MSONcommon::NoteTagShapeID::FollowUpFlagNoDate:
    return "FollowUpFlagNoDate";
  case MSONcommon::NoteTagShapeID::PersonCheckBoxBlue:
    return "PersonCheckBoxBlue";
  case MSONcommon::NoteTagShapeID::PersonCheckBoxYellow:
    return "PersonCheckBoxYellow";
  case MSONcommon::NoteTagShapeID::PersonCheckBoxGreen:
    return "PersonCheckBoxGreen";
  case MSONcommon::NoteTagShapeID::CheckBoxBlueFlag:
    return "CheckBoxBlueFlag";
  case MSONcommon::NoteTagShapeID::CheckBoxRedFlag:
    return "CheckBoxRedFlag";
  case MSONcommon::NoteTagShapeID::CheckBoxGreenFlag:
    return "CheckBoxGreenFlag";
  case MSONcommon::NoteTagShapeID::SquareRed:
    return "SquareRed";
  case MSONcommon::NoteTagShapeID::SquareYellow:
    return "SquareYellow";
  case MSONcommon::NoteTagShapeID::SquareBlue:
    return "SquareBlue";
  case MSONcommon::NoteTagShapeID::SquareGreen:
    return "SquareGreen";
  case MSONcommon::NoteTagShapeID::SquareOrange:
    return "SquareOrange";
  case MSONcommon::NoteTagShapeID::SquarePink:
    return "SquarePink";
  case MSONcommon::NoteTagShapeID::EmailMessage:
    return "EmailMessage";
  case MSONcommon::NoteTagShapeID::EnvelopeClosed:
    return "EnvelopeClosed";
  case MSONcommon::NoteTagShapeID::EnvelopeOpen:
    return "EnvelopeOpen";
  case MSONcommon::NoteTagShapeID::Mobilephone:
    return "Mobilephone";
  case MSONcommon::NoteTagShapeID::TelephoneWithClock:
    return "TelephoneWithClock";
  case MSONcommon::NoteTagShapeID::QuestionBalloon:
    return "QuestionBalloon";
  case MSONcommon::NoteTagShapeID::PaperClip:
    return "PaperClip";
  case MSONcommon::NoteTagShapeID::FrowningFace:
    return "FrowningFace";
  case MSONcommon::NoteTagShapeID::InstantMessaging:
    return "InstantMessaging";
  case MSONcommon::NoteTagShapeID::PersonWithExclamationMark:
    return "PersonWithExclamationMark";
  case MSONcommon::NoteTagShapeID::TwoPeople:
    return "TwoPeople";
  case MSONcommon::NoteTagShapeID::ReminderBell:
    return "ReminderBell";
  case MSONcommon::NoteTagShapeID::Contact:
    return "Contact";
  case MSONcommon::NoteTagShapeID::Rose:
    return "Rose";
  case MSONcommon::NoteTagShapeID::DateWithClock:
    return "DateWithClock";
  case MSONcommon::NoteTagShapeID::MusicalNote:
    return "MusicalNote";
  case MSONcommon::NoteTagShapeID::MovieClip:
    return "MovieClip";
  case MSONcommon::NoteTagShapeID::QuotationMark:
    return "QuotationMark";
  case MSONcommon::NoteTagShapeID::Globe:
    return "Globe";
  case MSONcommon::NoteTagShapeID::HyperlinkGlobe:
    return "HyperlinkGlobe";
  case MSONcommon::NoteTagShapeID::Laptop:
    return "Laptop";
  case MSONcommon::NoteTagShapeID::Plane:
    return "Plane";
  case MSONcommon::NoteTagShapeID::Car:
    return "Car";
  case MSONcommon::NoteTagShapeID::Binoculars:
    return "Binoculars";
  case MSONcommon::NoteTagShapeID::PresentationSlide:
    return "PresentationSlide";
  case MSONcommon::NoteTagShapeID::Padlock:
    return "Padlock";
  case MSONcommon::NoteTagShapeID::OpenBook:
    return "OpenBook";
  case MSONcommon::NoteTagShapeID::NotebookWithClock:
    return "NotebookWithClock";
  case MSONcommon::NoteTagShapeID::BlankPaperWithLines:
    return "BlankPaperWithLines";
  case MSONcommon::NoteTagShapeID::Research:
    return "Research";
  case MSONcommon::NoteTagShapeID::Pen:
    return "Pen";
  case MSONcommon::NoteTagShapeID::DollarSign:
    return "DollarSign";
  case MSONcommon::NoteTagShapeID::Coins:
    return "Coins";
  case MSONcommon::NoteTagShapeID::ScheduledTask:
    return "ScheduledTask";
  case MSONcommon::NoteTagShapeID::LightningBolt:
    return "LightningBolt";
  case MSONcommon::NoteTagShapeID::Cloud:
    return "Cloud";
  case MSONcommon::NoteTagShapeID::Heart:
    return "Heart";
  case MSONcommon::NoteTagShapeID::Sunflower:
    return "Sunflower";
  default:
    return "invalid";
  }


}


} // namespace MSONcommon
