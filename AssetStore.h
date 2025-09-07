#pragma once
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class AssetStore {
private:
	static bool m_isInstantiated;

	std::map<std::string, sf::Texture> m_bitmaps;
	std::map<std::string, sf::SoundBuffer> m_soundBuffers;

public:
	AssetStore();
	~AssetStore();

	sf::Texture const& GetBitmap(std::string const& entityName);
	void AddBitmap(std::string const& entityName);

	sf::SoundBuffer const& GetSoundBuffer(std::string const& soundName);
	void AddSoundBuffer(std::string const& soundName);
};