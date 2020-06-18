#include "RevisionManifest.h"

std::vector<FileNode*> RevisionManifest::getFileNodeSquence() const
{
    return FileNodeSquence;
}

void RevisionManifest::setFileNodeSquence(const std::vector<FileNode*>& value)
{
    FileNodeSquence = value;
}

RevisionManifest::RevisionManifest()
    :FileNodeSquence {}
{

}

RevisionManifest::~RevisionManifest()
{
    for (auto *fns : FileNodeSquence) {
        delete fns;
    }
}
