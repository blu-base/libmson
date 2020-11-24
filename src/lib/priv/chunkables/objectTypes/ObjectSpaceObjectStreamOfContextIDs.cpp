#include "ObjectSpaceObjectStreamOfContextIDs.h"

namespace libmson {
namespace priv {

ObjectSpaceObjectStreamOfContextIDs::ObjectSpaceObjectStreamOfContextIDs()
    : IObjectSpaceObjectStream()
{
}

ObjectSpaceObjectStreamOfContextIDs::ObjectSpaceObjectStreamOfContextIDs(
    const ObjectSpaceObjectStreamHeader::OsidStreamPresence& osidStreamPresence,
    const ObjectSpaceObjectStreamHeader::ExtendedStreamPresence&
        extendedStreamPresence)
    : IObjectSpaceObjectStream(osidStreamPresence, extendedStreamPresence)
{
}

ObjectSpaceObjectStreamOfContextIDs::~ObjectSpaceObjectStreamOfContextIDs() {}

} // namespace priv
} // namespace libmson
