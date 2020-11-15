#include "TransactionLogFragment.h"
#include "../commonTypes/FileChunkReference64x32.h"

namespace libmson {
namespace priv {


TransactionLogFragment::TransactionLogFragment(
    const quint64 initialStp, const quint64 initialCb)
    : Chunkable(initialStp, initialCb), nextFragment(), m_paddingLength()
{
}


std::vector<std::shared_ptr<TransactionEntry>>
TransactionLogFragment::getSizeTable() const
{
  return sizeTable;
}

void TransactionLogFragment::setSizeTable(
    const std::vector<std::shared_ptr<TransactionEntry>>& value)
{
  sizeTable = value;
}


TransactionLogFragment_WPtr_t TransactionLogFragment::getNextFragment() const
{
  return nextFragment;
}

void TransactionLogFragment::setNextFragment(
    const TransactionLogFragment_WPtr_t value)
{
  nextFragment = value;
}

quint8 TransactionLogFragment::getPaddingLength() const
{
  return m_paddingLength;
}

void TransactionLogFragment::setPaddingLength(const quint8& paddingLength)
{
  m_paddingLength = paddingLength;
}


quint64 TransactionLogFragment::cb() const
{
  return sizeTable.size() * TransactionEntry::getSizeInFile() +
         FileChunkReference64x32::getSizeInFile() + m_paddingLength;
}

RevisionStoreChunkType TransactionLogFragment::getType() const
{
  return RevisionStoreChunkType::TransactionLogFragment;
}


// #############################################################################


TransactionEntry::TransactionEntry() : srcID{}, TransactionEntrySwitch{} {}

// void TransactionEntry::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {

//  xmlWriter.writeStartElement("TransactionEntry");

//  if (isZero()) {
//    xmlWriter.writeAttribute("isZero", "true");
//  } else {

//    xmlWriter.writeAttribute("size", qStringHex(srcID, 8));
//    xmlWriter.writeAttribute("TransactionEntrySwitch",
//                             qStringHex(TransactionEntrySwitch, 8));
//  }

//  xmlWriter.writeEndElement();
//}

void TransactionEntry::serialize(QDataStream& ds) const
{
  ds << srcID;
  ds << TransactionEntrySwitch;
}

void TransactionEntry::deserialize(QDataStream& ds)
{
  ds >> srcID;
  ds >> TransactionEntrySwitch;
}

// void TransactionEntry::toDebugString(QDebug &dbg) const {
//  dbg.noquote() << "TransactionEntry:  srcID: " << qStringHex(srcID, 8)
//                << " transactionEntrySwitch: "
//                << qStringHex(TransactionEntrySwitch, 8) << '\n';
//}

quint32 TransactionEntry::getSrcID() const { return srcID; }

void TransactionEntry::setSrcID(const quint32& value) { srcID = value; }

quint32 TransactionEntry::getTransactionEntrySwitch() const
{
  return TransactionEntrySwitch;
}

void TransactionEntry::setTransactionEntrySwitch(const quint32& value)
{
  TransactionEntrySwitch = value;
}

bool TransactionEntry::isZero() const
{
  return srcID == 0 && TransactionEntrySwitch == 0;
}


} // namespace priv
} // namespace libmson
