#include "RevisionRoleAndContextDeclarationFND.h"

RevisionRoleAndContextDeclarationFND::RevisionRoleAndContextDeclarationFND()
{

}

ExtendedGUID RevisionRoleAndContextDeclarationFND::getGctxid() const
{
    return gctxid;
}

void RevisionRoleAndContextDeclarationFND::setGctxid(const ExtendedGUID& value)
{
    gctxid = value;
}

RevisionRoleDeclarationFND RevisionRoleAndContextDeclarationFND::getBase() const
{
    return base;
}

void RevisionRoleAndContextDeclarationFND::setBase(const RevisionRoleDeclarationFND& value)
{
    base = value;
}


void RevisionRoleAndContextDeclarationFND::deserialize(QDataStream& ds)
{
    ds >> base;
    ds >> gctxid;
}

void RevisionRoleAndContextDeclarationFND::serialize(QDataStream& ds) const
{
    ds << base;
    ds << gctxid;
}

void RevisionRoleAndContextDeclarationFND::toDebugString(QDebug dbg) const
{
    dbg << "RevisionRoleAndContextDeclarationFND\n"
        << "Base:\n" << base << "gctxid: " << gctxid << '\n';
    }
