#pragma once
#include <QPixmap>
#include <QString>

#include "utilities/logging/Logger.hpp"

namespace Permafrost::Utils
{
class TextureManager
{
public:
	TextureManager() { m_Textures.reserve(5); }


	QPixmap* LoadPixmap(const QString& filePath, const QString& name)
	{
		auto [map, isInserted] = m_Textures
				.try_emplace(name, std::make_unique<QPixmap>(filePath));

		constexpr auto kStartMsg = "Couldn't create a QPixmap!";
		if (!isInserted)
		{
			lError("{} There already exists a texture with that name!", kStartMsg);
			return nullptr;
		}
		if (map->second->isNull())
		{
			lError("{} The provided file either doesn't exist or is invalid!", kStartMsg);
			m_Textures.erase(name);
			return nullptr;
		}

		return map->second.get();
	}

	void UnloadPixmap(const QString& name)
	{
		if (m_Textures.erase(name) == 0)
			lWarn("Can't unload the texture as the provided name doesn't exist.");
	}

	[[nodiscard]] QPixmap* GetPixmap(const QString& name)
	{
		if (m_Textures.contains(name)) return m_Textures[name].get();
		lWarn("Unable to retrive the texture! Make sure the name is correct.");
		return nullptr;
	}

private:
	std::unordered_map<QString, std::unique_ptr<QPixmap>> m_Textures{};
};
}
