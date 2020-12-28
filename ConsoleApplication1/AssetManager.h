#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
struct SharedContext;
class AssetManager {
public:
	AssetManager(SharedContext &context);
	~AssetManager() {}
	static sf::Texture& GetTexture(std::string const& filename);
	static sf::SoundBuffer& GetSoundBuffer(std::string const& filename);
	static sf::Font& GetFont(std::string const& filename);
	static sf::Shader* GetShader(std::string const& vsFile, std::string const& fsFile);

private:
	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, sf::SoundBuffer> m_SoundBuffer;
	std::map<std::string, sf::Font> m_fonts;
	std::map<std::string, std::unique_ptr<sf::Shader>>m_shaders;
	static AssetManager* sInstance;//contiene il puntatore all'unica istanza del manager
	SharedContext& context;
};
#endif