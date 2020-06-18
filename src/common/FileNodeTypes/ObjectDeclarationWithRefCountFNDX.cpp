#include "ObjectDeclarationWithRefCountFNDX.h"

ObjectDeclarationWithRefCountFNDX::ObjectDeclarationWithRefCountFNDX(FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat)
    : objectRef{FileNodeChunkReference(stpFormat, cbFormat)} {

}

ObjectDeclarationWithRefCountFNDX::ObjectDeclarationWithRefCountFNDX(quint8 stpFormat, quint8 cbFormat)
: objectRef{FileNodeChunkReference(stpFormat, cbFormat)}{

}

ObjectDeclarationWithRefCountFNDX::~ObjectDeclarationWithRefCountFNDX()
{

}



FileNodeChunkReference ObjectDeclarationWithRefCountFNDX::getObjectRef() const
{
    return objectRef;
}

void ObjectDeclarationWithRefCountFNDX::setObjectRef(const FileNodeChunkReference& value)
{
    objectRef = value;
}

ObjectDeclarationWithRefCountBody ObjectDeclarationWithRefCountFNDX::getBody() const
{
    return body;
}

void ObjectDeclarationWithRefCountFNDX::setBody(const ObjectDeclarationWithRefCountBody& value)
{
    body = value;
}

quint8 ObjectDeclarationWithRefCountFNDX::getCRef() const
{
    return cRef;
}

void ObjectDeclarationWithRefCountFNDX::setCRef(const quint8& value)
{
    cRef = value;
}



void ObjectDeclarationWithRefCountFNDX::deserialize(QDataStream& ds)
{
    ds >> objectRef;
    ds >> body;
    ds >> cRef;
}

void ObjectDeclarationWithRefCountFNDX::serialize(QDataStream& ds) const
{
    ds << objectRef;
    ds << body;
    ds << cRef;
}

void ObjectDeclarationWithRefCountFNDX::toDebugString(QDebug dbg) const
{
    dbg << "ObjectDeclarationWithRefCountFNDX:\n"
        << "objectRef: " << objectRef << '\n'
        << "body: " << body << '\n'
        << "cRef: " << cRef << '\n';
}
