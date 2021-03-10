#ifndef DATAELEMENTTYPE_H
#define DATAELEMENTTYPE_H

#include <cstdint>

namespace libmson {
namespace packStore {

enum class DataElementType : uint8_t {
  StorageIndex        = 0x01,
  StorageManifest     = 0x02,
  CellManifest        = 0x03,
  RevisionManifest    = 0x04,
  ObjectGroup         = 0x05,
  DataElementFragment = 0x06,
  ObjectDataBLOB      = 0x0A,
};

}
}

#endif // DATAELEMENTTYPE_H
