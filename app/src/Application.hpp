#pragma once
#include <QApplication>

#include "Camera.hpp"
#include "EventSystem.hpp"
#include "core/Engine.hpp"
#include "theme/ThemeManager.hpp"
#include "ui/BoardUI.hpp"
#include "utilities/QtLoggerAdapter.hpp"

namespace Permafrost
{
class Application
{
public:
	Application(int argc, char* argv[], QSize windSize);

	void Render();

private:
	void OnResize();
	void OnKeyPressed(QKeyEvent* event);

private:
	std::unique_ptr<QApplication> m_QtApp{nullptr};
	std::unique_ptr<ThemeManager> m_ThemeManager{nullptr};

	std::unique_ptr<QGraphicsScene> m_Window{nullptr};
	std::unique_ptr<Camera> m_Camera{nullptr};
	std::unique_ptr<UI::BoardUI> m_BoardUI{nullptr};
	PermafrostEngine::Core::Engine m_Engine{};
	EventSystem m_EventSystem{};
};
}
