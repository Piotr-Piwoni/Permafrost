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
	m_Window = std::make_unique<QWidget>();
	m_Window->setObjectName("context");
	m_Window->resize(windSize);
}


void Application::Render()
{
	// ReSharper disable once CppDFAMemoryLeak
	auto* characterSheetLayout = new QVBoxLayout(m_Window.get());
	// ReSharper disable once CppDFAMemoryLeak
	auto header = new QWidget();
	header->setMinimumHeight(50);
	header->setMaximumHeight(112);
	header->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
	characterSheetLayout->addWidget(header);


	// ReSharper disable once CppDFAMemoryLeak
	auto contentLayout = new QHBoxLayout();
	characterSheetLayout->addLayout(contentLayout);

	// Left Side.
	// ReSharper disable once CppDFAMemoryLeak
	auto infoLayout = new QVBoxLayout();
	contentLayout->addLayout(infoLayout, 1);

	// ReSharper disable once CppDFAMemoryLeak
	auto* infoBox1 = new QWidget();
	// ReSharper disable once CppDFAMemoryLeak
	auto infoBox2 = new QWidget();
	infoLayout->addWidget(infoBox1, 1);
	infoLayout->addWidget(infoBox2, 1);

	// Right Side.
	// ReSharper disable once CppDFAMemoryLeak
	auto skillBox = new QWidget();
	contentLayout->addWidget(skillBox, 2);

	characterSheetLayout->setContentsMargins(10, 10, 10, 10);
	characterSheetLayout->setSpacing(10);

	m_Window->show();
}
}
