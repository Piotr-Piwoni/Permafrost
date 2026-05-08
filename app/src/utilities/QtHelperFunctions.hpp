#pragma once
#include <QGraphicsItem>

namespace Permafrost::Utilis::QtHelpers
{
inline void DeleteAllChildren(QGraphicsItem* parent)
{
	for (auto children = parent->childItems(); QGraphicsItem* child : children)
		delete child;
}
}
