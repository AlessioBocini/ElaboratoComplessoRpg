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
	LoadTiles("assets/files/tiles.txt");
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
	LoadTiles("assets/files/tiles.txt");
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
	LoadTiles("assets/files/tiles.txt");
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
	LoadTiles("assets/files/tiles.txt");
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
TEST(TestGiocatore, OverflowRegenVitalita) {
	//suppongo sia il momento di rigenerare la vita e la vitalita è massima
	playervitalita = playerMaxVitalita;
	playerisalive = true;
	EXPECT_FALSE(RegenVitalita());
}

TEST(TestGiocatore, RegenDeadPlayer) {
	//suppongo sia il momento di rigenerare la vita e il player è morto
	playerisalive = false;
	EXPECT_FALSE(RegenVitalita());
}

TEST(TestGiocatore, RegenNormal) {
	//suppongo sia il momento di rigenerare la vita
	playervitalita = 20;
	playerisalive = true;
	bool regen = RegenVitalita();

	EXPECT_TRUE(regen);
}
TEST(TestInteraction, CollisioneConBlocked) {
	char pulsante = 'd';
	const std::string world = "mock1";
	bool movimento;


	LoadTiles("assets/files/tiles.txt");
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


	LoadTiles("assets/files/tiles.txt");
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


	LoadTiles("assets/files/tiles.txt");
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


	LoadTiles("assets/files/tiles.txt");
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


	LoadTiles("assets/files/tiles.txt");
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


	LoadTiles("assets/files/tiles.txt");
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

TEST(TestInseguimento, Versosinistra) {
	//char pulsante = 'f';
	const std::string world = "mock6";
	//bool attacco;
	
	Nemico ent = Nemico(sf::Vector2f(0, 0));
	std::vector<Nemico*> entities;
	LoadTiles("assets/files/tiles.txt");
	LoadMap(world, false, &ent);
	setSpawnPoint();
	SetEnemySpawnpoint(&ent);
	ent.SetFollowing(true);
	int dec = ent.nextStep();


	entities.clear();
	tileMap.clear();
	EXPECT_EQ(1, dec);
}
TEST(TestInseguimento, Versodestra) {
	//char pulsante = 'f';
	const std::string world = "mock7";
	//bool attacco;

	Nemico ent = Nemico(sf::Vector2f(0, 0));
	std::vector<Nemico*> entities;
	LoadTiles("assets/files/tiles.txt");
	LoadMap(world, false, &ent);
	setSpawnPoint();
	SetEnemySpawnpoint(&ent);
	ent.SetFollowing(true);
	int dec = ent.nextStep();


	entities.clear();
	tileMap.clear();
	EXPECT_EQ(0, dec);
}
TEST(TestInseguimento, VersoAlto) {
	//char pulsante = 'f';
	const std::string world = "mock9";
	//bool attacco;

	Nemico ent = Nemico(sf::Vector2f(0, 0));
	std::vector<Nemico*> entities;
	LoadTiles("assets/files/tiles.txt");
	LoadMap(world, false, &ent);
	setSpawnPoint();
	SetEnemySpawnpoint(&ent);
	ent.SetFollowing(true);
	int dec = ent.nextStep();


	entities.clear();
	tileMap.clear();
	EXPECT_EQ(3, dec);
}
TEST(TestInseguimento, VersoBasso) {
	//char pulsante = 'f';
	const std::string world = "mock8";
	//bool attacco;

	Nemico ent = Nemico(sf::Vector2f(0, 0));
	std::vector<Nemico*> entities;
	LoadTiles("assets/files/tiles.txt");
	LoadMap(world, false, &ent);
	setSpawnPoint();
	SetEnemySpawnpoint(&ent);
	ent.SetFollowing(true);
	int dec = ent.nextStep();


	entities.clear();
	tileMap.clear();
	EXPECT_EQ(2, dec);
}


TEST(TestDanno, dannoBase) {
	char pulsante = 'f';
	const std::string world = "mock5";
	bool attacco;

	Nemico ent = Nemico(sf::Vector2f(0, 0));
	std::vector<Nemico*> entities;
	LoadTiles("assets/files/tiles.txt");
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
	if (attacco) {
		Attacco(entities[0]);
	}

	int maxvit = entities[0]->GetMaxVitalita();
	int vitalita = entities[0]->GetVitalita();

	entities.clear();
	tileMap.clear();
	EXPECT_EQ(vitalita,(maxvit-playerforza));
}

TEST(TestDanno, dannoMaggiorato) {
	char pulsante = 'f';
	const std::string world = "mock5";
	bool attacco;
	inv.AddEquip(Equipaggiamento(10));

	Nemico ent = Nemico(sf::Vector2f(0, 0));
	std::vector<Nemico*> entities;
	LoadTiles("assets/files/tiles.txt");
	LoadMap(world, false, &ent);
	setSpawnPoint();
	SetEnemySpawnpoint(&ent);
	Movimento(1, 0);
	updateCollRect();
	inv.UseLastWeap();
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
	if (attacco) {
		Attacco(entities[0]);
	}

	int maxvit = entities[0]->GetMaxVitalita();
	int vitalita = entities[0]->GetVitalita();

	entities.clear();
	tileMap.clear();
	inv.getEquip().clear();
	EXPECT_FALSE(vitalita == (maxvit - playerforza));
}

TEST(TestGiocatore, MorteGiocatore) {
	char pulsante = 'f';
	const std::string world = "mock5";
	bool attacco;
	Nemico ent = Nemico(sf::Vector2f(0, 0));
	std::vector<Nemico*> entities;
	LoadTiles("assets/files/tiles.txt");
	LoadMap(world, false, &ent);
	setSpawnPoint();
	SetEnemySpawnpoint(&ent);
	Movimento(1, 0);
	updateCollRect();
	playervitalita = 100;
	playerisalive = true;
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
	if (attacco) {
		entities[0]->SetForza(playervitalita);
		entities[0]->Attacco();
	}

	

	entities.clear();
	tileMap.clear();
	EXPECT_FALSE(playerisalive);
}

TEST(TestGiocatore, dannoVitalitadaMostro) {
	char pulsante = 'f';
	const std::string world = "mock5";
	bool attacco;
	Nemico ent = Nemico(sf::Vector2f(0, 0));
	std::vector<Nemico*> entities;
	LoadTiles("assets/files/tiles.txt");
	LoadMap(world, false, &ent);
	setSpawnPoint();
	SetEnemySpawnpoint(&ent);
	Movimento(1, 0);
	updateCollRect();
	playervitalita = 100;
	playerisalive = true;
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
	if (attacco) {
		entities[0]->SetForza(10);
		entities[0]->Attacco();
	}



	entities.clear();
	tileMap.clear();
	EXPECT_TRUE(playerisalive);
}

TEST(TestInventario, SelezioneOggettiDiversi) {
	inv.AddEquip(Equipaggiamento(10));
	int idLast = inv.UseLastWeap(); //seleziono primo slot

	inv.AddEquip(Equipaggiamento(10));
	int idCurrent = inv.UseLastWeap(); //seleziono slot adiacente sulla destra

	inv.getEquip().clear();
	EXPECT_FALSE(idLast == idCurrent);
}
TEST(TestInventario, InserimentoOggettiOverflow) {
	Inventario inve = Inventario(2);
	inve.AddEquip(Equipaggiamento(10));
	inve.AddEquip(Equipaggiamento(10));
	inve.AddEquip(Equipaggiamento(10));
	inve.AddEquip(Equipaggiamento(10));
	int Nitems = inve.getEquip().size();

	inve.getEquip().clear();
	EXPECT_FALSE( Nitems == 4);
}

TEST(TestGiocatore, CompraArma) {
	Inventario inve = Inventario(2);
	char pulsante = 'r';
	const std::string world = "mock5";
	bool interazione;
	Nemico ent = Nemico(sf::Vector2f(0, 0));
	std::vector<Nemico*> entities;
	LoadTiles("assets/files/tiles.txt");
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
	int denaro = 10;
	int costoOggetto = 2;
	if (interazione && denaro>=costoOggetto) {
		denaro -= 2;
		inve.AddEquip(Equipaggiamento(10));
	}
	int size = inve.getEquip().size();

	inve.getEquip().clear();
	entities.clear();
	tileMap.clear();
	EXPECT_TRUE(1 == size); // interazione avvenuta con successo
}

TEST(TestGiocatore, NoCompraArma) {
	Inventario inve = Inventario(2);
	char pulsante = 'r';
	const std::string world = "mock5";
	bool interazione;
	Nemico ent = Nemico(sf::Vector2f(0, 0));
	std::vector<Nemico*> entities;
	LoadTiles("assets/files/tiles.txt");
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
	int denaro = 1;
	int costoOggetto = 2;
	if (interazione && denaro >= costoOggetto) {
		denaro -= 2;
		inve.AddEquip(Equipaggiamento(10));
	}
	int size = inve.getEquip().size();

	inve.getEquip().clear();
	entities.clear();
	tileMap.clear();
	EXPECT_FALSE(1 == size); // interazione avvenuta con successo
}

TEST(TestGiocatore, OttieneAchievement) {
	char pulsante = 'f';
	const std::string world = "mock5";
	bool attacco;
	int mobskilled = 2;
	int mobstogetAchievement = 3;

	Nemico ent = Nemico(sf::Vector2f(0, 0));
	std::vector<Nemico*> entities;
	LoadTiles("assets/files/tiles.txt");
	LoadMap(world, false, &ent);
	setSpawnPoint();
	SetEnemySpawnpoint(&ent);
	Movimento(1, 0);
	updateCollRect();
	ent.SetVitalita(1);
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
	bool isAlive = true;

	if (attacco) {
		//entities[0]->SetVitalita(1);
		isAlive = Attacco(entities[0]);
	}
	
	
	if (!isAlive) {
		mobskilled++;
	}
	

	entities.clear();
	tileMap.clear();
	EXPECT_EQ(mobskilled, mobstogetAchievement);
}

TEST(TestGiocatore, NoNOttieneAchievement) {
	char pulsante = 'f';
	const std::string world = "mock5";
	bool attacco;
	int mobskilled = 1;
	int mobstogetAchievement = 3;

	Nemico ent = Nemico(sf::Vector2f(0, 0));
	std::vector<Nemico*> entities;
	LoadTiles("assets/files/tiles.txt");
	LoadMap(world, false, &ent);
	setSpawnPoint();
	SetEnemySpawnpoint(&ent);
	Movimento(1, 0);
	updateCollRect();
	ent.SetVitalita(1);
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
	bool isAlive = true;
	if (attacco) {
		//entities[0]->SetVitalita(1);
		isAlive = Attacco(entities[0]);
	}


	if (!isAlive) {
		mobskilled++;
	}


	entities.clear();
	tileMap.clear();
	EXPECT_FALSE(mobskilled == mobstogetAchievement);
}
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
