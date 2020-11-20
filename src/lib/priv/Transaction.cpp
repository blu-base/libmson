#include "Transaction.h"
namespace libmson {
namespace priv {

Transaction::Transaction()
{

}


std::list<TransactionEntry_WPtr_t> Transaction::getEntries() const
{
  return m_entries;
}

void Transaction::setEntries(const std::list<TransactionEntry_WPtr_t>& entries)
{
  m_entries = entries;
}

quint32 Transaction::getCrc() const
{
  return m_crc;
}

void Transaction::setCrc(const quint32& crc)
{
  m_crc = crc;
}


} // namespace priv
} // namespace libmson
