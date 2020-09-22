#include "ObjectSpaceObjectStreamOfOIDs.h"

#include "ObjectSpaceObjectStreamHeader.h"

namespace MSONcommon {

ObjectSpaceObjectStreamOfOIDs::ObjectSpaceObjectStreamOfOIDs()
    : IObjectSpaceObjectStream() {}

ObjectSpaceObjectStreamOfOIDs::ObjectSpaceObjectStreamOfOIDs(
    const ObjectSpaceObjectStreamHeader::OsidStreamPresence &osidStreamPresence,
    const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence
        &extendedStreamPresence)
    : IObjectSpaceObjectStream(osidStreamPresence, extendedStreamPresence) {}

ObjectSpaceObjectStreamOfOIDs::~ObjectSpaceObjectStreamOfOIDs() {}

} // namespace MSONcommon
