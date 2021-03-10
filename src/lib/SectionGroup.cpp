#include "SectionGroup.h"

namespace libmson {

SectionGroup::SectionGroup() {}

QString SectionGroup::getFilePath() {}

ObjectID SectionGroup::getObjectID() {}

QString SectionGroup::getName() {}

QDateTime SectionGroup::getLastModifiedTime() {}

bool SectionGroup::isCurrentlyViewed() {}

bool SectionGroup::isInRecycleBin() {}

INode* SectionGroup::getParent() {}

std::vector<INode_SPtr_t> SectionGroup::getChildren() {}

INodeType SectionGroup::type() {}

Section SectionGroup::getSection() {}

bool SectionGroup::isUnread() {}

} // namespace libmson
