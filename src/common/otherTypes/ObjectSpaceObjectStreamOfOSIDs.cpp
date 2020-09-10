#include "ObjectSpaceObjectStreamOfOSIDs.h"

#include "ObjectSpaceObjectStreamHeader.h"

namespace MSONcommon {

ObjectSpaceObjectStreamOfOSIDs::ObjectSpaceObjectStreamOfOSIDs()
    : IObjectSpaceOpbjectStream() {}

ObjectSpaceObjectStreamOfOSIDs::ObjectSpaceObjectStreamOfOSIDs(
    const ObjectSpaceObjectStreamHeader::OsidStreamPresence &osidStreamPresence,
    const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence
        &extendedStreamPresence)
    : IObjectSpaceOpbjectStream(osidStreamPresence, extendedStreamPresence) {}

ObjectSpaceObjectStreamOfOSIDs::~ObjectSpaceObjectStreamOfOSIDs() {}

} // namespace MSONcommon
