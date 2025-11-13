#pragma once

class StateManager
{
private:
	static int score_;
	static int remaining_lives_;
	static int lives_max_;

public:
	static void KillEnemy();
	static void LostLife();

	static int GetScore();
	static int GetRemaingLives();
	static int GetLivesMax();

};

