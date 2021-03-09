#include "NoteTagShape.h"

namespace libmson {

NoteTagShape::NoteTagShape() : m_shape() {}

void NoteTagShape::setShapeID(const NoteTagShapeID& shape)
{
  m_shape = static_cast<quint16>(shape);
}

NoteTagShapeID NoteTagShape::getShapeID() const
{
  return static_cast<NoteTagShapeID>(m_shape);
}

void NoteTagShape::setShapeIDValue(const quint16 shape) { m_shape = shape; }

quint16 NoteTagShape::getShapeIDValue() const { return m_shape; }

void NoteTagShape::deserialize(QDataStream& ds) { ds >> m_shape; }

void NoteTagShape::serialize(QDataStream& ds) const { ds << m_shape; }

// void NoteTagShape::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
// xmlWriter.writeStartElement("NoteTagShape");
// xmlWriter.writeCharacters(idToString(m_shape));
// xmlWriter.writeEndElement();
// }

QString NoteTagShape::idToString(const quint16 shape)
{
  return idToString(static_cast<NoteTagShapeID>(shape));
}

QString NoteTagShape::idToString(const NoteTagShapeID& shape)
{

  switch (static_cast<NoteTagShapeID>(shape)) {

  case NoteTagShapeID::NoIcon:
    return "NoIcon";
  case NoteTagShapeID::CheckBoxGreen:
    return "CheckBoxGreen";
  case NoteTagShapeID::CheckBoxYellow:
    return "CheckBoxYellow";
  case NoteTagShapeID::CheckBoxBlue:
    return "CheckBoxBlue";
  case NoteTagShapeID::CheckBoxGreenStar:
    return "CheckBoxGreenStar";
  case NoteTagShapeID::CheckBoxYellowStar:
    return "CheckBoxYellowStar";
  case NoteTagShapeID::CheckBoxBlueStar:
    return "CheckBoxBlueStar";
  case NoteTagShapeID::CheckBoxGreenExclamation:
    return "CheckBoxGreenExclamation";
  case NoteTagShapeID::ChckBoxYellowExclamation:
    return "ChckBoxYellowExclamation";
  case NoteTagShapeID::CheckBoxBlueExclamation:
    return "CheckBoxBlueExclamation";
  case NoteTagShapeID::CheckBoxGreenArrow:
    return "CheckBoxGreenArrow";
  case NoteTagShapeID::CheckBoxYellowArrow:
    return "CheckBoxYellowArrow";
  case NoteTagShapeID::CheckBoxBlueArrow:
    return "CheckBoxBlueArrow";
  case NoteTagShapeID::Favorit:
    return "Favorit";
  case NoteTagShapeID::FlagBlueFollowUp:
    return "FlagBlueFollowUp";
  case NoteTagShapeID::QuestionMark:
    return "QuestionMark";
  case NoteTagShapeID::ArrowRightBlue:
    return "ArrowRightBlue";
  case NoteTagShapeID::HighPriority:
    return "HighPriority";
  case NoteTagShapeID::ContactInformation:
    return "ContactInformation";
  case NoteTagShapeID::Meeting:
    return "Meeting";
  case NoteTagShapeID::TimeSensitive:
    return "TimeSensitive";
  case NoteTagShapeID::Idea:
    return "Idea";
  case NoteTagShapeID::Pushpin:
    return "Pushpin";
  case NoteTagShapeID::Home:
    return "Home";
  case NoteTagShapeID::CommentBubble:
    return "CommentBubble";
  case NoteTagShapeID::SmilingFace:
    return "SmilingFace";
  case NoteTagShapeID::AwardRibbon:
    return "AwardRibbon";
  case NoteTagShapeID::KeyYellow:
    return "KeyYellow";
  case NoteTagShapeID::CheckBoxBlueNo1:
    return "CheckBoxBlueNo1";
  case NoteTagShapeID::CircleBlueNo1:
    return "CircleBlueNo1";
  case NoteTagShapeID::CheckBoxBlueNo2:
    return "CheckBoxBlueNo2";
  case NoteTagShapeID::CicleBlueNo2:
    return "CicleBlueNo2";
  case NoteTagShapeID::CheckBoxBlueNo3:
    return "CheckBoxBlueNo3";
  case NoteTagShapeID::CircleBlueNo3:
    return "CircleBlueNo3";
  case NoteTagShapeID::Star8PointBlue:
    return "Star8PointBlue";
  case NoteTagShapeID::CheckMarkBlue:
    return "CheckMarkBlue";
  case NoteTagShapeID::CircleBlue:
    return "CircleBlue";
  case NoteTagShapeID::ArrowDownBlue:
    return "ArrowDownBlue";
  case NoteTagShapeID::ArrowLeftBlue:
    return "ArrowLeftBlue";
  case NoteTagShapeID::TargetBlueSolid:
    return "TargetBlueSolid";
  case NoteTagShapeID::StarBlue:
    return "StarBlue";
  case NoteTagShapeID::SunBlue:
    return "SunBlue";
  case NoteTagShapeID::TargetBlue:
    return "TargetBlue";
  case NoteTagShapeID::TriangleBlue:
    return "TriangleBlue";
  case NoteTagShapeID::UmbrellaBlue:
    return "UmbrellaBlue";
  case NoteTagShapeID::ArrowUpBlue:
    return "ArrowUpBlue";
  case NoteTagShapeID::CrossBlueDotted:
    return "CrossBlueDotted";
  case NoteTagShapeID::CrossBlue:
    return "CrossBlue";
  case NoteTagShapeID::CheckBoxGreenNo1:
    return "CheckBoxGreenNo1";
  case NoteTagShapeID::CicleGreenNo1:
    return "CicleGreenNo1";
  case NoteTagShapeID::CheckBoxGreenNo2:
    return "CheckBoxGreenNo2";
  case NoteTagShapeID::CircleGreenNo2:
    return "CircleGreenNo2";
  case NoteTagShapeID::CheckBoxGreenNo3:
    return "CheckBoxGreenNo3";
  case NoteTagShapeID::CircleGreenNo3:
    return "CircleGreenNo3";
  case NoteTagShapeID::Star8PointGreen:
    return "Star8PointGreen";
  case NoteTagShapeID::CheckMarkGreen:
    return "CheckMarkGreen";
  case NoteTagShapeID::CircleGreen:
    return "CircleGreen";
  case NoteTagShapeID::ArrowDownGreen:
    return "ArrowDownGreen";
  case NoteTagShapeID::ArrowLeftGreen:
    return "ArrowLeftGreen";
  case NoteTagShapeID::ArrowRightGreen:
    return "ArrowRightGreen";
  case NoteTagShapeID::ArrowGreenSolid:
    return "ArrowGreenSolid";
  case NoteTagShapeID::StarGreen:
    return "StarGreen";
  case NoteTagShapeID::SunGreen:
    return "SunGreen";
  case NoteTagShapeID::TargetGreen:
    return "TargetGreen";
  case NoteTagShapeID::TriangleGreen:
    return "TriangleGreen";
  case NoteTagShapeID::UmbrellaGreen:
    return "UmbrellaGreen";
  case NoteTagShapeID::ArrowUpGreen:
    return "ArrowUpGreen";
  case NoteTagShapeID::CrossGreenDotted:
    return "CrossGreenDotted";
  case NoteTagShapeID::CrossGreen:
    return "CrossGreen";
  case NoteTagShapeID::CheckBoxYellowNo1:
    return "CheckBoxYellowNo1";
  case NoteTagShapeID::CircleYellowNo1:
    return "CircleYellowNo1";
  case NoteTagShapeID::CheckBoxYellowNo2:
    return "CheckBoxYellowNo2";
  case NoteTagShapeID::CircleYellowNo2:
    return "CircleYellowNo2";
  case NoteTagShapeID::CheckBoxYellowNo3:
    return "CheckBoxYellowNo3";
  case NoteTagShapeID::CircleYellowNo3:
    return "CircleYellowNo3";
  case NoteTagShapeID::Star8PointYellow:
    return "Star8PointYellow";
  case NoteTagShapeID::CheckMarkYellow:
    return "CheckMarkYellow";
  case NoteTagShapeID::CircleYellow:
    return "CircleYellow";
  case NoteTagShapeID::ArrowDownYellow:
    return "ArrowDownYellow";
  case NoteTagShapeID::ArrowLeftYellow:
    return "ArrowLeftYellow";
  case NoteTagShapeID::ArrowRightYellow:
    return "ArrowRightYellow";
  case NoteTagShapeID::TargetYellowSolid:
    return "TargetYellowSolid";
  case NoteTagShapeID::SunYellow:
    return "SunYellow";
  case NoteTagShapeID::TargetYellow:
    return "TargetYellow";
  case NoteTagShapeID::TriangleYellow:
    return "TriangleYellow";
  case NoteTagShapeID::UmbrellaYellow:
    return "UmbrellaYellow";
  case NoteTagShapeID::ArrowUpYellow:
    return "ArrowUpYellow";
  case NoteTagShapeID::CrossYellowDotted:
    return "CrossYellowDotted";
  case NoteTagShapeID::CrossYellow:
    return "CrossYellow";
  case NoteTagShapeID::FollowUpFlagToday:
    return "FollowUpFlagToday";
  case NoteTagShapeID::FollowUpFlagTomorrow:
    return "FollowUpFlagTomorrow";
  case NoteTagShapeID::FollowUpFlagThisWeek:
    return "FollowUpFlagThisWeek";
  case NoteTagShapeID::FollowUpFlagNextWeek:
    return "FollowUpFlagNextWeek";
  case NoteTagShapeID::FollowUpFlagNoDate:
    return "FollowUpFlagNoDate";
  case NoteTagShapeID::PersonCheckBoxBlue:
    return "PersonCheckBoxBlue";
  case NoteTagShapeID::PersonCheckBoxYellow:
    return "PersonCheckBoxYellow";
  case NoteTagShapeID::PersonCheckBoxGreen:
    return "PersonCheckBoxGreen";
  case NoteTagShapeID::CheckBoxBlueFlag:
    return "CheckBoxBlueFlag";
  case NoteTagShapeID::CheckBoxRedFlag:
    return "CheckBoxRedFlag";
  case NoteTagShapeID::CheckBoxGreenFlag:
    return "CheckBoxGreenFlag";
  case NoteTagShapeID::SquareRed:
    return "SquareRed";
  case NoteTagShapeID::SquareYellow:
    return "SquareYellow";
  case NoteTagShapeID::SquareBlue:
    return "SquareBlue";
  case NoteTagShapeID::SquareGreen:
    return "SquareGreen";
  case NoteTagShapeID::SquareOrange:
    return "SquareOrange";
  case NoteTagShapeID::SquarePink:
    return "SquarePink";
  case NoteTagShapeID::EmailMessage:
    return "EmailMessage";
  case NoteTagShapeID::EnvelopeClosed:
    return "EnvelopeClosed";
  case NoteTagShapeID::EnvelopeOpen:
    return "EnvelopeOpen";
  case NoteTagShapeID::Mobilephone:
    return "Mobilephone";
  case NoteTagShapeID::TelephoneWithClock:
    return "TelephoneWithClock";
  case NoteTagShapeID::QuestionBalloon:
    return "QuestionBalloon";
  case NoteTagShapeID::PaperClip:
    return "PaperClip";
  case NoteTagShapeID::FrowningFace:
    return "FrowningFace";
  case NoteTagShapeID::InstantMessaging:
    return "InstantMessaging";
  case NoteTagShapeID::PersonWithExclamationMark:
    return "PersonWithExclamationMark";
  case NoteTagShapeID::TwoPeople:
    return "TwoPeople";
  case NoteTagShapeID::ReminderBell:
    return "ReminderBell";
  case NoteTagShapeID::Contact:
    return "Contact";
  case NoteTagShapeID::Rose:
    return "Rose";
  case NoteTagShapeID::DateWithClock:
    return "DateWithClock";
  case NoteTagShapeID::MusicalNote:
    return "MusicalNote";
  case NoteTagShapeID::MovieClip:
    return "MovieClip";
  case NoteTagShapeID::QuotationMark:
    return "QuotationMark";
  case NoteTagShapeID::Globe:
    return "Globe";
  case NoteTagShapeID::HyperlinkGlobe:
    return "HyperlinkGlobe";
  case NoteTagShapeID::Laptop:
    return "Laptop";
  case NoteTagShapeID::Plane:
    return "Plane";
  case NoteTagShapeID::Car:
    return "Car";
  case NoteTagShapeID::Binoculars:
    return "Binoculars";
  case NoteTagShapeID::PresentationSlide:
    return "PresentationSlide";
  case NoteTagShapeID::Padlock:
    return "Padlock";
  case NoteTagShapeID::OpenBook:
    return "OpenBook";
  case NoteTagShapeID::NotebookWithClock:
    return "NotebookWithClock";
  case NoteTagShapeID::BlankPaperWithLines:
    return "BlankPaperWithLines";
  case NoteTagShapeID::Research:
    return "Research";
  case NoteTagShapeID::Pen:
    return "Pen";
  case NoteTagShapeID::DollarSign:
    return "DollarSign";
  case NoteTagShapeID::Coins:
    return "Coins";
  case NoteTagShapeID::ScheduledTask:
    return "ScheduledTask";
  case NoteTagShapeID::LightningBolt:
    return "LightningBolt";
  case NoteTagShapeID::Cloud:
    return "Cloud";
  case NoteTagShapeID::Heart:
    return "Heart";
  case NoteTagShapeID::Sunflower:
    return "Sunflower";

  default:
    return "invalid";
  }
}


} // namespace libmson
