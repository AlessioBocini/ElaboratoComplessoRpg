#pragma once
bool Movimento(char const& buttonPressed) {
	bool isMovement = true;
	switch (buttonPressed)
	{
	case 'w': {
		//todo movement
		break;
	}
	case 's': {
		//todo movement
		break;
	}
	case 'd': {
		//todo movement
		break;
	}
	case 'a': {
		//todo movement
		break;
	}
	default:
		isMovement = false;
		break;
	}

	return isMovement;
}
