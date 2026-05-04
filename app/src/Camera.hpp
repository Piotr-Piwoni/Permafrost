#pragma once
#include <QGraphicsView>
#include <functional>

namespace Permafrost
{
class Camera final : public QGraphicsView
{
public:
	using QGraphicsView::QGraphicsView;

	void OnResizeCallback(const std::function<void()>& func)
	{
		m_OnResizeFunction = func;
	}

protected:
	void resizeEvent(QResizeEvent* event) override
	{
		QGraphicsView::resizeEvent(event);
		fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
		m_OnResizeFunction();
	}

protected:
	std::function<void()> m_OnResizeFunction{nullptr};
};
}
