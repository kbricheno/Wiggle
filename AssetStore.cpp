#include "AssetStore.h"

//Define the static bool that allows only one instance of AssetStore to exist
bool AssetStore::m_isInstantiated = false;

//Construct the AssetStore instance, ensuring only one instance can be created
AssetStore::AssetStore() 
{
	assert(!m_isInstantiated);
	m_isInstantiated = true;
}

//Should the singular AssetStore instance be destroyed, another one can now be created
AssetStore::~AssetStore() 
{
	m_isInstantiated = false;
}

sf::Texture& const AssetStore::GetBitmap(std::string const& entityName) 
{
	return m_bitmaps.begin()->second;
}

void AssetStore::AddBitmap(std::string const& entityName) 
{
	//Check if entity name is already a key in the map
	//If not, create an entry at entityName with the loaded Texture from "Assets/" + entityName + ".png"
}

sf::SoundBuffer& const AssetStore::GetSoundBuffer(std::string const& soundName) 
{
	return m_soundBuffers.begin()->second;
}

void AssetStore::AddSoundBuffer(std::string const& soundName) 
{

}