#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QtCore/qglobal.h>

#include "chunkables/TransactionLogFragment.h"

namespace libmson {
namespace priv {



/// An abstraction of the TransactionEntries in the TransactionLogFragments
class Transaction {
private:
  std::list<TransactionEntry_SPtr_t> m_entries;


  quint32 m_crc;

public:
  Transaction();

  std::list<TransactionEntry_WPtr_t> getEntries() const;
  void setEntries(const std::list<TransactionEntry_WPtr_t>& entries);

  quint32 getCrc() const;
  void setCrc(const quint32& crc);

};

} // namespace priv
} // namespace libmson

#endif // TRANSACTION_H
