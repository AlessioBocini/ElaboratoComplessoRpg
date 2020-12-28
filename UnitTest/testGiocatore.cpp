#include "pch.h"
#include "testGiocatore.h"





///
///  learn how to import gtest.lib and other
/// @see https://stackoverflow.com/questions/19934714/googletest-c-unit-testing-linking-error


TEST(TestGiocatore, MovimentoDestraOk) {
	char pulsante = 'd';
	bool movimento;
	switch (pulsante) {
	case 'd': {
		movimento = Movimento(1, 0);
		break;
	}
	default: {
		movimento = false;
	}
	}


	EXPECT_EQ(1, movimento);
}



TEST(TestGiocatore, MovimentoDestraFAIL) {
	char pulsante = 'g';
	bool movimento;
	switch (pulsante) {
	case 'd': {
		movimento = Movimento(1, 0);
	}
	default: {
		movimento = false;
	}
	}
	if (movimento == true)
		FAIL();		//errore fatale.

	EXPECT_EQ(0, movimento);
}

TEST(TestGiocatore, Attacco) {
	char pulsante = 'f';
	const std::string world = "mock5";
	bool attacco;

	Nemico ent =Nemico(sf::Vector2f(0,0));
	std::vector<Nemico*> entities;
	LoadTiles("../assets/files/tiles.txt");
	LoadMap(world, false, &ent);
	setSpawnPoint();
	SetEnemySpawnpoint(&ent);
	Movimento(1, 0);
	updateCollRect();
	switch (pulsante) {
		case 'f': {
			CollisionEntity(&ent, &entities);
			attacco = ResolveCollisionEntity(pulsante, &entities);
			break;
		}
		default: {
			attacco = false;
		}
	}

	entities.clear();
	tileMap.clear();
	EXPECT_EQ(1, attacco);//attacco è avvenuto, 1

}
TEST(TestGiocatore, InterazioneEntita) {
	char pulsante = 'r';
	const std::string world = "mock5";
	bool interazione;

	Nemico ent = Nemico(sf::Vector2f(0, 0));
	std::vector<Nemico*> entities;
	LoadTiles("../assets/files/tiles.txt");
	LoadMap(world, false, &ent);
	setSpawnPoint();
	SetEnemySpawnpoint(&ent);
	Movimento(1, 0);
	updateCollRect();
	switch (pulsante) {
	case 'r': {
		CollisionEntity(&ent, &entities);
		interazione = ResolveCollisionEntity(pulsante, &entities);
		break;
	}
	default: {
		interazione = false;
	}
	}

	entities.clear();
	tileMap.clear();
	EXPECT_EQ(1, interazione); // interazione avvenuta con successo

}
TEST(TestGiocatore, NOInterazioneEntita) {
	char pulsante = 'r';
	const std::string world = "mock6";
	bool interazione;

	Nemico ent = Nemico(sf::Vector2f(0, 0));
	std::vector<Nemico*> entities;
	LoadTiles("../assets/files/tiles.txt");
	LoadMap(world, false, &ent);
	setSpawnPoint();
	SetEnemySpawnpoint(&ent);
	Movimento(1, 0);
	updateCollRect();
	switch (pulsante) {
	case 'r': {
		CollisionEntity(&ent, &entities);
		interazione = ResolveCollisionEntity(pulsante, &entities);
		break;
	}
	default: {
		interazione = false;
	}
	}

	entities.clear();
	tileMap.clear();
	EXPECT_EQ(0, interazione); //interazione non può avvenire

}
TEST(TestGiocatore, NoAttacco) {
	char pulsante = 'f';
	const std::string world = "mock6";
	bool attacco;

	Nemico ent = Nemico(sf::Vector2f(0, 0));
	std::vector<Nemico*> entities;
	LoadTiles("../assets/files/tiles.txt");
	LoadMap(world, false, &ent);	
	setSpawnPoint();
	Movimento(1, 0);
	updateCollRect();
	SetEnemySpawnpoint(&ent);
	
	switch (pulsante) {
	case 'f': {
		CollisionEntity(&ent, &entities);
		attacco = ResolveCollisionEntity(pulsante, &entities);
		break;
	}
	default: {
		attacco = false;
	}
	}

	entities.clear();
	tileMap.clear();
	EXPECT_EQ(0, attacco);
}
TEST(TestInteraction, CollisioneConBlocked) {
	char pulsante = 'd';
	const std::string world = "mock1";
	bool movimento;


	LoadTiles("../assets/files/tiles.txt");
	LoadMap(world, false);
	setSpawnPoint();
	switch (pulsante) {
	case 'd': {
		movimento = Movimento(1, 0);
		break;
	}
	default: {
		movimento = false;
	}
	}
	int collision = CheckCollisions(world);

	tileMap.clear();
	EXPECT_EQ(1, collision);//Blocked è 1
}
TEST(TestInteraction, CollisioneConNonBlocked) {
	char pulsante = 'd';
	const std::string world = "mock2";
	bool movimento;


	LoadTiles("../assets/files/tiles.txt");
	LoadMap(world, false);
	setSpawnPoint();
	switch (pulsante) {
	case 'd': {
		movimento = Movimento(1, 0);
		break;
	}
	default: {
		movimento = false;
	}
	}
	int collision = CheckCollisions(world);

	tileMap.clear();
	EXPECT_EQ(0, collision); //Nulla è 0
}
TEST(TestInteraction, CollisioneConNoNTeleport) {
	char pulsante = 'd';
	const std::string world = "mock2";
	bool movimento;


	LoadTiles("../assets/files/tiles.txt");
	LoadMap(world, false);
	setSpawnPoint();
	switch (pulsante) {
	case 'd': {
		movimento = Movimento(1, 0);
		break;
	}
	default: {
		movimento = false;
	}
	}
	int collision = CheckCollisions(world);

	tileMap.clear();
	EXPECT_FALSE(2 == collision);
}
TEST(TestInteraction, CollisioneConTeleport) {
	char pulsante = 'd';
	const std::string world = "mock4";
	bool movimento;


	LoadTiles("../assets/files/tiles.txt");
	LoadMap(world, false);
	setSpawnPoint();
	switch (pulsante) {
	case 'd': {
		movimento = Movimento(1, 0);
		break;
	}
	default: {
		movimento = false;
	}
	}
	int collision = CheckCollisions(world);

	tileMap.clear();
	EXPECT_TRUE(2 == collision);
}
TEST(TestInteraction, CollisioneConDeadly) {
	char pulsante = 'd';
	const std::string world = "mock3";
	bool movimento;


	LoadTiles("../assets/files/tiles.txt");
	LoadMap(world, false);
	setSpawnPoint();
	switch (pulsante) {
	case 'd': {
		movimento = Movimento(1, 0);
		break;
	}
	default: {
		movimento = false;
	}
	}
	bool collision = CheckCollisionsDeadly(world);

	tileMap.clear();
	EXPECT_EQ(1, collision);
}
TEST(TestInteraction, CollisioneConNoNDeadly) {
	char pulsante = 'd';
	const std::string world = "mock2";
	bool movimento;


	LoadTiles("../assets/files/tiles.txt");
	LoadMap(world, false);
	setSpawnPoint();
	switch (pulsante) {
	case 'd': {
		movimento = Movimento(1, 0);
		break;
	}
	default: {
		movimento = false;
	}
	}
	bool collision = CheckCollisionsDeadly(world);

	tileMap.clear();
	EXPECT_EQ(0, collision);
}
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
