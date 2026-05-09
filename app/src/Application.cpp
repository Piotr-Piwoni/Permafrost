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

	// Set up Event System.
	m_Window->addItem(&m_EventSystem);
	m_EventSystem.setFlag(QGraphicsItem::ItemIsFocusable);
	m_EventSystem.setFocus();
	m_EventSystem.SetOnKeyPressedCallback([this](QKeyEvent* event) {
		OnKeyPressed(event);
	});

	// Set up Camera.
	m_Camera = std::make_unique<Camera>(m_Window.get());
	m_Camera->setObjectName("context");
	m_Camera->setResizeAnchor(QGraphicsView::AnchorViewCenter);
	m_Camera->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	m_Camera->OnResizeCallback([this] { OnResize(); });
	m_Camera->viewport()->setMouseTracking(true);
	m_Camera->setMouseTracking(true);

	// Initialise board.
	m_BoardUI = std::make_unique<UI::BoardUI>();
	m_Window->addItem(m_BoardUI.get());
	m_Engine.AddListener(m_BoardUI.get());

	// Load Textures
	// Black Pieces.
	m_TextureManager.LoadPixmap(":/pieces/256px/b_pawn.png", "BPawn");
	m_TextureManager.LoadPixmap(":/pieces/256px/b_rook.png", "BRook");
	m_TextureManager.LoadPixmap(":/pieces/256px/b_knight.png", "BKnight");
	m_TextureManager.LoadPixmap(":/pieces/256px/b_bishop.png", "BBishop");
	m_TextureManager.LoadPixmap(":/pieces/256px/b_queen.png", "BQueen");
	m_TextureManager.LoadPixmap(":/pieces/256px/b_king.png", "BKing");
	// White Pieces.
	m_TextureManager.LoadPixmap(":/pieces/256px/w_pawn.png", "WPawn");
	m_TextureManager.LoadPixmap(":/pieces/256px/w_rook.png", "WRook");
	m_TextureManager.LoadPixmap(":/pieces/256px/w_knight.png", "WKnight");
	m_TextureManager.LoadPixmap(":/pieces/256px/w_bishop.png", "WBishop");
	m_TextureManager.LoadPixmap(":/pieces/256px/w_queen.png", "WQueen");
	m_TextureManager.LoadPixmap(":/pieces/256px/w_king.png", "WKing");

	SetupPieces();
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

void Application::OnKeyPressed(QKeyEvent* event)
{
	if (event->key() == Qt::Key::Key_K)
		m_BoardUI->SetShowNumbers(!m_BoardUI->ShowNumbers());
}

void Application::SetupPieces()
{
	m_Engine.SetupPieces();
	auto boardCells = m_BoardUI->GetPlayableArea();
	const auto& pieces = m_Engine.GetGamePieces();

	for (auto& piece : pieces)
	{
		// ReSharper disable once CppDFAMemoryLeak
		auto pieceUI = new UI::PieceUI();
		m_Window->addItem(pieceUI);

		// Set texture based on type and team.
		switch (piece->Type)
		{
		case PermafrostEngine::PieceType::None:
			lError("A piece has a type of \"None\" at UI generation!");
			break;
		case PermafrostEngine::PieceType::Pawn:
			if (piece->IsWhite) pieceUI->setPixmap(*m_TextureManager.GetPixmap("WPawn"));
			else pieceUI->setPixmap(*m_TextureManager.GetPixmap("BPawn"));
			break;
		case PermafrostEngine::PieceType::Rook:
			if (piece->IsWhite) pieceUI->setPixmap(*m_TextureManager.GetPixmap("WRook"));
			else pieceUI->setPixmap(*m_TextureManager.GetPixmap("BRook"));
			break;
		case PermafrostEngine::PieceType::Knight:
			if (piece->IsWhite)
				pieceUI->setPixmap(*m_TextureManager.GetPixmap("WKnight"));
			else pieceUI->setPixmap(*m_TextureManager.GetPixmap("BKnight"));
			break;
		case PermafrostEngine::PieceType::Bishop:
			if (piece->IsWhite)
				pieceUI->setPixmap(*m_TextureManager.GetPixmap("WBishop"));
			else pieceUI->setPixmap(*m_TextureManager.GetPixmap("BBishop"));
			break;
		case PermafrostEngine::PieceType::Queen:
			if (piece->IsWhite) pieceUI->setPixmap(*m_TextureManager.GetPixmap("WQueen"));
			else pieceUI->setPixmap(*m_TextureManager.GetPixmap("BQueen"));
			break;
		case PermafrostEngine::PieceType::King:
			if (piece->IsWhite) pieceUI->setPixmap(*m_TextureManager.GetPixmap("WKing"));
			else pieceUI->setPixmap(*m_TextureManager.GetPixmap("BKing"));
			break;
		}

		// Put the piece in the correct cell.
		pieceUI->setScale(0.1);
		pieceUI->setPos(boardCells[piece->Index]->sceneBoundingRect().x() +
						pieceUI->sceneBoundingRect().width() / 2 - 2,
						boardCells[piece->Index]->sceneBoundingRect().y() +
						pieceUI->sceneBoundingRect().height() / 2);
	}
}
}
