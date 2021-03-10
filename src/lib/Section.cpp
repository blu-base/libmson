#include "Section.h"

namespace libmson {


Section::Section() {}
QString Section::getFilePath() {}

ObjectID Section::getObjectID() {}

QString Section::getName() {}

QDateTime Section::getLastModifiedTime() {}

bool Section::isCurrentlyViewed() {}

bool Section::isInRecycleBin() {}

INode* Section::getParent() {}

std::vector<INode_SPtr_t> Section::getChildren() {}

INodeType Section::type() {}

std::weak_ptr<Section> Section::getSection() {}

bool Section::isUnread() {}

} // namespace libmson
