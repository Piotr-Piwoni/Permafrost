#pragma once
#include <QApplication>
#include "theme/ThemeManager.hpp"
#include "utilities/QtLoggerAdapter.hpp"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>

#include "Board.hpp"
#include "Camera.hpp"
#include "BoardCell.hpp"

namespace Permafrost
{
class Application
{
public:
	Application(int argc, char* argv[], QSize windSize);

	void Render();

private:
	void OnResize();

private:
	std::unique_ptr<QApplication> m_QtApp{nullptr};
	std::unique_ptr<ThemeManager> m_ThemeManager{nullptr};

	std::unique_ptr<QGraphicsScene> m_Window{nullptr};
	std::unique_ptr<Camera> m_Camera{nullptr};
	std::unique_ptr<Board> m_Board{nullptr};
};
}
