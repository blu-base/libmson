#include "RevisionManifestStart7FND.h"

RevisionManifestStart7FND::RevisionManifestStart7FND()
{

}

ExtendedGUID RevisionManifestStart7FND::getGctxid() const
{
    return gctxid;
}

void RevisionManifestStart7FND::setGctxid(const ExtendedGUID& value)
{
    gctxid = value;
}

void RevisionManifestStart7FND::deserialize(QDataStream& ds)
{
    ds >> base;
    ds >> gctxid;
}

void RevisionManifestStart7FND::serialize(QDataStream& ds) const
{
    ds << base;
    ds << gctxid;
}

void RevisionManifestStart7FND::toDebugString(QDebug dbg) const
{
    dbg << "RevisionManifestStart7FND:\n"
        << "base: " << base << "\ngctxid: " << gctxid << '\n';
}

RevisionManifestStart6FND RevisionManifestStart7FND::getBase() const
{
    return base;
}

void RevisionManifestStart7FND::setBase(const RevisionManifestStart6FND& value)
{
    base = value;
}
