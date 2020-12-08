#pragma once
#include <memory>
#include <string>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include "SharedContext.h"
#include "Animator.h"


enum Sheet { Tile_Size = 32, Sheet_Width = 1366, Sheet_Height = 720 };
using TileId = unsigned int;
using AnimSet = Animator::Animation;
struct TileInfo {
	TileInfo(SharedContext* context, const std::string& texture = "", TileId id = 0) : context(context), id(0), texture(texture), anim(sprite), blocked(false), deadly(false) {

		if (texture == "") {
			this->id = id;
			return;
		}

		this->id = id;
		sf::IntRect tileBoundaries(this->id % (Sheet::Sheet_Width / Sheet::Tile_Size) * Sheet::Tile_Size, this->id / (Sheet::Sheet_Height / Sheet::Tile_Size) * Sheet::Tile_Size,
			Sheet::Tile_Size, Sheet::Tile_Size);

		sprite.setTextureRect(tileBoundaries);

	}
	~TileInfo() {
		animation.clear();
	}
	sf::Sprite sprite;
	Animator anim;
	std::vector<AnimSet> animation;
	TileId id;
	std::string name;
	sf::Vector2f friction;
	bool deadly;
	bool blocked;
	std::string texture;
	std::unique_ptr<SharedContext> context;
	
};

struct Tile {

	TileInfo* properties;
	bool teleport;
	std::string nextMap;
	sf::Vector2f teleportPos;
	Tile() :teleport(false), properties(nullptr) {}
	~Tile() {

	}
};
