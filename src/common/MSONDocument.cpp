#include "MSONDocument.h"



MSONDocument::MSONDocument()
{

}

MSONDocument::~MSONDocument()
{

}

MSONHeader* MSONDocument::header() const
{
  return m_header;
}

void MSONDocument::setHeader(MSONHeader* header)
{
  m_header = header;
}
