#pragma once
#include <QBrush>
#include <QColor>
#include <QGraphicsRectItem>

namespace Permafrost::UI
{
class CellUI final : public QGraphicsRectItem
{
public:
	using QGraphicsRectItem::QGraphicsRectItem;

	void SetColour(const QColor& colour)
	{
		m_Colour = colour;
		setBrush(m_Colour);
	}

	void SetHighlightColour(const QColor& colour) { m_Highlight = colour; }

	[[nodiscard]] QColor GetColour() const { return m_Colour; }
	[[nodiscard]] QColor GetHighlightColour() const { return m_Highlight; }

protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override
	{
		setBrush({m_Highlight});
	}

	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override
	{
		setBrush({m_Colour});
	}

private:
	QColor m_Highlight{255, 0, 0, 51};
	QColor m_Colour{};
};
}
