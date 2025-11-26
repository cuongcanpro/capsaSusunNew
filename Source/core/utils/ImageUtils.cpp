#include "ImageUtils.h"

ax::Vec2 ImageUtils::imageMiddle(ax::Node* image)
{
	return ax::Vec2(image->getContentSize().width / 2, image->getContentSize().height / 2);
}

