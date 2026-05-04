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

	// Initialise board.
	m_Board = std::make_unique<QGraphicsItemGroup>();
	m_Window->addItem(m_Board.get());
}


void Application::Render()
{
	// Create chess board.
	for (int row = 0; row < kBoardSize; row++)
		for (int column = 0; column < kBoardSize; column++)
		{
			auto cell = m_Window->addRect({
				column * kCellSize,
				row * kCellSize,
				kCellSize,
				kCellSize
			});
			m_Board->addToGroup(cell);


			// Border.
			if (row == 0 || row == kBoardSize - 1 ||
				column == 0 || column == kBoardSize - 1)
			{
				cell->setBrush(Qt::darkRed);
				continue;
			}

			// Playable cell.
			if ((column + row) % 2 == 0) cell->setBrush(Qt::white);
			else cell->setBrush(Qt::gray);
		}


	m_Camera->show();
}


void Application::OnResize()
{
	double boardWidth = kCellSize * static_cast<double>(kBoardSize);
	double xCenterBoard = (m_Window->width() - boardWidth) / 2;
	double yCenterBoard = (m_Window->height() - boardWidth) / 2;
	m_Board->setPos({xCenterBoard, yCenterBoard});
}
}
