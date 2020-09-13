#include "TransactionLogFragment.h"
#include "helper/Helper.h"
namespace MSONcommon {
TransactionLogFragment::TransactionLogFragment(quint64 size) : m_size{size} {}

FileChunkReference64x32 TransactionLogFragment::getNextFragment() const {
  return nextFragment;
}

void TransactionLogFragment::setNextFragment(
    const FileChunkReference64x32 &value) {
  nextFragment = value;
}

void TransactionLogFragment::deserialize(QDataStream &ds) {
  quint64 num_entries = (m_size - 12) / 8;

  for (size_t i{0}; i < num_entries; i++) {
    std::shared_ptr<TransactionEntry> entry = std::make_shared<TransactionEntry>();
    ds >> *entry;
    sizeTable.push_back(entry);
  }

  ds >> nextFragment;
}

void TransactionLogFragment::serialize(QDataStream &ds) const {
  qDebug() << "TransactionLogFragment:  Reading at pos in file: "
           << qStringHex(ds.device()->pos(), 16);
  for (const auto& te : sizeTable) {
    ds << *te;
  }
  ds << nextFragment;

  qDebug() << "TransactionLogFragment: Finished at pos in file: "
           << qStringHex(ds.device()->pos(), 16);
}

void TransactionLogFragment::toDebugString(QDebug &dbg) const {
  dbg << "TransactionLogFragment: size: "
      << QString("0x%1").arg(m_size, 16, 16, QLatin1Char('0')) << '\n'
      << " nextFragment: " << nextFragment << '\n';
  for (const auto& te : sizeTable) {
    dbg << *te;
  }
}

void TransactionLogFragment::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("TransactionLogFragment");

  xmlWriter.writeStartElement("size");
  xmlWriter.writeCharacters(qStringHex(m_size, 16));
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("nextFragment");
  xmlWriter << nextFragment;
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("sizeTable");
  for (const auto &entry : sizeTable) {
    if (!entry->isZero()) {
      xmlWriter << *entry;
    }
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}

std::vector<std::shared_ptr<TransactionEntry>> TransactionLogFragment::getSizeTable() const {
  return sizeTable;
}

void TransactionLogFragment::setSizeTable(
    const std::vector<std::shared_ptr<TransactionEntry>> &value) {
  sizeTable = value;
}
} // namespace MSONcommon
