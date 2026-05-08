#pragma once

namespace PermafrostEngine::Core
{
class IEngineListener
{
public:
	virtual ~IEngineListener() = default;

	virtual void OnBoardChanged(unsigned int size, double cellSize,
								unsigned int borderWidth) {}
};
}
