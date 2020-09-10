#include "ObjectSpaceObjectStreamOfOIDs.h"

#include "ObjectSpaceObjectStreamHeader.h"

namespace MSONcommon {

ObjectSpaceObjectStreamOfOIDs::ObjectSpaceObjectStreamOfOIDs()
    : IObjectSpaceOpbjectStream() {}

ObjectSpaceObjectStreamOfOIDs::ObjectSpaceObjectStreamOfOIDs(
    const ObjectSpaceObjectStreamHeader::OsidStreamPresence &osidStreamPresence,
    const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence
        &extendedStreamPresence)
    : IObjectSpaceOpbjectStream(osidStreamPresence, extendedStreamPresence) {}

ObjectSpaceObjectStreamOfOIDs::~ObjectSpaceObjectStreamOfOIDs() {}

} // namespace MSONcommon
