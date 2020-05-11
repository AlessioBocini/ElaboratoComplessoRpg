#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../ConsoleApplication1/Game.h"
#include "../ConsoleApplication1/AssetManager.h"
#include "../ConsoleApplication1/Animator.h"

#include "testGiocatore.h"	//all functions to test

using namespace std;


	TEST(TestGiocatore, MovimentoDestraOk) {
		char pulsante = 'd';

		bool movimento = Movimento(pulsante);

		EXPECT_EQ(1, movimento);
	}



	TEST(TestGiocatore, MovimentoDestraFAIL) {
		char pulsante = 'g';

		bool movimento = Movimento(pulsante);
		if (movimento == true)
			FAIL();		//errore fatale.

		EXPECT_EQ(0, movimento);
	}

	TEST(TestGiocatore, Attacco) {
		//TODO
		EXPECT_EQ(1, 1);
	}
	TEST(TestGiocatore, InterazioneOK) {
		//TODO
		SUCCEED();
	}
	TEST(TestGiocatore, InterazioneFAIL) {
		SUCCEED();
	}


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
