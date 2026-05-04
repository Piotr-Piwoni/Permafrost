#pragma once
#include <QGraphicsView>

namespace Permafrost
{
class Camera final : public QGraphicsView
{
public:
	using QGraphicsView::QGraphicsView;

protected:
	void resizeEvent(QResizeEvent* event) override
	{
		QGraphicsView::resizeEvent(event);
		fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
	}
};
}
