#include "ObjectSpaceObjectStreamOfContextIDs.h"

#include "ObjectSpaceObjectStreamHeader.h"

namespace MSONcommon {

ObjectSpaceObjectStreamOfContextIDs::ObjectSpaceObjectStreamOfContextIDs()
    : IObjectSpaceObjectStream() {}

ObjectSpaceObjectStreamOfContextIDs::ObjectSpaceObjectStreamOfContextIDs(
    const ObjectSpaceObjectStreamHeader::OsidStreamPresence &osidStreamPresence,
    const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence
        &extendedStreamPresence)
    : IObjectSpaceObjectStream(osidStreamPresence, extendedStreamPresence) {}

ObjectSpaceObjectStreamOfContextIDs::~ObjectSpaceObjectStreamOfContextIDs() {}

} // namespace MSONcommon
