#include "TransactionLogFragment.h"
#include "../commonTypes/FileChunkReference64x32.h"

namespace libmson {
namespace priv {

TransactionLogFragment::TransactionLogFragment() {}

RSChunkContainer_WPtr_t TransactionLogFragment::getNextFragment() const
{
  return nextFragment;
}

void TransactionLogFragment::setNextFragment(
    const RSChunkContainer_WPtr_t value)
{
  nextFragment = value;
}

quint64 TransactionLogFragment::getSizeInFile() const
{
  return sizeTable.size() * TransactionEntry::getSizeInFile() +
         FileChunkReference64x32::getSizeInFile();
}

// void TransactionLogFragment::deserialize(QDataStream &ds) {
//  quint64 startLocation = ds.device()->pos();

//  if (ds.device()->bytesAvailable() < m_size) {

//    qWarning() << "Error while parsing TransactionLogFragment: would reach end
//    of "
//               << "file stream before finished parsing. \n"
//               << "Bytes available: " << ds.device()->bytesAvailable() << '\n'
//               << "Bytes requested: " << m_size;
//    return;
//  }

//  if( m_size  < nextFragment.getSizeInFile() ) {
//    qWarning() << "Error: could not parse TransactionLogFragment. Specified
//    size of TransactionLogFragment insufficient."; return;
//  }

//  quint64 num_entries = (m_size - nextFragment.getSizeInFile()) /
//                        TransactionEntry::getSizeInFile();

//  for (size_t i{0}; i < num_entries; i++) {
//    std::shared_ptr<TransactionEntry> entry =
//        std::make_shared<TransactionEntry>();

//    ds >> *entry;
//    sizeTable.push_back(entry);
//  }

//  ds.device()->seek(startLocation + m_size - 12);
//  ds >> nextFragment;
//}

// void TransactionLogFragment::serialize(QDataStream &ds) const {
//  qDebug() << "TransactionLogFragment:  Reading at pos in file: "
//           << qStringHex(ds.device()->pos(), 16);
//  for (const auto &te : sizeTable) {
//    ds << *te;
//  }
//  ds << nextFragment;

//  qDebug() << "TransactionLogFragment: Finished at pos in file: "
//           << qStringHex(ds.device()->pos(), 16);
//}

// void TransactionLogFragment::toDebugString(QDebug &dbg) const {
//  dbg << "TransactionLogFragment: size: "
//      << QString("0x%1").arg(m_size, 16, 16, QLatin1Char('0')) << '\n'
//      << " nextFragment: " << nextFragment << '\n';
//  for (const auto &te : sizeTable) {
//    dbg << *te;
//  }
//}

// void TransactionLogFragment::writeLowLevelXml(
//    QXmlStreamWriter &xmlWriter) const {
//  xmlWriter.writeStartElement("TransactionLogFragment");

//  xmlWriter.writeStartElement("size");
//  xmlWriter.writeCharacters(qStringHex(m_size, 16));
//  xmlWriter.writeEndElement();

//  xmlWriter.writeStartElement("nextFragment");
//  xmlWriter << nextFragment;
//  xmlWriter.writeEndElement();

//  xmlWriter.writeStartElement("sizeTable");
//  for (const auto &entry : sizeTable) {
//    if (!entry->isZero()) {
//      xmlWriter << *entry;
//    }
//  }
//  xmlWriter.writeEndElement();

//  xmlWriter.writeEndElement();
//}

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

quint64 TransactionLogFragment::cb() const { return getSizeInFile(); }

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
