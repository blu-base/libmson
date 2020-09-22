#include "ObjectSpaceObjectStreamOfOSIDs.h"

#include "ObjectSpaceObjectStreamHeader.h"

namespace MSONcommon {

ObjectSpaceObjectStreamOfOSIDs::ObjectSpaceObjectStreamOfOSIDs()
    : IObjectSpaceObjectStream() {}

ObjectSpaceObjectStreamOfOSIDs::ObjectSpaceObjectStreamOfOSIDs(
    const ObjectSpaceObjectStreamHeader::OsidStreamPresence &osidStreamPresence,
    const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence
        &extendedStreamPresence)
    : IObjectSpaceObjectStream(osidStreamPresence, extendedStreamPresence) {}

ObjectSpaceObjectStreamOfOSIDs::~ObjectSpaceObjectStreamOfOSIDs() {}

} // namespace MSONcommon
