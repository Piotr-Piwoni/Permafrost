#pragma once
#include <memory>
#include <vector>

#include "Board.hpp"
#include "IEngineListener.hpp"
#include "pieces/Piece.hpp"

namespace PermafrostEngine::Core
{
class Engine
{
public:
	Engine();

	void AddListener(IEngineListener* listener);

	void SetupPieces();
	[[nodiscard]] const std::vector<std::unique_ptr<Piece>>& GetGamePieces();

private:
	void Notify();

public:
	Board Board{};

private:
	std::vector<IEngineListener*> m_Listeners{};
	std::vector<std::unique_ptr<Piece>> m_GamePieces{};
};
}
