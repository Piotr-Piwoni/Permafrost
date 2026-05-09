#pragma once
#include <QGraphicsItem>
#include <QGraphicsTextItem>

#include "CellUI.hpp"
#include "../utilities/QtHelperFunctions.hpp"
#include "core/IEngineListener.hpp"
#include "utilities/logging/Logger.hpp"

namespace Permafrost::UI
{
class BoardUI final : public QGraphicsItem, public PermafrostEngine::Core::IEngineListener
{
public:
	using QGraphicsItem::QGraphicsItem;

	[[nodiscard]] QRectF boundingRect() const override
	{
		return {
			0,
			0,
			m_CellSize * (m_BoardSize + m_BorderWidth),
			m_CellSize * (m_BoardSize + m_BorderWidth)
		};
	}

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
			   QWidget* widget) override {}


	void CreateChessboard()
	{
		// Clear the UI.
		Utilis::QtHelpers::DeleteAllChildren(this);
		m_PlayableArea.clear();

		unsigned int size = m_BoardSize + m_BorderWidth;
		// Create chess board.
		for (int row = 0; row < size; row++)
			for (int column = 0; column < size; column++)
			{
				// ReSharper disable once CppDFAMemoryLeak
				auto cell = new CellUI(column * m_CellSize, row * m_CellSize,
									   m_CellSize, m_CellSize);
				cell->setAcceptHoverEvents(true);
				cell->setParentItem(this);

				// Border.
				if (row == 0 || row >= size - 1 ||
					column == 0 || column >= size - 1)
				{
					cell->SetColour(QColor{Qt::darkRed});
					cell->setAcceptHoverEvents(false);
					continue;
				}

				// Playable cell.
				if ((column + row) % 2 == 0) cell->SetColour(QColor{Qt::white});
				else cell->SetColour(QColor{Qt::gray});
				m_PlayableArea.push_back(cell);
			}

		CreateNumbers();
	}

	void CreateNumbers()
	{
		m_Numbers.clear();
		int index = 0;
		for (auto& cellUI : m_PlayableArea)
		{
			// ReSharper disable once CppDFAMemoryLeak
			auto text = new QGraphicsTextItem(QString::number(index + 1), this);
			m_Numbers.push_back(text);
			text->setDefaultTextColor(QColor{Qt::black});
			text->setVisible(m_ShowNumbers);

			text->setPos(cellUI->boundingRect().topLeft());
			index++;
		}
	}

	[[nodiscard]] std::vector<CellUI*> GetPlayableArea() { return m_PlayableArea; }

	void SetShowNumbers(bool val)
	{
		m_ShowNumbers = val;
		if (!m_Numbers.empty())
			for (auto& number : m_Numbers)
				number->setVisible(m_ShowNumbers);
	}

	[[nodiscard]] bool ShowNumbers() const { return m_ShowNumbers; }


	void OnBoardChanged(unsigned size, double cellSize, unsigned borderWidth) override
	{
		m_BoardSize = size;
		m_CellSize = cellSize;
		m_BorderWidth = borderWidth * 2;

		// Re-create the chessboard.
		CreateChessboard();
	}

private:
	double m_CellSize{0};
	unsigned int m_BoardSize{0};
	unsigned int m_BorderWidth{0};
	std::vector<CellUI*> m_PlayableArea{};
	std::vector<QGraphicsTextItem*> m_Numbers{};
	bool m_ShowNumbers{false};
};
}

