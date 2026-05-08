#pragma once
#include "IEvent.hpp"

namespace PermafrostEngine::Core
{
class Board final : public IEvent
{
public:
	void SetSize(unsigned int size)
	{
		m_BoardSize = size;
		m_NotifyFunc();
	}

	void SetCellSize(double size)
	{
		m_CellSize = size;
		m_NotifyFunc();
	}

	void SetBorderWidth(unsigned int size)
	{
		m_BorderWidth = size * 2; //< Times 2 as to account for both sides.
		m_NotifyFunc();
	}

	[[nodiscard]] int GetSize() const
	{
		return static_cast<int>(m_BoardSize + m_BorderWidth);
	}

	[[nodiscard]] int GetPlayableSize() const { return static_cast<int>(m_BoardSize); }
	[[nodiscard]] double GetCellSize() const { return m_CellSize; }

	[[nodiscard]] int GetBorderWidth() const
	{
		return static_cast<int>(m_BorderWidth / 2);
	}

	[[nodiscard]] double GetWidth() const
	{
		return m_CellSize * static_cast<double>(m_BoardSize + m_BorderWidth);
	}

private:
	double m_CellSize{40};
	unsigned int m_BoardSize{8};
	unsigned int m_BorderWidth{2};
};
}
