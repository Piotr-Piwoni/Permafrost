#include "Engine.hpp"

namespace PermafrostEngine::Core
{
Engine::Engine()
{
	m_Listeners.reserve(5);
	Board.NotifyCallback([this] { Notify(); });

	m_GamePieces.reserve(Board.GetPlayableSize() * Board.GetPlayableSize());
}


void Engine::AddListener(IEngineListener* listener)
{
	m_Listeners.push_back(listener);
	Notify();
}

void Engine::SetupPieces()
{
	const int size = Board.GetPlayableSize();

	auto AddPiece = [&](int row, int col, PieceType type, bool isWhite) {
		int index = row * size + col;
		m_GamePieces.emplace_back(std::make_unique<Piece>(index, type, isWhite));
	};

	// Pawns.
	for (int col = 0; col < size; col++)
	{
		AddPiece(1, col, PieceType::Pawn, false);       //< Black.
		AddPiece(size - 2, col, PieceType::Pawn, true); //< White.
	}

	// Back ranks.
	auto SetupBackRank = [&](int row, bool isWhite) {
		AddPiece(row, 0, PieceType::Rook, isWhite);
		AddPiece(row, 1, PieceType::Knight, isWhite);
		AddPiece(row, 2, PieceType::Bishop, isWhite);
		AddPiece(row, 3, PieceType::Queen, isWhite);
		AddPiece(row, 4, PieceType::King, isWhite);
		AddPiece(row, size - 3, PieceType::Bishop, isWhite);
		AddPiece(row, size - 2, PieceType::Knight, isWhite);
		AddPiece(row, size - 1, PieceType::Rook, isWhite);
	};

	SetupBackRank(0, false);       //< Black.
	SetupBackRank(size - 1, true); //< White.
}

const std::vector<std::unique_ptr<Piece>>& Engine::GetGamePieces()
{
	return m_GamePieces;
}


void Engine::Notify()
{
	for (auto& listener : m_Listeners)
	{
		{ // On Board Size Change.
			listener->OnBoardChanged(Board.GetPlayableSize(),
									 Board.GetCellSize(),
									 Board.GetBorderWidth());
			Board.UpdateBoardMaskSize();
			m_GamePieces.clear();
			m_GamePieces.reserve(Board.GetPlayableSize() * Board.GetPlayableSize());
		}
	}
}
}
