#pragma once
#include <QGraphicsObject>

namespace Permafrost
{
class Board : public QGraphicsObject
{
public:
	using QGraphicsObject::QGraphicsObject;

	[[nodiscard]] QRectF boundingRect() const override
	{
		return {0, 0, m_BoardSize * m_CellSize, m_BoardSize * m_CellSize};
	}

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
			   QWidget* widget) override {}


	void SetBoardSize(unsigned int size) { m_BoardSize = size; }
	void SetCellSize(double size) { m_CellSize = size; }
	void SetBorderWidth(unsigned int size) { m_BorderWidth = size * 2; }

	[[nodiscard]] int GetBoardSize() const { return static_cast<int>(m_BoardSize); }
	[[nodiscard]] double GetCellSize() const { return m_CellSize; }

	[[nodiscard]] int GetBorderWidth() const
	{
		return static_cast<int>(m_BorderWidth / 2);
	}

	[[nodiscard]] double GetWidth() const
	{
		return m_CellSize * static_cast<double>(m_BoardSize + m_BorderWidth);
	}

	[[nodiscard]] int GetSize() const
	{
		return static_cast<int>(m_BoardSize + m_BorderWidth);
	}

private:
	double m_CellSize{40};
	unsigned int m_BoardSize{8};
	unsigned int m_BorderWidth{1};
};
}
