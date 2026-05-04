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
	m_Window->setSceneRect(0L, 0L, windSize.width(), windSize.height());

	// Set up Camera.
	m_Camera = std::make_unique<Camera>(m_Window.get());
	m_Camera->setObjectName("context");
}


void Application::Render()
{
	m_Camera->show();
}
}
