#include "Application.hpp"

namespace Permafrost
{
Application::Application(int argc, char* argv[], const QSize windSize)
{
	m_QtApp = std::make_unique<QApplication>(argc, argv);
	QApplication::setApplicationName("Permafrost - Chess Engine");

	// Enable logging.
	auto filePath = QCoreApplication::applicationDirPath() + "/app.log";
	Utils::QtLoggerAdapter::Init(filePath.toStdString());

	// Create and connect the Theme Manager.
	m_ThemeManager = std::make_unique<ThemeManager>();
	QObject::connect(m_ThemeManager.get(), &ThemeManager::OnThemeChanged, m_QtApp.get(),
					 [this] {
						 m_QtApp->setStyleSheet(m_ThemeManager->GetStyleSheet());
					 });
	m_ThemeManager->SetTheme(":/themes/dark-mode");

	// Create the context window.
	m_Window = std::make_unique<QGraphicsScene>();
	m_Window->setSceneRect(0, 0, windSize.width(), windSize.height());

	// Set up Camera.
	m_Camera = std::make_unique<Camera>(m_Window.get());
	m_Camera->setObjectName("context");
	m_Camera->setResizeAnchor(QGraphicsView::AnchorViewCenter);
	m_Camera->OnResizeCallback([this] { OnResize(); });
	m_Camera->viewport()->setMouseTracking(true);
	m_Camera->setMouseTracking(true);

	// Initialise board.
	m_BoardUI = std::make_unique<BoardUI>();
	m_Window->addItem(m_BoardUI.get());
	m_Engine.AddListener(m_BoardUI.get());
}


void Application::Render()
{
	m_BoardUI->CreateChessboard();
	m_Camera->show();
}


void Application::OnResize()
{
	double xCenterBoard = (m_Window->width() - m_Engine.Board.GetWidth()) / 2;
	double yCenterBoard = (m_Window->height() - m_Engine.Board.GetWidth()) / 2;
	m_BoardUI->setPos({xCenterBoard, yCenterBoard});
}
}
