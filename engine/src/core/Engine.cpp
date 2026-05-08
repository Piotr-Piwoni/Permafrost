#include "Engine.hpp"

namespace PermafrostEngine::Core
{
Engine::Engine()
{
	m_Listeners.reserve(5);
	Board.NotifyCallback([this] { Notify(); });
}


void Engine::AddListener(IEngineListener* listener)
{
	m_Listeners.push_back(listener);
	Notify();
}

void Engine::Notify()
{
	for (auto& listener : m_Listeners)
	{
		listener->OnBoardChanged(Board.GetPlayableSize(),
								 Board.GetCellSize(),
								 Board.GetBorderWidth());
	}
}
}
