#pragma once
#include <vector>

#include "Board.hpp"
#include "IEngineListener.hpp"

namespace PermafrostEngine::Core
{
class Engine
{
public:
	Engine();

	void AddListener(IEngineListener* listener);

private:
	void Notify();

public:
	Board Board{};

private:
	std::vector<IEngineListener*> m_Listeners{};
};
}
