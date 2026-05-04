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
	m_Board = std::make_unique<Board>();
	m_Window->addItem(m_Board.get());
}


void Application::Render()
{
	// Create chess board.
	for (int row = 0; row < m_Board->GetSize(); row++)
		for (int column = 0; column < m_Board->GetSize(); column++)
		{
			// ReSharper disable once CppDFAMemoryLeak
			auto cell = new BoardCell(column * m_Board->GetCellSize(),
									  row * m_Board->GetCellSize(),
									  m_Board->GetCellSize(),
									  m_Board->GetCellSize());
			cell->setAcceptHoverEvents(true);

			// Border.
			if (row == 0 || row == m_Board->GetBoardSize() ||
				column == 0 || column == m_Board->GetBoardSize())
			{
				cell->SetColour(QColor{Qt::darkRed});
				cell->setAcceptHoverEvents(false);
				cell->setParentItem(m_Board.get());
				continue;
			}


			// Playable cell.
			if ((column + row) % 2 == 0) cell->SetColour(QColor{Qt::white});
			else cell->SetColour(QColor{Qt::gray});

			cell->setParentItem(m_Board.get());
		}


	m_Camera->show();
}


void Application::OnResize()
{
	double xCenterBoard = (m_Window->width() - m_Board->GetWidth()) / 2;
	double yCenterBoard = (m_Window->height() - m_Board->GetWidth()) / 2;
	m_Board->setPos({xCenterBoard, yCenterBoard});
}
}
