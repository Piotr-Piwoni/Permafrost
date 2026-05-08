#pragma once
#include <QApplication>
#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "theme/ThemeManager.hpp"
#include "utilities/QtLoggerAdapter.hpp"
#include "BoardCell.hpp"
#include "BoardUI.hpp"
#include "Camera.hpp"
#include "core/Engine.hpp"
#include "utilities/QtHelperFunctions.hpp"

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
	std::unique_ptr<BoardUI> m_BoardUI{nullptr};
	PermafrostEngine::Core::Engine m_Engine{};
};
}
