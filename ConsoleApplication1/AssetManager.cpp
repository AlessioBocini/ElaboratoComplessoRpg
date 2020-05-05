#include <assert.h>
#include "AssetManager.h"

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager() {
	assert(sInstance == nullptr);
	sInstance = this;
}


sf::Texture& AssetManager::GetTexture(std::string const& filename) {
	auto& textMap = sInstance->m_textures;

	auto pairFound = textMap.find(filename);

	if (pairFound != textMap.end()) {
		return pairFound->second;
	}
	else {
		auto& texture = textMap[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}

sf::SoundBuffer& AssetManager::GetSoundBuffer(std::string const& filename) {
	auto& sBufferMap = sInstance->m_SoundBuffer;
	auto pairFound = sBufferMap.find(filename);
	if (pairFound != sBufferMap.end()) {
		return pairFound->second;
	}
	else {
		auto& sBuffer = sBufferMap[filename];
		sBuffer.loadFromFile(filename);
		return sBuffer;
	}
}

sf::Font& AssetManager::GetFont(std::string const& filename) {
	auto& fontMap = sInstance->m_fonts;
	auto pairFound = fontMap.find(filename);
	if (pairFound != fontMap.end()) {
		return pairFound->second;
	}
	else {
		auto& sFont = fontMap[filename];
		sFont.loadFromFile(filename);
		return sFont;
	}
}

sf::Shader* AssetManager::GetShader(std::string const& vsFile, std::string const& fsFile) {
	auto& shaderMap = sInstance->m_shaders;
	auto combinedKey = vsFile + ";" + fsFile;
	auto pairFound = shaderMap.find(combinedKey);
	if (pairFound != shaderMap.end()) {
		return pairFound->second.get();
	}
	else {
		auto& shader = (shaderMap[combinedKey] = std::unique_ptr<sf::Shader>(new sf::Shader()));
		shader->loadFromFile(vsFile, fsFile);
		return shader.get();
	}
}