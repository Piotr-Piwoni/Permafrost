#pragma once
#include <cstdint>

namespace PermafrostEngine
{
enum class PieceType : std::uint8_t
{
	None = 0,
	Pawn,
	Rook,
	Knight,
	Bishop,
	Queen,
	King
};

struct Piece
{
	explicit Piece(unsigned int index = 0, PieceType type = PieceType::Pawn,
				   bool isWhite = true) :
		IsWhite{isWhite}, CellIndex{index}, Type{type} {}


	bool IsWhite{false};
	unsigned int CellIndex{0};
	PieceType Type{PieceType::None};
};
}
