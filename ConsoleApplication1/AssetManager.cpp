#include <assert.h>
#include "AssetManager.h"
#include "CustomException.h"

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

		try {
			texture.loadFromFile(filename);
		}
		catch (std::exception e) {
			throw TextureException("The texture has failed to load");
		}
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
		try {
			sBuffer.loadFromFile(filename);
		}
		catch (std::exception e) {
			throw SoundBufferException("The SoundBuffer has failed to load");
		}

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
		try {
			sFont.loadFromFile(filename);
		}
		catch (std::exception e) {
			throw FontException("Font not found");
		}

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