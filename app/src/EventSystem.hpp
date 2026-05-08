#pragma once
#include <QGraphicsItem>
#include <QKeyEvent>

#include "utilities/logging/Logger.hpp"

namespace Permafrost
{
class EventSystem final : public QGraphicsItem
{
public:
	using QGraphicsItem::QGraphicsItem;

	[[nodiscard]] QRectF boundingRect() const override
	{
		return {0, 0, scene()->width(), scene()->height()};
	}

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
			   QWidget* widget) override {}


	void SetOnKeyPressedCallback(const std::function<void(QKeyEvent*)>& func)
	{
		m_KeyPressFunc = func;
	}

protected:
	void keyPressEvent(QKeyEvent* event) override
	{
		m_KeyPressFunc(event);
		event->accept();
	}

private:
	std::function<void(QKeyEvent*)> m_KeyPressFunc{};
};
}
