#pragma once
#include <functional>

namespace PermafrostEngine::Core
{
class IEvent
{
public:
	virtual ~IEvent() = default;

	void NotifyCallback(const std::function<void()>& func)
	{
		m_NotifyFunc = func;
	}

protected:
	std::function<void()> m_NotifyFunc{};
};
}
