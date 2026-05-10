#pragma once
#include <QApplication>

#include "Camera.hpp"
#include "EventSystem.hpp"
#include "core/Engine.hpp"
#include "theme/ThemeManager.hpp"
#include "ui/BoardUI.hpp"
#include "ui/PieceUI.hpp"
#include "utilities/QtLoggerAdapter.hpp"
#include "utilities/TextureManager.hpp"

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
	void SetupPieces();
	void UpdatePiecesUIPosition();

private:
	std::unique_ptr<QApplication> m_QtApp{nullptr};
	std::unique_ptr<ThemeManager> m_ThemeManager{nullptr};

	std::unique_ptr<QGraphicsScene> m_Window{nullptr};
	std::unique_ptr<Camera> m_Camera{nullptr};
	std::unique_ptr<UI::BoardUI> m_BoardUI{nullptr};
	PermafrostEngine::Core::Engine m_Engine{};
	EventSystem m_EventSystem{};
	Utils::TextureManager m_TextureManager{};
	std::vector<std::unique_ptr<UI::PieceUI>> m_PiecesUIs{};
};
}
